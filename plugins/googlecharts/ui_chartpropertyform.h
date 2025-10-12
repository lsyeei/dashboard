/********************************************************************************
** Form generated from reading UI file 'chartpropertyform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARTPROPERTYFORM_H
#define UI_CHARTPROPERTYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "bicombobox.h"
#include "fillproperty.h"
#include "lineproperty.h"
#include "posproperty.h"

QT_BEGIN_NAMESPACE

class Ui_ChartPropertyForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    BIComboBox *stateBox;
    QFrame *line_4;
    PosProperty *posProperty;
    QFrame *line_2;
    LineProperty *lineProperty;
    QFrame *line;
    FillProperty *fillProperty;
    QFrame *line_3;
    QHBoxLayout *roundLayout;
    QCheckBox *roundChecked;
    QSpacerItem *roundSpacer;
    QSpinBox *roundSize;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *rotateSpacer;
    QDoubleSpinBox *rotation;
    QVBoxLayout *chartStyle;
    QLabel *label_4;
    QTextEdit *options;
    QVBoxLayout *chartData;
    QLabel *label_3;
    QTextEdit *defaultData;
    QHBoxLayout *updateBtnLayout;
    QPushButton *updateBtn;
    QSpacerItem *horizontalSpacer;
    QWidget *extendWidget;
    QVBoxLayout *verticalLayout_2;

    void setupUi(QWidget *ChartPropertyForm)
    {
        if (ChartPropertyForm->objectName().isEmpty())
            ChartPropertyForm->setObjectName("ChartPropertyForm");
        ChartPropertyForm->setEnabled(true);
        ChartPropertyForm->resize(223, 869);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ChartPropertyForm->sizePolicy().hasHeightForWidth());
        ChartPropertyForm->setSizePolicy(sizePolicy);
        ChartPropertyForm->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(ChartPropertyForm);
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        verticalLayout->setContentsMargins(0, -1, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_2 = new QLabel(ChartPropertyForm);
        label_2->setObjectName("label_2");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(label_2);

        stateBox = new BIComboBox(ChartPropertyForm);
        stateBox->setObjectName("stateBox");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(stateBox->sizePolicy().hasHeightForWidth());
        stateBox->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(stateBox);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 5);

        verticalLayout->addLayout(horizontalLayout_3);

        line_4 = new QFrame(ChartPropertyForm);
        line_4->setObjectName("line_4");
        sizePolicy2.setHeightForWidth(line_4->sizePolicy().hasHeightForWidth());
        line_4->setSizePolicy(sizePolicy2);
        line_4->setFrameShadow(QFrame::Shadow::Sunken);
        line_4->setLineWidth(1);
        line_4->setFrameShape(QFrame::Shape::HLine);

        verticalLayout->addWidget(line_4);

        posProperty = new PosProperty(ChartPropertyForm);
        posProperty->setObjectName("posProperty");
        sizePolicy.setHeightForWidth(posProperty->sizePolicy().hasHeightForWidth());
        posProperty->setSizePolicy(sizePolicy);
        posProperty->setMinimumSize(QSize(142, 123));

        verticalLayout->addWidget(posProperty);

        line_2 = new QFrame(ChartPropertyForm);
        line_2->setObjectName("line_2");
        sizePolicy2.setHeightForWidth(line_2->sizePolicy().hasHeightForWidth());
        line_2->setSizePolicy(sizePolicy2);
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line_2);

        lineProperty = new LineProperty(ChartPropertyForm);
        lineProperty->setObjectName("lineProperty");
        sizePolicy.setHeightForWidth(lineProperty->sizePolicy().hasHeightForWidth());
        lineProperty->setSizePolicy(sizePolicy);
        lineProperty->setMinimumSize(QSize(99, 52));
        lineProperty->setMaximumSize(QSize(16777215, 16777215));
        lineProperty->setShowLine(true);

        verticalLayout->addWidget(lineProperty);

        line = new QFrame(ChartPropertyForm);
        line->setObjectName("line");
        sizePolicy2.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy2);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        line->setLineWidth(1);
        line->setFrameShape(QFrame::Shape::HLine);

        verticalLayout->addWidget(line);

        fillProperty = new FillProperty(ChartPropertyForm);
        fillProperty->setObjectName("fillProperty");
        fillProperty->setEnabled(true);
        sizePolicy.setHeightForWidth(fillProperty->sizePolicy().hasHeightForWidth());
        fillProperty->setSizePolicy(sizePolicy);
        fillProperty->setMinimumSize(QSize(173, 79));
        fillProperty->setMaximumSize(QSize(16777215, 16777215));
        fillProperty->setProperty("fill", QVariant(true));
        fillProperty->setBrushStyle(Qt::BrushStyle::SolidPattern);

        verticalLayout->addWidget(fillProperty);

        line_3 = new QFrame(ChartPropertyForm);
        line_3->setObjectName("line_3");
        sizePolicy2.setHeightForWidth(line_3->sizePolicy().hasHeightForWidth());
        line_3->setSizePolicy(sizePolicy2);
        line_3->setFrameShape(QFrame::Shape::HLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line_3);

        roundLayout = new QHBoxLayout();
        roundLayout->setSpacing(6);
        roundLayout->setObjectName("roundLayout");
        roundLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        roundLayout->setContentsMargins(-1, 0, -1, 0);
        roundChecked = new QCheckBox(ChartPropertyForm);
        roundChecked->setObjectName("roundChecked");
        sizePolicy2.setHeightForWidth(roundChecked->sizePolicy().hasHeightForWidth());
        roundChecked->setSizePolicy(sizePolicy2);

        roundLayout->addWidget(roundChecked);

        roundSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        roundLayout->addItem(roundSpacer);

        roundSize = new QSpinBox(ChartPropertyForm);
        roundSize->setObjectName("roundSize");
        sizePolicy2.setHeightForWidth(roundSize->sizePolicy().hasHeightForWidth());
        roundSize->setSizePolicy(sizePolicy2);
        roundSize->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        roundSize->setMaximum(65536);

        roundLayout->addWidget(roundSize);


        verticalLayout->addLayout(roundLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        horizontalLayout_2->setContentsMargins(-1, 0, -1, 0);
        label = new QLabel(ChartPropertyForm);
        label->setObjectName("label");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(label);

        rotateSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(rotateSpacer);

        rotation = new QDoubleSpinBox(ChartPropertyForm);
        rotation->setObjectName("rotation");
        sizePolicy2.setHeightForWidth(rotation->sizePolicy().hasHeightForWidth());
        rotation->setSizePolicy(sizePolicy2);
        rotation->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        rotation->setDecimals(1);
        rotation->setMinimum(-360.000000000000000);
        rotation->setMaximum(360.000000000000000);

        horizontalLayout_2->addWidget(rotation);


        verticalLayout->addLayout(horizontalLayout_2);

        chartStyle = new QVBoxLayout();
        chartStyle->setObjectName("chartStyle");
        label_4 = new QLabel(ChartPropertyForm);
        label_4->setObjectName("label_4");

        chartStyle->addWidget(label_4);

        options = new QTextEdit(ChartPropertyForm);
        options->setObjectName("options");

        chartStyle->addWidget(options);


        verticalLayout->addLayout(chartStyle);

        chartData = new QVBoxLayout();
        chartData->setObjectName("chartData");
        label_3 = new QLabel(ChartPropertyForm);
        label_3->setObjectName("label_3");

        chartData->addWidget(label_3);

        defaultData = new QTextEdit(ChartPropertyForm);
        defaultData->setObjectName("defaultData");

        chartData->addWidget(defaultData);


        verticalLayout->addLayout(chartData);

        updateBtnLayout = new QHBoxLayout();
        updateBtnLayout->setObjectName("updateBtnLayout");
        updateBtn = new QPushButton(ChartPropertyForm);
        updateBtn->setObjectName("updateBtn");

        updateBtnLayout->addWidget(updateBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        updateBtnLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(updateBtnLayout);

        extendWidget = new QWidget(ChartPropertyForm);
        extendWidget->setObjectName("extendWidget");
        sizePolicy.setHeightForWidth(extendWidget->sizePolicy().hasHeightForWidth());
        extendWidget->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(extendWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        verticalLayout_2->setContentsMargins(0, 6, 0, 6);

        verticalLayout->addWidget(extendWidget);


        retranslateUi(ChartPropertyForm);

        QMetaObject::connectSlotsByName(ChartPropertyForm);
    } // setupUi

    void retranslateUi(QWidget *ChartPropertyForm)
    {
        ChartPropertyForm->setWindowTitle(QCoreApplication::translate("ChartPropertyForm", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("ChartPropertyForm", "\347\212\266\346\200\201", nullptr));
        roundChecked->setText(QCoreApplication::translate("ChartPropertyForm", "\345\234\206\350\247\222", nullptr));
        roundSize->setSuffix(QCoreApplication::translate("ChartPropertyForm", " px", nullptr));
        label->setText(QCoreApplication::translate("ChartPropertyForm", "\346\227\213\350\275\254", nullptr));
        rotation->setSuffix(QCoreApplication::translate("ChartPropertyForm", " \302\260", nullptr));
        label_4->setText(QCoreApplication::translate("ChartPropertyForm", "\345\233\276\350\241\250\346\240\267\345\274\217", nullptr));
        label_3->setText(QCoreApplication::translate("ChartPropertyForm", "\351\273\230\350\256\244\346\225\260\346\215\256", nullptr));
        updateBtn->setText(QCoreApplication::translate("ChartPropertyForm", "\346\233\264\346\226\260\345\233\276\350\241\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChartPropertyForm: public Ui_ChartPropertyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARTPROPERTYFORM_H
