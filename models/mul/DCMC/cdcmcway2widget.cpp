#include "cdcmcway2widget.h"
#include "ui_cdcmcway2widget.h"

#include "cdcmcalu2.h"

#include "../../../ccpu.h"
#include "../../../ctextout.h"

void CDcmcWay2EngineController::DoUpdateMemoryView() {
    mView->UpdateMemoryView(Engine());
}

void CDcmcWay2EngineController::DoUpdateLogicView() {
    mView->UpdateLogicView(Engine());
}

void CDcmcWay2EngineController::DoUpdateHintsView() {
    mView->UpdateHints(Engine());
}


CDcmcWay2Widget::CDcmcWay2Widget(CEngineModel* engine, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CDcmcWay2Widget),
    mController(this)
{
    ui->setupUi(this);

    engine->AppendController(&mController);
    UpdateHints(Engine());
}

CDcmcWay2Widget::~CDcmcWay2Widget() {
    delete ui;
}

void CDcmcWay2Widget::UpdateMemoryView(const CEngineModel *engine) {
    //обновить значения выходов элементов памяти
    CTextOut::UpdateAluCounterVal(ui->mCt1Val, engine, 1);

    CTextOut::UpdateAluRegisterVal(ui->mRg1Val, engine, 1);
    CTextOut::UpdateAluRegister2nVal(ui->mRg2Val, engine, 2);
    CTextOut::UpdateAluRegister2nVal(ui->mRg3Val, engine, 3);

    //обновить значения осведомительных сигналов, снимаемых с элементов памяти
    CTextOut::UpdateAluPVal(ui->mCt1Out3Val,  engine, CDcmcAlu2::P_CT1_3);
    CTextOut::UpdateAluPVal(ui->mRg1Out0Val,  engine, CDcmcAlu2::P_RG1_0);
    CTextOut::UpdateAluPVal(ui->mRg1Out7Val,  engine, CDcmcAlu2::P_RG1_7);
    CTextOut::UpdateAluPVal(ui->mRg2Out15Val, engine, CDcmcAlu2::P_RG2_15);

    CTextOut::UpdateAluPVal(ui->mRg1LvVal, engine, CDcmcAlu2::P_RG1_0);
}

void CDcmcWay2Widget::UpdateLogicView(const CEngineModel *engine) {
    //обновить значение на шине
    CTextOut::UpdateEngineBus(ui->mDVal, engine);

    //обновить значения входных сигналов
    CTextOut::UpdateAluYVal(ui->mCt1WrVal,  engine, CDcmcAlu2::Y_CT1_WR );
    CTextOut::UpdateAluYVal(ui->mCt1IncVal, engine, CDcmcAlu2::Y_CT1_INC);
    CTextOut::UpdateAluYVal(ui->mRg1WrVal,  engine, CDcmcAlu2::Y_RG1_WR );
    CTextOut::UpdateAluYVal(ui->mRg1ShrVal, engine, CDcmcAlu2::Y_RG1_SHR);
    CTextOut::UpdateAluYVal(ui->mRg2WrVal,  engine, CDcmcAlu2::Y_RG2_WR );
    CTextOut::UpdateAluYVal(ui->mRg2ShlVal, engine, CDcmcAlu2::Y_RG2_SHL);
    CTextOut::UpdateAluYVal(ui->mRg3RstVal, engine, CDcmcAlu2::Y_RG3_RST);
    CTextOut::UpdateAluYVal(ui->mRg3WrVal,  engine, CDcmcAlu2::Y_RG3_WR );
    CTextOut::UpdateAluYVal(ui->mMs1SelVal, engine, CDcmcAlu2::Y_MS1_SEL);
    CTextOut::UpdateAluYVal(ui->mMs1NotVal, engine, CDcmcAlu2::Y_SM1_C_MS1_NOT);
    CTextOut::UpdateAluYVal(ui->mSm1CVal,   engine, CDcmcAlu2::Y_SM1_C_MS1_NOT);
    CTextOut::UpdateAluYVal(ui->mBd1OutVal, engine, CDcmcAlu2::Y_BD1_OUT);
    CTextOut::UpdateAluYVal(ui->mBd2OutVal, engine, CDcmcAlu2::Y_BD2_OUT);

    //обновить сумматор
    CTextOut::UpdateAluSm2nVal(ui->mSm1OutVal, engine, 1);

    //обновить мультиплексор
    CTextOut::UpdateAluMs2nVal(ui->mMs1Val, engine, 1);

    //обновить инвертор
    CTextOut::UpdateAluXor2nVal(ui->mXor1Val, engine, 1);

    //обновить выходы буферных усилителей
    CTextOut::UpdateAluBusDriverVal(ui->mBd1Val, engine, 1, CDcmcAlu2::Y_BD1_OUT);
    CTextOut::UpdateAluBusDriverVal(ui->mBd2Val, engine, 2, CDcmcAlu2::Y_BD2_OUT);
}

void CDcmcWay2Widget::UpdateHints(const CEngineModel *engine) {
    //обновить обозначения управляющих сигналов
    CTextOut::UpdateAluPhysicalYHint(ui->mCt1WrHint,  engine, CDcmcAlu2::Y_CT1_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mCt1IncHint, engine, CDcmcAlu2::Y_CT1_INC);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg1WrHint,  engine, CDcmcAlu2::Y_RG1_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg1ShrHint, engine, CDcmcAlu2::Y_RG1_SHR);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg2WrHint,  engine, CDcmcAlu2::Y_RG2_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg3RstHint, engine, CDcmcAlu2::Y_RG3_RST);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg3WrHint,  engine, CDcmcAlu2::Y_RG3_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg2ShlHint, engine, CDcmcAlu2::Y_RG2_SHL);
    CTextOut::UpdateAluPhysicalYHint(ui->mSm1CHint,   engine, CDcmcAlu2::Y_SM1_C_MS1_NOT);
    CTextOut::UpdateAluPhysicalYHint(ui->mMs1SelHint, engine, CDcmcAlu2::Y_MS1_SEL);
    CTextOut::UpdateAluPhysicalYHint(ui->mMs1NotHint, engine, CDcmcAlu2::Y_SM1_C_MS1_NOT);
    CTextOut::UpdateAluPhysicalYHint(ui->mBd1OutHint, engine, CDcmcAlu2::Y_BD1_OUT);
    CTextOut::UpdateAluPhysicalYHint(ui->mBd2OutHint, engine, CDcmcAlu2::Y_BD2_OUT);

    //обновить обозначения осведомительных сигналов
    CTextOut::UpdateAluPhysicalPHint(ui->mCt1Out3Hint,  engine, CDcmcAlu2::P_CT1_3);
    CTextOut::UpdateAluPhysicalPHint(ui->mRg1Out0Hint,  engine, CDcmcAlu2::P_RG1_0);
    CTextOut::UpdateAluPhysicalPHint(ui->mRg1Out7Hint,  engine, CDcmcAlu2::P_RG1_7);
    CTextOut::UpdateAluPhysicalPHint(ui->mRg2Out15Hint, engine, CDcmcAlu2::P_RG2_15);

    //обновить обозначение входа замещения разряда первого регистра
    CTextOut::UpdateAluPhysicalPHint(ui->mRg1LvHint, engine, CDcmcAlu2::P_RG1_0);
}

