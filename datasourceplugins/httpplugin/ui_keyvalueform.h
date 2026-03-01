/********************************************************************************
** Form generated from reading UI file 'keyvalueform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KEYVALUEFORM_H
#define UI_KEYVALUEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KeyValueForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QToolButton *addBtn;
    QToolButton *delBtn;
    QTableWidget *keyValueTable;

    void setupUi(QWidget *KeyValueForm)
    {
        if (KeyValueForm->objectName().isEmpty())
            KeyValueForm->setObjectName("KeyValueForm");
        KeyValueForm->resize(250, 83);
        verticalLayout = new QVBoxLayout(KeyValueForm);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(4);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label = new QLabel(KeyValueForm);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(label);

        addBtn = new QToolButton(KeyValueForm);
        addBtn->setObjectName("addBtn");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(addBtn->sizePolicy().hasHeightForWidth());
        addBtn->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(addBtn);

        delBtn = new QToolButton(KeyValueForm);
        delBtn->setObjectName("delBtn");
        sizePolicy1.setHeightForWidth(delBtn->sizePolicy().hasHeightForWidth());
        delBtn->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(delBtn);


        verticalLayout->addLayout(horizontalLayout_5);

        keyValueTable = new QTableWidget(KeyValueForm);
        if (keyValueTable->columnCount() < 3)
            keyValueTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        keyValueTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        keyValueTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        keyValueTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        keyValueTable->setObjectName("keyValueTable");
        sizePolicy1.setHeightForWidth(keyValueTable->sizePolicy().hasHeightForWidth());
        keyValueTable->setSizePolicy(sizePolicy1);
        keyValueTable->setFrameShape(QFrame::Shape::Box);
        keyValueTable->setFrameShadow(QFrame::Shadow::Plain);
        keyValueTable->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents);
        keyValueTable->setEditTriggers(QAbstractItemView::EditTrigger::DoubleClicked|QAbstractItemView::EditTrigger::EditKeyPressed);
        keyValueTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        keyValueTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        keyValueTable->setRowCount(0);
        keyValueTable->setColumnCount(3);

        verticalLayout->addWidget(keyValueTable);


        retranslateUi(KeyValueForm);

        QMetaObject::connectSlotsByName(KeyValueForm);
    } // setupUi

    void retranslateUi(QWidget *KeyValueForm)
    {
        KeyValueForm->setWindowTitle(QCoreApplication::translate("KeyValueForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("KeyValueForm", "\345\217\214\345\207\273\350\241\250\346\240\274\350\277\233\345\205\245\347\274\226\350\276\221\346\250\241\345\274\217", nullptr));
#if QT_CONFIG(tooltip)
        addBtn->setToolTip(QCoreApplication::translate("KeyValueForm", "\346\267\273\345\212\240", nullptr));
#endif // QT_CONFIG(tooltip)
        addBtn->setText(QCoreApplication::translate("KeyValueForm", " + ", nullptr));
#if QT_CONFIG(tooltip)
        delBtn->setToolTip(QCoreApplication::translate("KeyValueForm", "\345\210\240\351\231\244", nullptr));
#endif // QT_CONFIG(tooltip)
        delBtn->setText(QCoreApplication::translate("KeyValueForm", " - ", nullptr));
        QTableWidgetItem *___qtablewidgetitem = keyValueTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("KeyValueForm", "\345\217\202\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = keyValueTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("KeyValueForm", "\351\273\230\350\256\244\345\200\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = keyValueTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("KeyValueForm", "\350\257\264\346\230\216", nullptr));
    } // retranslateUi

};

namespace Ui {
    class KeyValueForm: public Ui_KeyValueForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEYVALUEFORM_H
