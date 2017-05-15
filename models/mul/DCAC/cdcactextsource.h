#ifndef CDCACTEXTSOURCE_H
#define CDCACTEXTSOURCE_H


#include <QObject>
#include "../../../chint.h"


class CDcacTextSource : public QObject {
    Q_OBJECT
public:
    explicit CDcacTextSource(QObject *parent = 0);

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


class CDcacHint_Way1 : public CHint {
protected:
    virtual QString DoY(unsigned int index) const {return CDcacTextSource::PhysicalY_Way1(index);}
    virtual QString DoP(unsigned int index) const {return CDcacTextSource::PhysicalP_Way1(index);}
};


class CDcacHint_Way2 : public CHint {
protected:
    virtual QString DoY(unsigned int index) const {return CDcacTextSource::PhysicalY_Way2(index);}
    virtual QString DoP(unsigned int index) const {return CDcacTextSource::PhysicalP_Way2(index);}
};

class CDcacHint_Way3 : public CHint {
protected:
    virtual QString DoY(unsigned int index) const {return CDcacTextSource::PhysicalY_Way3(index);}
    virtual QString DoP(unsigned int index) const {return CDcacTextSource::PhysicalP_Way3(index);}
};

class CDcacHint_Way4 : public CHint {
protected:
    virtual QString DoY(unsigned int index) const {return CDcacTextSource::PhysicalY_Way4(index);}
    virtual QString DoP(unsigned int index) const {return CDcacTextSource::PhysicalP_Way4(index);}
};



#endif // CDCACTEXTSOURCE_H
