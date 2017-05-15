#include "cengine.h"

#include "calu.h"
#include "cmcu.h"
#include "ccpu.h"

#include "cengineerror.h"


CEngineTimeline::CTick::CTick(CAlu *alu, CMcu *mcu, CCpu *cpu) {
    mAlu = alu; mMcu = mcu; mCpu = cpu;
}

CEngineTimeline::CTick::CTick(const CEngineTimeline::CTick &tick) {
    mAlu = tick.Alu()->Clone();
    mMcu = tick.Mcu()->Clone();
    mCpu = tick.Cpu()->Clone();
}

CEngineTimeline::CTick::~CTick() {
    delete mAlu; delete mMcu; delete mCpu;
}


CEngineTimeline::CEngineTimeline(CAlu *alu, CMcu *mcu, CCpu *cpu)
    : mInitialTick(alu, mcu, cpu)
{
    mCurrentTick = new CTick(mInitialTick);
}

CEngineTimeline::~CEngineTimeline() {
    ClearHistory();
    DeleteCurrentTick();
}

void CEngineTimeline::ShiftPresent() {
    mPastTicks.push_back(mCurrentTick);
    mCurrentTick = new CTick(*mCurrentTick);

    ClearFutureHistory();
}

void CEngineTimeline::StepToFuture() {
    Q_ASSERT(IsFutureTicks());

    mPastTicks.push_back(mCurrentTick);
    mCurrentTick = mFutureTicks.back();
    mFutureTicks.pop_back();
}

void CEngineTimeline::StepToPast() {
    Q_ASSERT(IsPastTicks());

    mFutureTicks.push_back(mCurrentTick);
    mCurrentTick = mPastTicks.back();
    mPastTicks.pop_back();
}

SharedPtr<CRom> CEngineTimeline::ProgramRom() const {
    return mInitialTick.Mcu()->ProgramRom();
}

void CEngineTimeline::ClearHistory() {
    ClearFutureHistory();
    ClearPastHistory();
}

void CEngineTimeline::ClearPastHistory() {
    while (!mPastTicks.empty()) {
        CTick *tick = mPastTicks.back();
        delete tick;

        mPastTicks.pop_back();
    }
}

void CEngineTimeline::ClearFutureHistory() {
    while (!mFutureTicks.empty()) {
        CTick *tick = mFutureTicks.back();
        delete tick;

        mFutureTicks.pop_back();
    }
}

void CEngineTimeline::DeleteCurrentTick() {
    delete mCurrentTick;
}


CEngineModel::CEngineModel(unsigned int  stateDim,
                           unsigned int  groupDim,
                           CAlu         *alu,
                           CTestVector  *testVector,
                           CHint        *hint)
    : mHint(hint)
    , mCurrentTimeline(0)
    , mMcuInputSwap(alu->ControlOutputDim() + CCpu::OUT_COUNT)
    , mMcuOutputSwap(alu->ControlInputDim() + CCpu::IN_COUNT)
{
    mStateDim = stateDim;
    mGroupDim = groupDim;

    mDataDim             = alu->DataDim();
    mAluControlInputDim  = alu->ControlInputDim();
    mAluControlOutputDim = alu->ControlOutputDim();

    mIsPrgramExecution = false;

    SharedPtr<CTestVector> sharedTests(testVector);

    CreateTimelines(alu, sharedTests);

    SetInitialState();
}

CEngineModel::~CEngineModel() {
    delete mManualTimeline;
    delete mMiliTimeline;
    delete mMooreTimeline;

    delete mHint;
}

CBitBlock CEngineModel::LogicalAluOutput() const {
    return CurrentAlu()->ControlOutput(); //internals is logical
}

unsigned int CEngineModel::DataOutsCount() const {
    return
              CurrentAlu()->DataOutCount()
            + CurrentMcu()->DataOutCount()
            + CurrentCpu()->DataOutCount()
            ;
}

