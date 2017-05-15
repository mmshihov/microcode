#ifndef CMCU_H
#define CMCU_H

#include "cfunctionalunit.h"
#include "celectronicunits.h"
#include "sharedptr.h"


class CEngineModel;


class CMcu : public CFunctionalUnit {
public:
    CMcu(unsigned int stateDim, unsigned int controlInputDim, unsigned int controlOutputDim);
    virtual ~CMcu();

    void SetRomAddress(unsigned int address);
    unsigned int RomAddress() const;

    static unsigned int MinDimensionFor(unsigned int xmax);
    static unsigned int PowerForDimension(unsigned int dim);

    CMcu *Clone() const {return (CMcu *)DoClone();}

    unsigned int RomAddressDim() const {return mRomAddressDim;}

    SharedPtr<CRom> ProgramRom() const {return DoProgramRom();}

protected:
    virtual SharedPtr<CRom> DoProgramRom() const = 0;
    virtual void DoReset();

    const CRegister *RomAddressRegister() const {return &mRomAddressRegister;}

    void SetRomAddressRegisterWriteInput(const CBitBlock &value);
    void RomAddressRegisterShift();
    void ResetRomAddressRegister();

private:
    unsigned int mRomAddressDim;
    CRegister    mRomAddressRegister;
};


class CManualMcu : public CMcu {
public:
    CManualMcu(unsigned int stateDim, unsigned int controlInputDim, unsigned int controlOutputDim);

    static const unsigned int ROM_ADDRESS_REGISTER_INDEX = 1;

protected:
    virtual CMcu* DoClone() const {return new CManualMcu(*this);}

    virtual const CRegister* Register(unsigned int i) const;

    virtual void DoSpreadInput() {/*DO NOTHING*/}
    virtual void DoShiftState() {/*DO NOTHING*/}
    virtual CBitBlock DoControlOutput() const;

    virtual SharedPtr<CRom> DoProgramRom() const {return mProgramRom;}

private:
    SharedPtr<CRom> mProgramRom;

    void CreateSharedRom();
};


class CAutomate : public CMcu {
public:
    CAutomate(unsigned int stateDim,
              unsigned int controlInputGroupDim,
              unsigned int controlInputDim,
              unsigned int controlOutputDim);

    unsigned int GroupDim() const {return mGroupDim;}
    unsigned int GroupsCount() const {return mGroupsCount;}

    unsigned int StatePower() const {return PowerForDimension(RomAddressDim());}

protected:
    void DoShiftState() {RomAddressRegisterShift();}

    CBitBlock ControlInputGroup(unsigned int index) const;

private:
    unsigned int mGroupDim;
    unsigned int mGroupsCount;
};


class CMiliAutomate : public CAutomate {
public:
    static const unsigned int GROUP_MUX_INDEX   = 1;
    static const unsigned int STATE_MUX_INDEX   = 2;
    static const unsigned int CONTROL_MUX_INDEX = 3;

    static const unsigned int STATE_REGISTER_INDEX  = 1;

    static const unsigned int PROGRAM_ROM_INDEX     = 1;

    CMiliAutomate(unsigned int stateDim,
                  unsigned int controlInputGroupDim,
                  unsigned int controlInputDim,
                  unsigned int controlOutputDim);

    virtual const CRegister* Register(unsigned int i) const;
    virtual const CMultiplexor* Multiplexor(unsigned int i) const;
    virtual const CRom* Rom(unsigned int i) const;

protected:
    virtual CBitBlock DoControlOutput() const;
    virtual void DoSpreadInput();
    virtual CMcu* DoClone() const {return new CMiliAutomate(*this);}
    virtual SharedPtr<CRom> DoProgramRom() const {return mProgramRom;}

private:

    SharedPtr<CRom> mProgramRom;

    CMultiplexor    mGroupMux;
    CMultiplexor    mStateMux;
    CMultiplexor    mControlOutputMux;

    void CreateSharedRom();
};

class CMooreAutomate : public CAutomate {
public:
    static const unsigned int GROUP_MUX_INDEX  = 1;
    static const unsigned int STATE_MUX_INDEX  = 2;

    static const unsigned int STATE_REGISTER_INDEX = 1;

    static const unsigned int PROGRAM_ROM_INDEX = 1;

    CMooreAutomate(unsigned int stateDim,
                   unsigned int controlInputGroupDim,
                   unsigned int controlInputDim,
                   unsigned int controlOutputDim);

    virtual const CRegister* Register(unsigned int i) const;
    virtual const CMultiplexor* Multiplexor(unsigned int i) const;
    virtual const CRom* Rom(unsigned int i) const;

protected:
    virtual CBitBlock DoControlOutput() const;
    virtual void DoSpreadInput();
    virtual CMcu* DoClone() const {return new CMooreAutomate(*this);}
    virtual SharedPtr<CRom> DoProgramRom() const {return mProgramRom;}

private:
    SharedPtr<CRom> mProgramRom;

    CMultiplexor    mGroupMux;
    CMultiplexor    mStateMux;

    void CreateSharedRom();
};

class CMcuController {
public:
    CMcuController() {}
    virtual ~CMcuController() {}

    void UpdateLogic(const CEngineModel* engine) {DoUpdateLogicView(engine);}
    void UpdateMemory(const CEngineModel* engine) {DoUpdateMemoryView(engine);}
    void UpdateHints(const CEngineModel* engine) {DoUpdateHintsView(engine);}

protected:
    virtual void DoUpdateLogicView(const CEngineModel* engine) = 0;
    virtual void DoUpdateMemoryView(const CEngineModel* engine) = 0;
    virtual void DoUpdateHintsView(const CEngineModel* engine) = 0;
};

#endif // CCONTROLUNIT_H
