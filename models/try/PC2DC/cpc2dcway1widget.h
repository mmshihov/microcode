#ifndef CPC2DCWAY1WIDGET_H
#define CPC2DCWAY1WIDGET_H

#include <QWidget>

#include "../../../cengine.h"

namespace Ui {
class CPc2DcWay1Widget;
}


class QLabel;
class CPc2DcWay1Widget;


class CPc2DcWay1EngineController : public CEngineController {
public:
    CPc2DcWay1EngineController(CPc2DcWay1Widget *view) : CEngineController() {mView = view;}

protected:
    virtual void DoUpdateMemoryView();
    virtual void DoUpdateLogicView();
    virtual void DoUpdateHintsView();
    virtual void DoUpdateModeView() {}
    virtual void DoUpdateMcuTypeView() {}

private:
    CPc2DcWay1Widget *mView;
};


class CPc2DcWay1Widget : public QWidget {
    Q_OBJECT
    
public:
    explicit CPc2DcWay1Widget(CEngineModel* engine, QWidget *parent = 0);
    ~CPc2DcWay1Widget();

    void UpdateMemoryView(const CEngineModel* engine);
    void UpdateLogicView(const CEngineModel* engine);
    void UpdateHints(const CEngineModel* engine);

private:
    Ui::CPc2DcWay1Widget *ui;

    CPc2DcWay1EngineController mController;

    const CEngineModel *Engine() const {return mController.Engine();}
};

#endif // CPC2DCWAY1WIDGET_H
