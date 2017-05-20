#include "cindividualtask.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QCryptographicHash>

#include <ctime>

const QString CIndividualTask::STUDENT_ID_STRING_JSON_KEY = "id";
const QString CIndividualTask::STUDENT_SECRET_PREFIX_STRING_JSON_KEY = "secret_prefix";
const QString CIndividualTask::SWAP_HISTORY_STRING_JSON_KEY = "swap_history";
const QString CIndividualTask::SIGNATURE_STRING_JSON_KEY = "signature";


void CIndividualTask::InitSignalPermutation(CSignalPermutation &permutation) {
    unsigned int *p2l = new unsigned int[permutation.Dim()];

    for (unsigned int i=0; i<permutation.Dim(); ++i) {
        p2l[i]  = i; // тождественная подстановка
    }

    InitP2L(p2l,permutation.Dim());
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
    task.insert(SWAP_HISTORY_STRING_JSON_KEY,   QJsonValue(QString(swapHistory.toBase64())));
    task.insert(SIGNATURE_STRING_JSON_KEY,      QJsonValue(QString(signature.toBase64())));

    QJsonDocument json(task);

    QFile file(taskFoldername + "/" + id.trimmed());
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

    QJsonDocument jsonTask;
    jsonTask.fromBinaryData(taskFile.readAll());

    if (!jsonTask.isObject())
        return;

    QJsonValue value;
    value = jsonTask.object().value(STUDENT_ID_STRING_JSON_KEY);
    if (value.isUndefined())
        return false;
    mStudentId = value.toString();

    value = jsonTask.object().value(SWAP_HISTORY_STRING_JSON_KEY);
    if (value.isUndefined())
        return false;
    mSwapHistory.clear();
    mSwapHistory.append(value.toString());

    value = jsonTask.object().value(SIGNATURE_STRING_JSON_KEY);
    if (value.isUndefined())
        return false;
    mCryptoSignature.clear();
    mCryptoSignature.append(value.toString());

    mIsLoaded = true;
}

void CIndividualTask::GenerateTasks(const QString &studentListFilename,
                                    const QString &taskFoldername,
                                    const QString &secretPostfix,
                                    EStatus& status,
                                    QString& errorMessage) {
    QFile listFile(studentListFilename);
    if (!listFile.open(QIODevice::ReadOnly)) {
        status = IO_ERROR;
        errorMessage = "Can't open persons list file!";
        return;
    }

    QJsonDocument list;
    list.fromBinaryData(listFile.readAll());

    if (!list.isArray()) {
        status = LIST_FORMAT;
        errorMessage = "Wrong JSON format for persons list!";
        return;
    }

    for (int i=0; i<list.array().count(); ++i) {
        QJsonValue item = list.array().at(i);
        if (!item.isObject()) {
            status = LIST_FORMAT;
            errorMessage = "Wrong JSON format for person in list!";
            return;
        }

        QJsonValue idItem = item.value(STUDENT_ID_STRING_JSON_KEY);
        QJsonValue prefixItem = item.value(STUDENT_SECRET_PREFIX_STRING_JSON_KEY);
        if (idItem.isUndefined() || prefixItem.isUndefined()) {
            status = LIST_FORMAT;
            errorMessage = "No necessary fields for person in JSON!";
            return;
        }

        QString    id = idItem.toString();
        QString    secret = prefixItem.toString() + secretPostfix;
        QByteArray swapHistory = GenerateRandomSwapHistory();

        QByteArray signature = GetSignature(id, swapHistory, secret);

        SaveSeparateTask(id, swapHistory, signature, taskFoldername, status);
        if (status != OK) {
            errorMessage = "Separate task save error!";
            return;
        }
    }
}