CBitBlock CEngineModel::DataBusValue() const {
    unsigned int outsCount = DataOutsCount();

    if (outsCount == 1) {
        if (CurrentAlu()->IsDataOut())
            return CurrentAlu()->DataOutput();

        if (CurrentMcu()->IsDataOut())
            return CurrentMcu()->DataOutput();

        if (CurrentCpu()->IsDataOut())
            return CurrentCpu()->DataOutput();
    } else if (outsCount > 1) {
        CBitBlock busValue(DataDim(), 0);

        if (CurrentAlu()->IsDataOut())
            busValue |= CurrentAlu()->DataOutput();

        if (CurrentMcu()->IsDataOut())
            busValue |= CurrentMcu()->DataOutput();

        if (CurrentCpu()->IsDataOut())
            busValue |= CurrentCpu()->DataOutput();

        return busValue;
    }

    return CBitBlock();
}

void CEngineModel::AppendController(CEngineController *controller) {
    controller->SetEngine(this);
    mControllers.push_back(controller);
}

unsigned int CEngineModel::DataDim() const {return mDataDim;}

unsigned int CEngineModel::AluControlInputDim() const {return mAluControlInputDim;}

unsigned int CEngineModel::AluControlOutputDim() const {return mAluControlOutputDim;}

unsigned int CEngineModel::CpuControlInputDim() const {return CCpu::IN_COUNT;}

unsigned int CEngineModel::CpuControlOutputDim() const {return CCpu::OUT_COUNT;}

unsigned int CEngineModel::McuControlInputDim() const {
    return CpuControlOutputDim() + AluControlOutputDim();
}

unsigned int CEngineModel::McuControlOutputDim() const {
    return CpuControlInputDim() + AluControlInputDim();
}

SharedPtr<CRom> CEngineModel::ManualProgramRom() const { return mManualTimeline->ProgramRom(); }

SharedPtr<CRom> CEngineModel::MiliProgramRom() const { return mMiliTimeline->ProgramRom(); }

SharedPtr<CRom> CEngineModel::MooreProgramRom() const { return mMooreTimeline->ProgramRom(); }

const CAlu *CEngineModel::CurrentAlu() const {
    Q_ASSERT(mCurrentTimeline != 0);

    return mCurrentTimeline->CurrentAlu();
}

CAlu *CEngineModel::CurrentAlu() {
    Q_ASSERT(mCurrentTimeline != 0);

    return mCurrentTimeline->CurrentAlu();
}

const CMcu *CEngineModel::CurrentMcu() const {
    Q_ASSERT(mCurrentTimeline != 0);

    return mCurrentTimeline->CurrentMcu();
}

CMcu *CEngineModel::CurrentMcu() {
    Q_ASSERT(mCurrentTimeline != 0);

    return mCurrentTimeline->CurrentMcu();
}

const CCpu *CEngineModel::CurrentCpu() const {
    Q_ASSERT(mCurrentTimeline != 0);

    return mCurrentTimeline->CurrentCpu();
}

CCpu *CEngineModel::CurrentCpu() {
    Q_ASSERT(mCurrentTimeline != 0);

    return mCurrentTimeline->CurrentCpu();
}

void CEngineModel::CheckEngineError() {
    if (mErrorState.IsError())
        return;

    if (CurrentAlu()->IsError()) {
        mErrorState = CurrentAlu()->ErrorState();
        return;
    }

    if (CurrentMcu()->IsError()) {
        mErrorState = CurrentMcu()->ErrorState();
        return;
    }

    if (CurrentCpu()->IsError())
        mErrorState = CurrentCpu()->ErrorState();
}

bool CEngineModel::IsFutureTicks() {
    return IsTickHistoryEnabled() && mCurrentTimeline->IsFutureTicks();
}

bool CEngineModel::IsPastTicks() {
    return IsTickHistoryEnabled() && mCurrentTimeline->IsPastTicks();
}

QString CEngineModel::HintForLogicalYIndex(unsigned int index) const {
    return mHint->Y(L2PMcuOutputIndex(index));
}

