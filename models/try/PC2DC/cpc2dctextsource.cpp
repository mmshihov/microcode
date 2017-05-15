#include "cpc2dctextsource.h"

#include "cpc2dcalu1.h"

#include "../../../ccpu.h"


CPc2DcTextSource::CPc2DcTextSource(QObject *parent) :
    QObject(parent) {}

QString CPc2DcTextSource::PhysicalY_Way1(unsigned int index) {
    switch (index) {
    case (CCpu::READY_IN):  return tr("'READY' to CPU");
    case (CCpu::RESULT_IN): return tr("'RESULT' to CPU");
    case (CPc2DcAlu1::Y_RG1_WR  + CCpu::IN_COUNT): return tr("Write to RG1");
    case (CPc2DcAlu1::Y_XR1_NOT + CCpu::IN_COUNT): return tr("Invert modulo");
    case (CPc2DcAlu1::Y_CT1_WR  + CCpu::IN_COUNT): return tr("Write to CT1");
    case (CPc2DcAlu1::Y_CT1_INC + CCpu::IN_COUNT): return tr("CT1:=CT1+1");
    case (CPc2DcAlu1::Y_BD1_OUT + CCpu::IN_COUNT): return tr("D=BD1");
    default: break;
    }
    return QString();
}

QString CPc2DcTextSource::PhysicalP_Way1(unsigned int index) {
    switch (index) {
    case (CCpu::BUS_OUT):  return tr("'BUS' from CPU");
    case (CCpu::TASK_OUT): return tr("'TASK' from CPU");
    case (CPc2DcAlu1::P_RG1_7 + CCpu::OUT_COUNT): return tr("RG1[7] - analysis");
    default: break;
    }
    return QString();
}

QString CPc2DcTextSource::NameWay1() {
    return tr("Direct to Two's compliment (hardline)");
}

