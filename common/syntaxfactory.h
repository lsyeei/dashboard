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
#ifndef SYNTAXFACTORY_H
#define SYNTAXFACTORY_H

#include <QMap>
#include <QString>
#include "ksyntaxhighlighting/include/syntaxhighlighter.h"
#include "ksyntaxhighlighting/include/repository.h"
#include "ksyntaxhighlighting/include/theme.h"

class QTextDocument;
class SyntaxFactory
{
    SyntaxFactory();
public:
    ~SyntaxFactory();
    static SyntaxFactory *instance();
    bool highlightDocument(QTextDocument *doc, const QString &language);
    bool setTheme(const QString &themeName);
    QList<QString> themeNameList();
    QList<QString> languageList();
private:
    QMap<QTextDocument *, KSyntaxHighlighting::SyntaxHighlighter*> docMap;
    KSyntaxHighlighting::Repository repository;
    KSyntaxHighlighting::Theme currentTheme;
};

#endif // SYNTAXFACTORY_H
