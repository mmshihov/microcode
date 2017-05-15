#ifndef CPCS1TEXTSOURCE_H
#define CPCS1TEXTSOURCE_H

#include <QObject>
#include "../../../chint.h"

class CPcs1TextSource : public QObject {
    Q_OBJECT
public:
    explicit CPcs1TextSource(QObject *parent = 0);
    
    static QString PhysicalY_Way1(unsigned int index);
    static QString PhysicalP_Way1(unsigned int index);
    static QString NameWay1();

    static QString PhysicalY_Way2(unsigned int index);
    static QString PhysicalP_Way2(unsigned int index);
    static QString NameWay2();

    static QString PhysicalY_Way3(unsigned int index);
    static QString PhysicalP_Way3(unsigned int index);
    static QString NameWay3();

    static QString PhysicalY_Way4(unsigned int index);
    static QString PhysicalP_Way4(unsigned int index);
    static QString NameWay4();
};

class CPcs1Hint_Way1 : public CHint {
protected:
    virtual QString DoY(unsigned int index) const {return CPcs1TextSource::PhysicalY_Way1(index);}
    virtual QString DoP(unsigned int index) const {return CPcs1TextSource::PhysicalP_Way1(index);}
};

class CPcs1Hint_Way2 : public CHint {
protected:
    virtual QString DoY(unsigned int index) const {return CPcs1TextSource::PhysicalY_Way2(index);}
    virtual QString DoP(unsigned int index) const {return CPcs1TextSource::PhysicalP_Way2(index);}
};

class CPcs1Hint_Way3 : public CHint {
protected:
    virtual QString DoY(unsigned int index) const {return CPcs1TextSource::PhysicalY_Way3(index);}
    virtual QString DoP(unsigned int index) const {return CPcs1TextSource::PhysicalP_Way3(index);}
};

class CPcs1Hint_Way4 : public CHint {
protected:
    virtual QString DoY(unsigned int index) const {return CPcs1TextSource::PhysicalY_Way4(index);}
    virtual QString DoP(unsigned int index) const {return CPcs1TextSource::PhysicalP_Way4(index);}
};

#endif // CPCS1TEXTSOURCE_H
