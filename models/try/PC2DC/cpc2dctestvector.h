#ifndef CPC2DCTESTVECTOR_H
#define CPC2DCTESTVECTOR_H

#include "../../../ctestvector.h"

class CPc2DcTestVector : public CTestVector {
public:
    CPc2DcTestVector();

protected:
    virtual void DoInitAutoTests();
    virtual CBitBlock DoRightOutputPart(unsigned int testIndex, unsigned int partIndex) const;

private:
    void CreateTest_P(unsigned int testIndex);
    void CreateTest_N(unsigned int testIndex);

    CBitBlock MakeResult(const CBitBlock& A) const;
};

#endif // CPC2DCTESTVECTOR_H
