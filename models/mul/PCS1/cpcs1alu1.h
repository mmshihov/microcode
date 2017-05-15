#ifndef CPCS1ALU1_H
#define CPCS1ALU1_H

#include "../../../calu.h"
#include "../../../celectronicunits.h"

class CPcs1Alu1 : public CAlu {
public:
    static const int XOR_T1_T2 = 1;
    static const int OR_RG3    = 2;
    static const int AND_SIGN  = 3;

    static const int Y_CT1_WR      = 0;
    static const int Y_CT1_INC     = 1;
    static const int Y_RG1_WR      = 2;
    static const int Y_RG1_SHR     = 3;
    static const int Y_RG2_WR      = 4;
    static const int Y_RG3_RST     = 5;
    static const int Y_RG3_WR      = 6;
    static const int Y_RG3_RG4_SHR = 7;
    static const int Y_T1_C        = 8;
    static const int Y_T2_C        = 9;
    static const int Y_BD1_OUT     = 10;
    static const int Y_BD2_OUT     = 11;

    static const int Y_COUNT       = 12;

    static const int P_CT1_3 = 0;
    static const int P_RG1_0 = 1;
    static const int P_COUNT = 2;

    CPcs1Alu1();

    virtual const CRegister*    Register(unsigned int index) const;
    virtual bool                Trigger(unsigned int index) const;
    virtual const CCounter*     Counter(unsigned int index) const;
    virtual const CSummator*    Summator(unsigned int index) const;
    virtual bool                Logic(unsigned int index) const;
    virtual       CBitBlock     BusMaker(unsigned int index) const;

protected:
    virtual CBitBlock DoDataOutput() const;
    virtual CBitBlock DoControlOutput() const;

    virtual unsigned int DoDataOutCount() const;

    virtual void DoShiftState();
    virtual void DoSpreadInput();

    virtual void DoReset();

    virtual CFunctionalUnit* DoClone() const {return new CPcs1Alu1(*this);}

private:
    CRegister mRg1,mRg2,mRg3,mRg4;
    CCounter  mCt1;
    CSummator mSm1;
    bool      mT1,mT2;

    CBitBlock BusOut1() const;
    CBitBlock BusOut2() const;

    void ClearAllControls();
    unsigned int Ct1Controls() const;
    unsigned int Rg1Controls() const;
    unsigned int Rg2Controls() const;
    unsigned int Rg3Controls() const;
    unsigned int Rg4Controls() const;

    void CheckErrors();

    bool IsXorT1T2() const;
    bool IsOnesInRg3Rg4Bits() const;
    bool IsSign() const;

    void ResetCt1();
    void ResetRg1();
    void ResetRg2();
    void ResetRg3();
    void ResetRg4();
    void ResetT1() {mT1 = false;}
    void ResetT2() {mT2 = false;}
};


#endif // CPCS1ALU1_H
