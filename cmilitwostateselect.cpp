#include "cmilitwostateselect.h"
#include "ui_cmilitwostateselect.h"

#include "cengine.h"
#include "ctextout.h"

void CMili2McuController::DoUpdateLogicView(const CEngineModel *engine) {
    if (engine->CurrentMcuType() == CEngineModel::MILI_MCU)
        mView->UpdateLogicView(engine);
}

void CMili2McuController::DoUpdateMemoryView(const CEngineModel *engine) {
    if (engine->CurrentMcuType() == CEngineModel::MILI_MCU)
        mView->UpdateMemoryView(engine);
}

void CMili2McuController::DoUpdateHintsView(const CEngineModel *engine) {
    if (engine->CurrentMcuType() == CEngineModel::MILI_MCU)
        mView->UpdateHintsView(engine);
}

// -------------------------------------------------------------

CMiliTwoStateSelect::CMiliTwoStateSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CMiliTwoStateSelect),
    mMcuController(this)
{
    ui->setupUi(this);
}

CMiliTwoStateSelect::~CMiliTwoStateSelect()
{
    delete ui;
}

void CMiliTwoStateSelect::UpdateMemoryView(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == CEngineModel::MILI_MCU);

    UpdateRG(engine);
}

void CMiliTwoStateSelect::UpdateLogicView(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == CEngineModel::MILI_MCU);

    UpdateMS1(engine);
    UpdateMS2(engine);

    UpdateY(engine);
}

void CMiliTwoStateSelect::UpdateHintsView(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == CEngineModel::MILI_MCU);

    ui->mRgMsbNoHint->setText(CTextOut::FormatDec(engine->StateDim() - 1));
    ui->mYDimHint->setText(CTextOut::FormatDec(engine->McuControlOutputDim()));
    ui->mMs1MsbHint->setText(QString("p%1").arg(CTextOut::FormatDec(engine->McuControlInputDim() - 1)));
    ui->mMs2MsbHint->setText(CTextOut::FormatDec(engine->McuControlOutputDim() + engine->StateDim() - 1));
}

void CMiliTwoStateSelect::UpdateRG(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == CEngineModel::MILI_MCU);

    const CRegister *rg = engine->CurrentMcu()->Register(CMiliAutomate::STATE_REGISTER_INDEX);
    unsigned int stateDim = engine->StateDim();

    ui->mRgVal->setText(CTextOut::FormatHex(rg->Output(), stateDim));
    ui->mSVal->setText(CTextOut::FormatHex(rg->Output(), stateDim));
}

void CMiliTwoStateSelect::UpdateMS1(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == CEngineModel::MILI_MCU);

    const CMultiplexor *mux = engine->CurrentMcu()->Multiplexor(CMiliAutomate::GROUP_MUX_INDEX);

    ui->mMS1P0Val->setText(CTextOut::FormatBin(mux->Input(0), 1));
    ui->mMS1P1Val->setText(CTextOut::FormatBin(mux->Input(1), 1));

    unsigned int lastIndex = engine->McuControlInputDim() - 1;
    ui->mMS1PnVal->setText(CTextOut::FormatBin(mux->Input(lastIndex).AsInt(), 1));

    ui->mMs1SelVal->setText(CTextOut::FormatHex(mux->InputIndex(), mux->IndexDim()));
    ui->mMs1Val->setText(CTextOut::FormatBin(mux->Output().AsInt(), 1));
}

void CMiliTwoStateSelect::UpdateMS2(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == CEngineModel::MILI_MCU);

    const CMultiplexor *mux = engine->CurrentMcu()->Multiplexor(CMiliAutomate::STATE_MUX_INDEX);

    ui->mMS2S0Val->setText(CTextOut::FormatHex(mux->Input(0)));
    ui->mMS2S1Val->setText(CTextOut::FormatHex(mux->Input(1)));

    ui->mMs2SVal->setText(CTextOut::FormatHex(mux->Output()));

    mux = engine->CurrentMcu()->Multiplexor(CMiliAutomate::CONTROL_MUX_INDEX);

    ui->mMS2Y0Val->setText(CTextOut::FormatHex(mux->Input(0)));
    ui->mMS2Y1Val->setText(CTextOut::FormatHex(mux->Input(1)));

    ui->mMs2YVal->setText(CTextOut::FormatHex(mux->Output()));
}

void CMiliTwoStateSelect::UpdateY(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == CEngineModel::MILI_MCU);

    ui->mYVal->setText(CTextOut::FormatHex(engine->CurrentMcu()->ControlOutput()));
}

