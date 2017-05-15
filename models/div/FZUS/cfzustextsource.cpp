#include "cfzustextsource.h"

#include "cfzusalu1.h"
#include "cfzusalu2.h"
#include "cfzusalu3.h"

#include "../../../ccpu.h"


CFzusTextSource::CFzusTextSource(QObject *parent) :
    QObject(parent) {}

QString CFzusTextSource::PhysicalY_Way1(unsigned int index) {
    switch (index) {
    case (CCpu::READY_IN):  return tr("'READY' to CPU");
    case (CCpu::RESULT_IN): return tr("'RESULT' to CPU");
    case (CFzusAlu1::Y_CT1_WR      + CCpu::IN_COUNT): return tr("Write to CT1");
    case (CFzusAlu1::Y_CT1_INC     + CCpu::IN_COUNT): return tr("CT1:=CT1+1");
    case (CFzusAlu1::Y_RG1_RST     + CCpu::IN_COUNT): return tr("RG1:=0");
    case (CFzusAlu1::Y_RG1_WR      + CCpu::IN_COUNT): return tr("Write to RG1");
    case (CFzusAlu1::Y_RG1_RG2_SHR + CCpu::IN_COUNT): return tr("Shift RG1,RG2 right");
    case (CFzusAlu1::Y_RG2_RST     + CCpu::IN_COUNT): return tr("RG2:=0");
    case (CFzusAlu1::Y_RG2_WR      + CCpu::IN_COUNT): return tr("Write to RG2");
    case (CFzusAlu1::Y_RG3_RST     + CCpu::IN_COUNT): return tr("RG3:=0");
    case (CFzusAlu1::Y_RG3_WR      + CCpu::IN_COUNT): return tr("Write to RG3");
    case (CFzusAlu1::Y_RG3_SHL     + CCpu::IN_COUNT): return tr("Shift RG3 left");
    case (CFzusAlu1::Y_SM1_C_XR1_NOT + CCpu::IN_COUNT): return tr("Add/Subtract");
    case (CFzusAlu1::Y_BD1_OUT     + CCpu::IN_COUNT): return tr("D=BD1");
    case (CFzusAlu1::Y_BD2_OUT     + CCpu::IN_COUNT): return tr("D=BD2");
    case (CFzusAlu1::Y_BD3_OUT     + CCpu::IN_COUNT): return tr("D=BD3");
    default: break;
    }
    return QString();
}

QString CFzusTextSource::PhysicalP_Way1(unsigned int index) {
    switch (index) {
    case (CCpu::BUS_OUT):  return tr("'BUS' from CPU");
    case (CCpu::TASK_OUT): return tr("'TASK' from CPU");
    case (CFzusAlu1::P_CT1_3  + CCpu::OUT_COUNT): return tr("CT1[3] - stop condition");
    case (CFzusAlu1::P_RG3_16 + CCpu::OUT_COUNT): return tr("RG3[16] - analysis");
    default: break;
    }
    return QString();
}

QString CFzusTextSource::NameWay1() {
    return tr("Unsigned division: Universal");
}


QString CFzusTextSource::PhysicalY_Way2(unsigned int index) {
    switch (index) {
    case (CCpu::READY_IN):  return tr("'READY' to CPU");
    case (CCpu::RESULT_IN): return tr("'RESULT' to CPU");
    case (CFzusAlu2::Y_CT1_WR      + CCpu::IN_COUNT): return tr("Write to CT1");
    case (CFzusAlu2::Y_CT1_INC     + CCpu::IN_COUNT): return tr("CT1:=CT1+1");
    case (CFzusAlu2::Y_RG1_WR      + CCpu::IN_COUNT): return tr("Write to RG1");
    case (CFzusAlu2::Y_RG2_WR      + CCpu::IN_COUNT): return tr("Write to RG2");
    case (CFzusAlu2::Y_RG2_RG3_SHL + CCpu::IN_COUNT): return tr("Shift RG1,RG2 left");
    case (CFzusAlu2::Y_SM1_C_XR1_NOT + CCpu::IN_COUNT): return tr("Add/Subtract");
    case (CFzusAlu2::Y_RG3_RST     + CCpu::IN_COUNT): return tr("RG3:=0");
    case (CFzusAlu2::Y_RG3_WR      + CCpu::IN_COUNT): return tr("Write to RG3");
    case (CFzusAlu2::Y_RG4_SHL     + CCpu::IN_COUNT): return tr("Shift RG4 left");
    case (CFzusAlu2::Y_BD1_OUT     + CCpu::IN_COUNT): return tr("D=BD1");
    case (CFzusAlu2::Y_BD2_OUT     + CCpu::IN_COUNT): return tr("D=BD2");
    default: break;
    }
    return QString();
}

