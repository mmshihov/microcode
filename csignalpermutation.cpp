#include "csignalpermutation.h"
#include <QtGlobal>

CSignalPermutation::CSignalPermutation(unsigned int dim) {
    mDim  = dim;

    mL2P = new unsigned int [mDim];
    mP2L = new unsigned int [mDim];

    for (unsigned int i=0; i<mDim; ++i)
        mL2P[i] = mP2L[i] = i;
}

CSignalPermutation::CSignalPermutation(unsigned int dim,  unsigned int *P2L) {
    mDim  = dim;

    mL2P = new unsigned int [mDim];
    mP2L = new unsigned int [mDim];

    SetP2L(P2L);
}

CSignalPermutation::~CSignalPermutation() {
    delete[] mL2P; mL2P = 0;
    delete[] mP2L; mP2L = 0;
}

void CSignalPermutation::SetP2L(const unsigned int *p2l) {
    for (unsigned int i=0; i<Dim(); ++i)  {
        Q_ASSERT(p2l[i] < Dim());

        mP2L[i] = p2l[i];
        mL2P[p2l[i]] = i;
    }
}

unsigned int CSignalPermutation::P2LIndex(unsigned int index) const {
    Q_ASSERT(index < Dim());

    return mP2L[index];
}

unsigned int CSignalPermutation::L2PIndex(unsigned int index) const {
    Q_ASSERT(index < Dim());

    return mL2P[index];
}

CBitBlock CSignalPermutation::P2LBlock(const CBitBlock &physical) const {
    CBitBlock logical(Dim());
    for (unsigned int i=0; i<Dim(); ++i)
        logical.SetBoolAt(i, physical.IsSetAt(L2PIndex(i)));
    return logical;
}

CBitBlock CSignalPermutation::L2PBlock(const CBitBlock &logical) const {
    CBitBlock physical(Dim());
    for (unsigned int i=0; i<Dim(); ++i)
        physical.SetBoolAt(i, logical.IsSetAt(P2LIndex(i)));
    return physical;
}
