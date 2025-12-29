/********************************************************************************
** Form generated from reading UI file 'datadirdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATADIRDIALOG_H
#define UI_DATADIRDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataDirDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *topRadio;
    QRadioButton *childRadio;
    QHBoxLayout *horizontalLayout_5;
    QLabel *parentItem;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *dirNameEdit;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *dataSourceCheckBox;
    QComboBox *dataSourceComboBox;
    QSpacerItem *horizontalSpacer_2;
    QWidget *dataSourceWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *DataDirDialog)
    {
        if (DataDirDialog->objectName().isEmpty())
            DataDirDialog->setObjectName("DataDirDialog");
        DataDirDialog->resize(221, 184);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DataDirDialog->sizePolicy().hasHeightForWidth());
        DataDirDialog->setSizePolicy(sizePolicy);
        DataDirDialog->setAutoFillBackground(true);
        verticalLayout = new QVBoxLayout(DataDirDialog);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        topRadio = new QRadioButton(DataDirDialog);
        topRadio->setObjectName("topRadio");
        topRadio->setChecked(true);

        horizontalLayout_4->addWidget(topRadio);

        childRadio = new QRadioButton(DataDirDialog);
        childRadio->setObjectName("childRadio");

        horizontalLayout_4->addWidget(childRadio);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        parentItem = new QLabel(DataDirDialog);
        parentItem->setObjectName("parentItem");

        horizontalLayout_5->addWidget(parentItem);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(DataDirDialog);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        dirNameEdit = new QLineEdit(DataDirDialog);
        dirNameEdit->setObjectName("dirNameEdit");

        horizontalLayout->addWidget(dirNameEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        dataSourceCheckBox = new QCheckBox(DataDirDialog);
        dataSourceCheckBox->setObjectName("dataSourceCheckBox");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dataSourceCheckBox->sizePolicy().hasHeightForWidth());
        dataSourceCheckBox->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(dataSourceCheckBox);

        dataSourceComboBox = new QComboBox(DataDirDialog);
        dataSourceComboBox->setObjectName("dataSourceComboBox");

        horizontalLayout_2->addWidget(dataSourceComboBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        dataSourceWidget = new QWidget(DataDirDialog);
        dataSourceWidget->setObjectName("dataSourceWidget");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(dataSourceWidget->sizePolicy().hasHeightForWidth());
        dataSourceWidget->setSizePolicy(sizePolicy2);
        verticalLayout_2 = new QVBoxLayout(dataSourceWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);

        verticalLayout->addWidget(dataSourceWidget);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        okButton = new QPushButton(DataDirDialog);
        okButton->setObjectName("okButton");

        horizontalLayout_3->addWidget(okButton);

        cancelButton = new QPushButton(DataDirDialog);
        cancelButton->setObjectName("cancelButton");

        horizontalLayout_3->addWidget(cancelButton);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(DataDirDialog);

        QMetaObject::connectSlotsByName(DataDirDialog);
    } // setupUi

    void retranslateUi(QDialog *DataDirDialog)
    {
        DataDirDialog->setWindowTitle(QCoreApplication::translate("DataDirDialog", "\346\225\260\346\215\256\347\233\256\345\275\225", nullptr));
        topRadio->setText(QCoreApplication::translate("DataDirDialog", "\351\241\266\345\261\202\345\210\206\347\261\273", nullptr));
        childRadio->setText(QCoreApplication::translate("DataDirDialog", "\344\270\213\347\272\247\345\210\206\347\261\273", nullptr));
        parentItem->setText(QCoreApplication::translate("DataDirDialog", "\344\270\212\347\272\247\345\210\206\347\261\273", nullptr));
        label->setText(QCoreApplication::translate("DataDirDialog", "\345\220\215\347\247\260", nullptr));
        dataSourceCheckBox->setText(QCoreApplication::translate("DataDirDialog", "\346\225\260\346\215\256\346\272\220", nullptr));
        okButton->setText(QCoreApplication::translate("DataDirDialog", "\347\241\256\345\256\232", nullptr));
        cancelButton->setText(QCoreApplication::translate("DataDirDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DataDirDialog: public Ui_DataDirDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATADIRDIALOG_H
