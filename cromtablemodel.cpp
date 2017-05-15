#include "cromtablemodel.h"
#include "ctextout.h"

CRomProxy::CRomProxy(SharedPtr<CRom> programRom, unsigned int groupDim)
    : mComments(programRom->RowCount())
{
    Construct(programRom, groupDim);
}

CRomProxy::CRomProxy(SharedPtr<CRom> programRom, unsigned int groupDim, const CRomProxy::TComments &comments)
    : mComments(programRom->RowCount())
{
    Construct(programRom, groupDim);
    Construct(comments);
}

QString CRomProxy::Comment(unsigned int row) const {
    if (row < mProgramRom->RowCount()) {
        return mComments[row];
    }
    return QString();
}

void CRomProxy::SetComment(unsigned int index, const QString &comment) {
    if (index < mProgramRom->RowCount()) {
        mComments[index] = comment;
    }
}

void CRomProxy::Construct(SharedPtr<CRom> programRom, unsigned int groupDim) {
    mProgramRom = programRom;
    mGroupDim   = groupDim;
    mStateDim   = CMcu::MinDimensionFor(programRom->RowCount());
}

void CRomProxy::Construct(const CRomProxy::TComments &comments) {
    for (int i = 0; i < mComments.size(); ++i) {
        if (i >= comments.size())
            break;
        mComments[i] = comments[i];
    }
}


// --------------------------- common rom model ---------------------------------
unsigned int CRomTableModel::HexDigitsForRomColDim(unsigned int col) const {
    return (RomColDim(col) + 3) >> 2; //(a + 3)/4
}

Qt::ItemFlags CRomTableModel::flags(const QModelIndex &index) const {
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if (index.isValid()) {
        flags |= (Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        if (mRomProxy.IsProgrammable())
            flags |= Qt::ItemIsEditable;
    }
    return flags;
}

int CRomTableModel::columnCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;

    return (RomColCount() + 1);
}

int CRomTableModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;

    return RomRowCount();
}

QVariant CRomTableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    switch (role) {
    case Qt::DisplayRole:    return dataForDisplayRole(index);
    case Qt::EditRole:       return dataForEditRole(index);
    case Qt::DecorationRole: return dataForDecorationRole(index);
    case Qt::WhatsThisRole:  return dataForWhatThisRole(index);
    }

    return QVariant();
}

bool CRomTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && role == Qt::EditRole) {
        if ((0 <= index.row()) && (index.row() < (int)RomRowCount())) {
            if ((0 <= index.column()) && (index.column() < (int)RomColCount())) {
                CRom::Address address;
                address.col = index.column();
                address.row = index.row();

                CBitBlock cellValue(RomColDim(address.col), value.toUInt());
                mRomProxy.ProgramRom()->ProgramCell(address, cellValue);

                emit dataChanged(index, index);
            } else if (index.column() == (int)RomColCount()) {
                mRomProxy.SetComment(index.row(), value.toString());
            } else
                return false;

            emit dataChanged(index, index);
        }
        return true;
    }
    return false;
}

QVariant CRomTableModel::dataForDisplayRole(const QModelIndex &index) const {
    if (!index.isValid())
        return QVariant();

    if ((index.row() < 0) || (index.column() < 0))
        return QVariant();

    unsigned int row = (unsigned int)index.row();
    unsigned int col = (unsigned int)index.column();

    if (row < RomRowCount()) {
        if (col < RomColCount()) {
            CRom::Address address;
            address.col = col;
            address.row = row;
            return CTextOut::FormatHex(RomCell(address).AsInt(), RomColDim(col));
        } else if (col == RomColCount()) {
            return RomComment(row);
        }
    }

    return QVariant();
}

