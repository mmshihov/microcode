#include "cdcacway1widget.h"
#include "ui_cdcacway1widget.h"

#include "cdcacalu1.h"

#include "../../../ccpu.h"
#include "../../../ctextout.h"

void CDcacWay1EngineController::DoUpdateMemoryView() {
    mView->UpdateMemoryView(Engine());
}

void CDcacWay1EngineController::DoUpdateLogicView() {
    mView->UpdateLogicView(Engine());
}

void CDcacWay1EngineController::DoUpdateHintsView() {
    mView->UpdateHints(Engine());
}

CDcacWay1Widget::CDcacWay1Widget(CEngineModel* engine, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CDcacWay1Widget),
    mController(this)
{
    ui->setupUi(this);

    engine->AppendController(&mController);
    UpdateHints(Engine());
}

CDcacWay1Widget::~CDcacWay1Widget() {
    delete ui;
}

void CDcacWay1Widget::UpdateMemoryView(const CEngineModel *engine) {
    //обновить значения выходов элементов памяти
    CTextOut::UpdateAluCounterVal(ui->mCt1Val, engine, 1);

    CTextOut::UpdateAluRegisterVal(ui->mRg1Val, engine, 1);
    CTextOut::UpdateAluRegisterVal(ui->mRg2Val, engine, 2);
    CTextOut::UpdateAluRegisterVal(ui->mRg3Val, engine, 3);
    CTextOut::UpdateAluRegisterVal(ui->mRg4Val, engine, 4);

    //обновить значения осведомительных сигналов, снимаемых с элементов памяти
    CTextOut::UpdateAluPVal(ui->mCt1Out3Val,   engine, CDcacAlu1::P_CT1_3);
    CTextOut::UpdateAluG2Val(ui->mRg1Out10Val, engine, CDcacAlu1::P_RG1_1, CDcacAlu1::P_RG1_0);
}

void CDcacWay1Widget::UpdateLogicView(const CEngineModel *engine) {
    //обновить значение на шине
    CTextOut::UpdateEngineBus(ui->mDVal, engine);

    //обновить значения входных сигналов
    CTextOut::UpdateAluYVal(ui->mCt1WrVal,   engine, CDcacAlu1::Y_CT1_WR );
    CTextOut::UpdateAluYVal(ui->mCt1IncVal,  engine, CDcacAlu1::Y_CT1_INC);
    CTextOut::UpdateAluYVal(ui->mRg1WrVal,   engine, CDcacAlu1::Y_RG1_WR );
    CTextOut::UpdateAluYVal(ui->mRg1ShrVal,  engine, CDcacAlu1::Y_RG1_SHR);
    CTextOut::UpdateAluYVal(ui->mRg2WrVal,   engine, CDcacAlu1::Y_RG2_WR );
    CTextOut::UpdateAluYVal(ui->mRg3RstVal,  engine, CDcacAlu1::Y_RG3_RST);
    CTextOut::UpdateAluYVal(ui->mRg3WrVal,   engine, CDcacAlu1::Y_RG3_WR );
    CTextOut::UpdateAluYVal(ui->mRg3ShrVal,  engine, CDcacAlu1::Y_RG3_RG4_SHR);
    CTextOut::UpdateAluYVal(ui->mRg4ShrVal,  engine, CDcacAlu1::Y_RG3_RG4_SHR);
    CTextOut::UpdateAluYVal(ui->mXor1NotVal, engine, CDcacAlu1::Y_SM1_C_RG2_NOT);
    CTextOut::UpdateAluYVal(ui->mSm1CVal,    engine, CDcacAlu1::Y_SM1_C_RG2_NOT);
    CTextOut::UpdateAluYVal(ui->mBd1OutVal,  engine, CDcacAlu1::Y_BD1_OUT);
    CTextOut::UpdateAluYVal(ui->mBd2OutVal,  engine, CDcacAlu1::Y_BD2_OUT);

    //обновить сумматор
    CTextOut::UpdateAluSmVal(ui->mSm1OutVal, engine, 1);

    //обновить инвертор
    CTextOut::UpdateAluXorVal(ui->mXor1Val, engine, 1);

    //обновить выходы буферных усилителей
    CTextOut::UpdateAluBusDriverVal(ui->mBd1Val, engine, 1, CDcacAlu1::Y_BD1_OUT);
    CTextOut::UpdateAluBusDriverVal(ui->mBd2Val, engine, 2, CDcacAlu1::Y_BD2_OUT);
}

void CDcacWay1Widget::UpdateHints(const CEngineModel *engine) {
    //обновить обозначения управляющих сигналов
    CTextOut::UpdateAluPhysicalYHint(ui->mCt1WrHint,   engine, CDcacAlu1::Y_CT1_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mCt1IncHint,  engine, CDcacAlu1::Y_CT1_INC);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg1WrHint,   engine, CDcacAlu1::Y_RG1_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg1ShrHint,  engine, CDcacAlu1::Y_RG1_SHR);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg2WrHint,   engine, CDcacAlu1::Y_RG2_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg3RstHint,  engine, CDcacAlu1::Y_RG3_RST);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg3WrHint,   engine, CDcacAlu1::Y_RG3_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg3ShrHint,  engine, CDcacAlu1::Y_RG3_RG4_SHR);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg4ShrHint,  engine, CDcacAlu1::Y_RG3_RG4_SHR);
    CTextOut::UpdateAluPhysicalYHint(ui->mSm1CHint,    engine, CDcacAlu1::Y_SM1_C_RG2_NOT);
    CTextOut::UpdateAluPhysicalYHint(ui->mXor1NotHint, engine, CDcacAlu1::Y_SM1_C_RG2_NOT);
    CTextOut::UpdateAluPhysicalYHint(ui->mBd1OutHint,  engine, CDcacAlu1::Y_BD1_OUT);
    CTextOut::UpdateAluPhysicalYHint(ui->mBd2OutHint,  engine, CDcacAlu1::Y_BD2_OUT);

    //обновить обозначения осведомительных сигналов
    CTextOut::UpdateAluPhysicalPHint(ui->mCt1Out3Hint,   engine, CDcacAlu1::P_CT1_3);
    CTextOut::UpdateAluPhysicalG2Hint(ui->mRg1Out10Hint, engine,
                                      CDcacAlu1::P_RG1_1, CDcacAlu1::P_RG1_0);
}

