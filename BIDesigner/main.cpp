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
#include <QNetworkProxyFactory>

int main(int argc, char *argv[])
{
    qSetMessagePattern("%{time MM-dd hh:mm:ss.sss} [ %{file}: %{line} ] %{message}");
    // QtWebEngineQuick::initialize();

    // 关闭代理
    QNetworkProxyFactory::setUseSystemConfiguration(false);
    // 启用 ANGLE
    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    // 指定 DirectX 11,使用 DirectX/Vulkan 替代 OpenGL
    qputenv("QT_ANGLE_PLATFORM", "d3d11");
    // 激活 Chromium 硬件加速参数 通过环境变量启用 GPU 光栅化与多线程渲染
    qputenv("QTWEBENGINE_CHROMIUM_FLAGS",
            "--ignore-gpu-blacklist --enable-gpu-rasterization --num-raster-threads=4");
    // QWebEngineProfile::defaultProfile()->setHttpCacheType(QWebEngineProfile::DiskHttpCache);
    // QWebEngineProfile::defaultProfile()->setPersistentCookiesPolicy(QWebEngineProfile::NoPersistentCookies);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
