#ifndef CFADDTESTVECTOR_H
#define CFADDTESTVECTOR_H

#include "../../../ctestvector.h"

class CFaddTestVector : public CTestVector {
public:
    CFaddTestVector();

    static const unsigned int CHAR_LEN = 6;
    static const unsigned int MANT_LEN = 10;
    static const unsigned int DIMENSION = (MANT_LEN + CHAR_LEN);

    static const unsigned int EC_RESULT_DEFINED = 0;
    static const unsigned int EC_POSITIVE_OVF   = 0xEE01;
    static const unsigned int EC_NEGATIVE_OVF   = 0xEEFF;
    static const unsigned int EC_UNREAL_ZERO    = 0xEE00;

    static CBitBlock MakeBitblockFromMantAndChar(unsigned int m, unsigned int c, bool &ok);
    static CBitBlock RightAnswerPart(const CBitBlock& A, const CBitBlock& B, unsigned int partIndex);

    static CBitBlock CharOf(const CBitBlock &x);
    static CBitBlock MantOf(const CBitBlock &x);
    static double DoubleOf(const CBitBlock &x);

protected:
    virtual void DoInitAutoTests();
    virtual CBitBlock DoRightOutputPart(unsigned int testIndex, unsigned int partIndex) const;
    virtual bool DoIsTestOk(unsigned int testIndex) const;

private:
    void CreateTest_PositiveOverflow(unsigned int testIndex);
    void CreateTest_NegativeOverflow(unsigned int testIndex);
    void CreateTest_UnrealZero(unsigned int testIndex);
    void CreateTest_DenormLeft(unsigned int testIndex);
    void CreateTest_DenormRight(unsigned int testIndex);
    void CreateTest_NoDenorm(unsigned int testIndex);
    void CreateTest_Right_PaGtPb(unsigned int testIndex);
    void CreateTest_Right_PbGtPa(unsigned int testIndex);
    void CreateTest_Right_Zero(unsigned int testIndex);

    CBitBlock RightErrorPart(unsigned int textIndex) const;
    CBitBlock RightResultPart(unsigned int textIndex) const;

    static CBitBlock ResultReturn(const CBitBlock& r, unsigned int partIndex);
    static CBitBlock ErrorReturn(unsigned int errorCode, unsigned int partIndex);
    static CBitBlock MakeResultFromInternals(unsigned int m, unsigned int c);

    static unsigned int InternalMantFrom(unsigned int m);
    static unsigned int InternalMantShr(unsigned int m, unsigned int count);
    static bool IsNormalizedInternalMant(unsigned int m);
    static bool IsPositiveInternalCharOverflow(unsigned int c);
    static bool IsNegativeInternalMant(unsigned int m);
    static bool IsNegativeInternalChar(unsigned int c);
};

#endif // CFADDTESTVECTOR_H
