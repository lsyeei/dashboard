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
#include <QtWidgets/QCheckBox>
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
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *selectAll;
    QSpacerItem *horizontalSpacer;
    QToolButton *delBtn;
    QToolButton *importBtn;
    QTableView *tableView;
    QLabel *label;

    void setupUi(QDialog *UserPluginManageForm)
    {
        if (UserPluginManageForm->objectName().isEmpty())
            UserPluginManageForm->setObjectName("UserPluginManageForm");
        UserPluginManageForm->setWindowModality(Qt::WindowModality::WindowModal);
        UserPluginManageForm->resize(400, 300);
        verticalLayout = new QVBoxLayout(UserPluginManageForm);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_2 = new QSpacerItem(15, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        selectAll = new QCheckBox(UserPluginManageForm);
        selectAll->setObjectName("selectAll");

        horizontalLayout->addWidget(selectAll);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        delBtn = new QToolButton(UserPluginManageForm);
        delBtn->setObjectName("delBtn");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::EditDelete));
        delBtn->setIcon(icon);
        delBtn->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextBesideIcon);

        horizontalLayout->addWidget(delBtn);

        importBtn = new QToolButton(UserPluginManageForm);
        importBtn->setObjectName("importBtn");
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::GoDown));
        importBtn->setIcon(icon1);
        importBtn->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextBesideIcon);

        horizontalLayout->addWidget(importBtn);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new QTableView(UserPluginManageForm);
        tableView->setObjectName("tableView");
        tableView->setFrameShape(QFrame::Shape::Box);

        verticalLayout->addWidget(tableView);

        label = new QLabel(UserPluginManageForm);
        label->setObjectName("label");

        verticalLayout->addWidget(label);


        retranslateUi(UserPluginManageForm);

        QMetaObject::connectSlotsByName(UserPluginManageForm);
    } // setupUi

    void retranslateUi(QDialog *UserPluginManageForm)
    {
        UserPluginManageForm->setWindowTitle(QCoreApplication::translate("UserPluginManageForm", "\347\256\241\347\220\206\345\233\276\345\205\203", nullptr));
        selectAll->setText(QCoreApplication::translate("UserPluginManageForm", "\345\205\250\351\200\211", nullptr));
        delBtn->setText(QCoreApplication::translate("UserPluginManageForm", "\345\210\240\351\231\244", nullptr));
        importBtn->setText(QCoreApplication::translate("UserPluginManageForm", "\345\257\274\345\205\245", nullptr));
        label->setText(QCoreApplication::translate("UserPluginManageForm", "\346\217\220\347\244\272\357\274\232\345\220\215\347\247\260\345\222\214\345\244\207\346\263\250\345\217\257\344\273\245\345\234\250\345\210\227\350\241\250\344\270\255\344\277\256\346\224\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserPluginManageForm: public Ui_UserPluginManageForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERPLUGINMANAGEFORM_H
