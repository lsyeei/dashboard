/********************************************************************************
** Form generated from reading UI file 'userplugingroupdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERPLUGINGROUPDIALOG_H
#define UI_USERPLUGINGROUPDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_UserPluginGroupDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QComboBox *pluginGroup;
    QToolButton *newBtn;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *UserPluginGroupDialog)
    {
        if (UserPluginGroupDialog->objectName().isEmpty())
            UserPluginGroupDialog->setObjectName("UserPluginGroupDialog");
        UserPluginGroupDialog->resize(265, 96);
        UserPluginGroupDialog->setModal(true);
        verticalLayout = new QVBoxLayout(UserPluginGroupDialog);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(UserPluginGroupDialog);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pluginGroup = new QComboBox(UserPluginGroupDialog);
        pluginGroup->setObjectName("pluginGroup");

        horizontalLayout->addWidget(pluginGroup);

        newBtn = new QToolButton(UserPluginGroupDialog);
        newBtn->setObjectName("newBtn");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::FolderNew));
        newBtn->setIcon(icon);
        newBtn->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextBesideIcon);

        horizontalLayout->addWidget(newBtn);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(UserPluginGroupDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        buttonBox->setCenterButtons(true);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(UserPluginGroupDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, UserPluginGroupDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, UserPluginGroupDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(UserPluginGroupDialog);
    } // setupUi

    void retranslateUi(QDialog *UserPluginGroupDialog)
    {
        UserPluginGroupDialog->setWindowTitle(QCoreApplication::translate("UserPluginGroupDialog", "\351\200\211\346\213\251\345\233\276\345\205\203\345\210\206\347\273\204", nullptr));
        label->setText(QCoreApplication::translate("UserPluginGroupDialog", "\351\200\211\346\213\251\345\233\276\345\205\203\345\210\206\347\273\204", nullptr));
        newBtn->setText(QCoreApplication::translate("UserPluginGroupDialog", "\346\226\260\345\273\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserPluginGroupDialog: public Ui_UserPluginGroupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERPLUGINGROUPDIALOG_H
