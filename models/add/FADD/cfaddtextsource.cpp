#include "cfaddtextsource.h"

#include "cfaddalu1.h"

#include "../../../ccpu.h"

CFaddTextSource::CFaddTextSource(QObject *parent) :
    QObject(parent) {}

QString CFaddTextSource::PhysicalY_Way1(unsigned int index) {
    switch (index) {
    case (CCpu::READY_IN):  return tr("'READY' to CPU");
    case (CCpu::RESULT_IN): return tr("'RESULT' to CPU");
    case (CFaddAlu1::Y_RG1_WR        + CCpu::IN_COUNT): return tr("Write to RG1");
    case (CFaddAlu1::Y_RG1_SHR       + CCpu::IN_COUNT): return tr("Shift RG1 right");
    case (CFaddAlu1::Y_RG2_RST       + CCpu::IN_COUNT): return tr("Shift RG1 left");
    case (CFaddAlu1::Y_RG2_WR        + CCpu::IN_COUNT): return tr("Write to RG2");
    case (CFaddAlu1::Y_RG2_SHR       + CCpu::IN_COUNT): return tr("Shift RG2 right");
    case (CFaddAlu1::Y_RG2_SHL       + CCpu::IN_COUNT): return tr("Shift RG2 left");
    case (CFaddAlu1::Y_CT1_RST       + CCpu::IN_COUNT): return tr("CT1:=0");
    case (CFaddAlu1::Y_CT1_WR        + CCpu::IN_COUNT): return tr("Write to CT1");
    case (CFaddAlu1::Y_CT1_INC       + CCpu::IN_COUNT): return tr("CT1:=CT1+1");
    case (CFaddAlu1::Y_CT1_DEC       + CCpu::IN_COUNT): return tr("CT1:=CT1-1");
    case (CFaddAlu1::Y_CT2_WR        + CCpu::IN_COUNT): return tr("Write to CT2");
    case (CFaddAlu1::Y_CT2_INC       + CCpu::IN_COUNT): return tr("CT2:=CT2+1");
    case (CFaddAlu1::Y_CT2_DEC       + CCpu::IN_COUNT): return tr("CT2:=CT2-1");
    case (CFaddAlu1::Y_XR1_NOT_SM2_C + CCpu::IN_COUNT): return tr("Add/Subtract");
    case (CFaddAlu1::Y_MS1_SEL0      + CCpu::IN_COUNT): return tr("Error code select 0");
    case (CFaddAlu1::Y_MS1_SEL1      + CCpu::IN_COUNT): return tr("Error code select 1");
    case (CFaddAlu1::Y_BD1_OUT       + CCpu::IN_COUNT): return tr("D=BD1");
    case (CFaddAlu1::Y_BD2_OUT       + CCpu::IN_COUNT): return tr("D=BD2");
    default: break;
    }
    return QString();
}

QString CFaddTextSource::PhysicalP_Way1(unsigned int index) {
    switch (index) {
    case (CCpu::BUS_OUT):  return tr("'BUS' from CPU");
    case (CCpu::TASK_OUT): return tr("'TASK' from CPU");
    case (CFaddAlu1::P_CT1_7              + CCpu::OUT_COUNT): return tr("CT1[7] - Sign(c) #1");
    case (CFaddAlu1::P_CT1_6              + CCpu::OUT_COUNT): return tr("CT1[6] - Sign(c) #0");
    case (CFaddAlu1::P_CT1_IS_GT_10       + CCpu::OUT_COUNT): return tr("CT1 >= 10");
    case (CFaddAlu1::P_CT1_IS_LT_MINUS_10 + CCpu::OUT_COUNT): return tr("CT1 <= -10");
    case (CFaddAlu1::P_CT1_IS_ZERO        + CCpu::OUT_COUNT): return tr("CT1 != 0");
    case (CFaddAlu1::P_RG2_10             + CCpu::OUT_COUNT): return tr("RG2[10] - Sign(m) #1");
    case (CFaddAlu1::P_RG2_9              + CCpu::OUT_COUNT): return tr("RG2[9] - Sign(m) #0");
    case (CFaddAlu1::P_RG2_IS_ZERO        + CCpu::OUT_COUNT): return tr("RG2 != 0");
    default: break;
    }
    return QString();
}

QString CFaddTextSource::NameWay1() {
    return tr("Floating point addition");
}
