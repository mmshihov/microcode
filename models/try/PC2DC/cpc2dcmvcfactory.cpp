#include "cpc2dcmvcfactory.h"

#include "cpc2dcway1widget.h"

#include "cpc2dcalu1.h"

#include "cpc2dctestvector.h"
#include "cpc2dctextsource.h"

#include "../../../cengine.h"
#include "../../../cmcuwidget.h"
#include "../../../chintwidget.h"
#include "../../../cenginewidget.h"


CEngineMvcItem CPc2DcMvcFactory::Way1() {
    CEngineModel *engine = new CEngineModel(5, 1, new CPc2DcAlu1(),
                                            new CPc2DcTestVector(),
                                            new CPc2DcHint_Way1());

    CHintWidget *hint = new CHintWidget(engine);
    CPc2DcWay1Widget *alu = new CPc2DcWay1Widget(engine);
    CMcuWidget *manualMcu = new CMcuWidget(CEngineModel::MANUAL_MCU, engine);
    CMcuWidget *miliMcu = new CMcuWidget(CEngineModel::MILI_MCU, engine);
    CMcuWidget *mooreMcu = new CMcuWidget(CEngineModel::MOORE_MCU, engine);

    CEngineWidget *widget = new CEngineWidget(engine, alu, hint, manualMcu, miliMcu, mooreMcu);

    return CEngineMvcItem(CPc2DcTextSource::NameWay1(), engine, widget);
}
