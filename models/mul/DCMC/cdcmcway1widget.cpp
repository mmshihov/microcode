#include "cdcmcway1widget.h"
#include "ui_cdcmcway1widget.h"

#include "cdcmcalu1.h"

#include "../../../ccpu.h"
#include "../../../ctextout.h"

void CDcmcWay1EngineController::DoUpdateMemoryView() {
    mView->UpdateMemoryView(Engine());
}

void CDcmcWay1EngineController::DoUpdateLogicView() {
    mView->UpdateLogicView(Engine());
}

void CDcmcWay1EngineController::DoUpdateHintsView() {
    mView->UpdateHints(Engine());
}

CDcmcWay1Widget::CDcmcWay1Widget(CEngineModel* engine, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CDcmcWay1Widget),
    mController(this)
{
    ui->setupUi(this);

    engine->AppendController(&mController);
    UpdateHints(Engine());
}

CDcmcWay1Widget::~CDcmcWay1Widget() {
    delete ui;
}

void CDcmcWay1Widget::UpdateMemoryView(const CEngineModel *engine) {
    //обновить значения выходов элементов памяти
    CTextOut::UpdateAluCounterVal(ui->mCt1Val, engine, 1);

    CTextOut::UpdateAluRegisterVal(ui->mRg1Val, engine, 1);
    CTextOut::UpdateAluRegisterVal(ui->mRg2Val, engine, 2);
    CTextOut::UpdateAluRegisterVal(ui->mRg3Val, engine, 3);
    CTextOut::UpdateAluRegisterVal(ui->mRg4Val, engine, 4);

    //обновить значения осведомительных сигналов, снимаемых с элементов памяти
    CTextOut::UpdateAluPVal(ui->mCt1Out3Val, engine, CDcmcAlu1::P_CT1_3);
    CTextOut::UpdateAluPVal(ui->mRg1Out0Val, engine, CDcmcAlu1::P_RG1_0);
    CTextOut::UpdateAluPVal(ui->mRg1Out7Val, engine, CDcmcAlu1::P_RG1_7);
    CTextOut::UpdateAluPVal(ui->mRg2Out7Val, engine, CDcmcAlu1::P_RG2_7);
}

void CDcmcWay1Widget::UpdateLogicView(const CEngineModel *engine) {
    //обновить значение на шине
    CTextOut::UpdateEngineBus(ui->mDVal, engine);

    //обновить значения входных сигналов
    CTextOut::UpdateAluYVal(ui->mCt1WrVal,  engine, CDcmcAlu1::Y_CT1_WR );
    CTextOut::UpdateAluYVal(ui->mCt1IncVal, engine, CDcmcAlu1::Y_CT1_INC);
    CTextOut::UpdateAluYVal(ui->mRg1WrVal,  engine, CDcmcAlu1::Y_RG1_WR );
    CTextOut::UpdateAluYVal(ui->mRg1ShrVal, engine, CDcmcAlu1::Y_RG1_SHR);
    CTextOut::UpdateAluYVal(ui->mRg2WrVal,  engine, CDcmcAlu1::Y_RG2_WR );
    CTextOut::UpdateAluYVal(ui->mRg3RstVal, engine, CDcmcAlu1::Y_RG3_RST);
    CTextOut::UpdateAluYVal(ui->mRg3WrVal,  engine, CDcmcAlu1::Y_RG3_WR );
    CTextOut::UpdateAluYVal(ui->mRg3ShrVal, engine, CDcmcAlu1::Y_RG3_RG4_SHR);
    CTextOut::UpdateAluYVal(ui->mRg4ShrVal, engine, CDcmcAlu1::Y_RG3_RG4_SHR);
    CTextOut::UpdateAluYVal(ui->mMs1SelVal, engine, CDcmcAlu1::Y_MS1_SEL);
    CTextOut::UpdateAluYVal(ui->mMs1NotVal, engine, CDcmcAlu1::Y_SM1_C_MS1_NOT);
    CTextOut::UpdateAluYVal(ui->mSm1CVal,   engine, CDcmcAlu1::Y_SM1_C_MS1_NOT);
    CTextOut::UpdateAluYVal(ui->mBd1OutVal, engine, CDcmcAlu1::Y_BD1_OUT);
    CTextOut::UpdateAluYVal(ui->mBd2OutVal, engine, CDcmcAlu1::Y_BD2_OUT);

    //обновить сумматор
    CTextOut::UpdateAluSmVal(ui->mSm1OutVal, engine, 1);

    //обновить мультиплексор
    CTextOut::UpdateAluMsVal(ui->mMs1Val, engine, 1);

    //обновить инвертор
    CTextOut::UpdateAluXorVal(ui->mXor1Val, engine, 1);

    //обновить выходы буферных усилителей
    CTextOut::UpdateAluBusDriverVal(ui->mBd1Val, engine, 1, CDcmcAlu1::Y_BD1_OUT);
    CTextOut::UpdateAluBusDriverVal(ui->mBd2Val, engine, 2, CDcmcAlu1::Y_BD2_OUT);
}

void CDcmcWay1Widget::UpdateHints(const CEngineModel *engine) {
    //обновить обозначения управляющих сигналов
    CTextOut::UpdateAluPhysicalYHint(ui->mCt1WrHint,  engine, CDcmcAlu1::Y_CT1_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mCt1IncHint, engine, CDcmcAlu1::Y_CT1_INC);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg1WrHint,  engine, CDcmcAlu1::Y_RG1_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg1ShrHint, engine, CDcmcAlu1::Y_RG1_SHR);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg2WrHint,  engine, CDcmcAlu1::Y_RG2_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg3RstHint, engine, CDcmcAlu1::Y_RG3_RST);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg3WrHint,  engine, CDcmcAlu1::Y_RG3_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg3ShrHint, engine, CDcmcAlu1::Y_RG3_RG4_SHR);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg4ShrHint, engine, CDcmcAlu1::Y_RG3_RG4_SHR);
    CTextOut::UpdateAluPhysicalYHint(ui->mSm1CHint,   engine, CDcmcAlu1::Y_SM1_C_MS1_NOT);
    CTextOut::UpdateAluPhysicalYHint(ui->mMs1SelHint, engine, CDcmcAlu1::Y_MS1_SEL);
    CTextOut::UpdateAluPhysicalYHint(ui->mMs1NotHint, engine, CDcmcAlu1::Y_SM1_C_MS1_NOT);
    CTextOut::UpdateAluPhysicalYHint(ui->mBd1OutHint, engine, CDcmcAlu1::Y_BD1_OUT);
    CTextOut::UpdateAluPhysicalYHint(ui->mBd2OutHint, engine, CDcmcAlu1::Y_BD2_OUT);

    //обновить обозначения осведомительных сигналов
    CTextOut::UpdateAluPhysicalPHint(ui->mCt1Out3Hint, engine, CDcmcAlu1::P_CT1_3);
    CTextOut::UpdateAluPhysicalPHint(ui->mRg1Out0Hint, engine, CDcmcAlu1::P_RG1_0);
    CTextOut::UpdateAluPhysicalPHint(ui->mRg1Out7Hint, engine, CDcmcAlu1::P_RG1_7);
    CTextOut::UpdateAluPhysicalPHint(ui->mRg2Out7Hint, engine, CDcmcAlu1::P_RG2_7);
}

