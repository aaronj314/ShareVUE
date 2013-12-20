// string_obfuscation.h
// this is a generated file, do not edit.

// When an OBFUSCATE_* function is used, the array of chars will
// not be recognizable as an ascii string.  The deobfuscate function
// converts a string that was obfuscated using OBFUSCATE_* into 
// the original ascii.


// usage:
//   const char mystring[] = {OBFUSCATE_9('m','y','s','t','r','i','n','g',0)};
//   char buf[9];
//   printf("%s\n",deobfuscate(mystring,9));

#ifndef __STRING_OBFUSCATION__
#define __STRING_OBFUSCATION__

#include <utils/src/asplatform.h>

char* deobfuscate(const char* in, char* out, size_t size);

#define OBFUSCATE_1(char) (char+129)
#define OBFUSCATE_2(c0,c1) (c0+129),(c1+129)
#define OBFUSCATE_3(c0,c1,c2) (c0+129),(c1+129),(c2+129)
#define OBFUSCATE_4(c0,c1,c2,c3) (c0+129),(c1+129),(c2+129),(c3+129)
#define OBFUSCATE_5(c0,c1,c2,c3,c4) (c0+129),(c1+129),(c2+129),(c3+129),(c4+129)
#define OBFUSCATE_6(c0,c1,c2,c3,c4,c5) (c0+129),(c1+129),(c2+129),(c3+129),(c4+129),(c5+129)
#define OBFUSCATE_7(c0,c1,c2,c3,c4,c5,c6) (c0+129),(c1+129),(c2+129),(c3+129),(c4+129),(c5+129),(c6+129)
#define OBFUSCATE_8(c0,c1,c2,c3,c4,c5,c6,c7) (c0+129),(c1+129),(c2+129),(c3+129),(c4+129),(c5+129),(c6+129),(c7+129)
#define OBFUSCATE_9(c0,c1,c2,c3,c4,c5,c6,c7,c8) (c0+129),(c1+129),(c2+129),(c3+129),(c4+129),(c5+129),(c6+129),(c7+129),(c8+129)
#define OBFUSCATE_10(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9) (c0+129),(c1+129),(c2+129),(c3+129),(c4+129),(c5+129),(c6+129),(c7+129),(c8+129),(c9+129)
#define OBFUSCATE_11(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10) (c0+129),(c1+129),(c2+129),(c3+129),(c4+129),(c5+129),(c6+129),(c7+129),(c8+129),(c9+129),(c10+129)
#define OBFUSCATE_12(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11) (c0+129),(c1+129),(c2+129),(c3+129),(c4+129),(c5+129),(c6+129),(c7+129),(c8+129),(c9+129),(c10+129),(c11+129)
#define OBFUSCATE_13(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12) (c0+129),(c1+129),(c2+129),(c3+129),(c4+129),(c5+129),(c6+129),(c7+129),(c8+129),(c9+129),(c10+129),(c11+129),(c12+129)
#define OBFUSCATE_14(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13) (c0+129),(c1+129),(c2+129),(c3+129),(c4+129),(c5+129),(c6+129),(c7+129),(c8+129),(c9+129),(c10+129),(c11+129),(c12+129),(c13+129)
#define OBFUSCATE_15(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14) (c0+129),(c1+129),(c2+129),(c3+129),(c4+129),(c5+129),(c6+129),(c7+129),(c8+129),(c9+129),(c10+129),(c11+129),(c12+129),(c13+129),(c14+129)
#define OBFUSCATE_16(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15) (c0+129),(c1+129),(c2+129),(c3+129),(c4+129),(c5+129),(c6+129),(c7+129),(c8+129),(c9+129),(c10+129),(c11+129),(c12+129),(c13+129),(c14+129),(c15+129)

#endif // __STRING_OBFUSCATION__
