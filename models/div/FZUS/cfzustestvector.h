#ifndef CFZUSTESTVECTOR_H
#define CFZUSTESTVECTOR_H

#include "../../../ctestvector.h"

class CFzusTestVector : public CTestVector {
public:
    CFzusTestVector();

protected:
    virtual void DoInitAutoTests();
    virtual CBitBlock DoRightOutputPart(unsigned int testIndex, unsigned int partIndex) const;

private:
    void CreateTest_0Q1R(unsigned int testIndex);
    void CreateTest_1Q0R(unsigned int testIndex);
    void CreateTest_1Q1R(unsigned int testIndex);

    CBitBlock MakeResult(const CBitBlock& A, const CBitBlock& B) const;
};

#endif // CFZUSTESTVECTOR_H
