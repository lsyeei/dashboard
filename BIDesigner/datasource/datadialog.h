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
#ifndef DATADIALOG_H
#define DATADIALOG_H

#include "datamarketdo.h"
#include "ksyntaxhighlighting/repository.h"

#include <QDialog>
#include <QPointer>


namespace KSyntaxHighlighting { class SyntaxHighlighter; }
namespace Ui {
class DataDialog;
}
class IDataQueryWidget;
class DataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DataDialog(QWidget *parent = nullptr);
    ~DataDialog();
    void setData(DataMarketDO dataObj);
    DataMarketDO getData();
protected Q_SLOTS:
    void onTestProcessCode();
private:
    Ui::DataDialog *ui;
    DataMarketDO data;
    QPointer<IDataQueryWidget> queryWidget;
    KSyntaxHighlighting::Repository m_repository;
    QPointer<KSyntaxHighlighting::SyntaxHighlighter> m_highlighter;
    void updateData();
    bool validate();
    void setEditorHighlight();
};

#endif // DATADIALOG_H
