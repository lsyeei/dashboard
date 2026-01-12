/********************************************************************************
** Form generated from reading UI file 'dataselectordialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATASELECTORDIALOG_H
#define UI_DATASELECTORDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DataSelectorDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

    void setupUi(QDialog *DataSelectorDialog)
    {
        if (DataSelectorDialog->objectName().isEmpty())
            DataSelectorDialog->setObjectName("DataSelectorDialog");
        DataSelectorDialog->resize(364, 108);
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::FolderOpen));
        DataSelectorDialog->setWindowIcon(icon);
        DataSelectorDialog->setAutoFillBackground(true);
        verticalLayout = new QVBoxLayout(DataSelectorDialog);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okBtn = new QPushButton(DataSelectorDialog);
        okBtn->setObjectName("okBtn");

        horizontalLayout->addWidget(okBtn);

        cancelBtn = new QPushButton(DataSelectorDialog);
        cancelBtn->setObjectName("cancelBtn");

        horizontalLayout->addWidget(cancelBtn);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(DataSelectorDialog);

        QMetaObject::connectSlotsByName(DataSelectorDialog);
    } // setupUi

    void retranslateUi(QDialog *DataSelectorDialog)
    {
        DataSelectorDialog->setWindowTitle(QCoreApplication::translate("DataSelectorDialog", "\351\200\211\346\213\251\346\225\260\346\215\256", nullptr));
        okBtn->setText(QCoreApplication::translate("DataSelectorDialog", "\347\241\256\345\256\232", nullptr));
        cancelBtn->setText(QCoreApplication::translate("DataSelectorDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DataSelectorDialog: public Ui_DataSelectorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATASELECTORDIALOG_H