QString CFzusTextSource::PhysicalP_Way2(unsigned int index) {
    switch (index) {
    case (CCpu::BUS_OUT):  return tr("'BUS' from CPU");
    case (CCpu::TASK_OUT): return tr("'TASK' from CPU");
    case (CFzusAlu2::P_CT1_3 + CCpu::OUT_COUNT): return tr("CT1[3] - stop condition");
    case (CFzusAlu2::P_RG3_8 + CCpu::OUT_COUNT): return tr("RG3[8] - analysis");
    default: break;
    }
    return QString();
}

QString CFzusTextSource::NameWay2() {
    return tr("Unsigned division: 1st way");
}


QString CFzusTextSource::PhysicalY_Way3(unsigned int index) {
    switch (index) {
    case (CCpu::READY_IN):  return tr("'READY' to CPU");
    case (CCpu::RESULT_IN): return tr("'RESULT' to CPU");
    case (CFzusAlu3::Y_CT1_WR      + CCpu::IN_COUNT): return tr("Write to CT1");
    case (CFzusAlu3::Y_CT1_INC     + CCpu::IN_COUNT): return tr("CT1:=CT1+1");
    case (CFzusAlu3::Y_RG1_RST     + CCpu::IN_COUNT): return tr("RG1:=0");
    case (CFzusAlu3::Y_RG1_WR      + CCpu::IN_COUNT): return tr("Write to RG1");
    case (CFzusAlu3::Y_RG1_RG2_SHR + CCpu::IN_COUNT): return tr("Shift RG1,RG2 right");
    case (CFzusAlu3::Y_RG2_RST     + CCpu::IN_COUNT): return tr("RG2:=0");
    case (CFzusAlu3::Y_RG2_WR      + CCpu::IN_COUNT): return tr("Write to RG2");
    case (CFzusAlu3::Y_RG3_RST     + CCpu::IN_COUNT): return tr("RG3:=0");
    case (CFzusAlu3::Y_RG3_WR      + CCpu::IN_COUNT): return tr("Write to RG3");
    case (CFzusAlu3::Y_SM1_C_XR1_NOT + CCpu::IN_COUNT): return tr("Add/Subtract");
    case (CFzusAlu3::Y_BD1_OUT     + CCpu::IN_COUNT): return tr("D=BD1");
    case (CFzusAlu3::Y_BD2_OUT     + CCpu::IN_COUNT): return tr("D=BD2");
    default: break;
    }
    return QString();
}

QString CFzusTextSource::PhysicalP_Way3(unsigned int index) {
    switch (index) {
    case (CCpu::BUS_OUT):  return tr("'BUS' from CPU");
    case (CCpu::TASK_OUT): return tr("'TASK' from CPU");
    case (CFzusAlu3::P_CT1_3 + CCpu::OUT_COUNT): return tr("CT1[3] - stop condition");
    case (CFzusAlu3::P_RG3_16 + CCpu::OUT_COUNT): return tr("RG3[16] - analysis");
    default: break;
    }
    return QString();
}

QString CFzusTextSource::NameWay3() {
    return tr("Unsigned division: 2nd way");
}


