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

#ifndef ANIMATIONFACTORY_H
#define ANIMATIONFACTORY_H

#include "AnimationParam.h"
#include <QString>
#include <QObject>
#include <QParallelAnimationGroup>
#include <QPointer>

class IGraphicsScene;
class QGraphicsItem;

class AnimationFactory : public QObject
{
    Q_OBJECT
    AnimationFactory();
    ~AnimationFactory();
public:
    static AnimationFactory *instance();
    /**
     * @brief graphicAnimation 获取指定图元的动画参数
     * @param id 图元ID
     * @return  动画参数列表
     */
    QList<AnimationParam> graphicAnimation(const QString &id);
    /**
     * @brief setGraphicAnimation 设置指定图元的动画参数
     * @param id 图元ID
     * @return  动画参数列表
     * @param paramList 动画参数列表
     */
    void setGraphicAnimation(const QString &id, QList<AnimationParam> paramList);
    /**
     * @brief toXml 动画集合转为xml
     * @return  xml文本
     */
    QString toXml();
    /**
     * @brief parseXml 从xml中解析动画集合
     * @param xml xml文本
     */
    void parseXml(const QString &xml);
    /**
     * @brief bindScene 绑定scene
     * @param scenePtr 要绑定的scene
     */
    void bindScene(IGraphicsScene *scenePtr);
    /**
     * @brief play 播放指定图元的动画
     * @param graphic 图元对象
     * @return 动画对象
     */
    QAbstractAnimation *play(QGraphicsItem *graphic);
    /**
     * @brief playAll 播放所有动画
     * @return 动画对象
     */
    QAbstractAnimation *playAll();
    /**
     * @brief updateAnimate 更新动画数据
     * @param graphic 图元对象
     * @param animates 动画参数列表
     */
    void updateAnimate(QGraphicsItem * graphic, const QList<AnimationParam> animates);
    /**
     * @brief animateTypeList 获取支持的动画类型列表
     * @return 动画类型列表
     */
    QList<AnimateType*> animateTypeList();
    /**
     * @brief getAnimateType 根据ID查找动画类型
     * @param id 动画类型ID
     * @return 动画类型
     */
    AnimateType *getAnimateType(const QString &id);

protected Q_SLOTS:

private:
    static AnimationFactory *factory;
    // 动画类型
    QList<AnimateType*> typeList;
    // 动画集合，key 图元ID，value 动画参数
    QMap<QString, QList<AnimationParam>> animations;
    // 用于执行动画的scene
    IGraphicsScene *scene{nullptr};
    // 动画播放（并行播放）
    QPointer<QParallelAnimationGroup> player;
    // /**
    //  * @brief createAnimation 创建动画
    //  * @param graphic 图元对象
    //  * @param act 动画参数
    //  * @return 动画对象
    //  */
    // QAbstractAnimation *createAnimation(QGraphicsItem *graphic, const AnimationParam &act);
    /**
     * @brief scaleAnimation 缩放动画
     * @param graphic 图元对象
     * @param act 动画参数
     * @return 动画对象
     */
    static QAbstractAnimation *scaleAnimation(QGraphicsItem *graphic, const AnimationParam &act);
    // 水平缩放
    static QAbstractAnimation *scaleHAnimation(QGraphicsItem *graphic, const AnimationParam &act);
    // 垂直缩放
    static QAbstractAnimation *scaleVAnimation(QGraphicsItem *graphic, const AnimationParam &act);
    /**
     * @brief blinkAnimation 闪烁动画
     * @param graphic 图元对象
     * @param act 动画参数
     * @return  动画对象
     */
    static QAbstractAnimation *blinkAnimation(QGraphicsItem *graphic, const AnimationParam &act);
    static QAbstractAnimation *moveAnimation(QGraphicsItem *graphic, const AnimationParam &act);
    static QAbstractAnimation *rotateAnimation(QGraphicsItem *graphic, const AnimationParam &act);
    static QAbstractAnimation *rotateHAnimation(QGraphicsItem *graphic, const AnimationParam &act);
    static QAbstractAnimation *rotateVAnimation(QGraphicsItem *graphic, const AnimationParam &act);
    static QAbstractAnimation *addDelay(QAbstractAnimation *animate, qreal delay);
    // 禁止移动和拷贝
    Q_DISABLE_COPY_MOVE(AnimationFactory)
};

#endif // ANIMATIONFACTORY_H
