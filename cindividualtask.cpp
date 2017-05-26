#include "cindividualtask.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QCryptographicHash>

#include <ctime>


const QString CIndividualTask::STUDENT_ID_STRING_JSON_KEY("id");
const QString CIndividualTask::STUDENT_SECRET_PREFIX_STRING_JSON_KEY("secret_prefix");
const QString CIndividualTask::SWAP_HISTORY_STRING_JSON_KEY("swap_history");
const QString CIndividualTask::SIGNATURE_STRING_JSON_KEY("signature");


void CIndividualTask::InitSignalPermutation(CSignalPermutation &permutation) {
    unsigned int *p2l = new unsigned int[permutation.Dim()];

    for (unsigned int i=0; i<permutation.Dim(); ++i) {
        p2l[i]  = i; // тождественная подстановка
    }

    InitP2L(p2l, permutation.Dim());
    permutation.SetP2L(p2l);

    delete[] p2l;
}

void CIndividualTask::InitP2L(unsigned int *p2l, unsigned int dim) {
    Q_ASSERT(dim > 1);

    unsigned int bitIndex = 0;
    unsigned int bitCount = mSwapHistory.size() * 8;

    while(1) {
        if (bitIndex >= bitCount)
            break;

        for (unsigned int itemCount = (dim - 1); itemCount >= 1; --itemCount) {
            for (unsigned int i = 0; i<itemCount; ++i) {
                char currentByte = mSwapHistory.at(bitIndex>>3);

                if (currentByte & (1 << (bitIndex & 0x7))) {
                    unsigned int t;

                    t        = p2l[i]; //swap
                    p2l[i]   = p2l[i+1];
                    p2l[i+1] = t;
                }

                ++bitIndex;

                if (bitIndex >= bitCount)
                    break;
            }
            if (bitIndex >= bitCount)
                break;
        }
    }
}

QByteArray CIndividualTask::GetSignature(const QString& studentId,
                                         const QByteArray& swapHistory,
                                         const QString& secret) {
    QByteArray buffer;

    buffer.append(studentId.trimmed());
    buffer.append(swapHistory);
    buffer.append(secret);

    return QCryptographicHash::hash(buffer, QCryptographicHash::Sha256);
}

QByteArray CIndividualTask::GenerateRandomSwapHistory() {
    QByteArray swapHistory;
    for (unsigned int i=0; i<SWAP_HISTORY_BYTE_COUNT; ++i) {
        char ch = (char)(qrand() & 0xFF);
        swapHistory.append(ch);
    }
    return swapHistory;
}

void CIndividualTask::InitRng() {
    qsrand((unsigned int)time(0));
}

void CIndividualTask::SaveSeparateTask(const QString&            id,
                                       const QByteArray&         swapHistory,
                                       const QByteArray&         signature,
                                       const QString&            taskFoldername,
                                       CIndividualTask::EStatus& status) {
    QJsonObject task;
    task.insert(STUDENT_ID_STRING_JSON_KEY,     QJsonValue(id));
    task.insert(SWAP_HISTORY_STRING_JSON_KEY,   QJsonValue(QString(swapHistory.toHex())));
    task.insert(SIGNATURE_STRING_JSON_KEY,      QJsonValue(QString(signature.toHex())));

    QJsonDocument json(task);

    QFile file(taskFoldername + "/" + id.trimmed() + ".json");
    if (!file.open(QIODevice::WriteOnly)) {
        status = IO_ERROR;
        return;
    }

    file.write(json.toJson());
    file.flush();
    file.close();

    status = OK;
}

CIndividualTask *CIndividualTask::Instance() {
    static CIndividualTask instance;
    return &instance;
}

bool CIndividualTask::IsIntegrityValid(const QString& secret) const {
    return mCryptoSignature == GetSignature(mStudentId, mSwapHistory, secret);
}

