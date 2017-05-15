#include "ctestvector.h"

CTestVector::CTestItem::CTestItem(unsigned int inputPartCount,
                                  unsigned int outputPartCount,
                                  unsigned int dimension) {
    mInputPartCount = inputPartCount;
    mInputParts = new CBitBlock*[mInputPartCount];
    for (unsigned int i=0; i<mInputPartCount; ++i)
        mInputParts[i] = new CBitBlock(dimension);

    mOutputPartCount = outputPartCount;
    mOutputParts = new CBitBlock*[mOutputPartCount];
    for (unsigned int i=0; i<mOutputPartCount; ++i)
        mOutputParts[i] = new CBitBlock(dimension);
}

CTestVector::CTestItem::~CTestItem() {
    for (unsigned int i=0; i<mInputPartCount; ++i) {
        delete mInputParts[i];
        mInputParts[i] = 0;
    }
    delete[] mInputParts;

    for (unsigned int i=0; i<mOutputPartCount; ++i) {
        delete mOutputParts[i];
        mOutputParts[i] = 0;
    }
    delete[] mOutputParts;
}

CBitBlock CTestVector::CTestItem::InputPart(unsigned int partIndex) const {
    Q_ASSERT(partIndex < mInputPartCount);

    if (partIndex < mInputPartCount)
        return *(mInputParts[partIndex]);
    return CBitBlock();
}

CBitBlock CTestVector::CTestItem::OutputPart(unsigned int partIndex) const {
    Q_ASSERT(partIndex < mOutputPartCount);

    if (partIndex < mOutputPartCount)
        return *(mOutputParts[partIndex]);
    return CBitBlock();
}

void CTestVector::CTestItem::ProgramInputPart(unsigned int partIndex, const CBitBlock &part) {
    Q_ASSERT(partIndex < mInputPartCount);

    if (partIndex < mInputPartCount)
        (mInputParts[partIndex])->CopyFrom(part);
}

void CTestVector::CTestItem::SetOutputPart(unsigned int partIndex, const CBitBlock &part) {
    Q_ASSERT(partIndex < mOutputPartCount);

    if (partIndex < mOutputPartCount)
        (mOutputParts[partIndex])->CopyFrom(part);
}


//------------------------------------------------------------------------------------

CTestVector::CTestVector(
        unsigned int inputPartCount,
        unsigned int outputPartCount,
        unsigned int dimension,
        unsigned int autoTestCount,
        CDebugInputSource *inputSource)
{
    mInputPartCount     = inputPartCount;
    mOutputPartCount    = outputPartCount;
    mDimension          = dimension;
    mAutoTestCount      = autoTestCount;
    mDebugInputSource   = inputSource;
    mTests              = 0;

    CreateVector();
}

CTestVector::~CTestVector() {
    if (mTests == 0)
        return;

    for (unsigned int i=0; i<AutoTestCount(); ++i) {
        delete mTests[i];
        mTests[i] = 0;
    }
    delete[] mTests;

    delete mDebugInputSource;
}

bool CTestVector::IsSuccessfulInitDebugTest() {
    return mDebugInputSource->IsSuccessfulQueryAndInitDebugTest(this);
}

void CTestVector::CreateVector() {
    mTests = new CTestItem*[AutoTestCount()];
    for (unsigned int i=0; i<AutoTestCount(); ++i) {
        mTests[i] = new CTestItem(InputPartCount(), OutputPartCount(), Dimension());
    }
}

CBitBlock CTestVector::InputPart(unsigned int testIndex, unsigned int inputIndex) const {
    Q_ASSERT(testIndex < AutoTestCount());

    if (testIndex < AutoTestCount())
        return mTests[testIndex]->InputPart(inputIndex);
    return CBitBlock();
}

CBitBlock CTestVector::OutputPart(unsigned int testIndex, unsigned int partIndex) const {
    Q_ASSERT(testIndex < AutoTestCount());

    if (testIndex < AutoTestCount())
        return mTests[testIndex]->OutputPart(partIndex);
    return CBitBlock();
}

CBitBlock CTestVector::RightOutputPart(unsigned int testIndex, unsigned int partIndex) const {
    return DoRightOutputPart(testIndex, partIndex);
}

void CTestVector::ProgramInputPart(unsigned int testIndex, unsigned int inputIndex, const CBitBlock &input) {
    Q_ASSERT(testIndex < AutoTestCount());

    if (testIndex < AutoTestCount())
        mTests[testIndex]->ProgramInputPart(inputIndex, input);
}

void CTestVector::SetOutputPart(unsigned int testIndex, unsigned int outputIndex, const CBitBlock &output) {
    Q_ASSERT(testIndex < AutoTestCount());

    if (testIndex < AutoTestCount())
        mTests[testIndex]->SetOutputPart(outputIndex, output);
}

void CTestVector::MakeWrongOutputPartsForTest(unsigned int testIndex) {
    for (unsigned int partIndex=0; partIndex<OutputPartCount(); ++partIndex)
        SetOutputPart(testIndex, partIndex, ~RightOutputPart(testIndex, partIndex));
}

bool CTestVector::DoIsTestOk(unsigned int testIndex) const {
    for (unsigned int partIndex=0; partIndex<OutputPartCount(); ++partIndex) {
        if (OutputPart(testIndex, partIndex) != RightOutputPart(testIndex, partIndex))
            return false;
    }
    return true;
}
