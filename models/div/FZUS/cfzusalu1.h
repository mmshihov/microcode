#ifndef CFZUSALU1_H
#define CFZUSALU1_H

#include "../../../calu.h"
#include "../../../celectronicunits.h"


class CFzusAlu1 : public CAlu {
public:
    static const int Y_CT1_WR        = 0;
    static const int Y_CT1_INC       = 1;
    static const int Y_RG1_RST       = 2;
    static const int Y_RG1_WR        = 3;
    static const int Y_RG1_RG2_SHR   = 4;
    static const int Y_RG2_RST       = 5;
    static const int Y_RG2_WR        = 6;
    static const int Y_SM1_C_XR1_NOT = 7;
    static const int Y_RG3_RST       = 8;
    static const int Y_RG3_WR        = 9;
    static const int Y_RG3_SHL       = 10;
    static const int Y_RG4_SHL       = 11;
    static const int Y_BD1_OUT       = 12;
    static const int Y_BD2_OUT       = 13;
    static const int Y_BD3_OUT       = 14;

    static const int Y_COUNT         = 15;

    static const int P_CT1_3  = 0;
    static const int P_RG3_16 = 1;

    static const int P_COUNT  = 2;

    CFzusAlu1();

    virtual const CRegister*    Register(unsigned int index) const;
    virtual const CCounter*     Counter(unsigned int index) const;
    virtual const CSummator*    Summator(unsigned int index) const;
    virtual const CXor*         Xor(unsigned int index) const;
    virtual       CBitBlock     BusMaker(unsigned int index) const;

protected:
    virtual CBitBlock DoDataOutput() const;
    virtual CBitBlock DoControlOutput() const;

    virtual unsigned int DoDataOutCount() const;

    virtual void DoShiftState();
    virtual void DoSpreadInput();

    virtual void DoReset();

    virtual CFunctionalUnit* DoClone() const {return new CFzusAlu1(*this);}

private:
    CRegister    mRg1,mRg2,mRg3,mRg4;
    CCounter     mCt1;
    CXor         mXor1;
    CSummator    mSm1;

    CBitBlock BusOut1() const;
    CBitBlock BusOut2() const;
    CBitBlock BusOut3() const;

    void ClearAllControls();
    unsigned int Ct1Controls() const;
    unsigned int Rg1Controls() const;
    unsigned int Rg2Controls() const;
    unsigned int Rg3Controls() const;
    unsigned int Rg4Controls() const;

    void CheckErrors();

    void ResetCt1();
    void ResetRg1();
    void ResetRg2();
    void ResetRg3();
    void ResetRg4();
};


#endif // CFZUSALU1_H
