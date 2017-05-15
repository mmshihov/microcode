#include "cromeditordelegate.h"
#include "cromtablemodel.h"

#include<QValidator>
#include<QRegExpValidator>
#include<QLineEdit>

QWidget *CRomEditorDelegate::createEditor(QWidget *parent,
                                          const QStyleOptionViewItem &/*option*/,
                                          const QModelIndex &index) const {

    QLineEdit *edit = new QLineEdit(parent);

    const CRomTableModel *romModel = static_cast<const CRomTableModel*>(index.model());
    if ((0 <= index.column()) && (index.column() < (int)romModel->RomColCount())) {
        QRegExp rx(QString("[0-9a-fA-F]{0,%1}").arg(romModel->HexDigitsForRomColDim(index.column())));
        QValidator *validator = new QRegExpValidator(rx);

        edit->setValidator(validator);
    }

    return edit;
}

void CRomEditorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);

    const CRomTableModel *romModel = static_cast<const CRomTableModel*>(index.model());
    if ((0 <= index.column()) && (index.column() < (int)romModel->RomColCount())) {
        lineEdit->setText(index.model()->data(index, Qt::EditRole).toString());
    } else {
        QString value = index.model()->data(index, Qt::EditRole).toString();
        lineEdit->setText(value);
    }
}

void CRomEditorDelegate::setModelData(QWidget *editor,
                                      QAbstractItemModel *model,
                                      const QModelIndex &index) const {
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    const CRomTableModel *romModel = static_cast<const CRomTableModel*>(index.model());

    if ((0 <= index.column()) && (index.column() < (int)romModel->RomColCount())) {
        bool isOk;
        unsigned int value = lineEdit->text().toUpper().toUInt(&isOk, 16);
        if (isOk)
            model->setData(index, value, Qt::EditRole);
    } else {
        model->setData(index, lineEdit->text(), Qt::EditRole);
    }
}

void CRomEditorDelegate::updateEditorGeometry(QWidget *editor,
                                              const QStyleOptionViewItem &option,
                                              const QModelIndex &/*index*/) const {

    editor->setGeometry(option.rect);
}

