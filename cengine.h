#ifndef CENGINE_H
#define CENGINE_H

#include "cfunctionalunit.h"
#include "cengineerror.h"
#include "csignalpermutation.h"
#include "sharedptr.h"
#include "cengineerror.h"
#include "chint.h"


class CAlu;
class CMcu;
class CCpu;

class CTestVector;

class CEngineController;

class CEngineTimeline {
public:
    CEngineTimeline(CAlu *alu, CMcu *mcu, CCpu *cpu);
    ~CEngineTimeline();

    void ClearHistory();

    class CTick {
    public:
        CTick(CAlu *alu, CMcu *mcu, CCpu *cpu);
        CTick(const CTick& tick);
        ~CTick();

        CAlu *Alu() const {return mAlu;}
        CMcu *Mcu() const {return mMcu;}
        CCpu *Cpu() const {return mCpu;}

    private:
        CAlu *mAlu;
        CMcu *mMcu;
        CCpu *mCpu;
    };

    typedef std::list<CTick*> TTickHistory;

    CAlu *CurrentAlu() {return mCurrentTick->Alu();}
    CMcu *CurrentMcu() {return mCurrentTick->Mcu();}
    CCpu *CurrentCpu() {return mCurrentTick->Cpu();}

    bool IsPastTicks() const {return !mPastTicks.empty();}
    bool IsFutureTicks() const {return !mFutureTicks.empty();}

    void ShiftPresent();
    void StepToFuture();
    void StepToPast();

    SharedPtr<CRom> ProgramRom() const;

private:
    CTick *mCurrentTick;
    CTick  mInitialTick;

    TTickHistory mPastTicks;
    TTickHistory mFutureTicks;

    void ClearPastHistory();
    void ClearFutureHistory();
    void DeleteCurrentTick();
};


class CEngineModel {
public:
    enum TMode {DEBUG_MODE, AUTO_TEST_MODE, PROGRAMMING_MODE};
    enum TMcuType {MANUAL_MCU, MILI_MCU, MOORE_MCU};

    explicit CEngineModel(unsigned int  stateDim,
                          unsigned int  groupDim,
                          CAlu          *operationUnit,
                          CTestVector   *testVector,
                          CHint         *hint);
    ~CEngineModel();

    unsigned int L2PMcuInputIndex(unsigned int index) const {return mMcuInputSwap.L2PIndex(index);}
    unsigned int L2PMcuOutputIndex(unsigned int index) const {return mMcuOutputSwap.L2PIndex(index);}

    unsigned int P2LMcuInputIndex(unsigned int index) const {return mMcuInputSwap.P2LIndex(index);}
    unsigned int P2LMcuOutputIndex(unsigned int index) const {return mMcuOutputSwap.P2LIndex(index);}

    CBitBlock LogicalAluInput() const {return AluControlInput();}
    CBitBlock LogicalAluOutput() const;

    unsigned int DataOutsCount() const;
    CBitBlock DataBusValue() const;

    void AppendController(CEngineController* controller);

    const CAlu *CurrentAlu() const;
    CAlu *CurrentAlu();
    const CMcu *CurrentMcu() const;
    CMcu *CurrentMcu();
    const CCpu *CurrentCpu() const;
    CCpu *CurrentCpu();

    void CheckEngineError();
    bool IsError() const {return ErrorState().IsError();}
    const CErrorState& ErrorState() const {return mErrorState;}

    bool IsExecutionMode() const;
    bool IsProgrammingMode() const;
    bool IsProgramExecution() const {return mIsPrgramExecution;}

    bool IsExternalBreak() const {return mIsExternalBreak;}
    void SetExternalBreak(bool val) {mIsExternalBreak = val;}
    bool IsCpuInHaltState() const;

    bool IsFutureTicks();
    bool IsPastTicks();

    TMode CurrentMode() const {return mMode;}
    TMcuType CurrentMcuType() const {return mMcuType;}

    QString HintForLogicalYIndex(unsigned int index) const;
    QString HintForLogicalPIndex(unsigned int index) const;

    //>>>MVC interface
    void SetCurrentMode(TMode mode);
    void SetCurrentMcuType(TMcuType mcuType);

    void Execute();
    void SetExternalBreakRequest();
    void SetMcuRomAddress(unsigned int address);

