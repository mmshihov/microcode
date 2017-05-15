#ifndef CHINTWIDGET_H
#define CHINTWIDGET_H

#include <QWidget>

#include "cengine.h"

class QLabel;
class QVBoxLayout;

class CHintWidget;


class CHintWidgetEngineController : public CEngineController {
public:
    CHintWidgetEngineController(CHintWidget *view) : CEngineController() {mView = view;}

protected:
    virtual void DoUpdateMemoryView() {}
    virtual void DoUpdateLogicView() {}
    virtual void DoUpdateHintsView();
    virtual void DoUpdateModeView() {}
    virtual void DoUpdateMcuTypeView() {}

private:
    CHintWidget *mView;
};


class CHintWidget : public QWidget {
    Q_OBJECT
public:
    static const int WIDGET_HEIGHT = 100;
    static const int WIDGET_WIDTH  = 1200;

    CHintWidget(CEngineModel *model, QWidget *parent = 0);

    void UpdateHints();

private:
    CHintWidgetEngineController mEngineController;

    QLabel **mMcuControlInputs;
    QLabel **mMcuControlOutputs;

    const CEngineModel *Engine() const {return mEngineController.Engine();}
    unsigned int ControlInputDim() const {return Engine()->McuControlInputDim();}
    unsigned int ControlOutputDim() const {return Engine()->McuControlOutputDim();}

    void CreateUi();
    void CreateLabels();
    void LayoutLabels();
    QVBoxLayout *CreateVerticalLayout() const;

signals:

public slots:

};

#endif // CHINTWIDGET_H
