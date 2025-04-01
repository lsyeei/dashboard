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

/**
 * 添加移动路径的步骤：
 * 1. 继承 AbstractLinePath 创建路径类，或继承IMovePath接口创建路径类；例如：
 *
 * class CustomPath : public AbstractLinePath
 * {
 *     Q_OBJECT
 * public:
 *     static QString PATH_ID;
 *     explicit CustomPath(QGraphicsItem *parent = nullptr);
 *     explicit CustomPath(const QString &xml, QGraphicsItem *parent = nullptr);
 *     QString classId() const override;
 * protected:
 *     QPainterPath linePath(QList<QPointF> points) const Q_DECL_OVERRIDE;
 *     void createPredefinedItem() Q_DECL_OVERRIDE;
 *     void afterCreateSelector(LineSelector *s) Q_DECL_OVERRIDE;
 * };
 *
 * 2. 继承 IMovePathPlugin 创建路径插件；
 *
 * .h 文件
 * #include "pathpluginhelper.h"
 *
 * class CustomPathPlugin : public QObject, public IMovePathPlugin
 * {
 *     Q_OBJECT
 * public:
 *     CustomPathPlugin();
 *     PLUGIN_INTERFACE
 * };
 * .cpp 文件
 * CustomPathPlugin::CustomPathPlugin() {}
 * PLUGIN_DEFINE(CustomPath, "路径名", "分组", :/animation/path/icons/polygonLine.svg)
 *
 * 3. 在 MovePathFactory 构造函数中添加新创建的插件。
 *  plugins << new CustomPathPlugin();
 */
#include "movepathfactory.h"
#include "imovepathplugin.h"
#include "linepathplugin.h"
#include "polygonpathplugin.h"
#include "curvedpathplugin.h"

MovePathFactory *MovePathFactory::factory = nullptr;
MovePathFactory::MovePathFactory() {
    plugins << new LinePathPlugin()
            << new PolygonPathPlugin()
            << new CurvedPathPlugin();
}

MovePathFactory::~MovePathFactory()
{}

MovePathFactory *MovePathFactory::instance()
{
    if (factory == nullptr) {
        factory = new MovePathFactory();
    }
    return factory;
}

QList<IMovePathPlugin*> MovePathFactory::allPath()
{
    return plugins;
}

void MovePathFactory::setPathEditable(IMovePath *path)
{
    path->setFlag(QGraphicsItem::ItemIsMovable, true);
    path->setFlag(QGraphicsItem::ItemIsSelectable, true);
    path->setFlag(QGraphicsItem::ItemIsFocusable, true);
}

IMovePath *MovePathFactory::createPath(const QString &id)
{
    if (id.isEmpty()) {
        return nullptr;
    }
    auto plugin = std::find_if(plugins.begin(), plugins.end(),
                              [&](IMovePathPlugin* item){return item->id().compare(id) == 0;});
    if (plugin != plugins.end()) {
        auto path = plugin[0]->createPath();
        setPathEditable(path);
        return path;
    }
    return nullptr;
}

IMovePath *MovePathFactory::createPath(const QString &id, const QString &xml)
{
    if (id.isEmpty() || xml.isEmpty()) {
        return nullptr;
    }
    auto plugin = std::find_if(plugins.begin(), plugins.end(),
                               [&](IMovePathPlugin* item){return item->id().compare(id) == 0;});
    if (plugin != plugins.end()) {
        auto path = plugin[0]->createPath(xml);
        setPathEditable(path);
        return path;
    }
    return nullptr;
}
