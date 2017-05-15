#include "csignalvalue.h"
#include "ui_csignalvalue.h"

CSignalValue::CSignalValue(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CSignalValue)
{
    ui->setupUi(this);
}

CSignalValue::~CSignalValue() {
    delete ui;
}

void CSignalValue::SetUnused() {
    ui->mHint->setText("-");
    ui->mValue->setText("x");
}

void CSignalValue::SetSignalValue(bool value) {
    if (value) {
        ui->mValue->setText("1");
    } else {
        ui->mValue->setText("0");
    }
}

void CSignalValue::SetSignalHint(const QString &hint) {
    ui->mHint->setText(hint);
}
