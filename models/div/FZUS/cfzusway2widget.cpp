#include "cfzusway2widget.h"
#include "ui_cfzusway2widget.h"

#include "cfzusalu2.h"

#include "../../../ccpu.h"
#include "../../../ctextout.h"

void CFzusWay2EngineController::DoUpdateMemoryView() {
    mView->UpdateMemoryView(Engine());
}

void CFzusWay2EngineController::DoUpdateLogicView() {
    mView->UpdateLogicView(Engine());
}

void CFzusWay2EngineController::DoUpdateHintsView() {
    mView->UpdateHints(Engine());
}


//-----------------------------------------------------------------------

CFzusWay2Widget::CFzusWay2Widget(CEngineModel* engine, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFzusWay2Widget),
    mController(this)
{
    ui->setupUi(this);

    engine->AppendController(&mController);
    UpdateHints(Engine());
}

CFzusWay2Widget::~CFzusWay2Widget() {
    delete ui;
}

void CFzusWay2Widget::UpdateMemoryView(const CEngineModel *engine) {
    //обновить значения выходов элементов памяти
    CTextOut::UpdateAluCounterVal(ui->mCt1Val, engine, 1);

    CTextOut::UpdateAluRegisterVal(ui->mRg1Val, engine, 1);
    CTextOut::UpdateAluRegisterVal(ui->mRg2Val, engine, 2);
    CTextOut::UpdateAluRegisterVal(ui->mRg3Val, engine, 3);
    CTextOut::UpdateAluRegisterVal(ui->mRg4Val, engine, 4);

    //обновить значения осведомительных сигналов, снимаемых с элементов памяти
    CTextOut::UpdateAluPVal(ui->mCt1Out3Val, engine, CFzusAlu2::P_CT1_3);
    CTextOut::UpdateAluPVal(ui->mRg3Out8Val, engine, CFzusAlu2::P_RG3_8);
}

void CFzusWay2Widget::UpdateLogicView(const CEngineModel *engine) {
    //обновить значение на шине
    CTextOut::UpdateEngineBus(ui->mDVal, engine);

    //обновить значения входных сигналов
    CTextOut::UpdateAluYVal(ui->mCt1WrVal,   engine, CFzusAlu2::Y_CT1_WR );
    CTextOut::UpdateAluYVal(ui->mCt1IncVal,  engine, CFzusAlu2::Y_CT1_INC);
    CTextOut::UpdateAluYVal(ui->mRg1WrVal,   engine, CFzusAlu2::Y_RG1_WR );
    CTextOut::UpdateAluYVal(ui->mRg2WrVal,   engine, CFzusAlu2::Y_RG2_WR );
    CTextOut::UpdateAluYVal(ui->mRg2ShlVal,  engine, CFzusAlu2::Y_RG2_RG3_SHL);
    CTextOut::UpdateAluYVal(ui->mXor1NotVal, engine, CFzusAlu2::Y_SM1_C_XR1_NOT);
    CTextOut::UpdateAluYVal(ui->mSm1CVal,    engine, CFzusAlu2::Y_SM1_C_XR1_NOT);
    CTextOut::UpdateAluYVal(ui->mRg3RstVal,  engine, CFzusAlu2::Y_RG3_RST);
    CTextOut::UpdateAluYVal(ui->mRg3WrVal,   engine, CFzusAlu2::Y_RG3_WR );
    CTextOut::UpdateAluYVal(ui->mRg3ShlVal,  engine, CFzusAlu2::Y_RG2_RG3_SHL);
    CTextOut::UpdateAluYVal(ui->mRg4ShlVal,  engine, CFzusAlu2::Y_RG4_SHL);
    CTextOut::UpdateAluYVal(ui->mBd1OutVal,  engine, CFzusAlu2::Y_BD1_OUT);
    CTextOut::UpdateAluYVal(ui->mBd2OutVal,  engine, CFzusAlu2::Y_BD2_OUT);

    //обновить сумматор
    CTextOut::UpdateAluSmVal(ui->mSm1OutVal, engine, 1);

    //обновить инвертор
    CTextOut::UpdateAluXorVal(ui->mXor1Val, engine, 1);

    //обновить выходы буферных усилителей
    CTextOut::UpdateAluBusDriverVal(ui->mBd1Val, engine, 1, CFzusAlu2::Y_BD1_OUT);
    CTextOut::UpdateAluBusDriverVal(ui->mBd2Val, engine, 2, CFzusAlu2::Y_BD2_OUT);
}

void CFzusWay2Widget::UpdateHints(const CEngineModel *engine) {
    //обновить обозначения управляющих сигналов
    CTextOut::UpdateAluPhysicalYHint(ui->mCt1WrHint,   engine, CFzusAlu2::Y_CT1_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mCt1IncHint,  engine, CFzusAlu2::Y_CT1_INC);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg1WrHint,   engine, CFzusAlu2::Y_RG1_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg2WrHint,   engine, CFzusAlu2::Y_RG2_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg2ShlHint,  engine, CFzusAlu2::Y_RG2_RG3_SHL);
    CTextOut::UpdateAluPhysicalYHint(ui->mSm1CHint,    engine, CFzusAlu2::Y_SM1_C_XR1_NOT);
    CTextOut::UpdateAluPhysicalYHint(ui->mXor1NotHint, engine, CFzusAlu2::Y_SM1_C_XR1_NOT);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg3RstHint,  engine, CFzusAlu2::Y_RG3_RST);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg3WrHint,   engine, CFzusAlu2::Y_RG3_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg3ShlHint,  engine, CFzusAlu2::Y_RG2_RG3_SHL);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg4ShlHint,  engine, CFzusAlu2::Y_RG4_SHL);
    CTextOut::UpdateAluPhysicalYHint(ui->mBd1OutHint,  engine, CFzusAlu2::Y_BD1_OUT);
    CTextOut::UpdateAluPhysicalYHint(ui->mBd2OutHint,  engine, CFzusAlu2::Y_BD2_OUT);

    //обновить обозначения осведомительных сигналов
    CTextOut::UpdateAluPhysicalPHint(ui->mCt1Out3Hint, engine, CFzusAlu2::P_CT1_3);
    CTextOut::UpdateAluPhysicalPHint(ui->mRg3Out8Hint, engine, CFzusAlu2::P_RG3_8);
}

