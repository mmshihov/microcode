#ifndef CFADDALU1_H
#define CFADDALU1_H

#include "../../../calu.h"
#include "../../../celectronicunits.h"


class CFaddAlu1 : public CAlu {
public:
    static const int Y_RG1_WR           = 0;
    static const int Y_RG1_SHR          = 1;
    static const int Y_RG2_RST          = 2;
    static const int Y_RG2_WR           = 3;
    static const int Y_RG2_SHR          = 4;
    static const int Y_RG2_SHL          = 5;
    static const int Y_CT1_RST          = 6;
    static const int Y_CT1_WR           = 7;
    static const int Y_CT1_INC          = 8;
    static const int Y_CT1_DEC          = 9;
    static const int Y_CT2_WR           = 10;
    static const int Y_CT2_INC          = 11;
    static const int Y_CT2_DEC          = 12;
    static const int Y_XR1_NOT_SM2_C    = 13;
    static const int Y_MS1_SEL0         = 14;
    static const int Y_MS1_SEL1         = 15;
    static const int Y_BD1_OUT          = 16;
    static const int Y_BD2_OUT          = 17;

    static const int Y_COUNT            = 18;

    static const int P_CT1_7              = 0;
    static const int P_CT1_6              = 1;
    static const int P_CT1_IS_GT_10       = 2;
    static const int P_CT1_IS_LT_MINUS_10 = 3;
    static const int P_CT1_IS_ZERO        = 4;
    static const int P_RG2_10             = 5;
    static const int P_RG2_9              = 6;
    static const int P_RG2_IS_ZERO        = 7;

    static const int P_COUNT              = 8;

    CFaddAlu1();

    virtual const CRegister*    Register(unsigned int index) const;
    virtual const CCounter*     Counter(unsigned int index) const;
    virtual const CSummator*    Summator(unsigned int index) const;
    virtual const CXor*         Xor(unsigned int index) const;
    virtual const CMultiplexor* Multiplexor(unsigned int index) const;
    virtual       CBitBlock     BusMaker(unsigned int index) const;
    virtual       bool          Logic(unsigned int index) const;

protected:
    virtual CBitBlock DoDataOutput() const;
    virtual CBitBlock DoControlOutput() const;

    virtual unsigned int DoDataOutCount() const;

    virtual void DoShiftState();
    virtual void DoSpreadInput();

    virtual void DoReset();

    virtual CFunctionalUnit* DoClone() const {return new CFaddAlu1(*this);}

private:
    CRegister    mRg1,mRg2;
    CCounter     mCt1,mCt2;
    CXor         mXor1;
    CSummator    mSm1,mSm2;
    CMultiplexor mMs1;

    CBitBlock BusOut1() const;
    CBitBlock BusOut2() const;

    void ClearAllControls();
    unsigned int Ct1Controls() const;
    unsigned int Ct2Controls() const;
    unsigned int Rg1Controls() const;
    unsigned int Rg2Controls() const;

    void CheckErrors();

    void ResetCt1();
    void ResetCt2();
    void ResetRg1();
    void ResetRg2();

    bool IsCt1Gt10() const;
    bool IsCt1LtMinus10() const;
    bool IsCt1Zero() const;
    bool IsRg2Zero() const;
};

#endif // CFADDALU1_H
