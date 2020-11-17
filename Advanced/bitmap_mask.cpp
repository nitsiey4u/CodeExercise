/**********************************************************
  Bit Mask - Map Data Structure of N size bits
  Useful for storing bit information for indexed records
***********************************************************/

#include <cstdio>
#include <cstring>
#include <cstdlib>

#define MAX_BITS 8
typedef unsigned char uchar_t;
typedef unsigned int  uint_t;

class BitMask{
private:
  uchar_t*  bitmask;   // Bitmask of unsigned character
  uint_t    bitsize;   // Size of Bitmask
  uint_t    octsize;   // Number of octects

public:
  BitMask(const int length) {
    bitsize = length;
    octsize = bitsize / MAX_BITS + ((bitsize % MAX_BITS) ? 1 : 0);
    bitmask = (uchar_t*)malloc(sizeof(uchar_t) * octsize);
    for(int index = 0; index < octsize; index++) {
      bitmask[index] = 0;
    }
  }

  void display() {
    int bitval[bitsize];
    int position = 0;
    for(int index = 0; index < octsize; index++) {
      uchar_t mask = bitmask[index];
      for(int count = 0; count < MAX_BITS; count++) {
        bitval[position] = (mask & 1) ? 1 : 0;
        position++;
        mask = mask >> 1;
      }
    }
    // Display bitmask
    printf("\nBitMask => ");
    printf("\nIndex: ");
    for(int index = (bitsize - 1); index >= 0; index--) {
      printf("\t%d", index);
    }
    printf("\nValue: ");
    for(int index = (bitsize - 1); index >= 0; index--) {
      printf("\t%d", bitval[index]);
    }
  }

  // Get octect number for specific position
  uint_t octet_index(const uint_t position) {
    return position / MAX_BITS;
  }

  // Set bit at specific position
  void set(const uint_t position) {
    uint_t   index = octet_index(position);
    uchar_t  valmask = (1 << (position % MAX_BITS));
    bitmask[index] = bitmask[index] | valmask;
  }

  // Reset bit at specific position
  void reset(const uint_t position) {
    uint_t   index = octet_index(position);
    uchar_t  valmask = ~(1 << (position % MAX_BITS));
    bitmask[index] = bitmask[index] & valmask;
  }

  // Toggle bit at specific position
  void toggle(const uint_t position) {
    uint_t   index = octet_index(position);
    uchar_t  valmask = (1 << (position % MAX_BITS));
    bitmask[index] = bitmask[index] ^ valmask;
  }

  // Get value at specific position
  int check(const uint_t position) {
    uint_t   index    = octet_index(position);
    uchar_t  valmask  = bitmask[index] >> (position % MAX_BITS);
    return (valmask & 1);
  }

  // Get index position for first set bit
  int first_set() {
    const uchar_t setmask = 1;
    // Iterate over octects in ascending order
    for(int index = 0; index < octsize; index++) {
      uchar_t valmask = bitmask[index];
      // Check for last bit set from Right to Left
      for(int position = 0; position < MAX_BITS; position++) {
        if(valmask & setmask) {
          return position + (index * MAX_BITS);
        }
        valmask = valmask >> 1;
      }
    }
    return -1;
  }

  // Get index position for last set bit
  int last_set() {
    const uchar_t setmask = 1 << (MAX_BITS - 1);
    // Iterate over octects in reverse order
    for(int index = (octsize - 1); index >= 0; index--) {
      uchar_t valmask = bitmask[index];
      // Check for last bit set from Left to Right
      for(int position = (MAX_BITS - 1); position >=0; position--) {
        if(valmask & setmask) {
          return position + (index * MAX_BITS);
        }
        valmask = valmask << 1;
      }
    }
    return -1;
  }

  // Count number of set bits
  int count_set() {
    int count = 0;
    // Iterate over octects in ascending order
    for(int index = 0; index < octsize; index++) {
      uchar_t valmask = bitmask[index];
      // Count bits set for specific octect
      while(valmask != 0) {
        count++;
        valmask = valmask & (valmask - 1);
      }
    }
    return count;
  }

  ~BitMask() {
    free(bitmask);
    bitmask = NULL;
  }

};


int main(int argc, char* argv[]) {
  BitMask bitmask(20);
  bitmask.set(5);
  bitmask.set(15);
  bitmask.display();
  bitmask.toggle(7);
  bitmask.toggle(10);
  bitmask.display();
  bitmask.reset(10);
  bitmask.display();
  printf("\nCount Set: %d", bitmask.count_set());
  printf("\nFirst Set: %d", bitmask.first_set());
  printf("\nLast Set: %d", bitmask.last_set());
  bitmask.toggle(5);
  bitmask.toggle(7);
  printf("\nFirst Set: %d", bitmask.first_set());
  printf("\nLast Set: %d", bitmask.last_set());
  return 0;
}
