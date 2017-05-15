#ifndef CSIGNALPERMUTATION_H
#define CSIGNALPERMUTATION_H

#include "cbitblock.h"

class CSignalPermutation {
public:
    CSignalPermutation(unsigned int dim);
    CSignalPermutation(unsigned int dim,  unsigned int *P2L);
    ~CSignalPermutation();

    void SetP2L(const unsigned int *p2l);

    unsigned int P2LIndex(unsigned int index) const;
    unsigned int L2PIndex(unsigned int index) const;

    CBitBlock P2LBlock(const CBitBlock& physical) const;
    CBitBlock L2PBlock(const CBitBlock& logical) const;

    unsigned int Dim() const {return mDim;}

private:
    unsigned int *mP2L; //[controlInputDim]
    unsigned int *mL2P; //[controlInputDim]

    unsigned int mDim;
};

#endif // CSIGNALPERMUTATION_H