QString CEngineModel::HintForLogicalPIndex(unsigned int index) const {
    return mHint->P(L2PMcuInputIndex(index));
}

void CEngineModel::SetCurrentMode(CEngineModel::TMode mode) {
    mMode = mode;

    switch (mode) {
    case AUTO_TEST_MODE:    PrepareAutoTest();    break;
    case DEBUG_MODE:        PrepareDebug();       break;
    case PROGRAMMING_MODE:
    default:
        mMode = PROGRAMMING_MODE;
        PrepareProgramming();
    }

    UpdateModeViews();

    SpreadSignals();
    UpdateUnitViews();
}

void CEngineModel::SetCurrentMcuType(CEngineModel::TMcuType mcuType) {
    mMcuType = mcuType;

    switch (mcuType) {
    case MANUAL_MCU: mCurrentTimeline = mManualTimeline; break;
    case MILI_MCU:   mCurrentTimeline = mMiliTimeline; break;
    case MOORE_MCU:  mCurrentTimeline = mMooreTimeline; break;
    default:
        Q_ASSERT(false);

        mMcuType         = MANUAL_MCU;
        mCurrentTimeline = mManualTimeline;
        return;
    }

    UpdateMcuTypeViews();

    SpreadSignals();
    UpdateUnitViews();
}

void CEngineModel::Execute() {
    mIsPrgramExecution = true;

    if (IsStepByStepExecution()) {
        ExecuteStep();
    } else {
        ExecuteProcess();
    }

    mIsPrgramExecution = false;
}

void CEngineModel::SetExternalBreakRequest() {SetExternalBreak(true);}

void CEngineModel::SetMcuRomAddress(unsigned int address) {
    CurrentMcu()->SetRomAddress(address);

    SpreadSignals();
    UpdateUnitViews();
}

void CEngineModel::GoPast() {
    if (mCurrentTimeline->IsPastTicks()) {
        mCurrentTimeline->StepToPast();

        SpreadSignals();
        UpdateUnitViews();
    }
}

void CEngineModel::GoFuture() {
    if (mCurrentTimeline->IsFutureTicks()) {
        mCurrentTimeline->StepToFuture();

        SpreadSignals();
        UpdateUnitViews();
    }
}

void CEngineModel::UpdateUnitViews() {
    UpdateMemoryViews();
    UpdateLogicViews();
}

void CEngineModel::UpdateMemoryViews() {
    for (TControllers::iterator it=mControllers.begin(); it != mControllers.end(); ++it)
        (*it)->UpdateMemoryView();
}

void CEngineModel::UpdateLogicViews() {
    for (TControllers::iterator it=mControllers.begin(); it != mControllers.end(); ++it)
        (*it)->UpdateLogicView();
}

void CEngineModel::UpdateModeViews() {
    for (TControllers::iterator it=mControllers.begin(); it != mControllers.end(); ++it)
        (*it)->UpdateModeView();
}

void CEngineModel::UpdateMcuTypeViews() {
    for (TControllers::iterator it=mControllers.begin(); it != mControllers.end(); ++it)
        (*it)->UpdateMcuTypeView();
}

void CEngineModel::CheckExternalBreak() {
    for (TControllers::iterator it=mControllers.begin(); it != mControllers.end(); ++it)
        (*it)->CheckUserBreak();
}

void CEngineModel::UpdateHintsViews() {
    for (TControllers::iterator it=mControllers.begin(); it != mControllers.end(); ++it)
        (*it)->UpdateHintsView();
}

void CEngineModel::ShiftState() {
    CurrentAlu()->ShiftState();
    CurrentMcu()->ShiftState();
    CurrentCpu()->ShiftState();
}

