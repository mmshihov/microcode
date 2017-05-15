#ifndef CDCACWAY3WIDGET_H
#define CDCACWAY3WIDGET_H

#include <QWidget>

#include "../../../cengine.h"

namespace Ui {
class CDcacWay3Widget;
}


class QLabel;
class CDcacWay3Widget;


class CDcacWay3EngineController : public CEngineController {
public:
    CDcacWay3EngineController(CDcacWay3Widget *view) : CEngineController() {mView = view;}

protected:
    virtual void DoUpdateMemoryView();
    virtual void DoUpdateLogicView();
    virtual void DoUpdateHintsView();
    virtual void DoUpdateModeView() {}
    virtual void DoUpdateMcuTypeView() {}

private:
    CDcacWay3Widget *mView;
};


class CDcacWay3Widget : public QWidget {
    Q_OBJECT
    
public:
    explicit CDcacWay3Widget(CEngineModel* engine, QWidget *parent = 0);
    ~CDcacWay3Widget();
    
    void UpdateMemoryView(const CEngineModel* engine);
    void UpdateLogicView(const CEngineModel* engine);
    void UpdateHints(const CEngineModel* engine);

private:
    Ui::CDcacWay3Widget *ui;

    CDcacWay3EngineController mController;

    const CEngineModel *Engine() const {return mController.Engine();}
};

#endif // CDCACWAY3WIDGET_H
