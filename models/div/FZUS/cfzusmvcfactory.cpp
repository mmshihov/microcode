#include "cfzusmvcfactory.h"

#include "cfzusway1widget.h"
#include "cfzusway2widget.h"
#include "cfzusway3widget.h"

#include "cfzusalu1.h"
#include "cfzusalu2.h"
#include "cfzusalu3.h"

#include "cfzustestvector.h"
#include "cfzustextsource.h"

#include "../../../cengine.h"
#include "../../../cmcuwidget.h"
#include "../../../chintwidget.h"
#include "../../../cenginewidget.h"


CEngineMvcItem CFzusMvcFactory::Way1() {
    CEngineModel *engine = new CEngineModel(5, 1, new CFzusAlu1(),
                                            new CFzusTestVector(),
                                            new CFzusHint_Way1());

    CHintWidget *hint = new CHintWidget(engine);
    CFzusWay1Widget *alu = new CFzusWay1Widget(engine);
    CMcuWidget *manualMcu = new CMcuWidget(CEngineModel::MANUAL_MCU, engine);
    CMcuWidget *miliMcu = new CMcuWidget(CEngineModel::MILI_MCU, engine);
    CMcuWidget *mooreMcu = new CMcuWidget(CEngineModel::MOORE_MCU, engine);

    CEngineWidget *widget = new CEngineWidget(engine, alu, hint, manualMcu, miliMcu, mooreMcu);

    return CEngineMvcItem(CFzusTextSource::NameWay1(), engine, widget);
}

CEngineMvcItem CFzusMvcFactory::Way2() {
    CEngineModel *engine = new CEngineModel(5, 1, new CFzusAlu2(),
                                            new CFzusTestVector(),
                                            new CFzusHint_Way2());

    CHintWidget *hint = new CHintWidget(engine);
    CFzusWay2Widget *alu = new CFzusWay2Widget(engine);
    CMcuWidget *manualMcu = new CMcuWidget(CEngineModel::MANUAL_MCU, engine);
    CMcuWidget *miliMcu = new CMcuWidget(CEngineModel::MILI_MCU, engine);
    CMcuWidget *mooreMcu = new CMcuWidget(CEngineModel::MOORE_MCU, engine);

    CEngineWidget *widget = new CEngineWidget(engine, alu, hint, manualMcu, miliMcu, mooreMcu);

    return CEngineMvcItem(CFzusTextSource::NameWay2(), engine, widget);
}

CEngineMvcItem CFzusMvcFactory::Way3() {
    CEngineModel *engine = new CEngineModel(5, 1, new CFzusAlu3(),
                                            new CFzusTestVector(),
                                            new CFzusHint_Way3());

    CHintWidget *hint = new CHintWidget(engine);
    CFzusWay3Widget *alu = new CFzusWay3Widget(engine);
    CMcuWidget *manualMcu = new CMcuWidget(CEngineModel::MANUAL_MCU, engine);
    CMcuWidget *miliMcu = new CMcuWidget(CEngineModel::MILI_MCU, engine);
    CMcuWidget *mooreMcu = new CMcuWidget(CEngineModel::MOORE_MCU, engine);

    CEngineWidget *widget = new CEngineWidget(engine, alu, hint, manualMcu, miliMcu, mooreMcu);

    return CEngineMvcItem(CFzusTextSource::NameWay3(), engine, widget);
}
