#include "cdcacmvcfactory.h"

#include "cdcacway1widget.h"
#include "cdcacway2widget.h"
#include "cdcacway3widget.h"
#include "cdcacway4widget.h"

#include "cdcacalu1.h"
#include "cdcacalu2.h"
#include "cdcacalu3.h"
#include "cdcacalu4.h"

#include "cdcactestvector.h"
#include "cdcactextsource.h"

#include "../../../cengine.h"
#include "../../../cmcuwidget.h"
#include "../../../chintwidget.h"
#include "../../../cenginewidget.h"


CEngineMvcItem CDcacMvcFactory::Way1() {
    CEngineModel *engine = new CEngineModel(5, 2, new CDcacAlu1(),
                                            new CDcacTestVector(),
                                            new CDcacHint_Way1());

    CHintWidget *hint = new CHintWidget(engine);
    CDcacWay1Widget *alu = new CDcacWay1Widget(engine);
    CMcuWidget *manualMcu = new CMcuWidget(CEngineModel::MANUAL_MCU, engine);
    CMcuWidget *miliMcu = new CMcuWidget(CEngineModel::MILI_MCU, engine);
    CMcuWidget *mooreMcu = new CMcuWidget(CEngineModel::MOORE_MCU, engine);

    CEngineWidget *widget = new CEngineWidget(engine, alu, hint, manualMcu, miliMcu, mooreMcu);

    return CEngineMvcItem(CDcacTextSource::NameWay1(), engine, widget);
}

CEngineMvcItem CDcacMvcFactory::Way2() {
    CEngineModel *engine = new CEngineModel(5, 2, new CDcacAlu2(),
                                            new CDcacTestVector(),
                                            new CDcacHint_Way2());

    CHintWidget *hint = new CHintWidget(engine);
    CDcacWay2Widget *alu = new CDcacWay2Widget(engine);
    CMcuWidget *manualMcu = new CMcuWidget(CEngineModel::MANUAL_MCU, engine);
    CMcuWidget *miliMcu = new CMcuWidget(CEngineModel::MILI_MCU, engine);
    CMcuWidget *mooreMcu = new CMcuWidget(CEngineModel::MOORE_MCU, engine);

    CEngineWidget *widget = new CEngineWidget(engine, alu, hint, manualMcu, miliMcu, mooreMcu);

    return CEngineMvcItem(CDcacTextSource::NameWay2(), engine, widget);
}

CEngineMvcItem CDcacMvcFactory::Way3() {
    CEngineModel *engine = new CEngineModel(5, 2, new CDcacAlu3(),
                                            new CDcacTestVector(),
                                            new CDcacHint_Way3());

    CHintWidget *hint = new CHintWidget(engine);
    CDcacWay3Widget *alu = new CDcacWay3Widget(engine);
    CMcuWidget *manualMcu = new CMcuWidget(CEngineModel::MANUAL_MCU, engine);
    CMcuWidget *miliMcu = new CMcuWidget(CEngineModel::MILI_MCU, engine);
    CMcuWidget *mooreMcu = new CMcuWidget(CEngineModel::MOORE_MCU, engine);

    CEngineWidget *widget = new CEngineWidget(engine, alu, hint, manualMcu, miliMcu, mooreMcu);

    return CEngineMvcItem(CDcacTextSource::NameWay3(), engine, widget);
}

CEngineMvcItem CDcacMvcFactory::Way4() {
    CEngineModel *engine = new CEngineModel(5, 2, new CDcacAlu4(),
                                            new CDcacTestVector(),
                                            new CDcacHint_Way4());

    CHintWidget *hint = new CHintWidget(engine);
    CDcacWay4Widget *alu = new CDcacWay4Widget(engine);
    CMcuWidget *manualMcu = new CMcuWidget(CEngineModel::MANUAL_MCU, engine);
    CMcuWidget *miliMcu = new CMcuWidget(CEngineModel::MILI_MCU, engine);
    CMcuWidget *mooreMcu = new CMcuWidget(CEngineModel::MOORE_MCU, engine);

    CEngineWidget *widget = new CEngineWidget(engine, alu, hint, manualMcu, miliMcu, mooreMcu);

    return CEngineMvcItem(CDcacTextSource::NameWay4(), engine, widget);
}
