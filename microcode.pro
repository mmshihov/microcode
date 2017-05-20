#-------------------------------------------------
#
# Project created by QtCreator 2016-09-28T09:04:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = microcode
TEMPLATE = app


SOURCES += main.cpp\
        cmicrocodemainwindow.cpp \
    cbitblock.cpp \
    cengine.cpp \
    cfunctionalunit.cpp \
    celectronicunits.cpp \
    cengineerror.cpp \
    cromeditordelegate.cpp \
    cromtablemodel.cpp \
    ctestvector.cpp \
    models/mul/PCS1/cpcs1testvector.cpp \
    models/mul/PCS1/cpcs1textsource.cpp \
    csignalpermutation.cpp \
    calu.cpp \
    cmcu.cpp \
    ccpu.cpp \
    models/mul/PCS1/cpcs1firstwidget.cpp \
    cmilifourstateselect.cpp \
    cmilitwostateselect.cpp \
    cmoorefourstateselect.cpp \
    cmooretwostateselect.cpp \
    csignalvalue.cpp \
    csignalvaluegroup.cpp \
    cmcuwidget.cpp \
    cmanual.cpp \
    ctextout.cpp \
    chintwidget.cpp \
    chint.cpp \
    cenginewidget.cpp \
    cenginefactory.cpp \
    models/mul/PCS1/cpcs1mvcfactory.cpp \
    models/mul/PCS1/cpcs1inputdialog.cpp \
    models/mul/PCS1/cpcs1alu1.cpp \
    models/mul/PCS1/cpcs1alu2.cpp \
    models/mul/PCS1/cpcs1way2widget.cpp \
    models/mul/PCS1/cpcs1alu3.cpp \
    models/mul/PCS1/cpcs1way3widget.cpp \
    models/mul/PCS1/cpcs1alu4.cpp \
    models/mul/PCS1/cpcs1way4widget.cpp \
    models/mul/DCMC/cdcmcalu1.cpp \
    models/mul/DCMC/cdcmcway1widget.cpp \
    models/mul/DCMC/cdcmctestvector.cpp \
    models/mul/DCMC/cdcmctextsource.cpp \
    models/mul/DCMC/cdcmcmvcfactory.cpp \
    models/mul/DCMC/cdcmcinputdialog.cpp \
    models/mul/DCMC/cdcmcalu2.cpp \
    models/mul/DCMC/cdcmcway2widget.cpp \
    models/mul/DCMC/cdcmcalu3.cpp \
    models/mul/DCMC/cdcmcway3widget.cpp \
    models/mul/DCMC/cdcmcalu4.cpp \
    models/mul/DCMC/cdcmcway4widget.cpp \
    models/mul/DCAC/cdcacmvcfactory.cpp \
    models/mul/DCAC/cdcacalu1.cpp \
    models/mul/DCAC/cdcactextsource.cpp \
    models/mul/DCAC/cdcacway1widget.cpp \
    models/mul/DCAC/cdcacway2widget.cpp \
    models/mul/DCAC/cdcacalu2.cpp \
    models/mul/DCAC/cdcacway3widget.cpp \
    models/mul/DCAC/cdcacalu3.cpp \
    models/mul/DCAC/cdcacalu4.cpp \
    models/mul/DCAC/cdcacway4widget.cpp \
    models/try/PC2DC/cpc2dctestvector.cpp \
    models/try/PC2DC/cpc2dcalu1.cpp \
    models/try/PC2DC/cpc2dcinputdialog.cpp \
    models/try/PC2DC/cpc2dctextsource.cpp \
    models/try/PC2DC/cpc2dcway1widget.cpp \
    models/try/PC2DC/cpc2dcmvcfactory.cpp \
    models/div/FZUS/cfzustestvector.cpp \
    models/div/FZUS/cfzusalu1.cpp \
    models/div/FZUS/cfzusinputdialog.cpp \
    models/div/FZUS/cfzusway1widget.cpp \
    models/div/FZUS/cfzusmvcfactory.cpp \
    models/div/FZUS/cfzustextsource.cpp \
    models/div/FZUS/cfzusalu2.cpp \
    models/div/FZUS/cfzusway2widget.cpp \
    models/div/FZUS/cfzusalu3.cpp \
    models/div/FZUS/cfzusway3widget.cpp \
    models/add/FADD/cfaddway1widget.cpp \
    models/add/FADD/cfaddtestvector.cpp \
    models/add/FADD/cfaddalu1.cpp \
    models/add/FADD/cfaddmvcfactory.cpp \
    models/add/FADD/cfaddtextsource.cpp \
    models/add/FADD/cfaddinputdialog.cpp \
    cindividualtask.cpp

