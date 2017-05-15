#ifndef CALU_H
#define CALU_H

#include "cfunctionalunit.h"

class CAlu : public CFunctionalUnit {
public:
    CAlu(unsigned int dataDim, unsigned int addressDim, unsigned int controlInputDim, unsigned int controlOutputDim);

    CAlu *Clone() const {return (CAlu*)DoClone();}
};

#endif // COPERATIONUNIT_H
