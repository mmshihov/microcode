#include "cfaddway1widget.h"
#include "ui_cfaddway1widget.h"

#include "cfaddalu1.h"

#include "../../../ccpu.h"
#include "../../../ctextout.h"

void CFaddWay1EngineController::DoUpdateMemoryView() {
    mView->UpdateMemoryView(Engine());
}

void CFaddWay1EngineController::DoUpdateLogicView() {
    mView->UpdateLogicView(Engine());
}

void CFaddWay1EngineController::DoUpdateHintsView() {
    mView->UpdateHints(Engine());
}


//-----------------------------------------------------------------------

CFaddWay1Widget::CFaddWay1Widget(CEngineModel* engine, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFaddWay1Widget),
    mController(this)
{
    ui->setupUi(this);

    engine->AppendController(&mController);
    UpdateHints(Engine());
}

CFaddWay1Widget::~CFaddWay1Widget() {
    delete ui;
}

void CFaddWay1Widget::UpdateMemoryView(const CEngineModel *engine) {
    //обновить значения выходов элементов памяти
    CTextOut::UpdateAluCounterVal(ui->mCt1Val, engine, 1);
    CTextOut::UpdateAluCounterVal(ui->mCt2Val, engine, 2);

    CTextOut::UpdateAluRegisterVal(ui->mRg1Val, engine, 1);
    CTextOut::UpdateAluRegisterVal(ui->mRg2Val, engine, 2);

    //обновить значения осведомительных сигналов, снимаемых с элементов памяти
    CTextOut::UpdateAluPVal(ui->mCt1Out7Val,  engine, CFaddAlu1::P_CT1_7);
    CTextOut::UpdateAluPVal(ui->mCt1Out6Val,  engine, CFaddAlu1::P_CT1_6);

    CTextOut::UpdateAluPVal(ui->mRg2Out10Val, engine, CFaddAlu1::P_RG2_10);
    CTextOut::UpdateAluPVal(ui->mRg2Out9Val,  engine, CFaddAlu1::P_RG2_9);

    CTextOut::UpdateAluPVal(ui->mCt1IsGt10Val,    engine, CFaddAlu1::P_CT1_IS_GT_10);
    CTextOut::UpdateAluPVal(ui->mCt1IsLtMns10Val, engine, CFaddAlu1::P_CT1_IS_LT_MINUS_10);
    CTextOut::UpdateAluPVal(ui->mCt1IsZeroVal,    engine, CFaddAlu1::P_CT1_IS_ZERO);

    CTextOut::UpdateAluPVal(ui->mRg2IsZeroVal, engine, CFaddAlu1::P_RG2_IS_ZERO);
}

void CFaddWay1Widget::UpdateLogicView(const CEngineModel *engine) {
    //обновить значение на шине
    CTextOut::UpdateEngineBus(ui->mDVal, engine);

    //обновить значения управляющих сигналов
    CTextOut::UpdateAluYVal(ui->mRg1WrVal,   engine, CFaddAlu1::Y_RG1_WR );
    CTextOut::UpdateAluYVal(ui->mRg1ShrVal,  engine, CFaddAlu1::Y_RG1_SHR);

    CTextOut::UpdateAluYVal(ui->mCt1RstVal,  engine, CFaddAlu1::Y_CT1_RST);
    CTextOut::UpdateAluYVal(ui->mCt1WrVal,   engine, CFaddAlu1::Y_CT1_WR );
    CTextOut::UpdateAluYVal(ui->mCt1IncVal,  engine, CFaddAlu1::Y_CT1_INC);
    CTextOut::UpdateAluYVal(ui->mCt1DecVal,  engine, CFaddAlu1::Y_CT1_DEC);

    CTextOut::UpdateAluYVal(ui->mCt2WrVal,   engine, CFaddAlu1::Y_CT2_WR );
    CTextOut::UpdateAluYVal(ui->mCt2IncVal,  engine, CFaddAlu1::Y_CT2_INC);
    CTextOut::UpdateAluYVal(ui->mCt2DecVal,  engine, CFaddAlu1::Y_CT2_DEC);

    CTextOut::UpdateAluYVal(ui->mXor1NotVal, engine, CFaddAlu1::Y_XR1_NOT_SM2_C);

    CTextOut::UpdateAluYVal(ui->mRg2RstVal,  engine, CFaddAlu1::Y_RG2_RST);
    CTextOut::UpdateAluYVal(ui->mRg2WrVal,   engine, CFaddAlu1::Y_RG2_WR );
    CTextOut::UpdateAluYVal(ui->mRg2ShrVal,  engine, CFaddAlu1::Y_RG2_SHR);
    CTextOut::UpdateAluYVal(ui->mRg2ShlVal,  engine, CFaddAlu1::Y_RG2_SHL);

    CTextOut::UpdateAluY2Val(ui->mMs1SelVal, engine, CFaddAlu1::Y_MS1_SEL1, CFaddAlu1::Y_MS1_SEL0);

    CTextOut::UpdateAluYVal(ui->mBd1OutVal,  engine, CFaddAlu1::Y_BD1_OUT);
    CTextOut::UpdateAluYVal(ui->mBd2OutVal,  engine, CFaddAlu1::Y_BD2_OUT);

    //обновить мультиплексор
    CTextOut::UpdateAluMsHexVal(ui->mMs1OutVal, engine, 1);

    //обновить сумматоры
    CTextOut::UpdateAluSmVal(ui->mSm1OutVal, engine, 1);
    CTextOut::UpdateAluSmVal(ui->mSm2OutVal, engine, 2);

    //обновить инвертор
    CTextOut::UpdateAluXorVal(ui->mXor1Val, engine, 1);

    //обновить выходы буферных усилителей
    CTextOut::UpdateAluBusDriverVal(ui->mBd1Val, engine, 1, CFaddAlu1::Y_BD1_OUT);
    CTextOut::UpdateAluBusDriverHexVal(ui->mBd2Val, engine, 2, CFaddAlu1::Y_BD2_OUT);
}