HEADERS  += cmicrocodemainwindow.h \
    cbitblock.h \
    cengine.h \
    cfunctionalunit.h \
    celectronicunits.h \
    sharedptr.h \
    cengineerror.h \
    cromeditordelegate.h \
    cromtablemodel.h \
    ctestvector.h \
    models/mul/PCS1/cpcs1testvector.h \
    models/mul/PCS1/cpcs1textsource.h \
    csignalpermutation.h \
    calu.h \
    cmcu.h \
    ccpu.h \
    models/mul/PCS1/cpcs1firstwidget.h \
    cmilifourstateselect.h \
    cmilitwostateselect.h \
    cmoorefourstateselect.h \
    cmooretwostateselect.h \
    csignalvalue.h \
    csignalvaluegroup.h \
    cmcuwidget.h \
    cmanual.h \
    ctextout.h \
    chintwidget.h \
    chint.h \
    cenginewidget.h \
    cenginefactory.h \
    models/mul/PCS1/cpcs1mvcfactory.h \
    models/mul/PCS1/cpcs1inputdialog.h \
    models/mul/PCS1/cpcs1alu1.h \
    models/mul/PCS1/cpcs1alu2.h \
    models/mul/PCS1/cpcs1way2widget.h \
    models/mul/PCS1/cpcs1alu3.h \
    models/mul/PCS1/cpcs1way3widget.h \
    models/mul/PCS1/cpcs1alu4.h \
    models/mul/PCS1/cpcs1way4widget.h \
    models/mul/DCMC/cdcmcalu1.h \
    models/mul/DCMC/cdcmcway1widget.h \
    models/mul/DCMC/cdcmctestvector.h \
    models/mul/DCMC/cdcmctextsource.h \
    models/mul/DCMC/cdcmcmvcfactory.h \
    models/mul/DCMC/cdcmcinputdialog.h \
    models/mul/DCMC/cdcmcalu2.h \
    models/mul/DCMC/cdcmcway2widget.h \
    models/mul/DCMC/cdcmcalu3.h \
    models/mul/DCMC/cdcmcway3widget.h \
    models/mul/DCMC/cdcmcalu4.h \
    models/mul/DCMC/cdcmcway4widget.h \
    models/mul/DCAC/cdcactestvector.h \
    models/mul/DCAC/cdcacinputdialog.h \
    models/mul/DCAC/cdcacmvcfactory.h \
    models/mul/DCAC/cdcacalu1.h \
    models/mul/DCAC/cdcactextsource.h \
    models/mul/DCAC/cdcacway1widget.h \
    models/mul/DCAC/cdcacway2widget.h \
    models/mul/DCAC/cdcacalu2.h \
    models/mul/DCAC/cdcacway3widget.h \
    models/mul/DCAC/cdcacalu3.h \
    models/mul/DCAC/cdcacalu4.h \
    models/mul/DCAC/cdcacway4widget.h \
    models/try/PC2DC/cpc2dctestvector.h \
    models/try/PC2DC/cpc2dcalu1.h \
    models/try/PC2DC/cpc2dcinputdialog.h \
    models/try/PC2DC/cpc2dctextsource.h \
    models/try/PC2DC/cpc2dcway1widget.h \
    models/try/PC2DC/cpc2dcmvcfactory.h \
    models/div/FZUS/cfzustestvector.h \
    models/div/FZUS/cfzusalu1.h \
    models/div/FZUS/cfzusinputdialog.h \
    models/div/FZUS/cfzusway1widget.h \
    models/div/FZUS/cfzusmvcfactory.h \
    models/div/FZUS/cfzustextsource.h \
    models/div/FZUS/cfzusalu2.h \
    models/div/FZUS/cfzusway2widget.h \
    models/div/FZUS/cfzusalu3.h \
    models/div/FZUS/cfzusway3widget.h \
    models/add/FADD/cfaddway1widget.h \
    models/add/FADD/cfaddtestvector.h \
    models/add/FADD/cfaddalu1.h \
    models/add/FADD/cfaddmvcfactory.h \
    models/add/FADD/cfaddtextsource.h \
    models/add/FADD/cfaddinputdialog.h \
    version_number.h \
    cindividualtask.h

FORMS    += cmicrocodemainwindow.ui \
    models/mul/PCS1/cpcs1firstwidget.ui \
    cmilifourstateselect.ui \
    cmilitwostateselect.ui \
    cmoorefourstateselect.ui \
    cmooretwostateselect.ui \
    csignalvalue.ui \
    cmanual.ui \
    models/mul/PCS1/cpcs1inputdialog.ui \
    models/mul/PCS1/cpcs1way2widget.ui \
    models/mul/PCS1/cpcs1way3widget.ui \
    models/mul/PCS1/cpcs1way4widget.ui \
    models/mul/DCMC/cdcmcway1widget.ui \
    models/mul/DCMC/cdcmcinputdialog.ui \
    models/mul/DCMC/cdcmcway2widget.ui \
    models/mul/DCMC/cdcmcway3widget.ui \
    models/mul/DCMC/cdcmcway4widget.ui \
    models/mul/DCAC/cdcacway1widget.ui \
    models/mul/DCAC/cdcacway2widget.ui \
    models/mul/DCAC/cdcacway3widget.ui \
    models/mul/DCAC/cdcacway4widget.ui \
    models/try/PC2DC/cpc2dcinputdialog.ui \
    models/try/PC2DC/cpc2dcway1widget.ui \
    models/div/FZUS/cfzusinputdialog.ui \
    models/div/FZUS/cfzusway1widget.ui \
    models/div/FZUS/cfzusway2widget.ui \
    models/div/FZUS/cfzusway3widget.ui \
    models/add/FADD/cfaddway1widget.ui \
    models/add/FADD/cfaddinputdialog.ui

RESOURCES += \
    resources.qrc \
    models/mul/PCS1/pcs1resources.qrc \
    models/mul/DCMC/dcmcresources.qrc \
    models/mul/DCAC/dcacresources.qrc \
    models/try/PC2DC/pc2dcresources.qrc \
    models/div/FZUS/fzusresources.qrc \
    models/add/FADD/faddresources.qrc

OTHER_FILES += \
    TODO.txt

TRANSLATIONS += \
    translate/microcode_ru.ts
