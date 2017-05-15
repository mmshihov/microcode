#include "cmoorefourstateselect.h"
#include "ui_cmoorefourstateselect.h"

#include "cengine.h"
#include "cmcu.h"
#include "ctextout.h"


void CMoore4McuController::DoUpdateLogicView(const CEngineModel *engine) {
    if (engine->CurrentMcuType() == CEngineModel::MOORE_MCU)
        mView->UpdateLogicView(engine);
}

void CMoore4McuController::DoUpdateMemoryView(const CEngineModel *engine) {
    if (engine->CurrentMcuType() == CEngineModel::MOORE_MCU)
        mView->UpdateMemoryView(engine);
}

void CMoore4McuController::DoUpdateHintsView(const CEngineModel *engine) {
    if (engine->CurrentMcuType() == CEngineModel::MOORE_MCU)
        mView->UpdateHintsView(engine);
}

// --------------------------------------------------------------

CMooreFourStateSelect::CMooreFourStateSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CMooreFourStateSelect),
    mMcuController(this)
{
    ui->setupUi(this);
}

CMooreFourStateSelect::~CMooreFourStateSelect()
{
    delete ui;
}

void CMooreFourStateSelect::UpdateMemoryView(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == CEngineModel::MOORE_MCU);

    UpdateRG(engine);
}

void CMooreFourStateSelect::UpdateLogicView(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == CEngineModel::MOORE_MCU);

    UpdateMS1(engine);
    UpdateMS2(engine);

    UpdateY(engine);
}

void CMooreFourStateSelect::UpdateHintsView(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == CEngineModel::MOORE_MCU);

    ui->mRgMsbNoHint->setText(CTextOut::FormatDec(engine->StateDim() - 1));
    ui->mYDimHint->setText(CTextOut::FormatDec(engine->McuControlOutputDim()));
    ui->mMs1MsbHint->setText(QString("g%1").arg(CTextOut::FormatDec(engine->GroupCount() - 1)));
    ui->mMs2MsbHint->setText(CTextOut::FormatDec(engine->McuControlInputDim() + engine->StateDim() - 1));
}

void CMooreFourStateSelect::UpdateRG(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == CEngineModel::MOORE_MCU);

    const CRegister *rg = engine->CurrentMcu()->Register(CMooreAutomate::STATE_REGISTER_INDEX);

    ui->mRgVal->setText(CTextOut::FormatHex(rg->Output().AsInt(), engine->StateDim()));
    ui->mSVal->setText(CTextOut::FormatHex(rg->Output().AsInt(), engine->StateDim()));
}

void CMooreFourStateSelect::UpdateMS1(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == CEngineModel::MOORE_MCU);

    const CMultiplexor *mux = engine->CurrentMcu()->Multiplexor(CMooreAutomate::GROUP_MUX_INDEX);

    ui->mMS1P0Val->setText(CTextOut::FormatBin(mux->Input(0).AsInt(), 2));
    ui->mMS1P1Val->setText(CTextOut::FormatBin(mux->Input(1).AsInt(), 2));

    unsigned int lastIndex = engine->GroupCount() - 1;
    ui->mMS1PnVal->setText(CTextOut::FormatBin(mux->Input(lastIndex).AsInt(), 2));

    ui->mMs1SelVal->setText(CTextOut::FormatHex(mux->InputIndex(), mux->IndexDim()));
    ui->mMs1Val->setText(CTextOut::FormatHex(mux->Output().AsInt(), 2));
}

void CMooreFourStateSelect::UpdateMS2(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == CEngineModel::MOORE_MCU);

    const CMultiplexor *mux = engine->CurrentMcu()->Multiplexor(CMooreAutomate::STATE_MUX_INDEX);

    ui->mMS2S0Val->setText(CTextOut::FormatHex(mux->Input(0).AsInt(), engine->StateDim()));
    ui->mMS2S1Val->setText(CTextOut::FormatHex(mux->Input(1).AsInt(), engine->StateDim()));
    ui->mMS2S2Val->setText(CTextOut::FormatHex(mux->Input(2).AsInt(), engine->StateDim()));
    ui->mMS2S3Val->setText(CTextOut::FormatHex(mux->Input(3).AsInt(), engine->StateDim()));

    ui->mMs2SVal->setText(CTextOut::FormatHex(mux->Output().AsInt(), engine->StateDim()));
}

void CMooreFourStateSelect::UpdateY(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == CEngineModel::MOORE_MCU);

    ui->mYVal->setText(CTextOut::FormatHex(engine->CurrentMcu()->ControlOutput().AsInt(),
                                           engine->McuControlOutputDim()));
}


