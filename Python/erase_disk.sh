#!/bin/bash
# delete raid volumes and partitions
#
set -euxo pipefail

function check_disk_IOerrors() {
    #Python code
    def validate_drives_ioerr(self, server_obj):
        dev_err = []
        ret_val = self.NO_ERROR
        cmd_str = "/bin/sed -n \'/DRIVER_SENSE/,/end_request/p\' /var/log/kern.log > /tmp/kernel_errors.log"
        ret_str = server_obj.exec_ssh_command(cmd_str)
        if (ret_str is not None):
            cmd_str = "/bin/grep -o \"\[s[a-z0-9]\{2,\}\]\" /tmp/kernel_errors.log | /usr/bin/sort -u"
            ret_str = server_obj.exec_ssh_command(cmd_str)
            out_val = [] if (ret_str is None) else ret_str.splitlines()
            dev_err = ["/dev/%s" % item.strip('[]') for item in out_val]

        if (len(dev_err) > 0):
            logger_wdc.error("There are drive(s) with I/O errors and may need replacement")
            logger_wdc.error('{}'.format(dev_err))
            ret_val = "%s: Some drive(s) are bad and might need to be replaced." % (server_obj.name)
        return ret_val
}

function remove_raid() {
    # remove raid devices
    echo "Stopping Raid Volumes" >> $LOGFILE
    cat /proc/mdstat >> $LOGFILE
    for VOL in `cat /proc/mdstat | grep md | awk -F ':' '{print $1}'` ;  do
        VOL=/dev/$VOL
        echo "Raid drive $VOL" >> $LOGFILE
        if [[ -b $VOL ]] ; then
            for ((i=0; i < 3; i++)) ; do
                set +e
                /usr/share/mdadm/checkarray -x $VOL >> $LOGFILE
                mdadm --stop $VOL >> $LOGFILE
                re1=$?
                set -e
                echo "mdadm stop $VOL returned $re1" >> $LOGFILE
                if [[ $re1 -eq 0 ]]; then
                    break
                fi
            done
            if [[ $re1 -ne 0 ]]; then
                echo "mdadm stop $VOL returned non zero for 3 iterations. Exiting" >> $LOGFILE
                exit 1
            fi
            for ((i=0; i < 3; i++)) ; do
                set +e
                mdadm --remove $VOL >> $LOGFILE
                re1=$?
                set -e
                echo "mdadm remove $VOL returned $re1" >> $LOGFILE
                if [[ $re1 -eq 0 ]] ; then
                    break;
                fi
            done
            if [[ $re1 -ne 0 ]]; then
                echo "mdadm remove $VOL returned non zero for 3 iterations. Exiting" >> $LOGFILE
                exit 1
            fi
        fi
    done
}

collect_blk_info() {
    echo "Current Drives and Partitions"
    echo "lsblk" >> $LOGFILE
    lsblk >> $LOGFILE
    lsblk
    lsscsi -t >> $LOGFILE
    lsscsi -t
    echo "mdstat" >> $LOGFILE
    cat /proc/mdstat >> $LOGFILE
    cat /proc/mdstat
    echo "proc-partitions" >> $LOGFILE
    cat /proc/partitions >> $LOGFILE
    cat /proc/partitions
    echo "blkid" >> $LOGFILE
    blkid >> $LOGFILE
    blkid
    echo "parted -l" >> $LOGFILE
    parted -l >> $LOGFILE
    parted -l
}

wipe_sas_drives() {
    DR=$1
    sz=`blockdev --getsize64 $DR`
    l_blocksize=`blockdev --getss $DR`
    start_erase_size=$START_ERASE_LENGTH
    end_erase_size=$END_ERASE_LENGTH
    start_erase_count=$((start_erase_size/l_blocksize))
    end_erase_count=$((end_erase_size/l_blocksize))
    timeout=2400
    echo "Size of drive = $sz using bs $l_blocksize for drive $DR" >> $LOGFILE
    echo "Erasing drive $DR using sg_write_same -t $timeout -l 0 -n $start_erase_count $DR" >> $LOGFILE
    sg_write_same -t $timeout -l 0 -n $start_erase_count $DR >> $LOGFILE
    sk=$(((sz - $end_erase_size) / l_blocksize))
    echo "Erasing drive $DR using sg_write_same -t $timeout -l $sk -n $end_erase_count $DR" >> $LOGFILE
    sg_write_same -t $timeout -l $sk -n $end_erase_count $DR >> $LOGFILE
}

