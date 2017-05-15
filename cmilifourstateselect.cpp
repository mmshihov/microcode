#include "cmilifourstateselect.h"
#include "ui_cmilifourstateselect.h"

#include "cengine.h"
#include "cmcu.h"
#include "ctextout.h"


void CMili4McuController::DoUpdateLogicView(const CEngineModel *engine) {
    if (engine->CurrentMcuType() == CEngineModel::MILI_MCU)
        mView->UpdateLogicView(engine);
}

void CMili4McuController::DoUpdateMemoryView(const CEngineModel *engine) {
    if (engine->CurrentMcuType() == CEngineModel::MILI_MCU)
        mView->UpdateMemoryView(engine);
}

void CMili4McuController::DoUpdateHintsView(const CEngineModel *engine) {
    if (engine->CurrentMcuType() == CEngineModel::MILI_MCU)
        mView->UpdateHintsView(engine);
}

// ---------------------------------------------------------

CMiliFourStateSelect::CMiliFourStateSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CMiliFourStateSelect),
    mMcuController(this)
{
    ui->setupUi(this);
}

CMiliFourStateSelect::~CMiliFourStateSelect()
{
    delete ui;
}

void CMiliFourStateSelect::UpdateMemoryView(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == CEngineModel::MILI_MCU);

    UpdateRG(engine);
}

void CMiliFourStateSelect::UpdateLogicView(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == CEngineModel::MILI_MCU);

    UpdateMS1(engine);
    UpdateMS2(engine);

    UpdateY(engine);
}

void CMiliFourStateSelect::UpdateHintsView(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == CEngineModel::MILI_MCU);

    ui->mRgMsbNoHint->setText(CTextOut::FormatDec(engine->StateDim() - 1));
    ui->mYDimHint->setText(CTextOut::FormatDec(engine->McuControlOutputDim()));
    ui->mMs1MsbHint->setText(QString("g%1").arg(CTextOut::FormatDec(engine->GroupCount() - 1)));
    ui->mMs2MsbHint->setText(CTextOut::FormatDec(engine->McuControlInputDim() + engine->StateDim() - 1));
}

void CMiliFourStateSelect::UpdateRG(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == CEngineModel::MILI_MCU);

    const CRegister *rg = engine->CurrentMcu()->Register(CMiliAutomate::STATE_REGISTER_INDEX);

    ui->mRgVal->setText(CTextOut::FormatHex(rg->Output()));
    ui->mSVal->setText(CTextOut::FormatHex(rg->Output()));
}


void CMiliFourStateSelect::UpdateMS1(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == CEngineModel::MILI_MCU);

    const CMultiplexor *mux = engine->CurrentMcu()->Multiplexor(CMiliAutomate::GROUP_MUX_INDEX);

    ui->mMS1P0Val->setText(CTextOut::FormatBin(mux->Input(0), 2));
    ui->mMS1P1Val->setText(CTextOut::FormatBin(mux->Input(1), 2));

    unsigned int lastIndex = engine->GroupCount() - 1;
    ui->mMS1PnVal->setText(CTextOut::FormatBin(mux->Input(lastIndex), 2));

    ui->mMs1SelVal->setText(CTextOut::FormatHex(mux->InputIndex(), engine->McuControlInputDim()));
    ui->mMs1Val->setText(CTextOut::FormatBin(mux->Output(), 2));
}

void CMiliFourStateSelect::UpdateMS2(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == CEngineModel::MILI_MCU);

    const CMultiplexor *mux = engine->CurrentMcu()->Multiplexor(CMiliAutomate::STATE_MUX_INDEX);

    ui->mMS2S0Val->setText(CTextOut::FormatHex(mux->Input(0)));
    ui->mMS2S1Val->setText(CTextOut::FormatHex(mux->Input(1)));
    ui->mMS2S2Val->setText(CTextOut::FormatHex(mux->Input(2)));
    ui->mMS2S3Val->setText(CTextOut::FormatHex(mux->Input(3)));

    ui->mMs2SVal->setText(CTextOut::FormatHex(mux->Output()));

    mux = engine->CurrentMcu()->Multiplexor(CMiliAutomate::CONTROL_MUX_INDEX);

    ui->mMS2Y0Val->setText(CTextOut::FormatHex(mux->Input(0)));
    ui->mMS2Y1Val->setText(CTextOut::FormatHex(mux->Input(1)));
    ui->mMS2Y2Val->setText(CTextOut::FormatHex(mux->Input(2)));
    ui->mMS2Y3Val->setText(CTextOut::FormatHex(mux->Input(3)));

    ui->mMs2YVal->setText(CTextOut::FormatHex(mux->Output()));
}

void CMiliFourStateSelect::UpdateY(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == CEngineModel::MILI_MCU);

    ui->mYVal->setText(CTextOut::FormatHex(engine->CurrentMcu()->ControlOutput()));
}


