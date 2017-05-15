#include "cdcactextsource.h"


#include "cdcacalu1.h"
#include "cdcacalu2.h"
#include "cdcacalu3.h"
#include "cdcacalu4.h"

#include "../../../ccpu.h"


CDcacTextSource::CDcacTextSource(QObject *parent) :
    QObject(parent) {}

QString CDcacTextSource::PhysicalY_Way1(unsigned int index) {
    switch (index) {
    case (CCpu::READY_IN):  return tr("'READY' to CPU");
    case (CCpu::RESULT_IN): return tr("'RESULT' to CPU");
    case (CDcacAlu1::Y_CT1_WR  + CCpu::IN_COUNT): return tr("Write to CT1");
    case (CDcacAlu1::Y_CT1_INC + CCpu::IN_COUNT): return tr("CT1:=CT1+1");
    case (CDcacAlu1::Y_RG1_WR  + CCpu::IN_COUNT): return tr("Write to RG1");
    case (CDcacAlu1::Y_RG1_SHR + CCpu::IN_COUNT): return tr("Shift RG1 right");
    case (CDcacAlu1::Y_RG2_WR  + CCpu::IN_COUNT): return tr("Write to RG2");
    case (CDcacAlu1::Y_RG3_RST + CCpu::IN_COUNT): return tr("RG3:=0");
    case (CDcacAlu1::Y_RG3_WR  + CCpu::IN_COUNT): return tr("Write to RG3");
    case (CDcacAlu1::Y_RG3_RG4_SHR   + CCpu::IN_COUNT): return tr("Shift RG3,RG4 right");
    case (CDcacAlu1::Y_SM1_C_RG2_NOT + CCpu::IN_COUNT): return tr("Add/Subtract");
    case (CDcacAlu1::Y_BD1_OUT + CCpu::IN_COUNT): return tr("D=BD1");
    case (CDcacAlu1::Y_BD2_OUT + CCpu::IN_COUNT): return tr("D=BD2");
    default: break;
    }
    return QString();
}

QString CDcacTextSource::PhysicalP_Way1(unsigned int index) {
    switch (index) {
    case (CCpu::BUS_OUT):  return tr("'BUS' from CPU");
    case (CCpu::TASK_OUT): return tr("'TASK' from CPU");
    case (CDcacAlu1::P_CT1_3 + CCpu::OUT_COUNT): return tr("CT1[3] - stop condition");
    case (CDcacAlu1::P_RG1_0 + CCpu::OUT_COUNT): return tr("RG1[0] - analysis");
    case (CDcacAlu1::P_RG1_1 + CCpu::OUT_COUNT): return tr("RG1[1] - analysis");
    default: break;
    }
    return QString();
}

QString CDcacTextSource::NameWay1() {
    return tr("Two's compliment (auto correction): 1st way");
}


QString CDcacTextSource::PhysicalY_Way2(unsigned int index) {
    switch (index) {
    case (CCpu::READY_IN):  return tr("'READY' to CPU");
    case (CCpu::RESULT_IN): return tr("'RESULT' to CPU");
    case (CDcacAlu2::Y_CT1_WR  + CCpu::IN_COUNT): return tr("Write to CT1");
    case (CDcacAlu2::Y_CT1_INC + CCpu::IN_COUNT): return tr("CT1:=CT1+1");
    case (CDcacAlu2::Y_RG1_WR  + CCpu::IN_COUNT): return tr("Write to RG1");
    case (CDcacAlu2::Y_RG1_SHR + CCpu::IN_COUNT): return tr("Shift RG1 right");
    case (CDcacAlu2::Y_RG2_WR  + CCpu::IN_COUNT): return tr("Write to RG2");
    case (CDcacAlu2::Y_RG2_SHL + CCpu::IN_COUNT): return tr("Shift RG2 left");
    case (CDcacAlu2::Y_RG3_RST + CCpu::IN_COUNT): return tr("RG3:=0");
    case (CDcacAlu2::Y_RG3_WR  + CCpu::IN_COUNT): return tr("Write to RG3");
    case (CDcacAlu2::Y_SM1_C_RG2_NOT + CCpu::IN_COUNT): return tr("Add/Subtract");
    case (CDcacAlu2::Y_BD1_OUT + CCpu::IN_COUNT): return tr("D=BD1");
    case (CDcacAlu2::Y_BD2_OUT + CCpu::IN_COUNT): return tr("D=BD2");
    default: break;
    }
    return QString();
}

QString CDcacTextSource::PhysicalP_Way2(unsigned int index) {
    switch (index) {
    case (CCpu::BUS_OUT):  return tr("'BUS' from CPU");
    case (CCpu::TASK_OUT): return tr("'TASK' from CPU");
    case (CDcacAlu2::P_CT1_3 + CCpu::OUT_COUNT): return tr("CT1[3] - stop condition");
    case (CDcacAlu2::P_RG1_0 + CCpu::OUT_COUNT): return tr("RG1[0] - analysis");
    case (CDcacAlu2::P_RG1_1 + CCpu::OUT_COUNT): return tr("RG1[1] - analysis");
    default: break;
    }
    return QString();
}

