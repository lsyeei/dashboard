/********************************************************************************
** Form generated from reading UI file 'bicomboboxform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BICOMBOBOXFORM_H
#define UI_BICOMBOBOXFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ComboBoxForm
{
public:
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer;
    QToolButton *addBtn;
    QToolButton *editBtn;
    QToolButton *removeBtn;

    void setupUi(QWidget *ComboBoxForm)
    {
        if (ComboBoxForm->objectName().isEmpty())
            ComboBoxForm->setObjectName("ComboBoxForm");
        ComboBoxForm->resize(161, 24);
        horizontalLayout = new QHBoxLayout(ComboBoxForm);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        comboBox = new QComboBox(ComboBoxForm);
        comboBox->setObjectName("comboBox");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy);
        comboBox->setEditable(false);
        comboBox->setInsertPolicy(QComboBox::InsertPolicy::InsertAtTop);

        horizontalLayout->addWidget(comboBox);

        horizontalSpacer = new QSpacerItem(5, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        addBtn = new QToolButton(ComboBoxForm);
        addBtn->setObjectName("addBtn");

        horizontalLayout->addWidget(addBtn);

        editBtn = new QToolButton(ComboBoxForm);
        editBtn->setObjectName("editBtn");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::MailMessageNew));
        editBtn->setIcon(icon);
        editBtn->setIconSize(QSize(16, 16));

        horizontalLayout->addWidget(editBtn);

        removeBtn = new QToolButton(ComboBoxForm);
        removeBtn->setObjectName("removeBtn");

        horizontalLayout->addWidget(removeBtn);


        retranslateUi(ComboBoxForm);

        comboBox->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(ComboBoxForm);
    } // setupUi

    void retranslateUi(QWidget *ComboBoxForm)
    {
        ComboBoxForm->setWindowTitle(QCoreApplication::translate("ComboBoxForm", "Form", nullptr));
        comboBox->setCurrentText(QString());
        comboBox->setPlaceholderText(QString());
        addBtn->setText(QCoreApplication::translate("ComboBoxForm", "+", nullptr));
        editBtn->setText(QString());
        removeBtn->setText(QCoreApplication::translate("ComboBoxForm", "-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ComboBoxForm: public Ui_ComboBoxForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BICOMBOBOXFORM_H
