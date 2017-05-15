#ifndef CFADDTEXTSOURCE_H
#define CFADDTEXTSOURCE_H

#include <QObject>
#include "../../../chint.h"


class CFaddTextSource : public QObject {
    Q_OBJECT
public:
    explicit CFaddTextSource(QObject *parent = 0);

    static QString PhysicalY_Way1(unsigned int index);
    static QString PhysicalP_Way1(unsigned int index);
    static QString NameWay1();
};

class CFaddHint_Way1 : public CHint {
protected:
    virtual QString DoY(unsigned int index) const {return CFaddTextSource::PhysicalY_Way1(index);}
    virtual QString DoP(unsigned int index) const {return CFaddTextSource::PhysicalP_Way1(index);}
};

#endif // CFADDTEXTSOURCE_H