QString CDcacTextSource::NameWay2() {
    return tr("Two's compliment (auto correction): 2nd way");
}


QString CDcacTextSource::PhysicalY_Way3(unsigned int index) {
    switch (index) {
    case (CCpu::READY_IN):  return tr("'READY' to CPU");
    case (CCpu::RESULT_IN): return tr("'RESULT' to CPU");
    case (CDcacAlu3::Y_CT1_WR  + CCpu::IN_COUNT): return tr("Write to CT1");
    case (CDcacAlu3::Y_CT1_INC + CCpu::IN_COUNT): return tr("CT1:=CT1+1");
    case (CDcacAlu3::Y_RG1_WR  + CCpu::IN_COUNT): return tr("Write to RG1");
    case (CDcacAlu3::Y_RG1_SHL + CCpu::IN_COUNT): return tr("Shift RG1 left");
    case (CDcacAlu3::Y_RG2_WR  + CCpu::IN_COUNT): return tr("Write to RG2");
    case (CDcacAlu3::Y_RG3_RST + CCpu::IN_COUNT): return tr("RG3:=0");
    case (CDcacAlu3::Y_RG3_WR  + CCpu::IN_COUNT): return tr("Write to RG3");
    case (CDcacAlu3::Y_RG3_SHL + CCpu::IN_COUNT): return tr("Shift RG3 left");
    case (CDcacAlu3::Y_SM1_C_RG2_NOT + CCpu::IN_COUNT): return tr("Add/Subtract");
    case (CDcacAlu3::Y_BD1_OUT + CCpu::IN_COUNT): return tr("D=BD1");
    case (CDcacAlu3::Y_BD2_OUT + CCpu::IN_COUNT): return tr("D=BD2");
    default: break;
    }
    return QString();
}

QString CDcacTextSource::PhysicalP_Way3(unsigned int index) {
    switch (index) {
    case (CCpu::BUS_OUT):  return tr("'BUS' from CPU");
    case (CCpu::TASK_OUT): return tr("'TASK' from CPU");
    case (CDcacAlu3::P_CT1_3 + CCpu::OUT_COUNT): return tr("CT1[3] - stop condition");
    case (CDcacAlu3::P_RG1_6 + CCpu::OUT_COUNT): return tr("RG1[6] - analysis");
    case (CDcacAlu3::P_RG1_7 + CCpu::OUT_COUNT): return tr("RG1[7] - analysis");
    default: break;
    }
    return QString();
}

QString CDcacTextSource::NameWay3() {
    return tr("Two's compliment (auto correction): 3rd way");
}


QString CDcacTextSource::PhysicalY_Way4(unsigned int index) {
    switch (index) {
    case (CCpu::READY_IN):  return tr("'READY' to CPU");
    case (CCpu::RESULT_IN): return tr("'RESULT' to CPU");
    case (CDcacAlu4::Y_CT1_WR  + CCpu::IN_COUNT): return tr("Write to CT1");
    case (CDcacAlu4::Y_CT1_INC + CCpu::IN_COUNT): return tr("CT1:=CT1+1");
    case (CDcacAlu4::Y_RG1_WR  + CCpu::IN_COUNT): return tr("Write to RG1");
    case (CDcacAlu4::Y_RG1_SHL + CCpu::IN_COUNT): return tr("Shift RG1 left");
    case (CDcacAlu4::Y_RG2_WR  + CCpu::IN_COUNT): return tr("Write to RG2");
    case (CDcacAlu4::Y_RG2_SHR + CCpu::IN_COUNT): return tr("Shift RG2 right");
    case (CDcacAlu4::Y_RG3_RST + CCpu::IN_COUNT): return tr("RG3:=0");
    case (CDcacAlu4::Y_RG3_WR  + CCpu::IN_COUNT): return tr("Write to RG3");
    case (CDcacAlu4::Y_SM1_C_RG2_NOT + CCpu::IN_COUNT): return tr("Add/Subtract");
    case (CDcacAlu4::Y_BD1_OUT + CCpu::IN_COUNT): return tr("D=BD1");
    case (CDcacAlu4::Y_BD2_OUT + CCpu::IN_COUNT): return tr("D=BD2");
    default: break;
    }
    return QString();
}

QString CDcacTextSource::PhysicalP_Way4(unsigned int index) {
    switch (index) {
    case (CCpu::BUS_OUT):  return tr("'BUS' from CPU");
    case (CCpu::TASK_OUT): return tr("'TASK' from CPU");
    case (CDcacAlu4::P_CT1_3 + CCpu::OUT_COUNT): return tr("CT1[3] - stop condition");
    case (CDcacAlu4::P_RG1_6 + CCpu::OUT_COUNT): return tr("RG1[6] - analysis");
    case (CDcacAlu4::P_RG1_7 + CCpu::OUT_COUNT): return tr("RG1[7] - analysis");
    default: break;
    }
    return QString();
}

QString CDcacTextSource::NameWay4() {
    return tr("Two's compliment (auto correction): 4th way");
}
