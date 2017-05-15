#ifndef CDCMCWAY3WIDGET_H
#define CDCMCWAY3WIDGET_H

#include <QWidget>

#include "../../../cengine.h"

namespace Ui {
class CDcmcWay3Widget;
}



class QLabel;
class CDcmcWay3Widget;



class CDcmcWay3EngineController : public CEngineController {
public:
    CDcmcWay3EngineController(CDcmcWay3Widget *view) : CEngineController() {mView = view;}

protected:
    virtual void DoUpdateMemoryView();
    virtual void DoUpdateLogicView();
    virtual void DoUpdateHintsView();
    virtual void DoUpdateModeView() {}
    virtual void DoUpdateMcuTypeView() {}

private:
    CDcmcWay3Widget *mView;
};


class CDcmcWay3Widget : public QWidget {
    Q_OBJECT
    
public:
    explicit CDcmcWay3Widget(CEngineModel* engine, QWidget *parent = 0);
    ~CDcmcWay3Widget();
    
    void UpdateMemoryView(const CEngineModel* engine);
    void UpdateLogicView(const CEngineModel* engine);
    void UpdateHints(const CEngineModel* engine);

private:
    Ui::CDcmcWay3Widget *ui;

    CDcmcWay3EngineController mController;

    const CEngineModel *Engine() const {return mController.Engine();}
};

#endif // CDCMCWAY3WIDGET_H