wipe_sata_drives() {
    DR=$1
    sz=`blockdev --getsize64 $DR`
    start_erase_size=$START_ERASE_LENGTH
    end_erase_size=$END_ERASE_LENGTH
    #end_blocksize=`blockdev --getpbsz $DR`
    start_blocksize=$((1024*1024))
    end_blocksize=4096
    start_erase_count=$((start_erase_size/start_blocksize))
    end_erase_count=$((end_erase_size/end_blocksize))
    # First dd, we dont do in background, as the subsequent dd is at the end
    # and hence we dont need the HEAD to go back and forth from start to end.
    # We measured the performance and found this to be better.
    echo "Size of drive = $sz for drive $DR" >> $LOGFILE
    echo "Erasing drive $DR using dd if=/dev/zero with blocksize $start_blocksize for cnt $start_erase_count" >> $LOGFILE
    dd if=/dev/zero of=$DR count=$start_erase_count bs=$start_blocksize oflag=direct >> $LOGFILE 2>&1
    sk=$(((sz - end_erase_size) / end_blocksize))
    echo "Erasing drive $DR using dd if=/dev/zero with blocksize $end_blocksize for cnt $end_erase_count seek=$sk" >> $LOGFILE
    dd if=/dev/zero of=$DR count=$end_erase_count bs=$end_blocksize oflag=direct seek=$sk >> $LOGFILE 2>&1 &
}

# Check inputs
if [ "$(whoami)" != "root" ]; then
    echo "Please run as sudo/root"
    exit 1
fi

# Script expects user to input the drive names as parameters
if [[ $# -lt 1 ]] || [[ $1 == "-h" ]] || [[ $1 == "--h" ]] ; then
    echo "Usage: $0 drivename(s) | installer"
    echo "     : $0 sda (Lab mode, erase only sda)"
    echo "     : $0 sda sdb sdc (Lab mode, erase only sda sdb sdc)"
    echo "     : $0 installer (FI mode, Erase raid/boot drives only"
    exit 1
fi

LOGFILE=erase_$(date "+%Y.%m.%d-%H.%M.%S").log
VERSION=2.3
START_ERASE_LENGTH=$((150*1024*1024*1024))
END_ERASE_LENGTH=$((2*1024*1024*1024))

lsscsi > /dev/null 2>&1 || { echo "This program requires lsscsi, please install" ; exit 1; }

echo "$0($VERSION), parameters $@" >> $LOGFILE
echo "Start time $(date "+%Y.%m.%d-%H.%M.%S") " >> $LOGFILE
echo

echo "Collecting information before erase" >> $LOGFILE
collect_blk_info

user_input=$1
if [[ $user_input != "all" ]] && [[ $user_input != "installer" ]] ; then
    disklist=$@
else
    disklist=`lsblk -d | grep sd | awk '{print $1}'`
    START_ERASE_LENGTH=$((10*1024*1024))
    END_ERASE_LENGTH=$((1*1024*1024))
fi
echo "disklist = $disklist" >> $LOGFILE

echo "Erase Started" >> $LOGFILE
# erase all drives or the ones passed
for name in $disklist ; do
    if [[ $name == /dev/* ]]; then
        DISK=$name
    else
        DISK="/dev/$name"
    fi
    if [ -b $DISK ]; then
        # If user requires to erase only raid drives, then skip non raid/boot drives
        if [[ "$user_input" == "installer" ]] ; then
            echo "Checking whether drive $DISK has raid partitions" >> $LOGFILE
            set +e
            parted -s $DISK print | grep -e raid -e boot >> $LOGFILE
            non_raid=$?
            set -e
            if [[ $non_raid -ne 0 ]] ; then
                echo "Skipping $DISK as it is a non raid/os drive and user has specified only $user_input drives" >> $LOGFILE
                continue;
            fi
        fi
        # remove raid, clean and delete each partition
        serial_num=`lsscsi -i | grep $DISK | awk -F ' ' '{print $7}'`
        echo "Erasing drive $DISK with serial number: $serial_num" >> $LOGFILE
        for PART in $(parted -s $DISK print|awk '/^ / {print $1}')
        do
            # Need to remove raid, before we remove partitions.
            # Need to do before each partition, as wipefs and parted rm
            # could rescan and cause raid to be reconstructed again.
            remove_raid
            echo "Disk part = $DISK$PART" >> $LOGFILE
            file -sL $DISK$PART >> $LOGFILE
            set +e
            for ((i=0; i < 3; i++)) ; do
                #There is a timing issue seen with wipefs. Sometimes first time fails with ENOENT.
                #But second run succeeds.
                wipefs -a  $DISK$PART >> $LOGFILE
                ret=$?
                echo "Removing file system returned $ret" >> $LOGFILE
                if [[ $ret -eq 0 ]] ; then
                    break;
                fi
            done
            set -e
            parted -s $DISK rm $PART >> $LOGFILE
            ret=$?
            echo "Removing partition returned $ret" >> $LOGFILE
        done
        drive_transport=`lsscsi -t | grep $DISK | awk '{print $3}'`
        echo "Drive $DISK has $drive_transport" >> $LOGFILE
        if [[ "$drive_transport" == *sata* ]] ; then
            wipe_sata_drives $DISK
        else
            wipe_sas_drives $DISK
        fi
        echo "End Drive = $DISK" >> $LOGFILE
    fi
done

#Wait for all the drives to finish
wait

echo "Collecting information after erase" >> $LOGFILE
collect_blk_info
echo "End time $(date "+%Y.%m.%d-%H.%M.%S") " >> $LOGFILE
echo "Erase Completed for $@" >> $LOGFILE
exit 0
