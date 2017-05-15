#ifndef CTESTVECTOR_H
#define CTESTVECTOR_H

#include <QString>
#include "cbitblock.h"

class CTestVector;

class CDebugInputSource {
public:
    virtual ~CDebugInputSource() {}

    bool IsSuccessfulQueryAndInitDebugTest(CTestVector *testVector) {return DoIsSuccessfulQueryAndInitDebugTest(testVector);}
protected:
    virtual bool DoIsSuccessfulQueryAndInitDebugTest(CTestVector *testVector) = 0;
};


/**
 * @brief The CTestVector class
 * Этот абстрактный класс определяет набор тестов, которые выполняет CDispatcherUnit
 * (ЦУУ в структуре вычислительного устройства, см. методические указания).
 *
 * Идея взаимодействия ЦУУ и УЧ проста: ЦУУ выдает задание (ввод), УЧ (с помощью студента) вычисляет результат (вывод).
 *
 * Тест рассматривается как последовательность передач (ввод) операндов по шине, выполняемая ЦУУ и как последовательность
 * передач пакетов результата (вывод), которая выполняется УЧ.
 * Т.е. тест сводится к проверке того, правильные ли пакеты были выданы УЧ в ответ на входные пакеты.
 *
 * Тесты выполняются ЦУУ либо в режиме отладки, либо в режиме автотестирования.
 * В режиме отладки выполняется только нулевой тест в составе вектора, а в режиме автотестирования --- все.
 *
 * В режиме отладки исходные данные (ввод) для теста вводится пользователем конечной программы
 * через соотвествующий графический интерфейс пользователя. Т.е. пользователь вводит операнды, на которых хочет
 * в пошаговом режиме проверить корректность работы составленной им микропрограммы.
 * В программе для этого используется паттерн "стратегия" (передаваемый класс CDebugInputSource),
 * скрывающий детали реализации поставщика данных. Метод QueryAndInitDebugTest стратегии должен преобразовать
 * входные данные в тест:
 *
 * Для каждого нового вычислительного устройства, разработчик должен создать
 * наследника этого класса, который и передается в конструктор CDispatcherUnit.
 * Функция DoAutoTestCount() должна возвращать константу - максимальное количество тестов в векторе.
 * Функция DoInitAutoTests() должна заранее сгенерировать AutoTestCount случайных тестов (или точнее, непредсказуемых тестов,
 *   осмысленно проверящих алгоритм: например в алгоритме умножения в дополнительном коде с ручной коррекцией обязательно
 *   как минимум три теста со случайными ненулевыми величинами, которые проверят следующие сочетания (множимое,множитель):
 *   (-,+) (-,-) (+,+)
 * Функция DoIsTestOk() проверяет соответствует ли вывод вводу.
 */
class CTestVector {
public:
    CTestVector(unsigned int inputCount,
                unsigned int outputCount,
                unsigned int dimension,
                unsigned int autoTestCount,
                CDebugInputSource *inputSource);
    virtual ~CTestVector();

    bool IsSuccessfulInitDebugTest();
    void InitAutoTests() {DoInitAutoTests();}

    unsigned int AutoTestCount() const {return mAutoTestCount;}
    unsigned int InputPartCount() const {return mInputPartCount;}
    unsigned int OutputPartCount() const {return mOutputPartCount;}
    unsigned int Dimension() const {return mDimension;}

    CBitBlock InputPart(unsigned int testIndex, unsigned int inputIndex) const;
    CBitBlock OutputPart(unsigned int testIndex, unsigned int partIndex) const;
    CBitBlock RightOutputPart(unsigned int testIndex, unsigned int partIndex) const;
    void      ProgramInputPart(unsigned int testIndex, unsigned int inputIndex, const CBitBlock &input);
    void      SetOutputPart(unsigned int testIndex, unsigned int outputIndex, const CBitBlock& output);
    void      MakeWrongOutputPartsForTest(unsigned int testIndex);

    bool IsTestOk(unsigned int testIndex) const {return DoIsTestOk(testIndex);}

    void SetDebugInputSource(CDebugInputSource *source) {mDebugInputSource = source;}

protected:
    class CTestItem {
    public:
        CTestItem(unsigned int inputCount, unsigned int outputCount, unsigned int dimension);
        ~CTestItem();

        CBitBlock InputPart(unsigned int partIndex) const;
        CBitBlock OutputPart(unsigned int partIndex) const;
        void ProgramInputPart(unsigned int partIndex, const CBitBlock& part);
        void ProgramOutputPart(unsigned int partIndex, const CBitBlock& part);
        void SetOutputPart(unsigned int partIndex, const CBitBlock& part);
    private:
        unsigned int mInputPartCount, mOutputPartCount;
        CBitBlock **mInputParts;
        CBitBlock **mOutputParts;
    };

    virtual void DoInitAutoTests() = 0;
    virtual CBitBlock DoRightOutputPart(unsigned int testIndex, unsigned int partIndex) const = 0;
    virtual bool DoIsTestOk(unsigned int testIndex) const; //реализация по умолчанию

    void CreateVector();

private:
    unsigned int mTestCount, mInputPartCount, mOutputPartCount, mDimension, mAutoTestCount;

    CTestItem **mTests;

    CDebugInputSource *mDebugInputSource;

    void MakeWrongOutputs();
};

#endif // CTESTVECTOR_H
