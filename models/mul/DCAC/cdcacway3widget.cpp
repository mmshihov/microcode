#include "cdcacway3widget.h"
#include "ui_cdcacway3widget.h"

#include "cdcacalu3.h"

#include "../../../ccpu.h"
#include "../../../ctextout.h"

void CDcacWay3EngineController::DoUpdateMemoryView() {
    mView->UpdateMemoryView(Engine());
}

void CDcacWay3EngineController::DoUpdateLogicView() {
    mView->UpdateLogicView(Engine());
}

void CDcacWay3EngineController::DoUpdateHintsView() {
    mView->UpdateHints(Engine());
}

CDcacWay3Widget::CDcacWay3Widget(CEngineModel* engine, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CDcacWay3Widget),
    mController(this)
{
    ui->setupUi(this);

    engine->AppendController(&mController);
    UpdateHints(Engine());
}

CDcacWay3Widget::~CDcacWay3Widget() {
    delete ui;
}

void CDcacWay3Widget::UpdateMemoryView(const CEngineModel *engine) {
    //обновить значения выходов элементов памяти
    CTextOut::UpdateAluCounterVal(ui->mCt1Val, engine, 1);

    CTextOut::UpdateAluRegisterVal(ui->mRg1Val, engine, 1);
    CTextOut::UpdateAluRegisterVal(ui->mRg2Val, engine, 2);
    CTextOut::UpdateAluRegister2nVal(ui->mRg3Val, engine, 3);

    //обновить значения осведомительных сигналов, снимаемых с элементов памяти
    CTextOut::UpdateAluPVal(ui->mCt1Out3Val,   engine, CDcacAlu3::P_CT1_3);
    CTextOut::UpdateAluG2Val(ui->mRg1Out76Val, engine, CDcacAlu3::P_RG1_7, CDcacAlu3::P_RG1_6);
}

void CDcacWay3Widget::UpdateLogicView(const CEngineModel *engine) {
    //обновить значение на шине
    CTextOut::UpdateEngineBus(ui->mDVal, engine);

    //обновить значения входных сигналов
    CTextOut::UpdateAluYVal(ui->mCt1WrVal,   engine, CDcacAlu3::Y_CT1_WR );
    CTextOut::UpdateAluYVal(ui->mCt1IncVal,  engine, CDcacAlu3::Y_CT1_INC);
    CTextOut::UpdateAluYVal(ui->mRg1WrVal,   engine, CDcacAlu3::Y_RG1_WR );
    CTextOut::UpdateAluYVal(ui->mRg1ShlVal,  engine, CDcacAlu3::Y_RG1_SHL);
    CTextOut::UpdateAluYVal(ui->mRg2WrVal,   engine, CDcacAlu3::Y_RG2_WR );
    CTextOut::UpdateAluYVal(ui->mRg3RstVal,  engine, CDcacAlu3::Y_RG3_RST);
    CTextOut::UpdateAluYVal(ui->mRg3WrVal,   engine, CDcacAlu3::Y_RG3_WR );
    CTextOut::UpdateAluYVal(ui->mRg3ShlVal,  engine, CDcacAlu3::Y_RG3_SHL);
    CTextOut::UpdateAluYVal(ui->mXor1NotVal, engine, CDcacAlu3::Y_SM1_C_RG2_NOT);
    CTextOut::UpdateAluYVal(ui->mSm1CVal,    engine, CDcacAlu3::Y_SM1_C_RG2_NOT);
    CTextOut::UpdateAluYVal(ui->mBd1OutVal,  engine, CDcacAlu3::Y_BD1_OUT);
    CTextOut::UpdateAluYVal(ui->mBd2OutVal,  engine, CDcacAlu3::Y_BD2_OUT);

    //обновить сумматор
    CTextOut::UpdateAluSm2nVal(ui->mSm1OutVal, engine, 1);

    //обновить инвертор
    CTextOut::UpdateAluXor2nVal(ui->mXor1Val, engine, 1);

    //обновить выходы буферных усилителей
    CTextOut::UpdateAluBusDriverVal(ui->mBd1Val, engine, 1, CDcacAlu3::Y_BD1_OUT);
    CTextOut::UpdateAluBusDriverVal(ui->mBd2Val, engine, 2, CDcacAlu3::Y_BD2_OUT);
}

void CDcacWay3Widget::UpdateHints(const CEngineModel *engine) {
    //обновить обозначения управляющих сигналов
    CTextOut::UpdateAluPhysicalYHint(ui->mCt1WrHint,   engine, CDcacAlu3::Y_CT1_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mCt1IncHint,  engine, CDcacAlu3::Y_CT1_INC);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg1WrHint,   engine, CDcacAlu3::Y_RG1_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg1ShlHint,  engine, CDcacAlu3::Y_RG1_SHL);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg2WrHint,   engine, CDcacAlu3::Y_RG2_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg3RstHint,  engine, CDcacAlu3::Y_RG3_RST);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg3WrHint,   engine, CDcacAlu3::Y_RG3_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg3ShlHint,  engine, CDcacAlu3::Y_RG3_SHL);
    CTextOut::UpdateAluPhysicalYHint(ui->mSm1CHint,    engine, CDcacAlu3::Y_SM1_C_RG2_NOT);
    CTextOut::UpdateAluPhysicalYHint(ui->mXor1NotHint, engine, CDcacAlu3::Y_SM1_C_RG2_NOT);
    CTextOut::UpdateAluPhysicalYHint(ui->mBd1OutHint,  engine, CDcacAlu3::Y_BD1_OUT);
    CTextOut::UpdateAluPhysicalYHint(ui->mBd2OutHint,  engine, CDcacAlu3::Y_BD2_OUT);

    //обновить обозначения осведомительных сигналов
    CTextOut::UpdateAluPhysicalPHint(ui->mCt1Out3Hint,   engine, CDcacAlu3::P_CT1_3);
    CTextOut::UpdateAluPhysicalG2Hint(ui->mRg1Out76Hint, engine,
                                      CDcacAlu3::P_RG1_7, CDcacAlu3::P_RG1_6);
}

