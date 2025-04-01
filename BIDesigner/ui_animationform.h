/********************************************************************************
** Form generated from reading UI file 'animationform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANIMATIONFORM_H
#define UI_ANIMATIONFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "animation/animationlistview.h"

QT_BEGIN_NAMESPACE

class Ui_AnimationForm
{
public:
    QAction *scaleAction;
    QAction *blinkAction;
    QAction *moveAction;
    QAction *rotateAction;
    QAction *customAction;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QToolButton *addBtn;
    QPushButton *removeBtn;
    QPushButton *playBtn;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_3;
    AnimationListView *animationView;
    QWidget *property;
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *AnimationForm)
    {
        if (AnimationForm->objectName().isEmpty())
            AnimationForm->setObjectName("AnimationForm");
        AnimationForm->resize(312, 548);
        scaleAction = new QAction(AnimationForm);
        scaleAction->setObjectName("scaleAction");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::ViewFullscreen));
        scaleAction->setIcon(icon);
        scaleAction->setMenuRole(QAction::MenuRole::NoRole);
        blinkAction = new QAction(AnimationForm);
        blinkAction->setObjectName("blinkAction");
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::WeatherClear));
        blinkAction->setIcon(icon1);
        blinkAction->setMenuRole(QAction::MenuRole::NoRole);
        moveAction = new QAction(AnimationForm);
        moveAction->setObjectName("moveAction");
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::MailSend));
        moveAction->setIcon(icon2);
        moveAction->setMenuRole(QAction::MenuRole::NoRole);
        rotateAction = new QAction(AnimationForm);
        rotateAction->setObjectName("rotateAction");
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::SyncSynchronizing));
        rotateAction->setIcon(icon3);
        rotateAction->setMenuRole(QAction::MenuRole::NoRole);
        customAction = new QAction(AnimationForm);
        customAction->setObjectName("customAction");
        QIcon icon4(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaylistShuffle));
        customAction->setIcon(icon4);
        customAction->setMenuRole(QAction::MenuRole::NoRole);
        verticalLayout_2 = new QVBoxLayout(AnimationForm);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        addBtn = new QToolButton(AnimationForm);
        addBtn->setObjectName("addBtn");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(addBtn->sizePolicy().hasHeightForWidth());
        addBtn->setSizePolicy(sizePolicy);
        addBtn->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        addBtn->setPopupMode(QToolButton::ToolButtonPopupMode::InstantPopup);
        addBtn->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextOnly);
        addBtn->setAutoRaise(true);
        addBtn->setArrowType(Qt::ArrowType::DownArrow);

        horizontalLayout->addWidget(addBtn);

        removeBtn = new QPushButton(AnimationForm);
        removeBtn->setObjectName("removeBtn");
        QIcon icon5(QIcon::fromTheme(QIcon::ThemeIcon::EditDelete));
        removeBtn->setIcon(icon5);
        removeBtn->setFlat(true);

        horizontalLayout->addWidget(removeBtn);

        playBtn = new QPushButton(AnimationForm);
        playBtn->setObjectName("playBtn");
        QIcon icon6(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStart));
        playBtn->setIcon(icon6);
        playBtn->setFlat(true);

        horizontalLayout->addWidget(playBtn);


        verticalLayout_2->addLayout(horizontalLayout);

        scrollArea = new QScrollArea(AnimationForm);
        scrollArea->setObjectName("scrollArea");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy1);
        scrollArea->setFrameShape(QFrame::Shape::Panel);
        scrollArea->setFrameShadow(QFrame::Shadow::Plain);
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 292, 490));
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy2);
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(2, -1, 2, -1);
        animationView = new AnimationListView(scrollAreaWidgetContents);
        animationView->setObjectName("animationView");
        sizePolicy2.setHeightForWidth(animationView->sizePolicy().hasHeightForWidth());
        animationView->setSizePolicy(sizePolicy2);

        verticalLayout_3->addWidget(animationView);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);

        property = new QWidget(AnimationForm);
        property->setObjectName("property");
        sizePolicy2.setHeightForWidth(property->sizePolicy().hasHeightForWidth());
        property->setSizePolicy(sizePolicy2);
        verticalLayout = new QVBoxLayout(property);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);

        verticalLayout_2->addWidget(property);


        retranslateUi(AnimationForm);

        QMetaObject::connectSlotsByName(AnimationForm);
    } // setupUi

    void retranslateUi(QWidget *AnimationForm)
    {
        AnimationForm->setWindowTitle(QCoreApplication::translate("AnimationForm", "Form", nullptr));
        scaleAction->setText(QCoreApplication::translate("AnimationForm", "\347\274\251\346\224\276", nullptr));
#if QT_CONFIG(tooltip)
        scaleAction->setToolTip(QCoreApplication::translate("AnimationForm", "\346\214\211\346\214\207\345\256\232\346\257\224\344\276\213\347\274\251\346\224\276", nullptr));
#endif // QT_CONFIG(tooltip)
        blinkAction->setText(QCoreApplication::translate("AnimationForm", "\351\227\252\347\203\201", nullptr));
#if QT_CONFIG(tooltip)
        blinkAction->setToolTip(QCoreApplication::translate("AnimationForm", "\350\203\214\346\231\257\350\211\262\345\212\250\347\224\273", nullptr));
#endif // QT_CONFIG(tooltip)
        moveAction->setText(QCoreApplication::translate("AnimationForm", "\350\277\220\345\212\250", nullptr));
#if QT_CONFIG(tooltip)
        moveAction->setToolTip(QCoreApplication::translate("AnimationForm", "\346\214\211\346\214\207\345\256\232\350\267\257\347\272\277\350\277\220\345\212\250", nullptr));
#endif // QT_CONFIG(tooltip)
        rotateAction->setText(QCoreApplication::translate("AnimationForm", "\346\227\213\350\275\254", nullptr));
#if QT_CONFIG(tooltip)
        rotateAction->setToolTip(QCoreApplication::translate("AnimationForm", "\346\227\213\350\275\254\346\214\207\345\256\232\347\232\204\350\247\222\345\272\246", nullptr));
#endif // QT_CONFIG(tooltip)
        customAction->setText(QCoreApplication::translate("AnimationForm", "\350\207\252\345\256\232\344\271\211", nullptr));
#if QT_CONFIG(tooltip)
        customAction->setToolTip(QCoreApplication::translate("AnimationForm", "\350\207\252\345\256\232\344\271\211\345\212\250\347\224\273", nullptr));
#endif // QT_CONFIG(tooltip)
        addBtn->setText(QCoreApplication::translate("AnimationForm", "\346\267\273\345\212\240\345\212\250\347\224\273", nullptr));
        removeBtn->setText(QCoreApplication::translate("AnimationForm", "\347\247\273\351\231\244\345\212\250\347\224\273", nullptr));
        playBtn->setText(QCoreApplication::translate("AnimationForm", "\346\222\255\346\224\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AnimationForm: public Ui_AnimationForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANIMATIONFORM_H