void CIndividualTask::LoadFromFile(const QString &taskFilename) {
    QFile taskFile(taskFilename);

    mIsLoaded = false;

    if (!taskFile.open(QIODevice::ReadOnly))
        return;

    QJsonDocument jsonTask = QJsonDocument::fromJson(taskFile.readAll());

    if (!jsonTask.isObject())
        return;

    QJsonValue studentIdValue;
    studentIdValue = jsonTask.object().value(STUDENT_ID_STRING_JSON_KEY);
    if (studentIdValue.isUndefined())
        return;

    QJsonValue swapHistoryValue;
    swapHistoryValue = jsonTask.object().value(SWAP_HISTORY_STRING_JSON_KEY);
    if (swapHistoryValue.isUndefined())
        return;
    QByteArray swapHistoryHex;
    swapHistoryHex.append(swapHistoryValue.toString());

    QJsonValue signatureValue;
    signatureValue = jsonTask.object().value(SIGNATURE_STRING_JSON_KEY);
    if (signatureValue.isUndefined())
        return;

    mStudentId = studentIdValue.toString();

    QByteArray signatureHex;
    signatureHex.append(signatureValue.toString());
    mCryptoSignature.clear();
    mCryptoSignature.append(QByteArray::fromHex(signatureHex));

    mSwapHistory.clear();
    mSwapHistory.append(QByteArray::fromHex(swapHistoryHex));

    mIsLoaded = true;
}

void CIndividualTask::GenerateTasks(const QString &studentListFilename,
                                    const QString &taskFoldername,
                                    const QString &secretPostfix,
                                    EStatus& status,
                                    QString& errorMessage) {
    QFile listFile(studentListFilename);
    if (!listFile.open(QIODevice::ReadOnly)) {
        CIndividualTaskStatus::PersonsFileAccessError(status, errorMessage);
        return;
    }

    QByteArray content = listFile.readAll();
    QJsonDocument list = QJsonDocument::fromJson(content);

    if (!list.isArray()) {
        CIndividualTaskStatus::WrongJsonPersonListError(status, errorMessage);
        return;
    }

    for (int i=0; i<list.array().count(); ++i) {
        QJsonValue item = list.array().at(i);
        if (!item.isObject()) {
            CIndividualTaskStatus::WrongJsonPersonError(status, errorMessage);
            return;
        }

        QJsonValue idItem = item.toObject().value(STUDENT_ID_STRING_JSON_KEY);
        QJsonValue prefixItem = item.toObject().value(STUDENT_SECRET_PREFIX_STRING_JSON_KEY);
        if (idItem.isUndefined() || prefixItem.isUndefined()) {
            CIndividualTaskStatus::WrongJsonIncompletePersonError(status, errorMessage);
            return;
        }

        QString    id = idItem.toString();
        QString    secret = prefixItem.toString() + secretPostfix;
        QByteArray swapHistory = GenerateRandomSwapHistory();

        QByteArray signature = GetSignature(id, swapHistory, secret);

        SaveSeparateTask(id, swapHistory, signature, taskFoldername, status);
        if (status != OK) {
            CIndividualTaskStatus::TaskSaveError(status, errorMessage);
            return;
        }
    }
}


void CIndividualTaskStatus::PersonsFileAccessError(CIndividualTask::EStatus &status, QString &message) {
    status  = CIndividualTask::IO_ERROR;
    message = tr("Can't open persons list file!");
}

void CIndividualTaskStatus::WrongJsonPersonListError(CIndividualTask::EStatus &status, QString &message) {
    status  = CIndividualTask::LIST_FORMAT;
    message = tr("Wrong JSON format for persons list!");
}

void CIndividualTaskStatus::WrongJsonPersonError(CIndividualTask::EStatus &status, QString &message) {
    status  = CIndividualTask::LIST_FORMAT;
    message = tr("Wrong JSON format for person in list!");
}

void CIndividualTaskStatus::WrongJsonIncompletePersonError(CIndividualTask::EStatus &status, QString &message) {
    status  = CIndividualTask::LIST_FORMAT;
    message = tr("No necessary fields for person in JSON!");
}

void CIndividualTaskStatus::TaskSaveError(CIndividualTask::EStatus &status, QString &message) {
    status  = CIndividualTask::IO_ERROR;
    message = tr("Separate variant save error!");
}
