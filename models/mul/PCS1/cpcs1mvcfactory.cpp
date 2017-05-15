#include "cpcs1mvcfactory.h"

#include "cpcs1firstwidget.h"
#include "cpcs1way2widget.h"
#include "cpcs1way3widget.h"
#include "cpcs1way4widget.h"

#include "cpcs1alu1.h"
#include "cpcs1alu2.h"
#include "cpcs1alu3.h"
#include "cpcs1alu4.h"

#include "cpcs1testvector.h"
#include "cpcs1textsource.h"

#include "../../../cengine.h"
#include "../../../cmcuwidget.h"
#include "../../../chintwidget.h"
#include "../../../cenginewidget.h"

CEngineMvcItem CPcs1MvcFactory::Way1() {
    CEngineModel *engine = new CEngineModel(5, 1, new CPcs1Alu1(),
                                            new CPcs1TestVector(),
                                            new CPcs1Hint_Way1());

    CHintWidget *hint = new CHintWidget(engine);
    CPcs1FirstWidget *alu = new CPcs1FirstWidget(engine);
    CMcuWidget *manualMcu = new CMcuWidget(CEngineModel::MANUAL_MCU, engine);
    CMcuWidget *miliMcu = new CMcuWidget(CEngineModel::MILI_MCU, engine);
    CMcuWidget *mooreMcu = new CMcuWidget(CEngineModel::MOORE_MCU, engine);

    CEngineWidget *widget = new CEngineWidget(engine, alu, hint, manualMcu, miliMcu, mooreMcu);

    return CEngineMvcItem(CPcs1TextSource::NameWay1(), engine, widget);
}

CEngineMvcItem CPcs1MvcFactory::Way2() {
    CEngineModel *engine = new CEngineModel(5, 1, new CPcs1Alu2(),
                                            new CPcs1TestVector(),
                                            new CPcs1Hint_Way2());

    CHintWidget *hint = new CHintWidget(engine);
    CPcs1Way2Widget *alu = new CPcs1Way2Widget(engine);
    CMcuWidget *manualMcu = new CMcuWidget(CEngineModel::MANUAL_MCU, engine);
    CMcuWidget *miliMcu = new CMcuWidget(CEngineModel::MILI_MCU, engine);
    CMcuWidget *mooreMcu = new CMcuWidget(CEngineModel::MOORE_MCU, engine);

    CEngineWidget *widget = new CEngineWidget(engine, alu, hint, manualMcu, miliMcu, mooreMcu);

    return CEngineMvcItem(CPcs1TextSource::NameWay2(), engine, widget);
}

CEngineMvcItem CPcs1MvcFactory::Way3() {
    CEngineModel *engine = new CEngineModel(5, 1, new CPcs1Alu3(),
                                            new CPcs1TestVector(),
                                            new CPcs1Hint_Way3());

    CHintWidget *hint = new CHintWidget(engine);
    CPcs1Way3Widget *alu = new CPcs1Way3Widget(engine);
    CMcuWidget *manualMcu = new CMcuWidget(CEngineModel::MANUAL_MCU, engine);
    CMcuWidget *miliMcu = new CMcuWidget(CEngineModel::MILI_MCU, engine);
    CMcuWidget *mooreMcu = new CMcuWidget(CEngineModel::MOORE_MCU, engine);

    CEngineWidget *widget = new CEngineWidget(engine, alu, hint, manualMcu, miliMcu, mooreMcu);

    return CEngineMvcItem(CPcs1TextSource::NameWay3(), engine, widget);
}

CEngineMvcItem CPcs1MvcFactory::Way4() {
    CEngineModel *engine = new CEngineModel(5, 1, new CPcs1Alu4(),
                                            new CPcs1TestVector(),
                                            new CPcs1Hint_Way4());

    CHintWidget *hint = new CHintWidget(engine);
    CPcs1Way4Widget *alu = new CPcs1Way4Widget(engine);
    CMcuWidget *manualMcu = new CMcuWidget(CEngineModel::MANUAL_MCU, engine);
    CMcuWidget *miliMcu = new CMcuWidget(CEngineModel::MILI_MCU, engine);
    CMcuWidget *mooreMcu = new CMcuWidget(CEngineModel::MOORE_MCU, engine);

    CEngineWidget *widget = new CEngineWidget(engine, alu, hint, manualMcu, miliMcu, mooreMcu);

    return CEngineMvcItem(CPcs1TextSource::NameWay4(), engine, widget);
}
