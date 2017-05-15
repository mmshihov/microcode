#include "cenginefactory.h"

#include "models/mul/PCS1/cpcs1mvcfactory.h"
#include "models/mul/DCMC/cdcmcmvcfactory.h"
#include "models/mul/DCAC/cdcacmvcfactory.h"
#include "models/try/PC2DC/cpc2dcmvcfactory.h"
#include "models/div/FZUS/cfzusmvcfactory.h"
#include "models/add/FADD/cfaddmvcfactory.h"


CEngineMvcItem::CEngineMvcItem(QString name,
                               CEngineModel *engineModel,
                               QWidget *engineView)
    : mName(name)
    , mEngineModel(engineModel)
    , mEngineView(engineView)
{}


CEngineMvcItem CEngineFactory::Pcs1_Way1()  {return CPcs1MvcFactory::Way1();}
CEngineMvcItem CEngineFactory::Pcs1_Way2()  {return CPcs1MvcFactory::Way2();}
CEngineMvcItem CEngineFactory::Pcs1_Way3()  {return CPcs1MvcFactory::Way3();}
CEngineMvcItem CEngineFactory::Pcs1_Way4()  {return CPcs1MvcFactory::Way4();}


CEngineMvcItem CEngineFactory::Dcmc_Way1()  {return CDcmcMvcFactory::Way1();}
CEngineMvcItem CEngineFactory::Dcmc_Way2()  {return CDcmcMvcFactory::Way2();}
CEngineMvcItem CEngineFactory::Dcmc_Way3()  {return CDcmcMvcFactory::Way3();}
CEngineMvcItem CEngineFactory::Dcmc_Way4()  {return CDcmcMvcFactory::Way4();}


CEngineMvcItem CEngineFactory::Dcac_Way1()  {return CDcacMvcFactory::Way1();}
CEngineMvcItem CEngineFactory::Dcac_Way2()  {return CDcacMvcFactory::Way2();}
CEngineMvcItem CEngineFactory::Dcac_Way3()  {return CDcacMvcFactory::Way3();}
CEngineMvcItem CEngineFactory::Dcac_Way4()  {return CDcacMvcFactory::Way4();}

CEngineMvcItem CEngineFactory::Pc2Dc_Way1() {return CPc2DcMvcFactory::Way1();}

CEngineMvcItem CEngineFactory::Fzus_Way1()  {return CFzusMvcFactory::Way1();}
CEngineMvcItem CEngineFactory::Fzus_Way2()  {return CFzusMvcFactory::Way2();}
CEngineMvcItem CEngineFactory::Fzus_Way3()  {return CFzusMvcFactory::Way3();}

CEngineMvcItem CEngineFactory::Fadd_Way1()  {return CFaddMvcFactory::Way1();}
