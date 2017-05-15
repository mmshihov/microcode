#ifndef CDCMCTESTVECTOR_H
#define CDCMCTESTVECTOR_H

#include "../../../ctestvector.h"

class CDcmcTestVector : public CTestVector {
public:
    CDcmcTestVector();

protected:
    virtual void DoInitAutoTests();
    virtual CBitBlock DoRightOutputPart(unsigned int testIndex, unsigned int partIndex) const;

private:
    void CreateTest_PN(unsigned int testIndex);
    void CreateTest_NP(unsigned int testIndex);
    void CreateTest_PP(unsigned int testIndex);
    void CreateTest_NN(unsigned int testIndex);

    CBitBlock MakeResult(const CBitBlock& A, const CBitBlock& B) const;
};

#endif // CDCMCTESTVECTOR_H
