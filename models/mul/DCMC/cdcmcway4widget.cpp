#include "cdcmcway4widget.h"
#include "ui_cdcmcway4widget.h"

#include "cdcmcalu4.h"

#include "../../../ccpu.h"
#include "../../../ctextout.h"

void CDcmcWay4EngineController::DoUpdateMemoryView() {
    mView->UpdateMemoryView(Engine());
}

void CDcmcWay4EngineController::DoUpdateLogicView() {
    mView->UpdateLogicView(Engine());
}

void CDcmcWay4EngineController::DoUpdateHintsView() {
    mView->UpdateHints(Engine());
}


CDcmcWay4Widget::CDcmcWay4Widget(CEngineModel* engine, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CDcmcWay4Widget),
    mController(this)
{
    ui->setupUi(this);

    engine->AppendController(&mController);
    UpdateHints(Engine());
}

CDcmcWay4Widget::~CDcmcWay4Widget() {
    delete ui;
}

void CDcmcWay4Widget::UpdateMemoryView(const CEngineModel *engine) {
    //обновить значения выходов элементов памяти
    CTextOut::UpdateAluCounterVal(ui->mCt1Val, engine, 1);

    CTextOut::UpdateAluRegisterVal(ui->mRg1Val, engine, 1);
    CTextOut::UpdateAluRegister2nVal(ui->mRg2Val, engine, 2);
    CTextOut::UpdateAluRegister2nVal(ui->mRg3Val, engine, 3);

    //обновить значения осведомительных сигналов, снимаемых с элементов памяти
    CTextOut::UpdateAluPVal(ui->mCt1Out3Val,  engine, CDcmcAlu4::P_CT1_3);
    CTextOut::UpdateAluPVal(ui->mRg1Out7Val,  engine, CDcmcAlu4::P_RG1_7);
    CTextOut::UpdateAluPVal(ui->mRg2Out15Val, engine, CDcmcAlu4::P_RG2_15);
}

void CDcmcWay4Widget::UpdateLogicView(const CEngineModel *engine) {
    //обновить значение на шине
    CTextOut::UpdateEngineBus(ui->mDVal, engine);

    //обновить значения входных сигналов
    CTextOut::UpdateAluYVal(ui->mCt1WrVal,  engine, CDcmcAlu4::Y_CT1_WR );
    CTextOut::UpdateAluYVal(ui->mCt1IncVal, engine, CDcmcAlu4::Y_CT1_INC);
    CTextOut::UpdateAluYVal(ui->mRg1WrVal,  engine, CDcmcAlu4::Y_RG1_WR );
    CTextOut::UpdateAluYVal(ui->mRg1ShlVal, engine, CDcmcAlu4::Y_RG1_SHL);
    CTextOut::UpdateAluYVal(ui->mRg2WrVal,  engine, CDcmcAlu4::Y_RG2_WR );
    CTextOut::UpdateAluYVal(ui->mRg2ShrVal, engine, CDcmcAlu4::Y_RG2_SHR);
    CTextOut::UpdateAluYVal(ui->mRg3RstVal, engine, CDcmcAlu4::Y_RG3_RST);
    CTextOut::UpdateAluYVal(ui->mRg3WrVal,  engine, CDcmcAlu4::Y_RG3_WR );
    CTextOut::UpdateAluYVal(ui->mMs1SelVal, engine, CDcmcAlu4::Y_MS1_SEL);
    CTextOut::UpdateAluYVal(ui->mMs1NotVal, engine, CDcmcAlu4::Y_SM1_C_MS1_NOT);
    CTextOut::UpdateAluYVal(ui->mSm1CVal,   engine, CDcmcAlu4::Y_SM1_C_MS1_NOT);
    CTextOut::UpdateAluYVal(ui->mBd1OutVal, engine, CDcmcAlu4::Y_BD1_OUT);
    CTextOut::UpdateAluYVal(ui->mBd2OutVal, engine, CDcmcAlu4::Y_BD2_OUT);

    //обновить сумматор
    CTextOut::UpdateAluSm2nVal(ui->mSm1OutVal, engine, 1);

    //обновить мультиплексор
    CTextOut::UpdateAluMs2nVal(ui->mMs1Val, engine, 1);

    //обновить инвертор
    CTextOut::UpdateAluXor2nVal(ui->mXor1Val, engine, 1);

    //обновить выходы буферных усилителей
    CTextOut::UpdateAluBusDriverVal(ui->mBd1Val, engine, 1, CDcmcAlu4::Y_BD1_OUT);
    CTextOut::UpdateAluBusDriverVal(ui->mBd2Val, engine, 2, CDcmcAlu4::Y_BD2_OUT);
}

void CDcmcWay4Widget::UpdateHints(const CEngineModel *engine) {
    //обновить обозначения управляющих сигналов
    CTextOut::UpdateAluPhysicalYHint(ui->mCt1WrHint,  engine, CDcmcAlu4::Y_CT1_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mCt1IncHint, engine, CDcmcAlu4::Y_CT1_INC);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg1WrHint,  engine, CDcmcAlu4::Y_RG1_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg1ShlHint, engine, CDcmcAlu4::Y_RG1_SHL);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg2WrHint,  engine, CDcmcAlu4::Y_RG2_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg3RstHint, engine, CDcmcAlu4::Y_RG3_RST);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg3WrHint,  engine, CDcmcAlu4::Y_RG3_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg2ShrHint, engine, CDcmcAlu4::Y_RG2_SHR);
    CTextOut::UpdateAluPhysicalYHint(ui->mSm1CHint,   engine, CDcmcAlu4::Y_SM1_C_MS1_NOT);
    CTextOut::UpdateAluPhysicalYHint(ui->mMs1SelHint, engine, CDcmcAlu4::Y_MS1_SEL);
    CTextOut::UpdateAluPhysicalYHint(ui->mMs1NotHint, engine, CDcmcAlu4::Y_SM1_C_MS1_NOT);
    CTextOut::UpdateAluPhysicalYHint(ui->mBd1OutHint, engine, CDcmcAlu4::Y_BD1_OUT);
    CTextOut::UpdateAluPhysicalYHint(ui->mBd2OutHint, engine, CDcmcAlu4::Y_BD2_OUT);

    //обновить обозначения осведомительных сигналов
    CTextOut::UpdateAluPhysicalPHint(ui->mCt1Out3Hint,  engine, CDcmcAlu4::P_CT1_3);
    CTextOut::UpdateAluPhysicalPHint(ui->mRg1Out7Hint,  engine, CDcmcAlu4::P_RG1_7);
    CTextOut::UpdateAluPhysicalPHint(ui->mRg2Out15Hint, engine, CDcmcAlu4::P_RG2_15);
}