void CEngineModel::SpreadData() {
    unsigned int dataOutCount = DataOutsCount();

    CurrentAlu()->OffDataInput();
    CurrentMcu()->OffDataInput();
    CurrentCpu()->OffDataInput();

    if (dataOutCount > 1) {
        mErrorState.SetSignalInterferenceError();        
    } else if (dataOutCount == 1) {
        CBitBlock dio = DataBusValue();

        CurrentAlu()->SetDataInput(dio);
        CurrentMcu()->SetDataInput(dio);
        CurrentCpu()->SetDataInput(dio);
    } else {
        CBitBlock nullData(DataDim(), 0);

        CurrentAlu()->SetDataInput(nullData);
        //Пусть АЛУ считывает ноль! УУ и ЦУУ получать ввод не должны!
        // CurrentMcu()->SetDataInput(nullData);
        // CurrentCpu()->SetDataInput(nullData);
    }
}

void CEngineModel::Tick() {
    SpreadSignals();
    ShiftState();
}

void CEngineModel::SpreadSignals() {
    unsigned int i = 0;
    for (; i<RACE_TRESHOLD; ++i) {
        OffError();
        SpreadData();
        if (!SpreadControlAndGetIsRace())
            break;
    }

    if (i >= RACE_TRESHOLD)
        mErrorState.SetSignalRacingError();
}

void CEngineModel::OffError() {
    mErrorState.OffError();

    CurrentAlu()->OffError();
    CurrentMcu()->OffError();
    CurrentCpu()->OffError();
}

void CEngineModel::RememberTick() {
    if (IsTickHistoryEnabled())
        mCurrentTimeline->ShiftPresent();
}

bool CEngineModel::SpreadControlAndGetIsRace() {
    CBitBlock aluCO = CurrentAlu()->ControlOutput();
    CBitBlock mcuCO = CurrentMcu()->ControlOutput();
    CBitBlock cpuCO = CurrentCpu()->ControlOutput();

    CurrentAlu()->SetControlInput(AluControlInput());
    CurrentMcu()->SetControlInput(McuControlInput());
    CurrentCpu()->SetControlInput(CpuControlInput());

    CurrentAlu()->SpreadInput();
    CurrentMcu()->SpreadInput();
    CurrentCpu()->SpreadInput();

    if (aluCO != CurrentAlu()->ControlOutput()) return true;
    if (mcuCO != CurrentMcu()->ControlOutput()) return true;
    if (cpuCO != CurrentCpu()->ControlOutput()) return true;

    return false;
}

bool CEngineModel::IsTickHistoryEnabled() const {
    return CurrentMode() == DEBUG_MODE;
}

bool CEngineModel::IsStepByStepExecution() const {
    return (CurrentMode() != AUTO_TEST_MODE) || (CurrentMcuType() == MANUAL_MCU);
}

void CEngineModel::ExecuteStep() {
    RememberTick();
    Tick();

    CheckEngineError();
    if (IsError()) {
        HaltCpu();
        return;
    }

    SpreadSignals();
    UpdateUnitViews();
}

void CEngineModel::ExecuteProcess() {
    while (1) { //while not error,success,userbreak;
        Tick();

        CheckEngineError();
        if (       IsError()
                || IsCpuInHaltState()
                || IsExternalBreakChecked()) {
            HaltCpu();
            return;
        }

        SpreadSignals();
    }
}

bool CEngineModel::IsCpuInHaltState() const {
    return CurrentCpu()->IsHaltState();
}

bool CEngineModel::IsExecutionMode() const {
    return
            (CurrentMode() == DEBUG_MODE)
         || (CurrentMode() == AUTO_TEST_MODE)
            ;
}

bool CEngineModel::IsProgrammingMode() const {
    return (CurrentMode() == PROGRAMMING_MODE);
}

CBitBlock CEngineModel::AluControlInput() const {
    return mMcuOutputSwap
            .L2PBlock(CurrentMcu()->ControlOutput()) //physical
            .BitsAt(CurrentAlu()->ControlInputDim() + CurrentCpu()->ControlInputDim() - 1,
                    CurrentCpu()->ControlInputDim());
}