void CFaddWay1Widget::UpdateHints(const CEngineModel *engine) {
    //обновить обозначения управляющих сигналов
    CTextOut::UpdateAluPhysicalYHint(ui->mRg1WrHint,   engine, CFaddAlu1::Y_RG1_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg1ShrHint,  engine, CFaddAlu1::Y_RG1_SHR);

    CTextOut::UpdateAluPhysicalYHint(ui->mCt1RstHint,  engine, CFaddAlu1::Y_CT1_RST);
    CTextOut::UpdateAluPhysicalYHint(ui->mCt1WrHint,   engine, CFaddAlu1::Y_CT1_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mCt1IncHint,  engine, CFaddAlu1::Y_CT1_INC);
    CTextOut::UpdateAluPhysicalYHint(ui->mCt1DecHint,  engine, CFaddAlu1::Y_CT1_DEC);

    CTextOut::UpdateAluPhysicalYHint(ui->mCt2WrHint,   engine, CFaddAlu1::Y_CT2_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mCt2IncHint,  engine, CFaddAlu1::Y_CT2_INC);
    CTextOut::UpdateAluPhysicalYHint(ui->mCt2DecHint,  engine, CFaddAlu1::Y_CT2_DEC);

    CTextOut::UpdateAluPhysicalYHint(ui->mXor1NotHint, engine, CFaddAlu1::Y_XR1_NOT_SM2_C);

    CTextOut::UpdateAluPhysicalYHint(ui->mRg2RstHint,  engine, CFaddAlu1::Y_RG2_RST);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg2WrHint,   engine, CFaddAlu1::Y_RG2_WR );
    CTextOut::UpdateAluPhysicalYHint(ui->mRg2ShrHint,  engine, CFaddAlu1::Y_RG2_SHR);
    CTextOut::UpdateAluPhysicalYHint(ui->mRg2ShlHint,  engine, CFaddAlu1::Y_RG2_SHL);

    CTextOut::UpdateAluPhysicalY2Hint(ui->mMs1SelHint, engine, CFaddAlu1::Y_MS1_SEL1, CFaddAlu1::Y_MS1_SEL0);

    CTextOut::UpdateAluPhysicalYHint(ui->mBd1OutHint,  engine, CFaddAlu1::Y_BD1_OUT);
    CTextOut::UpdateAluPhysicalYHint(ui->mBd2OutHint,  engine, CFaddAlu1::Y_BD2_OUT);

    //обновить обозначения осведомительных сигналов
    CTextOut::UpdateAluPhysicalPHint(ui->mCt1Out7Hint,  engine, CFaddAlu1::P_CT1_7);
    CTextOut::UpdateAluPhysicalPHint(ui->mCt1Out6Hint,  engine, CFaddAlu1::P_CT1_6);

    CTextOut::UpdateAluPhysicalPHint(ui->mRg2Out10Hint, engine, CFaddAlu1::P_RG2_10);
    CTextOut::UpdateAluPhysicalPHint(ui->mRg2Out9Hint,  engine, CFaddAlu1::P_RG2_9);

    CTextOut::UpdateAluPhysicalPHint(ui->mCt1IsGt10Hint,    engine, CFaddAlu1::P_CT1_IS_GT_10);
    CTextOut::UpdateAluPhysicalPHint(ui->mCt1IsLtMns10Hint, engine, CFaddAlu1::P_CT1_IS_LT_MINUS_10);
    CTextOut::UpdateAluPhysicalPHint(ui->mCt1IsZeroHint,    engine, CFaddAlu1::P_CT1_IS_ZERO);

    CTextOut::UpdateAluPhysicalPHint(ui->mRg2IsZeroHint, engine, CFaddAlu1::P_RG2_IS_ZERO);
}

