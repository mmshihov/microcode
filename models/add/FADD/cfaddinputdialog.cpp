#include "cfaddinputdialog.h"
#include "ui_cfaddinputdialog.h"

#include <QMessageBox>

#include "cfaddtestvector.h"
#include "../../../ctextout.h"


CFaddInputDialog::CFaddInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CFaddInputDialog)
{
    ui->setupUi(this);
    InitInputValidators();
}

CFaddInputDialog::~CFaddInputDialog() {
    delete ui;
}

CBitBlock CFaddInputDialog::A() const {
    bool ok;
    return GetFromStrings(ui->mAmantEdit->text(), ui->mAcharEdit->text(), ok);
}

CBitBlock CFaddInputDialog::B() const {
    bool ok;
    return GetFromStrings(ui->mBmantEdit->text(), ui->mBcharEdit->text(), ok);
}

void CFaddInputDialog::InitInputValidators() {
    QRegExp mantRx(QString("[01]{%1}").arg(CFaddTestVector::MANT_LEN));
    QValidator *mantValidator = new QRegExpValidator(mantRx);

    ui->mAmantEdit->setValidator(mantValidator);
    ui->mBmantEdit->setValidator(mantValidator);

    QRegExp charRx(QString("[01]{%1}").arg(CFaddTestVector::CHAR_LEN));
    QValidator *charValidator = new QRegExpValidator(charRx);

    ui->mAcharEdit->setValidator(charValidator);
    ui->mBcharEdit->setValidator(charValidator);
}

bool CFaddInputDialog::IsValidInput() {
    bool ok;

    GetFromStrings(ui->mAmantEdit->text(), ui->mAcharEdit->text(), ok);
    if (!ok)
        return false;

    GetFromStrings(ui->mBmantEdit->text(), ui->mBcharEdit->text(), ok);
    return ok;
}

CBitBlock CFaddInputDialog::GetFromStrings(const QString &mantString, const QString &charString, bool &ok) {
    bool ok2bin;

    if ((mantString.length() != (int)CFaddTestVector::MANT_LEN)
            || (charString.length() != (int)CFaddTestVector::CHAR_LEN)) {
        ok = false;
        return CBitBlock();
    }

    unsigned int m;
    m = mantString.toUInt(&ok2bin, 2);
    if (!ok2bin) {
        ok = false;
        return CBitBlock();
    }

    unsigned int c;
    c = charString.toUInt(&ok2bin, 2);
    if (!ok2bin) {
        ok = false;
        return CBitBlock();
    }

    return CFaddTestVector::MakeBitblockFromMantAndChar(m,c,ok);
}

void CFaddInputDialog::UpdateResult() {
    bool ok;

    CBitBlock A = GetFromStrings(ui->mAmantEdit->text(), ui->mAcharEdit->text(), ok);
    if (!ok) {
        UpdateResultHint(tr("Incorrect format for A"), "");
        ui->mAValueText->setText("...");
        return;
    } else
        ui->mAValueText->setText(FormatDouble(CFaddTestVector::DoubleOf(A)));

    CBitBlock B = GetFromStrings(ui->mBmantEdit->text(), ui->mBcharEdit->text(), ok);
    if (!ok) {
        UpdateResultHint(tr("Incorrect format for B"), "");
        ui->mBValueText->setText("...");
        return;
    } else
        ui->mBValueText->setText(FormatDouble(CFaddTestVector::DoubleOf(B)));

    CBitBlock errorCode = CFaddTestVector::RightAnswerPart(A,B,0);
    CBitBlock result = CFaddTestVector::RightAnswerPart(A,B,1);
    UpdateResultHint(QString("ERROR(%1)").arg(CTextOut::FormatHex(errorCode)),
                     QString("(%1 %2) = %3")
                        .arg(CTextOut::FormatBin(CFaddTestVector::MantOf(result)))
                        .arg(CTextOut::FormatBin(CFaddTestVector::CharOf(result)))
                        .arg(FormatDouble(CFaddTestVector::DoubleOf(result))));
}

void CFaddInputDialog::UpdateResultHint(const QString &error, const QString &result) {
    ui->mErrorText->setText(error);
    ui->mResultText->setText(result);
}

QString CFaddInputDialog::FormatDouble(double value) {
    return QString("%1").arg(value);
}

void CFaddInputDialog::on_mInputButton_clicked() {
    if (IsValidInput()) {
        accept();
    } else {
        QMessageBox::information(this,
                                 tr("FPT error"),
                                 tr("- Mantiss must be normalized (10,01 - MSB's);\n"
                                    "- Zero is 00....00 (mantiss=0,char=0);\n"
                                    "- Type all bits."
                                    ));
    }
}

void CFaddInputDialog::on_mCancelButton_clicked() {reject();}

void CFaddInputDialog::on_mAmantEdit_textChanged(const QString &/*arg1*/) {
    UpdateResult();
}

void CFaddInputDialog::on_mBmantEdit_textChanged(const QString &/*arg1*/) {
    UpdateResult();
}

void CFaddInputDialog::on_mAcharEdit_textChanged(const QString &/*arg1*/) {
    UpdateResult();
}

void CFaddInputDialog::on_mBcharEdit_textChanged(const QString &/*arg1*/) {
    UpdateResult();
}


CFaddDebugInputSource::~CFaddDebugInputSource() {
    if (mInputDialog != 0)
        delete mInputDialog;
}

bool CFaddDebugInputSource::DoIsSuccessfulQueryAndInitDebugTest(CTestVector *testVector) {
    if (InputDialog()->exec() == QDialog::Accepted) {
        InitTest(testVector);

        return true;
    }
    return false;
}

CFaddInputDialog *CFaddDebugInputSource::InputDialog() const {
    if (mInputDialog != 0)
        return mInputDialog;

    return const_cast<CFaddDebugInputSource*>(this)->mInputDialog = new CFaddInputDialog();
}

void CFaddDebugInputSource::InitTest(CTestVector *testVector) {
    testVector->ProgramInputPart(0, 0, InputDialog()->A());
    testVector->ProgramInputPart(0, 1, InputDialog()->B());

    testVector->MakeWrongOutputPartsForTest(0);
}
