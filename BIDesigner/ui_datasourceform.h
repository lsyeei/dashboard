/********************************************************************************
** Form generated from reading UI file 'datasourceform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATASOURCEFORM_H
#define UI_DATASOURCEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <datasource/customtreewidget.h>

QT_BEGIN_NAMESPACE

class Ui_DataSourceForm
{
public:
    QAction *addCategory;
    QAction *delCategory;
    QAction *editCategory;
    QAction *addData;
    QAction *editData;
    QAction *delData;
    QVBoxLayout *verticalLayout;
    QWidget *toolWidget;
    QSplitter *splitter;
    CustomTreeWidget *dataDir;
    QTableWidget *dataTable;

    void setupUi(QDialog *DataSourceForm)
    {
        if (DataSourceForm->objectName().isEmpty())
            DataSourceForm->setObjectName("DataSourceForm");
        DataSourceForm->setWindowModality(Qt::WindowModality::ApplicationModal);
        DataSourceForm->resize(620, 410);
        addCategory = new QAction(DataSourceForm);
        addCategory->setObjectName("addCategory");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/tree_add.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        addCategory->setIcon(icon);
        addCategory->setMenuRole(QAction::MenuRole::NoRole);
        delCategory = new QAction(DataSourceForm);
        delCategory->setObjectName("delCategory");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/tree_delete.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        delCategory->setIcon(icon1);
        delCategory->setMenuRole(QAction::MenuRole::NoRole);
        editCategory = new QAction(DataSourceForm);
        editCategory->setObjectName("editCategory");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/icons/tree_edit.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        editCategory->setIcon(icon2);
        editCategory->setMenuRole(QAction::MenuRole::NoRole);
        addData = new QAction(DataSourceForm);
        addData->setObjectName("addData");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/icons/data_add.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        addData->setIcon(icon3);
        addData->setMenuRole(QAction::MenuRole::NoRole);
        editData = new QAction(DataSourceForm);
        editData->setObjectName("editData");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/icons/data_edit.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        editData->setIcon(icon4);
        editData->setMenuRole(QAction::MenuRole::NoRole);
        delData = new QAction(DataSourceForm);
        delData->setObjectName("delData");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/icons/data_delete.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        delData->setIcon(icon5);
        delData->setMenuRole(QAction::MenuRole::NoRole);
        verticalLayout = new QVBoxLayout(DataSourceForm);
        verticalLayout->setObjectName("verticalLayout");
        toolWidget = new QWidget(DataSourceForm);
        toolWidget->setObjectName("toolWidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(toolWidget->sizePolicy().hasHeightForWidth());
        toolWidget->setSizePolicy(sizePolicy);
        toolWidget->setMinimumSize(QSize(0, 24));

        verticalLayout->addWidget(toolWidget);

        splitter = new QSplitter(DataSourceForm);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Orientation::Horizontal);
        dataDir = new CustomTreeWidget(splitter);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        dataDir->setHeaderItem(__qtreewidgetitem);
        dataDir->setObjectName("dataDir");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dataDir->sizePolicy().hasHeightForWidth());
        dataDir->setSizePolicy(sizePolicy1);
        splitter->addWidget(dataDir);
        dataDir->header()->setVisible(false);
        dataTable = new QTableWidget(splitter);
        dataTable->setObjectName("dataTable");
        splitter->addWidget(dataTable);
        dataTable->verticalHeader()->setProperty("showSortIndicator", QVariant(true));

        verticalLayout->addWidget(splitter);


        retranslateUi(DataSourceForm);

        QMetaObject::connectSlotsByName(DataSourceForm);
    } // setupUi

    void retranslateUi(QDialog *DataSourceForm)
    {
        DataSourceForm->setWindowTitle(QCoreApplication::translate("DataSourceForm", "\346\225\260\346\215\256\346\272\220", nullptr));
        addCategory->setText(QCoreApplication::translate("DataSourceForm", "\346\226\260\345\273\272\345\210\206\347\261\273", nullptr));
#if QT_CONFIG(tooltip)
        addCategory->setToolTip(QCoreApplication::translate("DataSourceForm", "\346\267\273\345\212\240\346\225\260\346\215\256\345\210\206\347\261\273", nullptr));
#endif // QT_CONFIG(tooltip)
        delCategory->setText(QCoreApplication::translate("DataSourceForm", "\345\210\240\351\231\244\345\210\206\347\261\273", nullptr));
#if QT_CONFIG(tooltip)
        delCategory->setToolTip(QCoreApplication::translate("DataSourceForm", "\345\210\240\351\231\244\346\225\260\346\215\256\345\210\206\347\261\273", nullptr));
#endif // QT_CONFIG(tooltip)
        editCategory->setText(QCoreApplication::translate("DataSourceForm", "\347\274\226\350\276\221\345\210\206\347\261\273", nullptr));
#if QT_CONFIG(tooltip)
        editCategory->setToolTip(QCoreApplication::translate("DataSourceForm", "\347\274\226\350\276\221\346\225\260\346\215\256\345\210\206\347\261\273", nullptr));
#endif // QT_CONFIG(tooltip)
        addData->setText(QCoreApplication::translate("DataSourceForm", "\346\267\273\345\212\240\346\225\260\346\215\256", nullptr));
#if QT_CONFIG(tooltip)
        addData->setToolTip(QCoreApplication::translate("DataSourceForm", "\346\267\273\345\212\240\346\225\260\346\215\256", nullptr));
#endif // QT_CONFIG(tooltip)
        editData->setText(QCoreApplication::translate("DataSourceForm", "\344\277\256\346\224\271\346\225\260\346\215\256", nullptr));
#if QT_CONFIG(tooltip)
        editData->setToolTip(QCoreApplication::translate("DataSourceForm", "\344\277\256\346\224\271\346\225\260\346\215\256", nullptr));
#endif // QT_CONFIG(tooltip)
        delData->setText(QCoreApplication::translate("DataSourceForm", "\345\210\240\351\231\244\346\225\260\346\215\256", nullptr));
#if QT_CONFIG(tooltip)
        delData->setToolTip(QCoreApplication::translate("DataSourceForm", "\345\210\240\351\231\244\346\225\260\346\215\256", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

namespace Ui {
    class DataSourceForm: public Ui_DataSourceForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATASOURCEFORM_H
