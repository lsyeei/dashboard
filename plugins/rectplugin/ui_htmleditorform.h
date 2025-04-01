/**
* This file is part of the dashboard library
* 
* Copyright 2025 lishiying  lsyeei@163.com
* 
* Licensed under the Apache License, Version 2.0 (the License);
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
* http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an AS IS BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/********************************************************************************
** Form generated from reading UI file 'htmleditorform.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HTMLEDITORFORM_H
#define UI_HTMLEDITORFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HtmlEditorForm
{
public:
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *HtmlEditorForm)
    {
        if (HtmlEditorForm->objectName().isEmpty())
            HtmlEditorForm->setObjectName("HtmlEditorForm");
        HtmlEditorForm->setWindowModality(Qt::WindowModal);
        HtmlEditorForm->resize(635, 373);
        verticalLayout = new QVBoxLayout(HtmlEditorForm);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(HtmlEditorForm);

        QMetaObject::connectSlotsByName(HtmlEditorForm);
    } // setupUi

    void retranslateUi(QWidget *HtmlEditorForm)
    {
        HtmlEditorForm->setWindowTitle(QCoreApplication::translate("HtmlEditorForm", "HTML\347\274\226\350\276\221\345\231\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HtmlEditorForm: public Ui_HtmlEditorForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HTMLEDITORFORM_H
