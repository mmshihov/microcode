#ifndef CMCUWIDGET_H
#define CMCUWIDGET_H

#include <QWidget>

#include "cengine.h"


class QTableView;
class CMcuWidget;
class CSignalValue;
class CRomTableModel;
class CMcuController;

class CMcuWidgetEngineController : public CEngineController {
public:
    CMcuWidgetEngineController(CMcuWidget *view) : CEngineController() {mView = view;}

protected:
    virtual void DoUpdateMemoryView();
    virtual void DoUpdateLogicView();
    virtual void DoUpdateHintsView();
    virtual void DoUpdateModeView();
    virtual void DoUpdateMcuTypeView();

private:
    CMcuWidget *mView;
};

class CMcuWidget : public QWidget {
    Q_OBJECT
public:
    static const int WIDGET_HEIGHT = 600;
    static const int WIDGET_WIDTH  = 400;

    explicit CMcuWidget(CEngineModel::TMcuType mcuType,
                        CEngineModel *model,
                        QWidget *parent = 0);

    CEngineModel::TMcuType  McuType() const {return mMcuType;}
    unsigned int            GroupDim() const {return mGroupDim;}
    unsigned int            ControlInputDim() const {return mControlInputDim;}
    unsigned int            ControlOutputDim() const {return mControlOutputDim;}

    void UpdateMemoryView(const CEngineModel* engine);
    void UpdateLogicView(const CEngineModel* engine);
    void UpdateHintsView(const CEngineModel* engine);
    void UpdateModeView(const CEngineModel* engine);

private:
    CEngineModel::TMcuType  mMcuType;
    unsigned int            mGroupDim;
    unsigned int            mControlInputDim;
    unsigned int            mControlOutputDim;

    CMcuWidgetEngineController mEngineController;
    CMcuController      *mMcuController;
    
    CSignalValue        **mInputValues;
    CSignalValue        **mOutputValues;
    CRomTableModel       *mRomModel;
    QTableView           *mRomTableView;

    void CreateUi(const CEngineModel *model);

    QWidget *CreateIoGroup(unsigned int groupIndex, unsigned int groupDim, CSignalValue **signalValues, const QString &hint);
    QWidget *CreateIoWidget(unsigned int groupIndex, unsigned int groupDim, CSignalValue **&signalValues, const QString &hint);
    QWidget *CreateInputWidget();
    QWidget *CreateOutputWidget();

    QWidget *CreateRomLabelWidget();
    QWidget *CreateRomWidget(const CEngineModel *model);
    QWidget *CreateMcuWidget();

    QWidget *CreateManualMcu();
    QWidget *CreateMiliMcu();
    QWidget *CreateMooreMcu();

    void UpdateSignalValues(const CEngineModel *engine);
    void UpdateRomSelection(const CEngineModel *engine);
    bool IsAutomaticExecution(const CEngineModel *engine) const;

    void ConnectSignalsToRomTable();

signals:
    
public slots:
    void UpdateCurrentRomAddressSlot(const QModelIndex& currIndex, const QModelIndex& prevIndex);
};

#endif // CMCUWIDGET_H
