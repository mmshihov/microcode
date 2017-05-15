#ifndef CMILIFOURSTATESELECT_H
#define CMILIFOURSTATESELECT_H

#include <QWidget>
#include "cmcu.h"

namespace Ui {
class CMiliFourStateSelect;
}

class CEngineModel;
class CMiliFourStateSelect;

class CMili4McuController : public CMcuController {
public:
    CMili4McuController(CMiliFourStateSelect *view):CMcuController() {mView = view;}

protected:
    virtual void DoUpdateLogicView(const CEngineModel* engine);
    virtual void DoUpdateMemoryView(const CEngineModel* engine);
    virtual void DoUpdateHintsView(const CEngineModel* engine);

private:
    CMiliFourStateSelect *mView;
};

class CMiliFourStateSelect : public QWidget {
    Q_OBJECT
    
public:
    explicit CMiliFourStateSelect(QWidget *parent = 0);
    ~CMiliFourStateSelect();

    void UpdateMemoryView(const CEngineModel* engine);
    void UpdateLogicView(const CEngineModel* engine);
    void UpdateHintsView(const CEngineModel* engine);

    CMcuController *McuController() {return &mMcuController;}

private:
    Ui::CMiliFourStateSelect *ui;

    CMili4McuController mMcuController;

    void UpdateRG(const CEngineModel* engine);

    void UpdateMS1(const CEngineModel* engine);
    void UpdateMS2(const CEngineModel* engine);

    void UpdateY(const CEngineModel* engine);
};

#endif // CMILIFOURSTATESELECT_H
