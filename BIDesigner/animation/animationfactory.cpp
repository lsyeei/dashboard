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
 * 添加一个动画的步骤：
 * 1. 在AnimationFactory类中声明创建动画的方法，方法参数参照scaleAnimation()；
 * 2. 继承AbstractParamWidget，创建该动画的UI参数界面；
 * 3. 在AnimationFactory构造函数中 new AnimateType，并指定唯一的ID。
 */
#include "animationfactory.h"
#include "animation/paramwidget/blinkparamwidget.h"
#include "animation/paramwidget/moveparamwidget.h"
#include "animation/paramwidget/rotateparamwidget.h"
#include "animation/paramwidget/scaleparamwidget.h"
#include "filetemplate.h"
#include "igraphicsscene.h"
#include "opacityanimation.h"
#include "svghelper.h"
#include "tranfromanimation.h"
#include <QXmlStreamReader>
#include <QMessageBox>
#include <QAnimationGroup>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QTimeLine>
#include <QPropertyAnimation>
#include <QGraphicsItem>

AnimationFactory* AnimationFactory::factory = nullptr;
AnimationFactory::AnimationFactory() {
    typeList << new AnimateType("SCALE", tr("缩放"),
                            QIcon::fromTheme(QIcon::ThemeIcon::ViewFullscreen),
                            scaleAnimation, new ScaleParamWidget("SCALE"))
             << new AnimateType("BLINK", tr("闪烁"),
                            QIcon::fromTheme(QIcon::ThemeIcon::WeatherClear),
                            blinkAnimation, new BlinkParamWidget("BLINK"))
             << new AnimateType("MOVE", tr("运动"),
                            QIcon::fromTheme(QIcon::ThemeIcon::MailSend),
                            moveAnimation, new MoveParamWidget("MOVE"))
             << new AnimateType("ROTATE", tr("旋转"),
                            QIcon::fromTheme(QIcon::ThemeIcon::SyncSynchronizing),
                            rotateAnimation, new RotateParamWidget("ROTATE"));

    auto icon = QIcon::fromTheme(QIcon::ThemeIcon::ViewFullscreen);
    QPixmap map = icon.pixmap(24,24);
    QTransform trans;
    trans.rotate(45);
    typeList << new AnimateType("SCALE-H", tr("水平拉伸"), QIcon{map.transformed(trans)},
                                scaleHAnimation, new ScaleParamWidget("SCALE-H"));
    trans.reset();
    trans.rotate(-45);
    typeList << new AnimateType("SCALE-V", tr("垂直拉伸"),QIcon{map.transformed(trans)},
                                scaleVAnimation, new ScaleParamWidget("SCALE-V"));
    auto svg = SvgHelper{QString{":/icons/icons/rotateH.svg"}};
    typeList << new AnimateType("ROTATE-H", tr("水平翻转"),QIcon{svg.toPixmap(SvgHelper::Normal)},
                                rotateHAnimation, new RotateParamWidget("ROTATE-H"));
    auto svg2 = SvgHelper{QString{":/icons/icons/rotateV.svg"}};
    typeList << new AnimateType("ROTATE-V", tr("垂直翻转"),QIcon{svg2.toPixmap(SvgHelper::Normal)},
                                rotateVAnimation, new RotateParamWidget("ROTATE-V"));
}

AnimationFactory::~AnimationFactory()
{
    if (player->state() != QAbstractAnimation::Stopped) {
        player->stop();
    }
    player.clear();
    for (int i = 0; i < typeList.count(); ++i) {
        delete typeList[i];
    }
    typeList.clear();
}

AnimationFactory *AnimationFactory::instance()
{
    if (factory == nullptr) {
        factory = new AnimationFactory();
    }

    return factory;
}

QList<AnimationParam> AnimationFactory::graphicAnimation(const QString &id)
{
    return animations[id];
}

void AnimationFactory::setGraphicAnimation(const QString &id, QList<AnimationParam> paramList)
{
    animations[id] = paramList;
}

QString AnimationFactory::toXml()
{
    QString data;
    QScopedPointer<QXmlStreamWriter> xml(new QXmlStreamWriter(&data));
    xml->writeStartElement(XmlTemplate::animates);
    auto item = animations.begin();
    while(item != animations.end()){
        xml->writeStartElement(XmlTemplate::animatesTemplate::animate);
        xml->writeTextElement(XmlTemplate::animatesTemplate::animateTemplate::itemId,
                              item.key());
        xml->writeStartElement(XmlTemplate::animatesTemplate::animateTemplate::actions);
        QByteArray array;
        QDataStream stream(&array, QIODeviceBase::WriteOnly);
        stream << item.value();
        xml->writeCDATA(array.toHex());
        xml->writeEndElement();
        xml->writeEndElement();
        item ++;
    }
    xml->writeEndElement();
    return data;
}

