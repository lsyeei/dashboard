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
#include "syntaxfactory.h"
#include "ksyntaxhighlighting/include/repository_p.h"
#include "ksyntaxhighlighting/include/definition_p.h"
#include <QFile>
#include <QTextDocument>

SyntaxFactory::SyntaxFactory() {
    Q_INIT_RESOURCE(syntax);
    using namespace KSyntaxHighlighting;
    auto repoData = RepositoryPrivate::get(&repository);
    repoData->loadSyntaxFolder(&repository, ":/highlighting/ksyntaxhighlighting/syntax/");
    repoData->loadThemeFolder(":/highlighting/ksyntaxhighlighting/themes/");
    repoData->computeAlternativeDefLists();

    currentTheme = repository.theme("Radical");
    if(!currentTheme.isValid()){
        qWarning() << __FUNCTION__ << "syntax highlighter default theme not valid!";
    }
}

SyntaxFactory::~SyntaxFactory()
{
    foreach (auto lighter, docMap) {
        delete lighter;
        lighter = nullptr;
    }
    docMap.clear();
    Q_CLEANUP_RESOURCE(syntax);
}

SyntaxFactory *SyntaxFactory::instance()
{
    static SyntaxFactory *instance = new SyntaxFactory();
    return instance;
}

bool SyntaxFactory::highlightDocument(QTextDocument *doc, const QString &language)
{
    using namespace KSyntaxHighlighting;
    auto highlighter = docMap[doc];
    if (highlighter == nullptr) {
        highlighter = new SyntaxHighlighter(doc);
        docMap[doc] = highlighter;
    }

    auto def = repository.definitionForName(language);
    if (!def.isValid()) {
        qWarning() << __FUNCTION__ << doc->parent()->objectName()
                   << "syntax highlighter language not support!";
        return false;
    }
    highlighter->setDefinition(def);

    if(!currentTheme.isValid()){
        qWarning() << __FUNCTION__ << doc->parent()->objectName()
                   << "syntax highlighter theme not valid!";
        return false;
    }
    highlighter->setTheme(currentTheme);

    return true;
}

bool SyntaxFactory::setTheme(const QString &themeName)
{
    auto theme = repository.theme(themeName);
    if (!theme.isValid()) {
        qWarning() << __FUNCTION__ << "syntax highlighter theme not valid!";
        return false;
    }

    foreach (auto lighter, docMap) {
        lighter->setTheme(theme);
    }
    return true;
}

QList<QString> SyntaxFactory::themeNameList()
{
    QList<QString> themeNames;
    auto themes = repository.themes();
    foreach (auto theme, themes) {
        themeNames << theme.name();
    }
    return themeNames;
}

QList<QString> SyntaxFactory::languageList()
{
    QList<QString> languages;
    auto defs = repository.definitions();
    foreach (auto def, defs) {
        languages << def.name();
    }
    return languages;
}
