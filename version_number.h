#ifndef VERSION_NUMBER_H
#define VERSION_NUMBER_H

#define MICROCODE_VERSION_NUMBER     0  //fix version
#define MICROCODE_SUB_VERSION_NUMBER 33 //fix subversion

#define MICROCODE_NUMBER_TO_STR_2(val) # val
#define MICROCODE_NUMBER_TO_STR(val) MICROCODE_NUMBER_TO_STR_2(val)

#define MICROCODE_VERSION \
    MICROCODE_NUMBER_TO_STR(MICROCODE_VERSION_NUMBER) \
    "." \
    MICROCODE_NUMBER_TO_STR(MICROCODE_SUB_VERSION_NUMBER)

#endif // VERSION_NUMBER_H