void AnimationFactory::parseXml(const QString &xml)
{
    QXmlStreamReader reader(xml);
    while(!reader.atEnd()){
        reader.readNextStartElement();
        if (reader.hasError()) {
            QMessageBox::information(nullptr, tr("提示"), QString(tr("解析animation错误。%1" )).arg(reader.errorString()));
            break;
        }
        if (reader.name().compare(XmlTemplate::animatesTemplate::animate) == 0) {
            QString id = "";
            auto type = reader.readNext();
            if (type == QXmlStreamReader::StartElement &&
                reader.name().compare(XmlTemplate::animatesTemplate::animateTemplate::itemId) == 0) {
                id = reader.readElementText();
            }
            reader.readNextStartElement();
            if (reader.name().compare(XmlTemplate::animatesTemplate::animateTemplate::actions) == 0) {
                type = reader.readNext();
                if (type == QXmlStreamReader::Characters && reader.isCDATA()){
                    auto data = reader.text();
                    QByteArray array =  QByteArray::fromHex(data.toLocal8Bit());
                    QDataStream stream(&array, QIODeviceBase::ReadOnly);
                    QList<AnimationParam> params;
                    stream >> params;
                    if (!id.isEmpty()) {
                        animations[id] = params;
                    }
                }
            }
        }

    }
}

void AnimationFactory::bindScene(IGraphicsScene *scenePtr)
{
    if (scenePtr == nullptr || scene == scenePtr) {
        return;
    }
    scene = scenePtr;
}

QAbstractAnimation *AnimationFactory::play(QGraphicsItem *graphic)
{
    auto id = scene->getItemId(graphic);
    if (id.isEmpty()) {
        return nullptr;
    }
    auto actions = animations[id];
    if (actions.isEmpty()) {
        return nullptr;
    }
    if (!player.isNull()) {
        player->stop();
        player.clear();
    }
    player = new QParallelAnimationGroup();
    foreach (auto act, actions) {
            auto type = getAnimateType(act.getTypeId());
            if (!type->isEmpty()){
                player->addAnimation(type->createAnimation(graphic, act));
            }
    }
    player->start();
    return player;
}

QAbstractAnimation *AnimationFactory::playAll()
{
    if (!player.isNull()) {
        player->stop();
        player.clear();
    } //else {
        player = new QParallelAnimationGroup();
    //}
    auto it = animations.begin();
    while (it != animations.end()){
        auto graphic = scene->getItemById(it.key());
        if (graphic == nullptr) {
            continue;
        }
        auto actions = it.value();
        foreach (auto act, actions) {
            auto type = getAnimateType(act.getTypeId());
            if (!type->isEmpty()){
                player->addAnimation(type->createAnimation(graphic, act));
            }
        }
    }
    player->start();
    return player;
}

void AnimationFactory::updateAnimate(QGraphicsItem *graphic, const QList<AnimationParam> animates)
{
    if (graphic == nullptr){
        return;
    }
    auto id = scene->getItemId(graphic);
    if (id.isEmpty()) {
        return;
    }
    if (animates.isEmpty()) {
        animations.remove(id);
        return;
    }
    animations[id] = animates;
}

QList<AnimateType*> AnimationFactory::animateTypeList()
{
    return typeList;
}

AnimateType *AnimationFactory::getAnimateType(const QString &id)
{
    if (id.isEmpty()) {
        return nullptr;
    }
    auto type = std::find_if(typeList.begin(), typeList.end(),
                             [=](AnimateType *item){return id.compare(item->getId()) == 0;});
    if (type == typeList.end()) {
        return nullptr;
    }else{
        return *type;
    }
}

QAbstractAnimation *AnimationFactory::scaleAnimation(QGraphicsItem *graphic, const AnimationParam &act)
{
    return addDelay(new TranfromAnimation(graphic, act, TranfromAnimation::SCALE), act.getDelay());
}

QAbstractAnimation *AnimationFactory::scaleHAnimation(QGraphicsItem *graphic, const AnimationParam &act)
{
    return addDelay(new TranfromAnimation(graphic, act, TranfromAnimation::HSCALE), act.getDelay());
}

QAbstractAnimation *AnimationFactory::scaleVAnimation(QGraphicsItem *graphic, const AnimationParam &act)
{
    return addDelay(new TranfromAnimation(graphic, act, TranfromAnimation::VSCALE), act.getDelay());
}

QAbstractAnimation *AnimationFactory::blinkAnimation(QGraphicsItem *graphic, const AnimationParam &act)
{
    return addDelay(new OpacityAnimation(graphic, act, OpacityAnimation::Fixed), act.getDelay());
}

QAbstractAnimation *AnimationFactory::moveAnimation(QGraphicsItem *graphic, const AnimationParam &act)
{
    return addDelay(new TranfromAnimation(graphic, act, TranfromAnimation::TRANSLATION), act.getDelay());
}

QAbstractAnimation *AnimationFactory::rotateAnimation(QGraphicsItem *graphic, const AnimationParam &act)
{
    return addDelay(new TranfromAnimation(graphic, act, TranfromAnimation::ROTATE), act.getDelay());
}

QAbstractAnimation *AnimationFactory::rotateHAnimation(QGraphicsItem *graphic, const AnimationParam &act)
{
    return addDelay(new TranfromAnimation(graphic, act, TranfromAnimation::HROTATE), act.getDelay());
}

QAbstractAnimation *AnimationFactory::rotateVAnimation(QGraphicsItem *graphic, const AnimationParam &act)
{
    return addDelay(new TranfromAnimation(graphic, act, TranfromAnimation::VROTATE), act.getDelay());
}

QAbstractAnimation *AnimationFactory::addDelay(QAbstractAnimation *animate, qreal delay)
{
    if (delay > 0){
        auto group = new QSequentialAnimationGroup();
        group->addPause(delay*1000);
        group->addAnimation(animate);
        return group;
    }
    return animate;
}
