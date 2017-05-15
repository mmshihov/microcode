#include "cpcs1inputdialog.h"
#include "ui_cpcs1inputdialog.h"

#include <QMessageBox>

CPcs1InputDialog::CPcs1InputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CPcs1InputDialog)
{
    ui->setupUi(this);
    InitInputValidators();
}

CPcs1InputDialog::~CPcs1InputDialog() {
    delete ui;
}

unsigned int CPcs1InputDialog::ADirectCode() const {
    bool ok;

    unsigned int modulo = ui->mAModuloEdit->text().toInt(&ok, 2);
    unsigned int sign = ui->mASignEdit->text().toInt(&ok, 2);

    return MakeOperandDirectCode(sign, modulo);
}

unsigned int CPcs1InputDialog::BDirectCode() const {
    bool ok;

    unsigned int modulo = ui->mBModuloEdit->text().toInt(&ok, 2);
    unsigned int sign = ui->mBSignEdit->text().toInt(&ok, 2);

    return MakeOperandDirectCode(sign, modulo);
}

void CPcs1InputDialog::on_mInputButton_clicked() {
    if (IsValidInput()) {
        accept();
    } else {
        QMessageBox::information(this,
                                 tr("Direct code error"),
                                 tr("Code(X)=( Sign(X),Modulo(X) )\n"
                                    "Use binary digits!\n"
                                    "P.S. (1,0000000) - bad code!"
                                    ));
    }
}

void CPcs1InputDialog::on_mCancelButton_clicked() {reject();}

void CPcs1InputDialog::on_mASignEdit_textChanged(const QString &/*arg1*/) {
    UpdateResult();
}

void CPcs1InputDialog::on_mBSignEdit_textChanged(const QString &/*arg1*/) {
    UpdateResult();
}

void CPcs1InputDialog::on_mAModuloEdit_textChanged(const QString &/*arg1*/) {
    UpdateResult();
}

void CPcs1InputDialog::on_mBModuloEdit_textChanged(const QString &/*arg1*/) {
    UpdateResult();
}

void CPcs1InputDialog::InitInputValidators() {
    QRegExp signRx(QString("[01]"));
    QValidator *signValidator = new QRegExpValidator(signRx);

    ui->mASignEdit->setValidator(signValidator);
    ui->mBSignEdit->setValidator(signValidator);

    QRegExp moduloRx(QString("[01]{7}"));
    QValidator *moduloValidator = new QRegExpValidator(moduloRx);

    ui->mAModuloEdit->setValidator(moduloValidator);
    ui->mBModuloEdit->setValidator(moduloValidator);
}

bool CPcs1InputDialog::IsValidInput() {
    bool ok;
    ResultDirectCode(&ok);
    return ok;
}

void CPcs1InputDialog::UpdateResult() {
    bool aok, bok;

    unsigned int aSign, aModulo,
                 bSign, bModulo;
    int A, B;

    ParseInput(ui->mASignEdit->text(), ui->mAModuloEdit->text(), aSign, aModulo, A, &aok);
    ParseInput(ui->mBSignEdit->text(), ui->mBModuloEdit->text(), bSign, bModulo, B, &bok);

    if (aok && bok) {
        unsigned int value = MakeResoultDirectCode(
                           aSign ^ bSign,
                           aModulo * bModulo);

        ui->mAValueText->setText(QString("%1").arg(A));
        ui->mBValueText->setText(QString("%1").arg(B));

        ui->mABValueText->setText(QString("%1").arg(A*B));

        OutRightResult(value);
    } else {
        if (aok)
            ui->mAValueText->setText(QString("%1").arg(A));
        else
            ui->mAValueText->setText("?");

        if (bok)
            ui->mBValueText->setText(QString("%1").arg(B));
        else
            ui->mBValueText->setText("?");

        ui->mABValueText->setText("?");

        OutBadResult();
    }
}

void CPcs1InputDialog::OutRightResult(unsigned int code) {
    ui->mResultText->setText(QString("A*B=(%1,%2  %3)")
                             .arg((code >> 15) & 1)
                             .arg((code >> 8) & 0x7F, 7, 2, QLatin1Char('0'))
                             .arg(code & 0xFF, 8, 2, QLatin1Char('0')));
}

void CPcs1InputDialog::OutBadResult() {
    ui->mResultText->setText(tr("Bad operands..."));
}

void CPcs1InputDialog::ParseInput(const QString& signString, const QString& moduloString,
                                  unsigned int& signValue, unsigned int& moduloValue,
                                  int& value,
                                  bool *ok) {
    *ok = false;

    signValue = 0;
    moduloValue = 0;
    value = 0;

    int sign, modulo;
    sign = signString.toInt(ok, 2);
    if (!*ok)
        return;
    modulo = moduloString.toInt(ok, 2);
    if (!*ok)
        return;
    if ((sign & 1) && (modulo == 0)) {
        *ok = false;
        return;
    }

    signValue   = (sign & 1);
    moduloValue = modulo;
    value = (-2 * (signValue & 1) + 1) * moduloValue;
}

unsigned int CPcs1InputDialog::ResultDirectCode(bool *ok) const {
    unsigned int aSign, aModulo,
                 bSign, bModulo;
    int A, B;

    ParseInput(ui->mASignEdit->text(), ui->mAModuloEdit->text(), aSign, aModulo, A, ok);
    if (!*ok)
        return 0;

    ParseInput(ui->mBSignEdit->text(), ui->mBModuloEdit->text(), bSign, bModulo, B, ok);
    if (!*ok)
        return 0;

    return MakeResoultDirectCode(
                       aSign ^ bSign,
                       aModulo * bModulo);
}

unsigned int CPcs1InputDialog::MakeOperandDirectCode(unsigned int sign, unsigned int modulo) {
    sign = (modulo != 0) ? sign : 0;
    return ((sign & 1) << 7) | (modulo & 0x7F);
}

unsigned int CPcs1InputDialog::MakeResoultDirectCode(unsigned int sign, unsigned int modulo) {
    sign = (modulo != 0) ? sign : 0;
    return ((sign & 1) << 15) | (modulo & 0x7FFF);
}

CPcs1DebugInputSource::~CPcs1DebugInputSource() {
    if (mInputDialog != 0)
        delete mInputDialog;
}

bool CPcs1DebugInputSource::DoIsSuccessfulQueryAndInitDebugTest(CTestVector *testVector) {
    if (InputDialog()->exec() == QDialog::Accepted) {
        InitTest(testVector);

        return true;
    }
    return false;
}

CPcs1InputDialog *CPcs1DebugInputSource::InputDialog() const {
    if (mInputDialog != 0)
        return mInputDialog;

    return const_cast<CPcs1DebugInputSource*>(this)->mInputDialog = new CPcs1InputDialog();
}

void CPcs1DebugInputSource::InitTest(CTestVector *testVector) {
    CBitBlock A(8, InputDialog()->ADirectCode());
    CBitBlock B(8, InputDialog()->BDirectCode());

    testVector->ProgramInputPart(0, 0, A);
    testVector->ProgramInputPart(0, 1, B);

    testVector->MakeWrongOutputPartsForTest(0);
}

