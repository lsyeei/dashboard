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

#include "graphicdocument.h"
#include "filetemplate.h"
#include "xmlHelper.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QDataStream>
#include <QByteArray>

GraphicDocument::GraphicDocument(QWidget *parent)
    : QObject(nullptr), parent(parent)
{
}

GraphicDocument::~GraphicDocument()
{
}

// ========== 文件状态管理 ==========

void GraphicDocument::markDirty()
{
    if (!dirty) {
        dirty = true;
        updateWindowTitle();
        emit dirtyChanged(true);
    }
}

void GraphicDocument::clearDirty()
{
    if (dirty) {
        dirty = false;
        updateWindowTitle();
        emit dirtyChanged(false);
    }
}

bool GraphicDocument::isDirty() const
{
    return dirty;
}

QString GraphicDocument::getFilePath() const
{
    return currentFilePath;
}

QString GraphicDocument::getFileName() const
{
    if (currentFilePath.isEmpty()) {
        return QString();
    }
    QFileInfo fileInfo(currentFilePath);
    return fileInfo.fileName();
}

void GraphicDocument::setFilePath(const QString &filePath)
{
    if (currentFilePath != filePath) {
        currentFilePath = filePath;
        updateWindowTitle();
        emit filePathChanged(filePath);
    }
}

void GraphicDocument::updateWindowTitle()
{
    if (!parent) {
        return;
    }

    QString spliter{" - "}, dirtyFlag{" * "};
    QString title = parent->windowTitle();
    auto segment = title.split(spliter);
    title = segment.first();

    if (!currentFilePath.isEmpty()) {
        title += spliter + getFileName();
    }

    if (dirty) {
        title += dirtyFlag;
    }

    parent->setWindowTitle(title);
}

// ========== 文件操作 ==========

bool GraphicDocument::newFile()
{
    // 检查是否需要保存当前文件
    if (!checkSaveBeforeAction()) {
        lastError = tr("当前修改未存储");
        return false;
    }

    // 清空当前文件路径
    setFilePath(QString());
    clearDirty();

    return true;
}

bool GraphicDocument::open()
{
    return openFile();
}

bool GraphicDocument::openFile(const QString &filePath)
{
    // 检查是否需要保存当前文件
    if (!checkSaveBeforeAction()) {
        return false;
    }

    QString fileName = filePath;
    if (fileName.isEmpty()) {
        fileName = QFileDialog::getOpenFileName(
            parent,
            tr("打开"),
            currentFilePath.isEmpty() ? QDir::currentPath() : QFileInfo(currentFilePath).absolutePath(),
            tr("BI文件(*.bi)")
        );

        if (fileName.isEmpty()) {
            return false;
        }
    }

    // 读取文件
    if (!readFromFile(fileName)) {
        return false;
    }

    // 设置当前文件路径并清除脏标记
    setFilePath(fileName);
    clearDirty();
    emit fileOpened(fileName);

    return true;
}

bool GraphicDocument::save()
{
    if (currentFilePath.isEmpty()) {
        return saveAs();
    }

    if (writeToFile(currentFilePath)) {
        clearDirty();
        emit fileSaved(currentFilePath);
        return true;
    }

    return false;
}

bool GraphicDocument::saveAs(const QString &filePath)
{
    QString fileName = filePath;

    if (fileName.isEmpty()) {
        QString title = currentFilePath.isEmpty() ? tr("保存") : tr("另存为");
        fileName = QFileDialog::getSaveFileName(
            parent,
            title,
            currentFilePath.isEmpty() ? QDir::currentPath() : currentFilePath,
            tr("BI文件(*.bi)")
        );

        if (fileName.isEmpty()) {
            return false;
        }
    }

    if (writeToFile(fileName)) {
        setFilePath(fileName);
        clearDirty();
        emit fileSaved(fileName);
        QMessageBox::information(parent, tr("提示"), tr("文件保存成功"));
        return true;
    }

    return false;
}

bool GraphicDocument::checkSaveBeforeAction()
{
    if (!dirty) {
        return true;
    }

    int reply = showSavePrompt();

    if (reply == QMessageBox::Save) {
        if (currentFilePath.isEmpty()) {
            return saveAs();
        } else {
            return save();
        }
    } else if (reply == QMessageBox::Discard) {
        return true;
    } else {
        return false; // 用户取消
    }
}

bool GraphicDocument::writeToFile(const QString &filePath)
{
    if (!docCheck()) {
        return false;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        lastError = tr("打开文件错误，请重新保存。");
        return false;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement(XmlTemplate::root);

    xmlWriter.writeStartElement(XmlTemplate::project);
    xmlWriter.writeCharacters("");
    xmlWriter.device()->write(doc.project.toUtf8());
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement(XmlTemplate::board);
    xmlWriter.writeCharacters("");
    xmlWriter.device()->write(doc.page.toUtf8());
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement(XmlTemplate::shapes);
    xmlWriter.writeCharacters("");
    xmlWriter.device()->write(doc.shapes.toUtf8());
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement(XmlTemplate::animates);
    xmlWriter.writeCharacters("");
    xmlWriter.device()->write(doc.animates.toUtf8());
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement(XmlTemplate::dataSource);
    xmlWriter.writeCharacters("");
    xmlWriter.device()->write(doc.dataSource.toUtf8());
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();

    return true;
}

bool GraphicDocument::readFromFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        lastError = QString(tr("打开文件错误。%1")).arg(file.errorString());
        return false;
    }

    QXmlStreamReader reader(&file);
    while (!reader.atEnd()) {
        auto type = reader.readNext();
        if (reader.hasError()) {
            lastError = QString(tr("文件读取错误。%1")).arg(reader.errorString());
            file.close();
            return false;
        }
        if (type == QXmlStreamReader::StartDocument) {
            continue;
        } else if (type == QXmlStreamReader::StartElement) {
            auto startName = reader.name();
            if (startName.compare(XmlTemplate::project) == 0) {
                doc.project = XmlHelper::rawText(&reader, false);
            } else if (startName.compare(XmlTemplate::board) == 0) {
                doc.page = XmlHelper::rawText(&reader, false);
            } else if (startName.compare(XmlTemplate::shapes) == 0) {
                doc.shapes = XmlHelper::rawText(&reader, false);
            } else if (startName.compare(XmlTemplate::animates) == 0) {
                doc.animates = XmlHelper::rawText(&reader, false);
            } else if (startName.compare(XmlTemplate::dataSource) == 0) {
                doc.dataSource = XmlHelper::rawText(&reader, false);
            }
        }
    }

    file.close();
    return true;
}

int GraphicDocument::showSavePrompt()
{
    if (!currentFilePath.isEmpty()) {
        return QMessageBox::question(
            parent,
            tr("保存提示"),
            tr("文件已修改，是否保存？\n\n%1").arg(currentFilePath),
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel
        );
    } else {
        return QMessageBox::question(
            parent,
            tr("保存提示"),
            tr("文件已修改，是否保存？"),
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel
        );
    }
}

QString GraphicDocument::getLastError() const
{
    return lastError;
}

Document GraphicDocument::getDoc() const
{
    return doc;
}

void GraphicDocument::updateDoc(const Document &newDoc)
{
    doc = newDoc;
}