QVariant CRomTableModel::dataForEditRole(const QModelIndex &index) const {
    if (!index.isValid())
        return QVariant();

    if ((index.row() < 0) || (index.column() < 0))
        return QVariant();

    unsigned int row = (unsigned int)index.row();
    unsigned int col = (unsigned int)index.column();

    if (row < RomRowCount()) {
        if (col < RomColCount()) {
            CRom::Address address;
            address.col = col;
            address.row = row;
            unsigned int hexDim = HexDigitsForRomColDim(col);
            return QString("%1").arg(RomCell(address).AsInt(), hexDim, 16, QLatin1Char('0')) ;
        } else if (col == RomColCount()) {
            return RomComment(row);
        }
    }

    return QVariant();
}


// --------------------------mili-----------------------------
QVariant CMiliRomTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    switch (role) {
    case Qt::DisplayRole:    return headerForDisplayRole(section, orientation);
    case Qt::DecorationRole: return headerForDecorationRole(section, orientation);
    case Qt::WhatsThisRole:  return headerForWhatThisRole(section, orientation);
    }

    return QVariant();
}

QVariant CMiliRomTableModel::headerForDisplayRole(int section, Qt::Orientation orientation) const {
    if (orientation == Qt::Horizontal) {
        if ((0 <= section) && (section < (int)(2*RomGroupsCount() + 2))) {
            unsigned int col = (unsigned int) section;
            if (col == 0)
                return "j";

            col -= 1;
            if (col < 2*RomGroupsCount()) {
                unsigned int j = (col >> 1); //div 2
                if ((col & 1) == 0) {
                    return QString("%1%2").arg("S").arg(j,0,16);
                } else {
                    return QString("%1%2").arg("Y").arg(j,0,16);
                }
            }

            col -= 2*RomGroupsCount();
            if (col == 0)
                return tr("Comment");
        }
    } else if (orientation == Qt::Vertical) {
        if ((0 <= section) && (section < (int)RomRowCount())) {
            return CTextOut::FormatHex(section, RomStateDim());
        }
    }

    return QVariant();
}


// --------------------------moore-----------------------------
QVariant CMooreRomTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    switch (role) {
    case Qt::DisplayRole:    return headerForDisplayRole(section, orientation);
    case Qt::DecorationRole: return headerForDecorationRole(section, orientation);
    case Qt::WhatsThisRole:  return headerForWhatThisRole(section, orientation);
    }

    return QVariant();
}

QVariant CMooreRomTableModel::headerForDisplayRole(int section, Qt::Orientation orientation) const {
    if (orientation == Qt::Horizontal) {
        if ((0 <= section) && (section < (int)(RomGroupsCount() + 3))) {
            unsigned int col = (unsigned int) section;
            if (col == 0)
                return "j";

            col -= 1;
            if (col < RomGroupsCount())
                return QString("S%1").arg(col,0,16);

            col -= RomGroupsCount();
            if (col == 0)
                return "Y";

            col -= 1;
            if (col == 0)
                return tr("Comment");
        }
    } else if (orientation == Qt::Vertical) {
        if ((0 <= section) && (section < (int)RomRowCount())) {
            return CTextOut::FormatHex(section, RomStateDim());
        }
    }

    return QVariant();
}

// --------------------------manual-----------------------------
QVariant CManualRomTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    switch (role) {
    case Qt::DisplayRole:    return headerForDisplayRole(section, orientation);
    case Qt::DecorationRole: return headerForDecorationRole(section, orientation);
    case Qt::WhatsThisRole:  return headerForWhatThisRole(section, orientation);
    }

    return QVariant();
}

QVariant CManualRomTableModel::headerForDisplayRole(int section, Qt::Orientation orientation) const {
    if (orientation == Qt::Horizontal) {
        if (section == 0)
            return "Y";
        if (section == 1)
            return tr("Comment");
    } else if (orientation == Qt::Vertical) {
        if ((0 <= section) && (section < (int)RomRowCount())) {
            return CTextOut::FormatHex(section, RomStateDim());
        }
    }

    return QVariant();
}

