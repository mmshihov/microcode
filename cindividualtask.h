#ifndef CINDIVIDUALTASK_H
#define CINDIVIDUALTASK_H

#include <QObject>
#include <QString>
#include <QByteArray>

#include "csignalpermutation.h"

/**
 * @brief The CIndividualTask class
 *
 * Индивидуальное задание подразумевает индивидуальную для каждого студента перестановку управляющих сигналов.
 *
 * Файл индивидуального задания содержит:
 *    StudentId --- идентификатор ученика;
 *    SwapHistory --- достаточно большую случайную последовательность бит (256 бит на практике достаточно)
 *                    эта последовательность бит представляет собой протокол сортировки некоторой подстановки
 *                    методом "пузырька": очередной бит этой последовательности устанавливается в 1, если перестановка
 *                    соседних элементов массива имела место, и в 1 --- в противном случае.
 *                    Мы таким образом уходим от хранения подстановок, так как заранее не знаем их длину (для каждого
 *                    задания будет своё количество управляющих сигналов)
 *    CryptoSignature --- цифровая подпись, точнее криптографическая свертка вышеперечисленных аргументов
 *                    CryptoHash(StudentId,SwapHistory,SecretKey)
 *                    и секретного ключа SecretKey, который известен только преподавателю.
 *                    Для защиты от модификации.
 */
class CIndividualTask {
public:
    enum EStatus {OK, IO_ERROR, LIST_FORMAT};

    static CIndividualTask *Instance();

    bool IsIntegrityValid(const QString& secret) const;

    bool IsLoaded() const {return mIsLoaded;}

    void LoadFromFile(const QString& taskFilename);
    void GenerateTasks(const QString& studentListFilename, const QString& taskFoldername,
                       const QString& secret, EStatus& status, QString& errorMessage);

    void InitSignalPermutation(CSignalPermutation& permutation);

    QString StudentId() const {return mStudentId;}

private:
    CIndividualTask(){mIsLoaded = false;}
    CIndividualTask(const CIndividualTask&) {}

    virtual ~CIndividualTask() {}

    static const unsigned int SWAP_HISTORY_BYTE_COUNT = 32;

    static const QString STUDENT_ID_STRING_JSON_KEY;
    static const QString STUDENT_SECRET_PREFIX_STRING_JSON_KEY;

    static const QString SWAP_HISTORY_STRING_JSON_KEY;
    static const QString SIGNATURE_STRING_JSON_KEY;

    bool       mIsLoaded;
    QString    mStudentId;
    QByteArray mSwapHistory;
    QByteArray mCryptoSignature;

    void InitP2L(unsigned int *p2l, unsigned int dim);
    static QByteArray GetSignature(const QString& studentId, const QByteArray& swapHistory, const QString& secret);
    static QByteArray GenerateRandomSwapHistory();
    static void InitRng();
    void SaveSeparateTask(const QString& id,
                          const QByteArray& swapHistory,
                          const QByteArray& signature,
                          const QString& taskFoldername,
                          EStatus& status);
};

class CIndividualTaskStatus : public QObject {
    Q_OBJECT
public:
    explicit CIndividualTaskStatus(QObject *parent = 0) : QObject(parent) {}

    static void PersonsFileAccessError(CIndividualTask::EStatus &status, QString &message);
    static void WrongJsonPersonListError(CIndividualTask::EStatus &status, QString &message);
    static void WrongJsonPersonError(CIndividualTask::EStatus &status, QString &message);
    static void WrongJsonIncompletePersonError(CIndividualTask::EStatus &status, QString &message);
    static void TaskSaveError(CIndividualTask::EStatus &status, QString &message);
signals:
public slots:
};

#endif // CINDIVIDUALTASK_H
