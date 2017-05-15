#ifndef CPCS1TESTVECTOR_H
#define CPCS1TESTVECTOR_H

#include "../../../ctestvector.h"

class CPcs1TestVector : public CTestVector {
public:
    CPcs1TestVector();

protected:
    virtual void DoInitAutoTests();
    virtual CBitBlock DoRightOutputPart(unsigned int testIndex, unsigned int partIndex) const;

private:
    void CreateTest_NZNA_NZNB(unsigned int testIndex);
    void CreateTest_NZNA_ZB(unsigned int testIndex);
    void CreateTest_NZNA_NZPB(unsigned int testIndex);

    CBitBlock MakeResult(const CBitBlock& A, const CBitBlock& B) const;
};

#endif // CPCS1TESTVECTOR_H