CBitBlock CEngineModel::McuControlInput() const {
    CBitBlock physical(McuControlInputDim());
    physical.CopyFrom(CurrentCpu()->ControlOutput(), 0);
    physical.CopyFrom(CurrentAlu()->ControlOutput(), CpuControlOutputDim());
    return mMcuInputSwap.P2LBlock(physical); //logical input
}

CBitBlock CEngineModel::CpuControlInput() const {
    return mMcuOutputSwap
            .L2PBlock(CurrentMcu()->ControlOutput()) //physical
            .BitsAt(CpuControlInputDim() - 1,
                    0);
}

void CEngineModel::CreateTimelines(CAlu *alu, SharedPtr<CTestVector> testVector) {
    CreateManualTimeline(alu->Clone(), testVector);
    CreateMiliTimeline(alu->Clone(), testVector);
    CreateMooreTimeline(alu, testVector);
}

void CEngineModel::CreateManualTimeline(CAlu *alu, SharedPtr<CTestVector> testVector) {
    mManualTimeline = new CEngineTimeline(
                alu,
                new CManualMcu(StateDim(),
                               McuControlInputDim(),
                               McuControlOutputDim()),
                new CCpu(testVector));
}

void CEngineModel::CreateMiliTimeline(CAlu *alu, SharedPtr<CTestVector> testVector) {
    mMiliTimeline = new CEngineTimeline(
                alu,
                new CMiliAutomate(StateDim(), GroupDim(),
                                  McuControlInputDim(),
                                  McuControlOutputDim()),
                new CCpu(testVector));
}

void CEngineModel::CreateMooreTimeline(CAlu *alu, SharedPtr<CTestVector> testVector) {
    mMooreTimeline = new CEngineTimeline(
                alu,
                new CMooreAutomate(StateDim(), GroupDim(),
                                  McuControlInputDim(),
                                  McuControlOutputDim()),
                new CCpu(testVector));
}

void CEngineModel::PrepareAutoTest() {
    Reset();
    SetExternalBreak(false);
    DisableRomEdit();

    CurrentCpu()->StartAutoTests();
}

void CEngineModel::PrepareDebug() {
    if (!IsSuccessfulInitDebug()) {
        mMode = PROGRAMMING_MODE;
        PrepareProgramming();
    }
}

bool CEngineModel::IsSuccessfulInitDebug() {
    Reset();
    SetExternalBreak(false);
    DisableRomEdit();

    return CurrentCpu()->IsSuccessfulStartDebug();
}

void CEngineModel::PrepareProgramming() {
    SetExternalBreakRequest();
    Reset();
    EnableRomEdit();
}

void CEngineModel::DisableRomEdit() {
    mManualTimeline->ProgramRom()->SetProgrammable(false);
    mMiliTimeline->ProgramRom()->SetProgrammable(false);
    mMooreTimeline->ProgramRom()->SetProgrammable(false);
}

void CEngineModel::EnableRomEdit() {
    mManualTimeline->ProgramRom()->SetProgrammable(true);
    mMiliTimeline->ProgramRom()->SetProgrammable(true);
    mMooreTimeline->ProgramRom()->SetProgrammable(true);
}

void CEngineModel::Reset() {
    mManualTimeline->ClearHistory();
    mMooreTimeline->ClearHistory();
    mMiliTimeline->ClearHistory();

    CurrentAlu()->Reset();
    CurrentMcu()->Reset();
    CurrentCpu()->Reset();
}

void CEngineModel::SetInitialState() {
    SetCurrentMcuType(MANUAL_MCU);
    SetCurrentMode(PROGRAMMING_MODE);
}

void CEngineModel::HaltCpu() {
    CurrentCpu()->Halt();
}

bool CEngineModel::IsExternalBreakChecked() {
    CheckExternalBreak();
    return IsExternalBreak();
}

void CEngineController::SetMcuRomAddress(unsigned int address) {
    if (mModel != 0)
        mModel->SetMcuRomAddress(address);
}

