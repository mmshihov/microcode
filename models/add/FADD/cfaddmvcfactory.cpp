#include "cfaddmvcfactory.h"

#include "cfaddway1widget.h"

#include "cfaddalu1.h"

#include "cfaddtestvector.h"
#include "cfaddtextsource.h"

#include "../../../cengine.h"
#include "../../../cmcuwidget.h"
#include "../../../chintwidget.h"
#include "../../../cenginewidget.h"

CEngineMvcItem CFaddMvcFactory::Way1() {
    CEngineModel *engine = new CEngineModel(6, 1, new CFaddAlu1(),
                                            new CFaddTestVector(),
                                            new CFaddHint_Way1());

    CHintWidget *hint = new CHintWidget(engine);
    CFaddWay1Widget *alu = new CFaddWay1Widget(engine);
    CMcuWidget *manualMcu = new CMcuWidget(CEngineModel::MANUAL_MCU, engine);
    CMcuWidget *miliMcu = new CMcuWidget(CEngineModel::MILI_MCU, engine);
    CMcuWidget *mooreMcu = new CMcuWidget(CEngineModel::MOORE_MCU, engine);

    CEngineWidget *widget = new CEngineWidget(engine, alu, hint, manualMcu, miliMcu, mooreMcu);

    return CEngineMvcItem(CFaddTextSource::NameWay1(), engine, widget);
}