    void GoPast();
    void GoFuture();
    //<<<MVC interface

    void UpdateHintsViews();
    void UpdateMemoryViews();
    void UpdateLogicViews();
    void UpdateModeViews();
    void UpdateMcuTypeViews();
    void CheckExternalBreak();

    unsigned int DataDim() const;
    unsigned int AluControlInputDim()  const;
    unsigned int AluControlOutputDim() const;
    unsigned int CpuControlInputDim()  const;
    unsigned int CpuControlOutputDim() const;
    unsigned int McuControlInputDim()  const;
    unsigned int McuControlOutputDim() const;

    unsigned int StateDim() const {return mStateDim;}
    unsigned int GroupDim() const {return mGroupDim;}
    unsigned int GroupCount() const {return (McuControlInputDim() + GroupDim() - 1) / GroupDim();}

    SharedPtr<CRom> ManualProgramRom() const;
    SharedPtr<CRom> MiliProgramRom() const;
    SharedPtr<CRom> MooreProgramRom() const;

private:
    typedef std::list<CEngineController*> TControllers;

    static const unsigned int RACE_TRESHOLD = 5;

    unsigned int mStateDim;
    unsigned int mGroupDim;

    unsigned int mDataDim;
    unsigned int mAluControlInputDim;
    unsigned int mAluControlOutputDim;

    CHint            *mHint;
    TControllers     mControllers;

    TMode            mMode;
    TMcuType         mMcuType;

    bool             mIsPrgramExecution;
    bool             mIsExternalBreak;

    CEngineTimeline  *mCurrentTimeline;

    CEngineTimeline  *mManualTimeline;
    CEngineTimeline  *mMiliTimeline;
    CEngineTimeline  *mMooreTimeline;

    CErrorState         mErrorState;

    CSignalPermutation  mMcuInputSwap;
    CSignalPermutation  mMcuOutputSwap;

    void UpdateUnitViews();

    void ShiftState();
    void SpreadData();

    void Tick();
    void SpreadSignals();

    void OffError();
    void RememberTick();

    bool SpreadControlAndGetIsRace();

    bool IsTickHistoryEnabled() const;
    bool IsStepByStepExecution() const;
    void ExecuteStep();
    void ExecuteProcess();

    CBitBlock AluControlInput() const;
    CBitBlock McuControlInput() const;
    CBitBlock CpuControlInput() const;

    void CreateTimelines(CAlu *alu, SharedPtr<CTestVector> testVector);

    void CreateManualTimeline(CAlu *alu, SharedPtr<CTestVector> testVector);
    void CreateMiliTimeline(CAlu *alu, SharedPtr<CTestVector> testVector);
    void CreateMooreTimeline(CAlu *alu, SharedPtr<CTestVector> testVector);

    void PrepareAutoTest();
    void PrepareDebug();
    bool IsSuccessfulInitDebug();
    void PrepareProgramming();

    void DisableRomEdit();
    void EnableRomEdit();

    void Reset();
    void SetInitialState();

    void HaltCpu();

    bool IsExternalBreakChecked();
 };


class CEngineController {
public:
    CEngineController() {mModel = 0;}

    const CEngineModel *Engine() const {return mModel;}
    void SetEngine(CEngineModel *model) {mModel = model;}
    void DisconnectEngine() {mModel = 0;}

    void SetMcuRomAddress(unsigned int address);

    void UpdateMemoryView() {if (Engine() != 0) DoUpdateMemoryView();}
    void UpdateLogicView() {if (Engine() != 0) DoUpdateLogicView();}
    void UpdateHintsView() {if (Engine() != 0) DoUpdateHintsView();}
    void UpdateMcuTypeView() {if (Engine() != 0) DoUpdateMcuTypeView();}
    void UpdateModeView() {if (Engine() != 0) DoUpdateModeView();}
    void CheckUserBreak() {if (Engine() != 0) DoCheckUserBreak();}

protected:
    virtual void DoUpdateMemoryView() = 0;
    virtual void DoUpdateLogicView() = 0;
    virtual void DoUpdateHintsView() = 0;
    virtual void DoUpdateMcuTypeView() = 0;
    virtual void DoUpdateModeView() = 0;
    virtual void DoCheckUserBreak() {/*DO NOTHING*/}

private:
    CEngineModel *mModel;
};

#endif // CENGINE_H
