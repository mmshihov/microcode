#include "cpcs1textsource.h"

#include "cpcs1alu1.h"
#include "cpcs1alu2.h"
#include "cpcs1alu3.h"
#include "cpcs1alu4.h"

#include "../../../ccpu.h"

CPcs1TextSource::CPcs1TextSource(QObject *parent) :
    QObject(parent)
{
}

QString CPcs1TextSource::PhysicalY_Way1(unsigned int index) {
    switch (index) {
    case (CCpu::READY_IN):  return tr("'READY' to CPU");
    case (CCpu::RESULT_IN): return tr("'RESULT' to CPU");
    case (CPcs1Alu1::Y_CT1_WR  + CCpu::IN_COUNT): return tr("Write to CT1");
    case (CPcs1Alu1::Y_CT1_INC + CCpu::IN_COUNT): return tr("CT1:=CT1+1");
    case (CPcs1Alu1::Y_RG1_WR  + CCpu::IN_COUNT): return tr("Write to RG1");
    case (CPcs1Alu1::Y_RG1_SHR + CCpu::IN_COUNT): return tr("Shift RG1 right");
    case (CPcs1Alu1::Y_RG2_WR  + CCpu::IN_COUNT): return tr("Write to RG2");
    case (CPcs1Alu1::Y_RG3_RST + CCpu::IN_COUNT): return tr("RG3:=0");
    case (CPcs1Alu1::Y_RG3_WR  + CCpu::IN_COUNT): return tr("Write to RG3");
    case (CPcs1Alu1::Y_RG3_RG4_SHR + CCpu::IN_COUNT): return tr("Shift RG3,RG4 right");
    case (CPcs1Alu1::Y_T1_C    + CCpu::IN_COUNT): return tr("T1:=D[7]");
    case (CPcs1Alu1::Y_T2_C    + CCpu::IN_COUNT): return tr("T2:=D[7]");
    case (CPcs1Alu1::Y_BD1_OUT + CCpu::IN_COUNT): return tr("D=BD1");
    case (CPcs1Alu1::Y_BD2_OUT + CCpu::IN_COUNT): return tr("D=BD2");
    default: break;
    }
    return QString();
}

QString CPcs1TextSource::PhysicalP_Way1(unsigned int index) {
    switch (index) {
    case (CCpu::BUS_OUT):  return tr("'BUS' from CPU");
    case (CCpu::TASK_OUT): return tr("'TASK' from CPU");
    case (CPcs1Alu1::P_CT1_3 + CCpu::OUT_COUNT): return tr("CT1[3] - stop condition");
    case (CPcs1Alu1::P_RG1_0 + CCpu::OUT_COUNT): return tr("RG1[0]");
    default: break;
    }
    return QString();
}

QString CPcs1TextSource::NameWay1() {
    return tr("Direct code: 1st way");
}

QString CPcs1TextSource::PhysicalY_Way2(unsigned int index) {
    switch (index) {
    case (CCpu::READY_IN):                        return tr("'READY' to CPU");
    case (CCpu::RESULT_IN):                       return tr("'RESULT' to CPU");
    case (CPcs1Alu2::Y_CT1_WR  + CCpu::IN_COUNT): return tr("Write to CT1");
    case (CPcs1Alu2::Y_CT1_INC + CCpu::IN_COUNT): return tr("CT1:=CT1+1");
    case (CPcs1Alu2::Y_RG1_WR  + CCpu::IN_COUNT): return tr("Write to RG1");
    case (CPcs1Alu2::Y_RG1_SHR + CCpu::IN_COUNT): return tr("Shift RG1 right");
    case (CPcs1Alu2::Y_RG2_WR  + CCpu::IN_COUNT): return tr("Write to RG2");
    case (CPcs1Alu2::Y_RG3_RST + CCpu::IN_COUNT): return tr("RG3:=0");
    case (CPcs1Alu2::Y_RG3_WR  + CCpu::IN_COUNT): return tr("Write to RG3");
    case (CPcs1Alu2::Y_RG2_SHL + CCpu::IN_COUNT): return tr("Shift RG2 left");
    case (CPcs1Alu2::Y_T1_C    + CCpu::IN_COUNT): return tr("T1:=D[7]");
    case (CPcs1Alu2::Y_T2_C    + CCpu::IN_COUNT): return tr("T2:=D[7]");
    case (CPcs1Alu2::Y_BD1_OUT + CCpu::IN_COUNT): return tr("D=BD1");
    case (CPcs1Alu2::Y_BD2_OUT + CCpu::IN_COUNT): return tr("D=BD2");
    default: break;
    }
    return QString();
}

QString CPcs1TextSource::PhysicalP_Way2(unsigned int index) {
    switch (index) {
    case (CCpu::BUS_OUT):  return tr("'BUS' from CPU");
    case (CCpu::TASK_OUT): return tr("'TASK' from CPU");
    case (CPcs1Alu2::P_CT1_3 + CCpu::OUT_COUNT): return tr("CT1[3] - stop condition");
    case (CPcs1Alu2::P_RG1_0 + CCpu::OUT_COUNT): return tr("RG1[0]");
    default: break;
    }
    return QString();
}

