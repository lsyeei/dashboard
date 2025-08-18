/********************************************************************************
** Form generated from reading UI file 'graphicproperty.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHICPROPERTY_H
#define UI_GRAPHICPROPERTY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GraphicProperty
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *commonProperty;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *graphicName;

    void setupUi(QWidget *GraphicProperty)
    {
        if (GraphicProperty->objectName().isEmpty())
            GraphicProperty->setObjectName("GraphicProperty");
        GraphicProperty->resize(220, 285);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GraphicProperty->sizePolicy().hasHeightForWidth());
        GraphicProperty->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(GraphicProperty);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        commonProperty = new QWidget(GraphicProperty);
        commonProperty->setObjectName("commonProperty");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(commonProperty->sizePolicy().hasHeightForWidth());
        commonProperty->setSizePolicy(sizePolicy1);
        horizontalLayout = new QHBoxLayout(commonProperty);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(commonProperty);
        label->setObjectName("label");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(label);

        graphicName = new QLineEdit(commonProperty);
        graphicName->setObjectName("graphicName");
        sizePolicy1.setHeightForWidth(graphicName->sizePolicy().hasHeightForWidth());
        graphicName->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(graphicName);


        verticalLayout->addWidget(commonProperty);


        retranslateUi(GraphicProperty);

        QMetaObject::connectSlotsByName(GraphicProperty);
    } // setupUi

    void retranslateUi(QWidget *GraphicProperty)
    {
        GraphicProperty->setWindowTitle(QCoreApplication::translate("GraphicProperty", "Form", nullptr));
        label->setText(QCoreApplication::translate("GraphicProperty", "\345\220\215\347\247\260\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GraphicProperty: public Ui_GraphicProperty {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHICPROPERTY_H
