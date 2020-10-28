#
# Main
#
import atexit
import fnmatch
import platform
import sys
import time
import traceback
import uuid
import csv
import collections

try:
    import argparse
except:
    sys.exit("Please install ArgParse: sudo easy_install argparse")


parser = argparse.ArgumentParser(prog="hgst_installer",
                                 usage="%(prog)s [options]",
                                 description="HGST Installer main script",
                                 formatter_class=argparse.RawTextHelpFormatter)
parser.add_argument("-c", "--continue_from", type=str, nargs="+",
                    dest="continue_from", default="",
                    help="Skip all tests up to specified test.")
parser.add_argument("-d", "--debug_flags", type=str, nargs="+",
                    dest="debug_flags", default=DEFAULT_DEBUG,
                    help="Enable level debugging: %s" % DEBUG_FLAGS)
parser.add_argument("-f", "--factory_mode", action="store_true",
                    dest="factory_mode",
                    help="Enable factory mode installation.")
parser.add_argument("-i", "--ipmi_reset_from", choices=IPMI_RESET_CHOICES,
                    dest="ipmi_reset_from", default=DEFAULT_IPMI_RESET,
                    help="If set, reset IPMI from specified current setting.")
parser.add_argument("-l", "--log", type=str,
                    dest="logfile", default="",
                    help="Unix tee stdout to this file.")
parser.add_argument("-n", "--no_pdu_checks", action="store_true",
                    dest="no_pdu_checks", default=False,
                    help="Do not enable or test PDUs (old PDU racks).")
parser.add_argument("-o", "--operator_id", type=str,
                    dest="operator_id",
                    default="",
                    help="Name or ID of operator who  performed install " \
                    "(for logging only)")
parser.add_argument("-p", "--part_number", type=str,
                    dest="part_number", default="1ES0038",
                    help="""The Part Number of the system we are installing""")
parser.add_argument("-r", "--rack_serial", type=str, nargs="+",
                    dest="rack_serial", default="",
                    help="""Single Rack Serial (for 1geo) or Three Rack Serials (for 3 geo).
Rack Serial format is CCMMMMWWYYPPXXXX:
  CC   = Country Code : US, TH=Thailand
  MMMM = Manufacturer : CSJ0=Celestica San Jose 0
  WW   = Manufacturing Work Week : 00-52 (week starting on Sunday)
  YY   = Manufacturing Year : 00-99
  PP   = Product Code
  XXXX = ASCII of Hex Value 0001-FFFF""")
parser.add_argument("-s", "--skip_final_link_local", action="store_true",
                    dest="skip_final_link_local",
                    help="Skip setting to link local at the end.")
parser.add_argument("-t", "--template", type=str,
                    dest="tempfile",
                    default="",
                    help="Non-standard machine template file to be used for " \
                    "installation")
parser.add_argument("-u", "--scale_up_assist", action="store_true",
                    dest="scale_up_assist",
                    help="Enable the ScaleUp assisy for column groups 2/3.")
parser.add_argument("-v", "--version", action="version",
                    version="%(prog)s " + INSTALLER_VERSION)
parser.add_argument("-x", "--station_info", type=str,
                    dest="station_info", default="",
                    help="Description of test station for installation " \
                    "(for logging only)")
parser.add_argument("-fr", "--fs_reuse", action="store_true",
                    dest="fs_reuse",
                    help="Set this to reuse existing blockstore filesystems.")
parser.add_argument("-ids", "--deployment_ids", type=str, nargs="+",
                    dest="deployment_ids", default=None,
                    help="""List of deployment ids for installation.
Deployment ID in sequence (for each of the groups):
  scaler_deployment_id, column_group_deployment_ids ... """)
parser.add_argument("-ins", "--install_setup", type=str, choices=INSTALL_SETUP_CHOICES,
                    dest="install_setup", default=DEFAULT_INSTALL_SETUP,
help="""Type of rack setup used for installation
  default : Factory or Internal-dev Install
  partner : Partner Field Install """)
parser.add_argument("-A", "--phase_a_check", action="store_true",
                    dest="validate_mode",
                    help="Run Phase A validation.")
parser.add_argument("-B", "--phase_b", action="store_true",
                    dest="install_mode",
                    help="Run Phase B installation.")
