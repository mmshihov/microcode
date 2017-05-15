#include "cdcmcmvcfactory.h"

#include "cdcmcway1widget.h"
#include "cdcmcway2widget.h"
#include "cdcmcway3widget.h"
#include "cdcmcway4widget.h"

#include "cdcmcalu1.h"
#include "cdcmcalu2.h"
#include "cdcmcalu3.h"
#include "cdcmcalu4.h"

#include "cdcmctestvector.h"
#include "cdcmctextsource.h"

#include "../../../cengine.h"
#include "../../../cmcuwidget.h"
#include "../../../chintwidget.h"
#include "../../../cenginewidget.h"


CEngineMvcItem CDcmcMvcFactory::Way1() {
    CEngineModel *engine = new CEngineModel(5, 1, new CDcmcAlu1(),
                                            new CDcmcTestVector(),
                                            new CDcmcHint_Way1());

    CHintWidget *hint = new CHintWidget(engine);
    CDcmcWay1Widget *alu = new CDcmcWay1Widget(engine);
    CMcuWidget *manualMcu = new CMcuWidget(CEngineModel::MANUAL_MCU, engine);
    CMcuWidget *miliMcu = new CMcuWidget(CEngineModel::MILI_MCU, engine);
    CMcuWidget *mooreMcu = new CMcuWidget(CEngineModel::MOORE_MCU, engine);

    CEngineWidget *widget = new CEngineWidget(engine, alu, hint, manualMcu, miliMcu, mooreMcu);

    return CEngineMvcItem(CDcmcTextSource::NameWay1(), engine, widget);
}

CEngineMvcItem CDcmcMvcFactory::Way2() {
    CEngineModel *engine = new CEngineModel(5, 1, new CDcmcAlu2(),
                                            new CDcmcTestVector(),
                                            new CDcmcHint_Way2());

    CHintWidget *hint = new CHintWidget(engine);
    CDcmcWay2Widget *alu = new CDcmcWay2Widget(engine);
    CMcuWidget *manualMcu = new CMcuWidget(CEngineModel::MANUAL_MCU, engine);
    CMcuWidget *miliMcu = new CMcuWidget(CEngineModel::MILI_MCU, engine);
    CMcuWidget *mooreMcu = new CMcuWidget(CEngineModel::MOORE_MCU, engine);

    CEngineWidget *widget = new CEngineWidget(engine, alu, hint, manualMcu, miliMcu, mooreMcu);

    return CEngineMvcItem(CDcmcTextSource::NameWay2(), engine, widget);
}

CEngineMvcItem CDcmcMvcFactory::Way3() {
    CEngineModel *engine = new CEngineModel(5, 1, new CDcmcAlu3(),
                                            new CDcmcTestVector(),
                                            new CDcmcHint_Way3());

    CHintWidget *hint = new CHintWidget(engine);
    CDcmcWay3Widget *alu = new CDcmcWay3Widget(engine);
    CMcuWidget *manualMcu = new CMcuWidget(CEngineModel::MANUAL_MCU, engine);
    CMcuWidget *miliMcu = new CMcuWidget(CEngineModel::MILI_MCU, engine);
    CMcuWidget *mooreMcu = new CMcuWidget(CEngineModel::MOORE_MCU, engine);

    CEngineWidget *widget = new CEngineWidget(engine, alu, hint, manualMcu, miliMcu, mooreMcu);

    return CEngineMvcItem(CDcmcTextSource::NameWay3(), engine, widget);
}

CEngineMvcItem CDcmcMvcFactory::Way4() {
    CEngineModel *engine = new CEngineModel(5, 1, new CDcmcAlu4(),
                                            new CDcmcTestVector(),
                                            new CDcmcHint_Way4());

    CHintWidget *hint = new CHintWidget(engine);
    CDcmcWay4Widget *alu = new CDcmcWay4Widget(engine);
    CMcuWidget *manualMcu = new CMcuWidget(CEngineModel::MANUAL_MCU, engine);
    CMcuWidget *miliMcu = new CMcuWidget(CEngineModel::MILI_MCU, engine);
    CMcuWidget *mooreMcu = new CMcuWidget(CEngineModel::MOORE_MCU, engine);

    CEngineWidget *widget = new CEngineWidget(engine, alu, hint, manualMcu, miliMcu, mooreMcu);

    return CEngineMvcItem(CDcmcTextSource::NameWay4(), engine, widget);
}
