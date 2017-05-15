#include "cpcs1firstwidget.h"
#include "ui_cpcs1firstwidget.h"

#include "cpcs1alu1.h"

#include "../../../ccpu.h"
#include "../../../ctextout.h"

void CPcs1FirstEngineController::DoUpdateMemoryView() {
    mView->UpdateMemoryView(Engine());
}

void CPcs1FirstEngineController::DoUpdateLogicView() {
    mView->UpdateLogicView(Engine());
}

void CPcs1FirstEngineController::DoUpdateHintsView() {
    mView->UpdateHints(Engine());
}

CPcs1FirstWidget::CPcs1FirstWidget(CEngineModel* engine, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CPcs1FirstWidget),
    mController(this)
{
    ui->setupUi(this);

    engine->AppendController(&mController);
    UpdateHints(Engine());
}

CPcs1FirstWidget::~CPcs1FirstWidget() {
    delete ui;
}

void CPcs1FirstWidget::UpdateMemoryView(const CEngineModel *engine) {
    //обновить значения выходов элементов памяти
    CTextOut::UpdateAluCounterVal(ui->mCt1Val, engine, 1);

    CTextOut::UpdateAluRegisterVal(ui->mRg1Val, engine, 1);
    CTextOut::UpdateAluRegisterVal(ui->mRg2Val, engine, 2);

    CTextOut::UpdateAluRegisterVal(ui->mRg3Val, engine, 3);
    CTextOut::UpdateAluRegisterVal(ui->mRg4Val, engine, 4);

    CTextOut::UpdateAluTriggerVal(ui->mT1Val, engine, 1);
    CTextOut::UpdateAluTriggerVal(ui->mT2Val, engine, 2);

    //обновить значения осведомительных сигналов, снимаемых с элементов памяти
    CTextOut::UpdateAluPVal(ui->mCt1Out3Val, engine, CPcs1Alu1::P_CT1_3);
    CTextOut::UpdateAluPVal(ui->mRg1Out0Val, engine, CPcs1Alu1::P_RG1_0);
}

void CPcs1FirstWidget::UpdateLogicView(const CEngineModel *engine) {
    //обновить значение на шине
    CTextOut::UpdateEngineBus(ui->mDVal, engine);

    //обновить значения входных сигналов
    CTextOut::UpdateAluYVal(ui->mCt1WrVal,  engine, CPcs1Alu1::Y_CT1_WR );
    CTextOut::UpdateAluYVal(ui->mCt1IncVal, engine, CPcs1Alu1::Y_CT1_INC);
    CTextOut::UpdateAluYVal(ui->mRg1WrVal,  engine, CPcs1Alu1::Y_RG1_WR );
    CTextOut::UpdateAluYVal(ui->mRg1ShrVal, engine, CPcs1Alu1::Y_RG1_SHR);
    CTextOut::UpdateAluYVal(ui->mRg2WrVal,  engine, CPcs1Alu1::Y_RG2_WR );
    CTextOut::UpdateAluYVal(ui->mRg3RstVal, engine, CPcs1Alu1::Y_RG3_RST);
    CTextOut::UpdateAluYVal(ui->mRg3WrVal,  engine, CPcs1Alu1::Y_RG3_WR );
    CTextOut::UpdateAluYVal(ui->mRg3ShrVal, engine, CPcs1Alu1::Y_RG3_RG4_SHR);
    CTextOut::UpdateAluYVal(ui->mRg4ShrVal, engine, CPcs1Alu1::Y_RG3_RG4_SHR);
    CTextOut::UpdateAluYVal(ui->mT1CVal,    engine, CPcs1Alu1::Y_T1_C   );
    CTextOut::UpdateAluYVal(ui->mT2CVal,    engine, CPcs1Alu1::Y_T2_C   );
    CTextOut::UpdateAluYVal(ui->mBd1OutVal, engine, CPcs1Alu1::Y_BD1_OUT);
    CTextOut::UpdateAluYVal(ui->mBd2OutVal, engine, CPcs1Alu1::Y_BD2_OUT);

    //обновить выходы логики
    CTextOut::UpdateAluLogicVal(ui->mAndOutVal, engine, CPcs1Alu1::AND_SIGN);
    CTextOut::UpdateAluLogicVal(ui->mOrOutVal,  engine, CPcs1Alu1::OR_RG3);
    CTextOut::UpdateAluLogicVal(ui->mXorOutVal, engine, CPcs1Alu1::XOR_T1_T2);

    //обновить сумматор
    CTextOut::UpdateAluSmVal(ui->mSm1OutVal, engine, 1);
    CTextOut::UpdateAluSmPVal(ui->mSm1PVal, engine, 1);

    //обновить выходы буферных усилителей
    CTextOut::UpdateAluBusDriverVal(ui->mBd1Val, engine, 1, CPcs1Alu1::Y_BD1_OUT);
    CTextOut::UpdateAluBusDriverVal(ui->mBd2Val, engine, 2, CPcs1Alu1::Y_BD2_OUT);
}

void CPcs1FirstWidget::UpdateHints(const CEngineModel *engine) {
    //обновить обозначения управляющих сигналов
    CTextOut::UpdateAluPhysicalYHint(ui->mCt1WrHint,  engine, CPcs1Alu1::Y_CT1_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mCt1IncHint, engine, CPcs1Alu1::Y_CT1_INC);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg1WrHint,  engine, CPcs1Alu1::Y_RG1_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg1ShrHint, engine, CPcs1Alu1::Y_RG1_SHR);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg2WrHint,  engine, CPcs1Alu1::Y_RG2_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg3RstHint, engine, CPcs1Alu1::Y_RG3_RST);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg3WrHint,  engine, CPcs1Alu1::Y_RG3_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg3ShrHint, engine, CPcs1Alu1::Y_RG3_RG4_SHR);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg4ShrHint, engine, CPcs1Alu1::Y_RG3_RG4_SHR);
    CTextOut::UpdateAluPhysicalYHint(ui->mT1CHint,    engine, CPcs1Alu1::Y_T1_C   );
    CTextOut::UpdateAluPhysicalYHint(ui->mT2CHint,    engine, CPcs1Alu1::Y_T2_C   );
    CTextOut::UpdateAluPhysicalYHint(ui->mBd1OutHint, engine, CPcs1Alu1::Y_BD1_OUT);
    CTextOut::UpdateAluPhysicalYHint(ui->mBd2OutHint, engine, CPcs1Alu1::Y_BD2_OUT);

    //обновить обозначения осведомительных сигналов
    CTextOut::UpdateAluPhysicalPHint(ui->mCt1Out3Hint, engine, CPcs1Alu1::P_CT1_3);
    CTextOut::UpdateAluPhysicalPHint(ui->mRg1Out0Hint, engine, CPcs1Alu1::P_RG1_0);
}
