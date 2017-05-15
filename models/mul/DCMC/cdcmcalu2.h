#ifndef CDCMCALU2_H
#define CDCMCALU2_H

#include "../../../calu.h"
#include "../../../celectronicunits.h"

class CDcmcAlu2 : public CAlu {
public:
    static const int Y_RG1_WR        = 0;
    static const int Y_RG1_SHR       = 1;
    static const int Y_RG2_WR        = 2;
    static const int Y_RG2_SHL       = 3;
    static const int Y_RG3_RST       = 4;
    static const int Y_RG3_WR        = 5;
    static const int Y_MS1_SEL       = 6;
    static const int Y_CT1_WR        = 7;
    static const int Y_CT1_INC       = 8;
    static const int Y_SM1_C_MS1_NOT = 9;
    static const int Y_BD1_OUT       = 10;
    static const int Y_BD2_OUT       = 11;

    static const int Y_COUNT         = 12;

    static const int P_CT1_3   = 0;
    static const int P_RG1_0   = 1;
    static const int P_RG1_7   = 2;
    static const int P_RG2_15  = 3;

    static const int P_COUNT   = 4;

    CDcmcAlu2();

    virtual const CRegister*    Register(unsigned int index) const;
    virtual const CCounter*     Counter(unsigned int index) const;
    virtual const CSummator*    Summator(unsigned int index) const;
    virtual const CMultiplexor* Multiplexor(unsigned int index) const;
    virtual const CXor*         Xor(unsigned int index) const;
    virtual       CBitBlock     BusMaker(unsigned int index) const;

protected:
    virtual CBitBlock DoDataOutput() const;
    virtual CBitBlock DoControlOutput() const;

    virtual unsigned int DoDataOutCount() const;

    virtual void DoShiftState();
    virtual void DoSpreadInput();

    virtual void DoReset();

    virtual CFunctionalUnit* DoClone() const {return new CDcmcAlu2(*this);}

private:
    CRegister    mRg1,mRg2,mRg3;
    CCounter     mCt1;
    CMultiplexor mMs1;
    CXor         mXor1;
    CSummator    mSm1;

    CBitBlock BusOut1() const;
    CBitBlock BusOut2() const;

    void ClearAllControls();

    unsigned int Ct1Controls() const;
    unsigned int Rg1Controls() const;
    unsigned int Rg2Controls() const;
    unsigned int Rg3Controls() const;

    void CheckErrors();

    void ResetCt1();
    void ResetRg1();
    void ResetRg2();
    void ResetRg3();
};

#endif // CDCMCALU2_H
