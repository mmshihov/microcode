#ifndef CMILIROMTABLEMODEL_H
#define CMILIROMTABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>

#include "cmcu.h"

class CRomProxy {
public:
    typedef QVector<QString> TComments;

    CRomProxy(SharedPtr<CRom> programRom, unsigned int groupDim);
    CRomProxy(SharedPtr<CRom> programRom, unsigned int groupDim, const TComments& comments); /*when load from task*/

    SharedPtr<CRom>    ProgramRom() const {return mProgramRom;}
    QString            Comment(unsigned int row) const;
    void               SetComment(unsigned int index, const QString& comment);
    unsigned int       GroupsCount() const {return CMcu::PowerForDimension(mGroupDim);}
    unsigned int       StateDim() const {return mStateDim;}

    bool               IsProgrammable() const {return mProgramRom->IsProgrammable();}
    void               SetProgrammable(bool v) {mProgramRom->SetProgrammable(v);}

private:
    unsigned int        mGroupDim;
    unsigned int        mStateDim;

    SharedPtr<CRom>     mProgramRom;
    TComments           mComments;

    void Construct(SharedPtr<CRom> programRom, unsigned int groupDim);
    void Construct(const TComments& comments);
};


class CRomTableModel : public QAbstractTableModel  {
    Q_OBJECT
public:
    explicit CRomTableModel(
            SharedPtr<CRom> programRom,
            unsigned int groupDim,
            QObject *parent = 0) : QAbstractTableModel(parent), mRomProxy(programRom, groupDim) {}

    explicit CRomTableModel(
            SharedPtr<CRom> programRom,
            unsigned int groupDim,
            const CRomProxy::TComments& comments,
            QObject *parent = 0) : QAbstractTableModel(parent), mRomProxy(programRom, groupDim, comments) {}

    virtual Qt::ItemFlags flags(const QModelIndex& index) const;
    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const;
    virtual int rowCount(const QModelIndex& parent) const;
    virtual bool setData(const QModelIndex & index, const QVariant & value, int role);

    virtual QVariant data(const QModelIndex& index, int role) const;

    unsigned int RomColDim(unsigned int col) const {return mRomProxy.ProgramRom()->ColDim(col);}
    unsigned int HexDigitsForRomColDim(unsigned int col) const;

    unsigned int RomColCount() const {return mRomProxy.ProgramRom()->ColCount();}
    unsigned int RomRowCount() const {return mRomProxy.ProgramRom()->RowCount();}
    CBitBlock    RomCell(const CRom::Address &address) const {return mRomProxy.ProgramRom()->Cell(address);}
    QString      RomComment(unsigned int row) const {return mRomProxy.Comment(row);}

    unsigned int RomGroupsCount() const {return mRomProxy.GroupsCount();}
    unsigned int RomStateDim() const {return mRomProxy.StateDim();}

    void SetProgrammable(bool v) {mRomProxy.SetProgrammable(v);}
    const CRomProxy& RomProxy() const {return mRomProxy;}

protected:
    QVariant dataForDisplayRole(const QModelIndex& index) const;
    QVariant dataForEditRole(const QModelIndex& index) const;
    QVariant dataForDecorationRole(const QModelIndex& /*index*/) const {return QVariant();}
    QVariant dataForWhatThisRole(const QModelIndex& /*index*/) const {return QVariant();}

private:
    CRomProxy mRomProxy;
};

class CMiliRomTableModel : public CRomTableModel {
    Q_OBJECT
public:
    explicit CMiliRomTableModel(
            SharedPtr<CRom> programRom,
            unsigned int groupDim,
            QObject *parent = 0) : CRomTableModel(programRom, groupDim, parent) {}

    explicit CMiliRomTableModel(
            SharedPtr<CRom> programRom,
            unsigned int groupDim,
            const CRomProxy::TComments& comments,
            QObject *parent = 0) : CRomTableModel(programRom, groupDim, comments, parent) {}

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    QVariant headerForDisplayRole(int section, Qt::Orientation orientation) const;
    QVariant headerForDecorationRole(int /*section*/, Qt::Orientation /*orientation*/) const {return QVariant();}
    QVariant headerForWhatThisRole(int /*section*/, Qt::Orientation /*orientation*/) const {return QVariant();}
};

class CMooreRomTableModel : public CRomTableModel {
    Q_OBJECT
public:
    explicit CMooreRomTableModel(
            SharedPtr<CRom> programRom,
            unsigned int groupDim,
            QObject *parent = 0) : CRomTableModel(programRom, groupDim, parent) {}

    explicit CMooreRomTableModel(
            SharedPtr<CRom> programRom,
            unsigned int groupDim,
            const CRomProxy::TComments& comments,
            QObject *parent = 0) : CRomTableModel(programRom, groupDim, comments, parent) {}

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    QVariant headerForDisplayRole(int section, Qt::Orientation orientation) const;
    QVariant headerForDecorationRole(int /*section*/, Qt::Orientation /*orientation*/) const {return QVariant();}
    QVariant headerForWhatThisRole(int /*section*/, Qt::Orientation /*orientation*/) const {return QVariant();}
};

class CManualRomTableModel : public CRomTableModel {
    Q_OBJECT
public:
    explicit CManualRomTableModel(
            SharedPtr<CRom> programRom,
            QObject *parent = 0) : CRomTableModel(programRom, 1, parent) {}

    explicit CManualRomTableModel(
            SharedPtr<CRom> programRom,
            const CRomProxy::TComments& comments,
            QObject *parent = 0) : CRomTableModel(programRom, 1, comments, parent) {}

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    QVariant headerForDisplayRole(int section, Qt::Orientation orientation) const;
    QVariant headerForDecorationRole(int /*section*/, Qt::Orientation /*orientation*/) const {return QVariant();}
    QVariant headerForWhatThisRole(int /*section*/, Qt::Orientation /*orientation*/) const {return QVariant();}
};

#endif // CMILIROMTABLEMODEL_H
