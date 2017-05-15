#include "cdcmctextsource.h"

#include "cdcmcalu1.h"
#include "cdcmcalu2.h"
#include "cdcmcalu3.h"
#include "cdcmcalu4.h"

#include "../../../ccpu.h"


CDcmcTextSource::CDcmcTextSource(QObject *parent) :
    QObject(parent) {}

QString CDcmcTextSource::PhysicalY_Way1(unsigned int index) {
    switch (index) {
    case (CCpu::READY_IN):  return tr("'READY' to CPU");
    case (CCpu::RESULT_IN): return tr("'RESULT' to CPU");
    case (CDcmcAlu1::Y_CT1_WR  + CCpu::IN_COUNT): return tr("Write to CT1");
    case (CDcmcAlu1::Y_CT1_INC + CCpu::IN_COUNT): return tr("CT1:=CT1+1");
    case (CDcmcAlu1::Y_RG1_WR  + CCpu::IN_COUNT): return tr("Write to RG1");
    case (CDcmcAlu1::Y_RG1_SHR + CCpu::IN_COUNT): return tr("Shift RG1 right");
    case (CDcmcAlu1::Y_RG2_WR  + CCpu::IN_COUNT): return tr("Write to RG2");
    case (CDcmcAlu1::Y_RG3_RST + CCpu::IN_COUNT): return tr("RG3:=0");
    case (CDcmcAlu1::Y_RG3_WR  + CCpu::IN_COUNT): return tr("Write to RG3");
    case (CDcmcAlu1::Y_RG3_RG4_SHR   + CCpu::IN_COUNT): return tr("Shift RG3,RG4 right");
    case (CDcmcAlu1::Y_MS1_SEL       + CCpu::IN_COUNT): return tr("RG1/RG2 select");
    case (CDcmcAlu1::Y_SM1_C_MS1_NOT + CCpu::IN_COUNT): return tr("Add/Subtract");
    case (CDcmcAlu1::Y_BD1_OUT + CCpu::IN_COUNT): return tr("D=BD1");
    case (CDcmcAlu1::Y_BD2_OUT + CCpu::IN_COUNT): return tr("D=BD2");
    default: break;
    }
    return QString();
}

QString CDcmcTextSource::PhysicalP_Way1(unsigned int index) {
    switch (index) {
    case (CCpu::BUS_OUT):  return tr("'BUS' from CPU");
    case (CCpu::TASK_OUT): return tr("'TASK' from CPU");
    case (CDcmcAlu1::P_CT1_3 + CCpu::OUT_COUNT): return tr("CT1[3] - stop condition");
    case (CDcmcAlu1::P_RG1_0 + CCpu::OUT_COUNT): return tr("RG1[0] - analysis");
    case (CDcmcAlu1::P_RG1_7 + CCpu::OUT_COUNT): return tr("RG1[7] - sign");
    case (CDcmcAlu1::P_RG2_7 + CCpu::OUT_COUNT): return tr("RG2[7] - sign");
    default: break;
    }
    return QString();
}

QString CDcmcTextSource::NameWay1() {
    return tr("Two's compliment (manual correction): 1st way");
}


QString CDcmcTextSource::PhysicalY_Way2(unsigned int index) {
    switch (index) {
    case (CCpu::READY_IN):  return tr("'READY' to CPU");
    case (CCpu::RESULT_IN): return tr("'RESULT' to CPU");
    case (CDcmcAlu2::Y_CT1_WR  + CCpu::IN_COUNT): return tr("Write to CT1");
    case (CDcmcAlu2::Y_CT1_INC + CCpu::IN_COUNT): return tr("CT1:=CT1+1");
    case (CDcmcAlu2::Y_RG1_WR  + CCpu::IN_COUNT): return tr("Write to RG1");
    case (CDcmcAlu2::Y_RG1_SHR + CCpu::IN_COUNT): return tr("Shift RG1 right");
    case (CDcmcAlu2::Y_RG2_WR  + CCpu::IN_COUNT): return tr("Write to RG2");
    case (CDcmcAlu2::Y_RG2_SHL + CCpu::IN_COUNT): return tr("Shift RG2 left");
    case (CDcmcAlu2::Y_RG3_RST + CCpu::IN_COUNT): return tr("RG3:=0");
    case (CDcmcAlu2::Y_RG3_WR  + CCpu::IN_COUNT): return tr("Write to RG3");
    case (CDcmcAlu2::Y_MS1_SEL + CCpu::IN_COUNT): return tr("RG1/RG2 select");
    case (CDcmcAlu2::Y_SM1_C_MS1_NOT + CCpu::IN_COUNT): return tr("Add/Subtract");
    case (CDcmcAlu2::Y_BD1_OUT + CCpu::IN_COUNT): return tr("D=BD1");
    case (CDcmcAlu2::Y_BD2_OUT + CCpu::IN_COUNT): return tr("D=BD2");
    default: break;
    }
    return QString();
}

QString CDcmcTextSource::PhysicalP_Way2(unsigned int index) {
    switch (index) {
    case (CCpu::BUS_OUT):  return tr("'BUS' from CPU");
    case (CCpu::TASK_OUT): return tr("'TASK' from CPU");
    case (CDcmcAlu2::P_CT1_3  + CCpu::OUT_COUNT): return tr("CT1[3] - stop condition");
    case (CDcmcAlu2::P_RG1_0  + CCpu::OUT_COUNT): return tr("RG1[0] - analysis");
    case (CDcmcAlu2::P_RG1_7  + CCpu::OUT_COUNT): return tr("RG1[7] - sign");
    case (CDcmcAlu2::P_RG2_15 + CCpu::OUT_COUNT): return tr("RG2[15] - sign");
    default: break;
    }
    return QString();
}

