#include "cfzusway3widget.h"
#include "ui_cfzusway3widget.h"

#include "cfzusalu3.h"

#include "../../../ccpu.h"
#include "../../../ctextout.h"


void CFzusWay3EngineController::DoUpdateMemoryView() {
    mView->UpdateMemoryView(Engine());
}

void CFzusWay3EngineController::DoUpdateLogicView() {
    mView->UpdateLogicView(Engine());
}

void CFzusWay3EngineController::DoUpdateHintsView() {
    mView->UpdateHints(Engine());
}


//-----------------------------------------------------------------------

CFzusWay3Widget::CFzusWay3Widget(CEngineModel* engine, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFzusWay3Widget),
    mController(this)
{
    ui->setupUi(this);

    engine->AppendController(&mController);
    UpdateHints(Engine());
}

CFzusWay3Widget::~CFzusWay3Widget() {
    delete ui;
}

void CFzusWay3Widget::UpdateMemoryView(const CEngineModel *engine) {
    //обновить значения выходов элементов памяти
    CTextOut::UpdateAluCounterVal(ui->mCt1Val, engine, 1);

    CTextOut::UpdateAluRegisterVal(ui->mRg1Val, engine, 1);
    CTextOut::UpdateAluRegisterVal(ui->mRg2Val, engine, 2);
    CTextOut::UpdateAluRegister2nVal(ui->mRg3Val, engine, 3);
    CTextOut::UpdateAluRegisterVal(ui->mRg4Val, engine, 4);

    //обновить значения осведомительных сигналов, снимаемых с элементов памяти
    CTextOut::UpdateAluPVal(ui->mCt1Out3Val,  engine, CFzusAlu3::P_CT1_3);
    CTextOut::UpdateAluPVal(ui->mRg3Out16Val, engine, CFzusAlu3::P_RG3_16);
}

void CFzusWay3Widget::UpdateLogicView(const CEngineModel *engine) {
    //обновить значение на шине
    CTextOut::UpdateEngineBus(ui->mDVal, engine);

    //обновить значения входных сигналов
    CTextOut::UpdateAluYVal(ui->mCt1WrVal,   engine, CFzusAlu3::Y_CT1_WR );
    CTextOut::UpdateAluYVal(ui->mCt1IncVal,  engine, CFzusAlu3::Y_CT1_INC);
    CTextOut::UpdateAluYVal(ui->mRg1RstVal,  engine, CFzusAlu3::Y_RG1_RST);
    CTextOut::UpdateAluYVal(ui->mRg1WrVal,   engine, CFzusAlu3::Y_RG1_WR );
    CTextOut::UpdateAluYVal(ui->mRg1ShrVal,  engine, CFzusAlu3::Y_RG1_RG2_SHR);
    CTextOut::UpdateAluYVal(ui->mRg2RstVal,  engine, CFzusAlu3::Y_RG2_RST);
    CTextOut::UpdateAluYVal(ui->mRg2WrVal,   engine, CFzusAlu3::Y_RG2_WR );
    CTextOut::UpdateAluYVal(ui->mRg2ShrVal,  engine, CFzusAlu3::Y_RG1_RG2_SHR);
    CTextOut::UpdateAluYVal(ui->mXor1NotVal, engine, CFzusAlu3::Y_SM1_C_XR1_NOT);
    CTextOut::UpdateAluYVal(ui->mSm1CVal,    engine, CFzusAlu3::Y_SM1_C_XR1_NOT);
    CTextOut::UpdateAluYVal(ui->mRg3RstVal,  engine, CFzusAlu3::Y_RG3_RST);
    CTextOut::UpdateAluYVal(ui->mRg3WrVal,   engine, CFzusAlu3::Y_RG3_WR );
    CTextOut::UpdateAluYVal(ui->mRg4ShlVal,  engine, CFzusAlu3::Y_RG4_SHL);
    CTextOut::UpdateAluYVal(ui->mBd1OutVal,  engine, CFzusAlu3::Y_BD1_OUT);
    CTextOut::UpdateAluYVal(ui->mBd2OutVal,  engine, CFzusAlu3::Y_BD2_OUT);

    //обновить сумматор
    CTextOut::UpdateAluSm2nVal(ui->mSm1OutVal, engine, 1);

    //обновить инвертор
    CTextOut::UpdateAluXor2nVal(ui->mXor1Val, engine, 1);

    //обновить выходы буферных усилителей
    CTextOut::UpdateAluBusDriverVal(ui->mBd1Val, engine, 1, CFzusAlu3::Y_BD1_OUT);
    CTextOut::UpdateAluBusDriverVal(ui->mBd2Val, engine, 2, CFzusAlu3::Y_BD2_OUT);
}

void CFzusWay3Widget::UpdateHints(const CEngineModel *engine) {
    //обновить обозначения управляющих сигналов
    CTextOut::UpdateAluPhysicalYHint(ui->mCt1WrHint,   engine, CFzusAlu3::Y_CT1_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mCt1IncHint,  engine, CFzusAlu3::Y_CT1_INC);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg1RstHint,  engine, CFzusAlu3::Y_RG1_RST);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg1WrHint,   engine, CFzusAlu3::Y_RG1_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg1ShrHint,  engine, CFzusAlu3::Y_RG1_RG2_SHR);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg2RstHint,  engine, CFzusAlu3::Y_RG2_RST);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg2WrHint,   engine, CFzusAlu3::Y_RG2_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg2ShrHint,  engine, CFzusAlu3::Y_RG1_RG2_SHR);
    CTextOut::UpdateAluPhysicalYHint(ui->mSm1CHint,    engine, CFzusAlu3::Y_SM1_C_XR1_NOT);
    CTextOut::UpdateAluPhysicalYHint(ui->mXor1NotHint, engine, CFzusAlu3::Y_SM1_C_XR1_NOT);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg3RstHint,  engine, CFzusAlu3::Y_RG3_RST);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg3WrHint,   engine, CFzusAlu3::Y_RG3_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg4ShlHint,  engine, CFzusAlu3::Y_RG4_SHL);
    CTextOut::UpdateAluPhysicalYHint(ui->mBd1OutHint,  engine, CFzusAlu3::Y_BD1_OUT);
    CTextOut::UpdateAluPhysicalYHint(ui->mBd2OutHint,  engine, CFzusAlu3::Y_BD2_OUT);

    //обновить обозначения осведомительных сигналов
    CTextOut::UpdateAluPhysicalPHint(ui->mCt1Out3Hint,  engine, CFzusAlu3::P_CT1_3);
    CTextOut::UpdateAluPhysicalPHint(ui->mRg3Out16Hint, engine, CFzusAlu3::P_RG3_16);
}
