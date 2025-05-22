/********************************************************************************
** Form generated from reading UI file 'userpluginmanageform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERPLUGINMANAGEFORM_H
#define UI_USERPLUGINMANAGEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_UserPluginManageForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QToolButton *importBtn;
    QToolButton *delBtn;
    QTableView *tableView;

    void setupUi(QDialog *userPluginManageForm)
    {
        if (userPluginManageForm->objectName().isEmpty())
            userPluginManageForm->setObjectName("userPluginManageForm");
        userPluginManageForm->setWindowModality(Qt::WindowModality::WindowModal);
        userPluginManageForm->resize(400, 300);
        verticalLayout = new QVBoxLayout(userPluginManageForm);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(userPluginManageForm);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        importBtn = new QToolButton(userPluginManageForm);
        importBtn->setObjectName("importBtn");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/bottom.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        importBtn->setIcon(icon);
        importBtn->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextBesideIcon);

        horizontalLayout->addWidget(importBtn);

        delBtn = new QToolButton(userPluginManageForm);
        delBtn->setObjectName("delBtn");
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::EditClear));
        delBtn->setIcon(icon1);
        delBtn->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextBesideIcon);

        horizontalLayout->addWidget(delBtn);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new QTableView(userPluginManageForm);
        tableView->setObjectName("tableView");
        tableView->setFrameShape(QFrame::Shape::Box);

        verticalLayout->addWidget(tableView);


        retranslateUi(userPluginManageForm);

        QMetaObject::connectSlotsByName(userPluginManageForm);
    } // setupUi

    void retranslateUi(QDialog *userPluginManageForm)
    {
        userPluginManageForm->setWindowTitle(QCoreApplication::translate("UserPluginManageForm", "\347\256\241\347\220\206\345\233\276\345\205\203", nullptr));
        label->setText(QCoreApplication::translate("UserPluginManageForm", "\346\217\220\347\244\272\357\274\232\345\220\215\347\247\260\345\222\214\345\244\207\346\263\250\345\217\257\344\273\245\345\234\250\345\210\227\350\241\250\344\270\255\344\277\256\346\224\271", nullptr));
        importBtn->setText(QCoreApplication::translate("UserPluginManageForm", "\345\257\274\345\205\245", nullptr));
        delBtn->setText(QCoreApplication::translate("UserPluginManageForm", "\345\210\240\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserPluginManageForm: public Ui_UserPluginManageForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERPLUGINMANAGEFORM_H
