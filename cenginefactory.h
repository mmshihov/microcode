#ifndef CENGINEFACTORY_H
#define CENGINEFACTORY_H

#include <QString>

class CEngineModel;
class QWidget;

class CEngineMvcItem {
public:
    CEngineMvcItem() : mEngineModel(0), mEngineView(0) {}
    CEngineMvcItem(QString name, CEngineModel *engineModel, QWidget *engineView);

    QString       Name() {return mName;}
    CEngineModel *EngineModel() {return mEngineModel;}
    QWidget      *EngineView() {return mEngineView;}

private:
    QString       mName;
    CEngineModel *mEngineModel;
    QWidget      *mEngineView;
};


class CEngineFactory {
public:
    CEngineFactory();

    static CEngineMvcItem Pcs1_Way1();
    static CEngineMvcItem Pcs1_Way2();
    static CEngineMvcItem Pcs1_Way3();
    static CEngineMvcItem Pcs1_Way4();

    static CEngineMvcItem Dcmc_Way1();
    static CEngineMvcItem Dcmc_Way2();
    static CEngineMvcItem Dcmc_Way3();
    static CEngineMvcItem Dcmc_Way4();

    static CEngineMvcItem Dcac_Way1();
    static CEngineMvcItem Dcac_Way2();
    static CEngineMvcItem Dcac_Way3();
    static CEngineMvcItem Dcac_Way4();

    static CEngineMvcItem Pc2Dc_Way1();

    static CEngineMvcItem Fzus_Way1();
    static CEngineMvcItem Fzus_Way2();
    static CEngineMvcItem Fzus_Way3();

    static CEngineMvcItem Fadd_Way1();
};

#endif // CENGINEFACTORY_H
