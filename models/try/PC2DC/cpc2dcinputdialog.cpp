#include "cpc2dcinputdialog.h"
#include "ui_cpc2dcinputdialog.h"

#include <QMessageBox>

CPc2DcInputDialog::CPc2DcInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CPc2DcInputDialog)
{
    ui->setupUi(this);
    InitInputValidators();
}

CPc2DcInputDialog::~CPc2DcInputDialog() {
    delete ui;
}

unsigned int CPc2DcInputDialog::ADirectCode() const {
    bool ok;

    unsigned int modulo = ui->mAModuloEdit->text().toInt(&ok, 2);
    unsigned int sign = ui->mASignEdit->text().toInt(&ok, 2);

    return MakeOperandDirectCode(sign, modulo);
}

void CPc2DcInputDialog::on_mInputButton_clicked() {
    if (IsValidInput()) {
        accept();
    } else {
        QMessageBox::information(this,
                                 tr("Direct code error"),
                                 tr("Code(X)=(Sign(X),Modulo(X))\n"
                                    "Use binary digits!\n"
                                    "P.S. (1,0000000) - bad code!"
                                    ));
    }
}

void CPc2DcInputDialog::on_mCancelButton_clicked() {reject();}

void CPc2DcInputDialog::on_mASignEdit_textChanged(const QString &/*arg1*/) {
    UpdateResult();
}

void CPc2DcInputDialog::on_mAModuloEdit_textChanged(const QString &/*arg1*/) {
    UpdateResult();
}

void CPc2DcInputDialog::InitInputValidators() {
    QRegExp signRx(QString("[01]"));
    QValidator *signValidator = new QRegExpValidator(signRx);

    ui->mASignEdit->setValidator(signValidator);

    QRegExp moduloRx(QString("[01]{7}"));
    QValidator *moduloValidator = new QRegExpValidator(moduloRx);

    ui->mAModuloEdit->setValidator(moduloValidator);
}

bool CPc2DcInputDialog::IsValidInput() const {
    bool ok;
    ResultCode(&ok);
    return ok;
}

void CPc2DcInputDialog::UpdateResult() {
    bool ok;
    unsigned int value = ResultCode(&ok);

    if (ok)
        OutRightResult(value);
    else
        OutBadResult();
}

void CPc2DcInputDialog::OutRightResult(unsigned int code) {
    ui->mResultText->setText(QString("%1=(%2)")
                             .arg(tr("Output:"))
                             .arg(code & 0xFF, 8, 2, QLatin1Char('0')));
}

void CPc2DcInputDialog::OutBadResult() {
    ui->mResultText->setText(tr("Bad direct code..."));
}

unsigned int CPc2DcInputDialog::ResultCode(bool *rok) const {
    bool ok;

    *rok = false;

    int aSign, aModulo;
    aSign = ui->mASignEdit->text().toInt(&ok, 2);
    if (!ok)
        return 0;
    aModulo = ui->mAModuloEdit->text().toInt(&ok, 2);
    if (!ok)
        return 0;
    if ((aSign & 1) && (aModulo == 0))
        return 0;

    *rok = true;
    return MakeTwosCode(aSign, aModulo);
}

unsigned int CPc2DcInputDialog::MakeOperandDirectCode(unsigned int sign, unsigned int modulo) {
    sign = (modulo != 0) ? sign : 0;
    return ((sign & 1) << 7) | (modulo & 0x7F);
}

unsigned int CPc2DcInputDialog::MakeTwosCode(unsigned int sign, unsigned int modulo) {
    unsigned int dc = modulo & 0x7F;
    if ((sign & 1) != 0) {
        dc = ((~modulo) + 1) | 0x80;
    }
    return dc;
}

CPc2DcDebugInputSource::~CPc2DcDebugInputSource() {
    if (mInputDialog != 0)
        delete mInputDialog;
}

bool CPc2DcDebugInputSource::DoIsSuccessfulQueryAndInitDebugTest(CTestVector *testVector) {
    if (InputDialog()->exec() == QDialog::Accepted) {
        InitTest(testVector);

        return true;
    }
    return false;
}

CPc2DcInputDialog *CPc2DcDebugInputSource::InputDialog() const {
    if (mInputDialog != 0)
        return mInputDialog;

    return const_cast<CPc2DcDebugInputSource*>(this)->mInputDialog = new CPc2DcInputDialog();
}

void CPc2DcDebugInputSource::InitTest(CTestVector *testVector) {
    CBitBlock A(8, InputDialog()->ADirectCode());

    testVector->ProgramInputPart(0, 0, A);

    testVector->MakeWrongOutputPartsForTest(0);
}