parser.add_argument("-C", "--phase_c", action="store_true",
                    dest="test_mode",
                    help="Run Phase C test.")
parser.add_argument("-D", "--dryrun", action="store_true",
                    dest="dryrun",
                    help="Dryrun only, don't execute tests.")
parser.add_argument("-H", "--hardware", action="append",
                    dest="fw_list",choices=HW_COMPONENTS,
                    default=ALL_COMPONENTS,
                    help="Hardware component type to update firmware, All " \
                    "components are updated if this option is skipped.")
parser.add_argument("-I", "--interactive", action="store_true",
                    dest="interactive_mode",
                    help="Run interactive mode.")
parser.add_argument("-N", "--node", action="append",
                    dest="nodes",choices=NODE_NUMBERS,
                    default=ALL_NODES,
                    help="Node number to update firmware, All nodes are " \
                    "updated if this option is skipped.")
parser.add_argument("-F", "--field_installer", action="store_true",
                    dest="field_installer",
                    help="Set this if running Field installer")
parser.add_argument("-P", "--parallel", action="store_true", default = True,
                    dest="parallel_installer",
                    help="Enable parallelism in some phases of Installer")
parser.add_argument("-nP", "--nonParallel", action="store_true", default=False,
                    dest="nonParallel_installer",
                    help="Disable Parallelism in some phases of Installer")
parser.add_argument("-V", "--vm_installer", action="store_true",
                    dest="vm_installer",
                    help="Set this if running on a VM installer")

options = parser.parse_args()

# Init flags
DEBUG = "installer" in options.debug_flags
SYNOLOGY = ((options.factory_mode is True) and (options.field_installer is False))

# Install options
INSTALL_OPTIONS = dict()
if (options.field_installer):
    INSTALL_OPTIONS["install_mode"] = "field"
elif (options.factory_mode):
    INSTALL_OPTIONS["install_mode"] = "factory"
else:
    INSTALL_OPTIONS["install_mode"] = "internal-dev"
INSTALL_OPTIONS["tester_type"] = "virtual" if (options.vm_installer) else "physical"
INSTALL_OPTIONS["setup_type"] = options.install_setup.lower()

# Init logger
logger = Logger(options.factory_mode, DEBUG)
# Start logging
if options.logfile == "":
    rack_serial = "-".join(options.rack_serial)
    options.logfile = logger.GetLocalPhaseLogFile(rack_serial, options.part_number, "installer")
sys.stdout = Tee_Output(sys.stdout, options.logfile)

reload(log_module)
logger_wdc = log_module.getLogger('log_wdc', log_level= DEBUG, consolefile=options.logfile)
# Make sure we don't use Dev features in the factory
if (options.factory_mode):
    if (options.skip_final_link_local):
        logger_wdc.error(" Skipping Link Local is not supported in Factory Mode.")
        sys.exit(1)
    if (options.scale_up_assist):
        logger_wdc.error(" ScaleUp assist is not supported in Factory Mode.")
        sys.exit(1)
    if (options.dryrun):
        logger_wdc.error(" Dryrun is not supported in Factory Mode.")
        sys.exit(1)
    if (options.fs_reuse):
        logger_wdc.error(" File-system Reuse is not supported in Factory Mode.")
        sys.exit(1)

# Ensure deployment id(s) are provided in field mode
if ((options.field_installer is True) and (options.deployment_ids is None)):
    logger_wdc.error(" Deployment ID(s) not provided in Field Mode.")
    sys.exit(1)

#
# Make sure you are running as "root".
# NOTE: The "root" concept does not exist on windows.
#
plat = platform.system().split("_")[0]
if ((plat != "CYGWIN") and (plat != "Windows")):
    if (os.getuid() != 0):
        logger_wdc.error(" You must run as root or via sudo.")
        sys.exit(1)

# Check if we need to enter continue from mode
if (options.continue_from != ""):
    continue_from_testid = options.continue_from
    continue_from_mode = True
else:
    continue_from_testid = None
    continue_from_mode = False

# Validate input part number
if logger.ValidatePartNumber(options.part_number) is False:
    logger.__finalize__()
    logger_wdc.error(" Invalid Part Number %s." % (options.part_number))
    sys.exit(1)
else:
    logger.InitInstallation(options.part_number)