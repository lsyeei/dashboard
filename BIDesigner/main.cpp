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

#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QMutex>

QtMessageHandler originalHandler = nullptr;
// 全局互斥锁：保证多线程写日志时不冲突
static QMutex g_logMutex;

// 自定义日志处理函数
void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // 加锁：多线程环境下保证日志写入原子性
    QMutexLocker locker(&g_logMutex);

    // 采用预定义的日志格式格式化日志
    QString message = qFormatLogMessage(type, context, msg);
    auto dir = QCoreApplication::applicationDirPath();
    dir = dir + "/log";
    QDir path(dir);
    if (!path.exists()) {
        path.mkpath(dir);
    }
    auto prefix = QDate::currentDate().toString("yyyyMMdd");
    auto logFile = QString("%1/log_%2.txt").arg(dir).arg(prefix);
    // 打开日志文件（追加模式，不存在则创建）
    QFile log(logFile);
    if (log.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&log);
        stream.setEncoding(QStringConverter::Utf8);
        stream << message << "\n";
        log.flush();
        log.close();
    }
    if (originalHandler)
        originalHandler(type, context, msg);
}

int main(int argc, char *argv[])
{
    qSetMessagePattern("[%{time yy-MM-dd hh:mm:ss.sss}] [%{type}] [ %{file}: %{line}] %{message}");
    // 自定义日志文件
    qInstallMessageHandler(customMessageHandler);

    // 启用 ANGLE
    // QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
