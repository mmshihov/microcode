#include "cmanual.h"
#include "ui_cmanual.h"

#include "cengine.h"
#include "cmcu.h"
#include "ctextout.h"


void CManualMcuController::DoUpdateLogicView(const CEngineModel *engine) {
    if (engine->CurrentMcuType() == CEngineModel::MANUAL_MCU)
        mView->UpdateLogicView(engine);
}

void CManualMcuController::DoUpdateMemoryView(const CEngineModel *engine) {
    if (engine->CurrentMcuType() == CEngineModel::MANUAL_MCU)
        mView->UpdateMemoryView(engine);
}

void CManualMcuController::DoUpdateHintsView(const CEngineModel *engine) {
    if (engine->CurrentMcuType() == CEngineModel::MANUAL_MCU)
        mView->UpdateHintsView(engine);
}

// --------------------------------------------------------------

CManual::CManual(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CManual),
    mMcuController(this)
{
    ui->setupUi(this);
}

CManual::~CManual() {
    delete ui;
}

void CManual::UpdateMemoryView(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == CEngineModel::MANUAL_MCU);

    UpdateRG(engine);
    UpdateY(engine);
}

void CManual::UpdateLogicView(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == CEngineModel::MANUAL_MCU);

    UpdateRG(engine);
    UpdateY(engine);
}

void CManual::UpdateHintsView(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == CEngineModel::MANUAL_MCU);

    ui->mRgMsbNoHint->setText(CTextOut::FormatDec(engine->StateDim() - 1));
    ui->mYDimHint->setText(CTextOut::FormatDec(engine->McuControlOutputDim()));
}

void CManual::UpdateRG(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == CEngineModel::MANUAL_MCU);

    const CRegister *rg = engine->CurrentMcu()->Register(CManualMcu::ROM_ADDRESS_REGISTER_INDEX);

    ui->mRgVal->setText(CTextOut::FormatHex(rg->Output(), engine->StateDim()));
    ui->mSVal->setText(CTextOut::FormatHex(rg->Output(), engine->StateDim()));
}

void CManual::UpdateY(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == CEngineModel::MANUAL_MCU);

    ui->mYVal->setText(CTextOut::FormatHex(
                           engine->CurrentMcu()->ControlOutput().AsInt(),
                           engine->McuControlOutputDim()));
}