QString CPcs1TextSource::NameWay2() {
    return tr("Direct code: 2nd way");
}

QString CPcs1TextSource::PhysicalY_Way3(unsigned int index) {
    switch (index) {
    case (CCpu::READY_IN):  return tr("'READY' to CPU");
    case (CCpu::RESULT_IN): return tr("'RESULT' to CPU");
    case (CPcs1Alu3::Y_CT1_WR  + CCpu::IN_COUNT): return tr("Write to CT1");
    case (CPcs1Alu3::Y_CT1_INC + CCpu::IN_COUNT): return tr("CT1:=CT1+1");
    case (CPcs1Alu3::Y_RG1_WR  + CCpu::IN_COUNT): return tr("Write to RG1");
    case (CPcs1Alu3::Y_RG1_SHL + CCpu::IN_COUNT): return tr("Shift RG1 left");
    case (CPcs1Alu3::Y_RG2_WR  + CCpu::IN_COUNT): return tr("Write to RG2");
    case (CPcs1Alu3::Y_RG3_RST + CCpu::IN_COUNT): return tr("RG3:=0");
    case (CPcs1Alu3::Y_RG3_WR  + CCpu::IN_COUNT): return tr("Write to RG3");
    case (CPcs1Alu3::Y_RG3_SHL + CCpu::IN_COUNT): return tr("Shift RG3 left");
    case (CPcs1Alu3::Y_T1_C    + CCpu::IN_COUNT): return tr("T1:=D[7]");
    case (CPcs1Alu3::Y_T2_C    + CCpu::IN_COUNT): return tr("T2:=D[7]");
    case (CPcs1Alu3::Y_BD1_OUT + CCpu::IN_COUNT): return tr("D=BD1");
    case (CPcs1Alu3::Y_BD2_OUT + CCpu::IN_COUNT): return tr("D=BD2");
    default: break;
    }
    return QString();
}

QString CPcs1TextSource::PhysicalP_Way3(unsigned int index) {
    switch (index) {
    case (CCpu::BUS_OUT):  return tr("'BUS' from CPU");
    case (CCpu::TASK_OUT): return tr("'TASK' from CPU");
    case (CPcs1Alu3::P_CT1_3 + CCpu::OUT_COUNT): return tr("CT1[3] - stop condition");
    case (CPcs1Alu3::P_RG1_6 + CCpu::OUT_COUNT): return tr("RG1[6]");
    default: break;
    }
    return QString();
}

QString CPcs1TextSource::NameWay3() {
    return tr("Direct code: 3rd way");
}

QString CPcs1TextSource::PhysicalY_Way4(unsigned int index) {
    switch (index) {
    case (CCpu::READY_IN):                        return tr("'READY' to CPU");
    case (CCpu::RESULT_IN):                       return tr("'RESULT' to CPU");
    case (CPcs1Alu4::Y_CT1_WR  + CCpu::IN_COUNT): return tr("Write to CT1");
    case (CPcs1Alu4::Y_CT1_INC + CCpu::IN_COUNT): return tr("CT1:=CT1+1");
    case (CPcs1Alu4::Y_RG1_WR  + CCpu::IN_COUNT): return tr("Write to RG1");
    case (CPcs1Alu4::Y_RG1_SHL + CCpu::IN_COUNT): return tr("Shift RG1 left");
    case (CPcs1Alu4::Y_RG2_WR  + CCpu::IN_COUNT): return tr("Write to RG2");
    case (CPcs1Alu4::Y_RG3_RST + CCpu::IN_COUNT): return tr("RG3:=0");
    case (CPcs1Alu4::Y_RG3_WR  + CCpu::IN_COUNT): return tr("Write to RG3");
    case (CPcs1Alu4::Y_RG2_SHR + CCpu::IN_COUNT): return tr("Shift RG2 right");
    case (CPcs1Alu4::Y_T1_C    + CCpu::IN_COUNT): return tr("T1:=D[7]");
    case (CPcs1Alu4::Y_T2_C    + CCpu::IN_COUNT): return tr("T2:=D[7]");
    case (CPcs1Alu4::Y_BD1_OUT + CCpu::IN_COUNT): return tr("D=BD1");
    case (CPcs1Alu4::Y_BD2_OUT + CCpu::IN_COUNT): return tr("D=BD2");
    default: break;
    }
    return QString();
}

QString CPcs1TextSource::PhysicalP_Way4(unsigned int index) {
    switch (index) {
    case (CCpu::BUS_OUT):  return tr("'BUS' from CPU");
    case (CCpu::TASK_OUT): return tr("'TASK' from CPU");
    case (CPcs1Alu4::P_CT1_3 + CCpu::OUT_COUNT): return tr("CT1[3] - stop condition");
    case (CPcs1Alu4::P_RG1_6+ CCpu::OUT_COUNT): return tr("RG1[6]");
    default: break;
    }
    return QString();
}

QString CPcs1TextSource::NameWay4() {
    return tr("Direct code: 4th way");
}
