/********************************************************************************
** Form generated from reading UI file 'webpropertyform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEBPROPERTYFORM_H
#define UI_WEBPROPERTYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WebPropertyForm
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *line;
    QCheckBox *moveCheck;
    QHBoxLayout *horizontalLayout;
    QRadioButton *urlRadio;
    QRadioButton *fileRadio;
    QRadioButton *codeRadio;
    QSpacerItem *horizontalSpacer_2;
    QWidget *urlWidget;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *urlEdit;
    QPushButton *fileBtn;
    QTextEdit *codeEdit;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *updateBtn;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *WebPropertyForm)
    {
        if (WebPropertyForm->objectName().isEmpty())
            WebPropertyForm->setObjectName("WebPropertyForm");
        WebPropertyForm->resize(256, 330);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WebPropertyForm->sizePolicy().hasHeightForWidth());
        WebPropertyForm->setSizePolicy(sizePolicy);
        WebPropertyForm->setMinimumSize(QSize(0, 330));
        verticalLayout = new QVBoxLayout(WebPropertyForm);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        verticalLayout->setContentsMargins(0, 9, 0, 9);
        line = new QFrame(WebPropertyForm);
        line->setObjectName("line");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy1);
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line);

        moveCheck = new QCheckBox(WebPropertyForm);
        moveCheck->setObjectName("moveCheck");
        sizePolicy1.setHeightForWidth(moveCheck->sizePolicy().hasHeightForWidth());
        moveCheck->setSizePolicy(sizePolicy1);
        moveCheck->setChecked(true);

        verticalLayout->addWidget(moveCheck);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        urlRadio = new QRadioButton(WebPropertyForm);
        urlRadio->setObjectName("urlRadio");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(urlRadio->sizePolicy().hasHeightForWidth());
        urlRadio->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(urlRadio);

        fileRadio = new QRadioButton(WebPropertyForm);
        fileRadio->setObjectName("fileRadio");
        sizePolicy2.setHeightForWidth(fileRadio->sizePolicy().hasHeightForWidth());
        fileRadio->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(fileRadio);

        codeRadio = new QRadioButton(WebPropertyForm);
        codeRadio->setObjectName("codeRadio");
        sizePolicy2.setHeightForWidth(codeRadio->sizePolicy().hasHeightForWidth());
        codeRadio->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(codeRadio);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        urlWidget = new QWidget(WebPropertyForm);
        urlWidget->setObjectName("urlWidget");
        sizePolicy1.setHeightForWidth(urlWidget->sizePolicy().hasHeightForWidth());
        urlWidget->setSizePolicy(sizePolicy1);
        horizontalLayout_2 = new QHBoxLayout(urlWidget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        urlEdit = new QLineEdit(urlWidget);
        urlEdit->setObjectName("urlEdit");
        sizePolicy1.setHeightForWidth(urlEdit->sizePolicy().hasHeightForWidth());
        urlEdit->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(urlEdit);

        fileBtn = new QPushButton(urlWidget);
        fileBtn->setObjectName("fileBtn");
        sizePolicy2.setHeightForWidth(fileBtn->sizePolicy().hasHeightForWidth());
        fileBtn->setSizePolicy(sizePolicy2);
        fileBtn->setMaximumSize(QSize(24, 24));

        horizontalLayout_2->addWidget(fileBtn);


        verticalLayout->addWidget(urlWidget);

        codeEdit = new QTextEdit(WebPropertyForm);
        codeEdit->setObjectName("codeEdit");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(codeEdit->sizePolicy().hasHeightForWidth());
        codeEdit->setSizePolicy(sizePolicy3);
        codeEdit->setMinimumSize(QSize(0, 100));

        verticalLayout->addWidget(codeEdit);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        updateBtn = new QPushButton(WebPropertyForm);
        updateBtn->setObjectName("updateBtn");
        sizePolicy2.setHeightForWidth(updateBtn->sizePolicy().hasHeightForWidth());
        updateBtn->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(updateBtn);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(WebPropertyForm);

        QMetaObject::connectSlotsByName(WebPropertyForm);
    } // setupUi

    void retranslateUi(QWidget *WebPropertyForm)
    {
        WebPropertyForm->setWindowTitle(QCoreApplication::translate("WebPropertyForm", "Form", nullptr));
        moveCheck->setText(QCoreApplication::translate("WebPropertyForm", "\346\213\226\345\212\250\346\250\241\345\274\217", nullptr));
        urlRadio->setText(QCoreApplication::translate("WebPropertyForm", "\347\275\221\345\235\200", nullptr));
        fileRadio->setText(QCoreApplication::translate("WebPropertyForm", "\346\226\207\344\273\266", nullptr));
        codeRadio->setText(QCoreApplication::translate("WebPropertyForm", "\344\273\243\347\240\201", nullptr));
        fileBtn->setText(QCoreApplication::translate("WebPropertyForm", "...", nullptr));
        updateBtn->setText(QCoreApplication::translate("WebPropertyForm", "\346\233\264\346\226\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WebPropertyForm: public Ui_WebPropertyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEBPROPERTYFORM_H
