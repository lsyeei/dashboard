/********************************************************************************
** Form generated from reading UI file 'htmlpropertyform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HTMLPROPERTYFORM_H
#define UI_HTMLPROPERTYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HtmlPropertyForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QFrame *line;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *updateBtn;
    QPushButton *eidtBtn;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *HtmlPropertyForm)
    {
        if (HtmlPropertyForm->objectName().isEmpty())
            HtmlPropertyForm->setObjectName("HtmlPropertyForm");
        HtmlPropertyForm->resize(239, 240);
        verticalLayout = new QVBoxLayout(HtmlPropertyForm);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, -1, 0, -1);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(HtmlPropertyForm);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label);

        line = new QFrame(HtmlPropertyForm);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout->addWidget(line);


        verticalLayout->addLayout(horizontalLayout);

        textEdit = new QTextEdit(HtmlPropertyForm);
        textEdit->setObjectName("textEdit");

        verticalLayout->addWidget(textEdit);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        updateBtn = new QPushButton(HtmlPropertyForm);
        updateBtn->setObjectName("updateBtn");

        horizontalLayout_2->addWidget(updateBtn);

        eidtBtn = new QPushButton(HtmlPropertyForm);
        eidtBtn->setObjectName("eidtBtn");

        horizontalLayout_2->addWidget(eidtBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(HtmlPropertyForm);

        QMetaObject::connectSlotsByName(HtmlPropertyForm);
    } // setupUi

    void retranslateUi(QWidget *HtmlPropertyForm)
    {
        HtmlPropertyForm->setWindowTitle(QCoreApplication::translate("HtmlPropertyForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("HtmlPropertyForm", "HTML\347\274\226\350\276\221", nullptr));
        updateBtn->setText(QCoreApplication::translate("HtmlPropertyForm", "\346\233\264\346\226\260", nullptr));
        eidtBtn->setText(QCoreApplication::translate("HtmlPropertyForm", "\347\274\226\350\276\221\345\231\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HtmlPropertyForm: public Ui_HtmlPropertyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HTMLPROPERTYFORM_H
