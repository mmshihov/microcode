#include "cpc2dcway1widget.h"
#include "ui_cpc2dcway1widget.h"

#include "cpc2dcalu1.h"

#include "../../../ccpu.h"
#include "../../../ctextout.h"

void CPc2DcWay1EngineController::DoUpdateMemoryView() {
    mView->UpdateMemoryView(Engine());
}

void CPc2DcWay1EngineController::DoUpdateLogicView() {
    mView->UpdateLogicView(Engine());
}

void CPc2DcWay1EngineController::DoUpdateHintsView() {
    mView->UpdateHints(Engine());
}


//-----------------------------------------------------------------------

CPc2DcWay1Widget::CPc2DcWay1Widget(CEngineModel* engine, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CPc2DcWay1Widget),
    mController(this)
{
    ui->setupUi(this);

    engine->AppendController(&mController);
    UpdateHints(Engine());
}

CPc2DcWay1Widget::~CPc2DcWay1Widget() {
    delete ui;
}

void CPc2DcWay1Widget::UpdateMemoryView(const CEngineModel *engine) {
    //обновить значения выходов элементов памяти

    CTextOut::UpdateAluRegisterVal(ui->mRg1Val, engine, 1);
    CTextOut::UpdateAluCounterVal(ui->mCt1Val, engine, 1);

    //обновить значения осведомительных сигналов, снимаемых с элементов памяти
    CTextOut::UpdateAluPVal(ui->mRg1Out7Val, engine, CPc2DcAlu1::P_RG1_7);
}

void CPc2DcWay1Widget::UpdateLogicView(const CEngineModel *engine) {
    //обновить значение на шине
    CTextOut::UpdateEngineBus(ui->mDVal, engine);

    //обновить значения входных сигналов
    CTextOut::UpdateAluYVal(ui->mRg1WrVal,   engine, CPc2DcAlu1::Y_RG1_WR );
    CTextOut::UpdateAluYVal(ui->mCt1WrVal,   engine, CPc2DcAlu1::Y_CT1_WR );
    CTextOut::UpdateAluYVal(ui->mCt1IncVal,  engine, CPc2DcAlu1::Y_CT1_INC);
    CTextOut::UpdateAluYVal(ui->mXor1NotVal, engine, CPc2DcAlu1::Y_XR1_NOT);
    CTextOut::UpdateAluYVal(ui->mBd1OutVal,  engine, CPc2DcAlu1::Y_BD1_OUT);

    //обновить инвертор
    CTextOut::UpdateAluXorVal(ui->mXor1Val, engine, 1);

    //обновить выходы буферных усилителей
    CTextOut::UpdateAluBusDriverVal(ui->mBd1Val, engine, 1, CPc2DcAlu1::Y_BD1_OUT);
}

void CPc2DcWay1Widget::UpdateHints(const CEngineModel *engine) {
    //обновить обозначения управляющих сигналов
    CTextOut::UpdateAluPhysicalYHint(ui->mRg1WrHint,   engine, CPc2DcAlu1::Y_RG1_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mXor1NotHint, engine, CPc2DcAlu1::Y_XR1_NOT);
    CTextOut::UpdateAluPhysicalYHint(ui->mCt1WrHint,   engine, CPc2DcAlu1::Y_CT1_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mCt1IncHint,  engine, CPc2DcAlu1::Y_CT1_INC);
    CTextOut::UpdateAluPhysicalYHint(ui->mBd1OutHint,  engine, CPc2DcAlu1::Y_BD1_OUT);

    //обновить обозначения осведомительных сигналов
    CTextOut::UpdateAluPhysicalPHint(ui->mRg1Out7Hint, engine, CPc2DcAlu1::P_RG1_7);
}

