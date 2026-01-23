/********************************************************************************
** Form generated from reading UI file 'datacontrolform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATACONTROLFORM_H
#define UI_DATACONTROLFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataControlForm
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QToolButton *addBtn;
    QToolButton *delBtn;
    QTableWidget *actionTable;
    QWidget *configWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *symbolOptions;
    QDoubleSpinBox *minValueSpin;
    QLabel *valueSpliter;
    QDoubleSpinBox *maxValueSpin;
    QHBoxLayout *horizontalLayout_3;
    QLabel *controlLabel;
    QComboBox *controlOptions;
    QWidget *stateWidget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QComboBox *stateOptions;
    QWidget *animateWidget;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QComboBox *animationOptions;
    QWidget *propertyWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QComboBox *propertyOptions;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_8;
    QLineEdit *propertyValueEdit;
    QHBoxLayout *horizontalLayout_8;
    QLabel *propertyLabel;

    void setupUi(QWidget *DataControlForm)
    {
        if (DataControlForm->objectName().isEmpty())
            DataControlForm->setObjectName("DataControlForm");
        DataControlForm->resize(211, 298);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DataControlForm->sizePolicy().hasHeightForWidth());
        DataControlForm->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(DataControlForm);
        verticalLayout_2->setSpacing(8);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(DataControlForm);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        addBtn = new QToolButton(DataControlForm);
        addBtn->setObjectName("addBtn");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::ListAdd));
        addBtn->setIcon(icon);

        horizontalLayout->addWidget(addBtn);

        delBtn = new QToolButton(DataControlForm);
        delBtn->setObjectName("delBtn");
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::ListRemove));
        delBtn->setIcon(icon1);

        horizontalLayout->addWidget(delBtn);


        verticalLayout_2->addLayout(horizontalLayout);

        actionTable = new QTableWidget(DataControlForm);
        actionTable->setObjectName("actionTable");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(actionTable->sizePolicy().hasHeightForWidth());
        actionTable->setSizePolicy(sizePolicy1);
        actionTable->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustIgnored);
        actionTable->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        actionTable->setDragDropOverwriteMode(false);
        actionTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        actionTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        verticalLayout_2->addWidget(actionTable);

        configWidget = new QWidget(DataControlForm);
        configWidget->setObjectName("configWidget");
        verticalLayout_3 = new QVBoxLayout(configWidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        label_2 = new QLabel(configWidget);
        label_2->setObjectName("label_2");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(label_2);

        symbolOptions = new QComboBox(configWidget);
        symbolOptions->setObjectName("symbolOptions");

        horizontalLayout_2->addWidget(symbolOptions);

        minValueSpin = new QDoubleSpinBox(configWidget);
        minValueSpin->setObjectName("minValueSpin");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(minValueSpin->sizePolicy().hasHeightForWidth());
        minValueSpin->setSizePolicy(sizePolicy3);
        minValueSpin->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        minValueSpin->setDecimals(1);
        minValueSpin->setMinimum(-99999.000000000000000);
        minValueSpin->setMaximum(99999.000000000000000);

        horizontalLayout_2->addWidget(minValueSpin);

        valueSpliter = new QLabel(configWidget);
        valueSpliter->setObjectName("valueSpliter");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(valueSpliter->sizePolicy().hasHeightForWidth());
        valueSpliter->setSizePolicy(sizePolicy4);

        horizontalLayout_2->addWidget(valueSpliter);

        maxValueSpin = new QDoubleSpinBox(configWidget);
        maxValueSpin->setObjectName("maxValueSpin");
        sizePolicy3.setHeightForWidth(maxValueSpin->sizePolicy().hasHeightForWidth());
        maxValueSpin->setSizePolicy(sizePolicy3);
        maxValueSpin->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        maxValueSpin->setDecimals(1);
        maxValueSpin->setMinimum(-99999.000000000000000);
        maxValueSpin->setMaximum(99999.000000000000000);

        horizontalLayout_2->addWidget(maxValueSpin);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        controlLabel = new QLabel(configWidget);
        controlLabel->setObjectName("controlLabel");
        sizePolicy2.setHeightForWidth(controlLabel->sizePolicy().hasHeightForWidth());
        controlLabel->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(controlLabel);

        controlOptions = new QComboBox(configWidget);
        controlOptions->setObjectName("controlOptions");

        horizontalLayout_3->addWidget(controlOptions);


        verticalLayout_3->addLayout(horizontalLayout_3);

        stateWidget = new QWidget(configWidget);
        stateWidget->setObjectName("stateWidget");
        horizontalLayout_4 = new QHBoxLayout(stateWidget);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(stateWidget);
        label_5->setObjectName("label_5");
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(label_5);

        stateOptions = new QComboBox(stateWidget);
        stateOptions->setObjectName("stateOptions");

        horizontalLayout_4->addWidget(stateOptions);


        verticalLayout_3->addWidget(stateWidget);

        animateWidget = new QWidget(configWidget);
        animateWidget->setObjectName("animateWidget");
        horizontalLayout_5 = new QHBoxLayout(animateWidget);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(animateWidget);
        label_6->setObjectName("label_6");
        sizePolicy2.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy2);

        horizontalLayout_5->addWidget(label_6);

        animationOptions = new QComboBox(animateWidget);
        animationOptions->setObjectName("animationOptions");

        horizontalLayout_5->addWidget(animationOptions);


        verticalLayout_3->addWidget(animateWidget);

        propertyWidget = new QWidget(configWidget);
        propertyWidget->setObjectName("propertyWidget");
        verticalLayout = new QVBoxLayout(propertyWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_7 = new QLabel(propertyWidget);
        label_7->setObjectName("label_7");
        sizePolicy2.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy2);

        horizontalLayout_7->addWidget(label_7);

        propertyOptions = new QComboBox(propertyWidget);
        propertyOptions->setObjectName("propertyOptions");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(propertyOptions->sizePolicy().hasHeightForWidth());
        propertyOptions->setSizePolicy(sizePolicy5);

        horizontalLayout_7->addWidget(propertyOptions);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_8 = new QLabel(propertyWidget);
        label_8->setObjectName("label_8");
        sizePolicy2.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy2);

        horizontalLayout_6->addWidget(label_8);

        propertyValueEdit = new QLineEdit(propertyWidget);
        propertyValueEdit->setObjectName("propertyValueEdit");
        sizePolicy.setHeightForWidth(propertyValueEdit->sizePolicy().hasHeightForWidth());
        propertyValueEdit->setSizePolicy(sizePolicy);
        propertyValueEdit->setFrame(true);
        propertyValueEdit->setClearButtonEnabled(true);

        horizontalLayout_6->addWidget(propertyValueEdit);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        propertyLabel = new QLabel(propertyWidget);
        propertyLabel->setObjectName("propertyLabel");
        QSizePolicy sizePolicy6(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(propertyLabel->sizePolicy().hasHeightForWidth());
        propertyLabel->setSizePolicy(sizePolicy6);
        propertyLabel->setMargin(10);

        horizontalLayout_8->addWidget(propertyLabel);


        verticalLayout->addLayout(horizontalLayout_8);


        verticalLayout_3->addWidget(propertyWidget);


        verticalLayout_2->addWidget(configWidget);


        retranslateUi(DataControlForm);

        QMetaObject::connectSlotsByName(DataControlForm);
    } // setupUi

    void retranslateUi(QWidget *DataControlForm)
    {
        DataControlForm->setWindowTitle(QCoreApplication::translate("DataControlForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("DataControlForm", "\346\235\241\344\273\266\344\270\216\345\212\250\344\275\234", nullptr));
#if QT_CONFIG(tooltip)
        addBtn->setToolTip(QCoreApplication::translate("DataControlForm", "\346\267\273\345\212\240\346\235\241\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        addBtn->setText(QString());
#if QT_CONFIG(tooltip)
        delBtn->setToolTip(QCoreApplication::translate("DataControlForm", "\345\210\240\351\231\244\346\235\241\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        delBtn->setText(QCoreApplication::translate("DataControlForm", "...", nullptr));
        label_2->setText(QCoreApplication::translate("DataControlForm", "\346\235\241\344\273\266", nullptr));
        valueSpliter->setText(QCoreApplication::translate("DataControlForm", "-", nullptr));
        controlLabel->setText(QCoreApplication::translate("DataControlForm", "\345\212\250\344\275\234", nullptr));
        label_5->setText(QCoreApplication::translate("DataControlForm", "\345\210\207\346\215\242\345\210\260", nullptr));
        label_6->setText(QCoreApplication::translate("DataControlForm", "\346\222\255\346\224\276", nullptr));
        label_7->setText(QCoreApplication::translate("DataControlForm", "\345\233\276\345\205\203\345\261\236\346\200\247", nullptr));
        label_8->setText(QCoreApplication::translate("DataControlForm", "\350\256\276\347\275\256\344\270\272", nullptr));
        propertyLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DataControlForm: public Ui_DataControlForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATACONTROLFORM_H