QString CDcmcTextSource::NameWay2() {
    return tr("Two's compliment (manual correction): 2nd way");
}


QString CDcmcTextSource::PhysicalY_Way3(unsigned int index) {
    switch (index) {
    case (CCpu::READY_IN):  return tr("'READY' to CPU");
    case (CCpu::RESULT_IN): return tr("'RESULT' to CPU");
    case (CDcmcAlu3::Y_CT1_WR  + CCpu::IN_COUNT): return tr("Write to CT1");
    case (CDcmcAlu3::Y_CT1_INC + CCpu::IN_COUNT): return tr("CT1:=CT1+1");
    case (CDcmcAlu3::Y_RG1_WR  + CCpu::IN_COUNT): return tr("Write to RG1");
    case (CDcmcAlu3::Y_RG1_SHL + CCpu::IN_COUNT): return tr("Shift RG1 left");
    case (CDcmcAlu3::Y_RG2_WR  + CCpu::IN_COUNT): return tr("Write to RG2");
    case (CDcmcAlu3::Y_RG3_RST + CCpu::IN_COUNT): return tr("RG3:=0");
    case (CDcmcAlu3::Y_RG3_WR  + CCpu::IN_COUNT): return tr("Write to RG3");
    case (CDcmcAlu3::Y_RG3_SHL + CCpu::IN_COUNT): return tr("Shift RG3 left");
    case (CDcmcAlu3::Y_MS1_SEL + CCpu::IN_COUNT): return tr("RG1/RG2 select");
    case (CDcmcAlu3::Y_SM1_C_MS1_NOT + CCpu::IN_COUNT): return tr("Add/Subtract");
    case (CDcmcAlu3::Y_BD1_OUT + CCpu::IN_COUNT): return tr("D=BD1");
    case (CDcmcAlu3::Y_BD2_OUT + CCpu::IN_COUNT): return tr("D=BD2");
    default: break;
    }
    return QString();
}

QString CDcmcTextSource::PhysicalP_Way3(unsigned int index) {
    switch (index) {
    case (CCpu::BUS_OUT):  return tr("'BUS' from CPU");
    case (CCpu::TASK_OUT): return tr("'TASK' from CPU");
    case (CDcmcAlu3::P_CT1_3 + CCpu::OUT_COUNT): return tr("CT1[3] - stop condition");
    case (CDcmcAlu3::P_RG1_7 + CCpu::OUT_COUNT): return tr("RG1[7] - sign,analysis");
    case (CDcmcAlu3::P_RG2_7 + CCpu::OUT_COUNT): return tr("RG2[7] - sign");
    default: break;
    }
    return QString();
}

QString CDcmcTextSource::NameWay3() {
    return tr("Two's compliment (manual correction): 3rd way");
}


QString CDcmcTextSource::PhysicalY_Way4(unsigned int index) {
    switch (index) {
    case (CCpu::READY_IN):  return tr("'READY' to CPU");
    case (CCpu::RESULT_IN): return tr("'RESULT' to CPU");
    case (CDcmcAlu4::Y_CT1_WR  + CCpu::IN_COUNT): return tr("Write to CT1");
    case (CDcmcAlu4::Y_CT1_INC + CCpu::IN_COUNT): return tr("CT1:=CT1+1");
    case (CDcmcAlu4::Y_RG1_WR  + CCpu::IN_COUNT): return tr("Write to RG1");
    case (CDcmcAlu4::Y_RG1_SHL + CCpu::IN_COUNT): return tr("Shift RG1 left");
    case (CDcmcAlu4::Y_RG2_WR  + CCpu::IN_COUNT): return tr("Write to RG2");
    case (CDcmcAlu4::Y_RG2_SHR + CCpu::IN_COUNT): return tr("Shift RG2 right");
    case (CDcmcAlu4::Y_RG3_RST + CCpu::IN_COUNT): return tr("RG3:=0");
    case (CDcmcAlu4::Y_RG3_WR  + CCpu::IN_COUNT): return tr("Write to RG3");
    case (CDcmcAlu4::Y_MS1_SEL + CCpu::IN_COUNT): return tr("RG1/RG2 select");
    case (CDcmcAlu4::Y_SM1_C_MS1_NOT + CCpu::IN_COUNT): return tr("Add/Subtract");
    case (CDcmcAlu4::Y_BD1_OUT + CCpu::IN_COUNT): return tr("D=BD1");
    case (CDcmcAlu4::Y_BD2_OUT + CCpu::IN_COUNT): return tr("D=BD2");
    default: break;
    }
    return QString();
}

QString CDcmcTextSource::PhysicalP_Way4(unsigned int index) {
    switch (index) {
    case (CCpu::BUS_OUT):  return tr("'BUS' from CPU");
    case (CCpu::TASK_OUT): return tr("'TASK' from CPU");
    case (CDcmcAlu4::P_CT1_3  + CCpu::OUT_COUNT): return tr("CT1[3] - stop condition");
    case (CDcmcAlu4::P_RG1_7  + CCpu::OUT_COUNT): return tr("RG1[7] - sign,analysis");
    case (CDcmcAlu4::P_RG2_15 + CCpu::OUT_COUNT): return tr("RG2[15] - sign");
    default: break;
    }
    return QString();
}

QString CDcmcTextSource::NameWay4() {
    return tr("Two's compliment (manual correction): 4th way");
}
