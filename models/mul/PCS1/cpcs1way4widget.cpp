#include "cpcs1way4widget.h"
#include "ui_cpcs1way4widget.h"

#include "cpcs1alu4.h"

#include "../../../ccpu.h"
#include "../../../ctextout.h"

void CPcs1Way4EngineController::DoUpdateMemoryView() {
    mView->UpdateMemoryView(Engine());
}

void CPcs1Way4EngineController::DoUpdateLogicView() {
    mView->UpdateLogicView(Engine());
}

void CPcs1Way4EngineController::DoUpdateHintsView() {
    mView->UpdateHints(Engine());
}

CPcs1Way4Widget::CPcs1Way4Widget(CEngineModel* engine, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CPcs1Way4Widget),
    mController(this)
{
    ui->setupUi(this);

    engine->AppendController(&mController);
    UpdateHints(Engine());
}

CPcs1Way4Widget::~CPcs1Way4Widget() {
    delete ui;
}

void CPcs1Way4Widget::UpdateMemoryView(const CEngineModel *engine) {
    //обновить значения выходов элементов памяти
    CTextOut::UpdateAluCounterVal(ui->mCt1Val, engine, 1);

    CTextOut::UpdateAluRegisterVal(ui->mRg1Val, engine, 1);
    CTextOut::UpdateAluRegister2nVal(ui->mRg2Val, engine, 2);

    CTextOut::UpdateAluRegister2nVal(ui->mRg3Val, engine, 3);

    CTextOut::UpdateAluTriggerVal(ui->mT1Val, engine, 1);
    CTextOut::UpdateAluTriggerVal(ui->mT2Val, engine, 2);

    //обновить значения осведомительных сигналов, снимаемых с элементов памяти
    CTextOut::UpdateAluPVal(ui->mCt1Out3Val, engine, CPcs1Alu4::P_CT1_3);
    CTextOut::UpdateAluPVal(ui->mRg1Out6Val, engine, CPcs1Alu4::P_RG1_6);
}

void CPcs1Way4Widget::UpdateLogicView(const CEngineModel *engine) {
    //обновить значение на шине
    CTextOut::UpdateEngineBus(ui->mDVal, engine);

    //обновить значения входных сигналов
    CTextOut::UpdateAluYVal(ui->mCt1WrVal,  engine, CPcs1Alu4::Y_CT1_WR );
    CTextOut::UpdateAluYVal(ui->mCt1IncVal, engine, CPcs1Alu4::Y_CT1_INC);
    CTextOut::UpdateAluYVal(ui->mRg1WrVal,  engine, CPcs1Alu4::Y_RG1_WR );
    CTextOut::UpdateAluYVal(ui->mRg1ShlVal, engine, CPcs1Alu4::Y_RG1_SHL);
    CTextOut::UpdateAluYVal(ui->mRg2WrVal,  engine, CPcs1Alu4::Y_RG2_WR );
    CTextOut::UpdateAluYVal(ui->mRg3RstVal, engine, CPcs1Alu4::Y_RG3_RST);
    CTextOut::UpdateAluYVal(ui->mRg3WrVal,  engine, CPcs1Alu4::Y_RG3_WR );
    CTextOut::UpdateAluYVal(ui->mRg2ShrVal, engine, CPcs1Alu4::Y_RG2_SHR);
    CTextOut::UpdateAluYVal(ui->mT1CVal,    engine, CPcs1Alu4::Y_T1_C   );
    CTextOut::UpdateAluYVal(ui->mT2CVal,    engine, CPcs1Alu4::Y_T2_C   );
    CTextOut::UpdateAluYVal(ui->mBd1OutVal, engine, CPcs1Alu4::Y_BD1_OUT);
    CTextOut::UpdateAluYVal(ui->mBd2OutVal, engine, CPcs1Alu4::Y_BD2_OUT);

    //обновить выходы логики
    CTextOut::UpdateAluLogicVal(ui->mAndOutVal, engine, CPcs1Alu4::AND_SIGN);
    CTextOut::UpdateAluLogicVal(ui->mOrOutVal,  engine, CPcs1Alu4::OR_RG3);
    CTextOut::UpdateAluLogicVal(ui->mXorOutVal, engine, CPcs1Alu4::XOR_T1_T2);

    //обновить сумматор
    CTextOut::UpdateAluSm2nVal(ui->mSm1OutVal, engine, 1);

    //обновить выходы буферных усилителей
    CTextOut::UpdateAluBusDriverVal(ui->mBd1Val, engine, 1, CPcs1Alu4::Y_BD1_OUT);
    CTextOut::UpdateAluBusDriverVal(ui->mBd2Val, engine, 2, CPcs1Alu4::Y_BD2_OUT);
}

void CPcs1Way4Widget::UpdateHints(const CEngineModel *engine) {
    //обновить обозначения управляющих сигналов
    CTextOut::UpdateAluPhysicalYHint(ui->mCt1WrHint,  engine, CPcs1Alu4::Y_CT1_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mCt1IncHint, engine, CPcs1Alu4::Y_CT1_INC);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg1WrHint,  engine, CPcs1Alu4::Y_RG1_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg1ShlHint, engine, CPcs1Alu4::Y_RG1_SHL);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg2WrHint,  engine, CPcs1Alu4::Y_RG2_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg3RstHint, engine, CPcs1Alu4::Y_RG3_RST);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg3WrHint,  engine, CPcs1Alu4::Y_RG3_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg2ShrHint, engine, CPcs1Alu4::Y_RG2_SHR);
    CTextOut::UpdateAluPhysicalYHint(ui->mT1CHint,    engine, CPcs1Alu4::Y_T1_C   );
    CTextOut::UpdateAluPhysicalYHint(ui->mT2CHint,    engine, CPcs1Alu4::Y_T2_C   );
    CTextOut::UpdateAluPhysicalYHint(ui->mBd1OutHint, engine, CPcs1Alu4::Y_BD1_OUT);
    CTextOut::UpdateAluPhysicalYHint(ui->mBd2OutHint, engine, CPcs1Alu4::Y_BD2_OUT);

    //обновить обозначения осведомительных сигналов
    CTextOut::UpdateAluPhysicalPHint(ui->mCt1Out3Hint, engine, CPcs1Alu4::P_CT1_3);
    CTextOut::UpdateAluPhysicalPHint(ui->mRg1Out6Hint, engine, CPcs1Alu4::P_RG1_6);
}
