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
#ifndef CONTROLACTION_H
#define CONTROLACTION_H

#include "qtmetamacros.h"
#include "abstractaction.h"
#include "assignaction.h"
#include "serializable.h"
#include <QPair>
#include <enuminfo.h>

enum class LogicSymbol{GREAT, GREATE_EQUAL, RANGE, LESS, LESS_EQUAL, EQUAL, UNEQUAL};
enum class ControlType{PLAY_ANIMATION, SWITCH_STATE, SET_PROPERTY};

class ControlLogic : public Serializable
{
    Q_GADGET
    SERIALIZE(ControlLogic)
public:
    ControlLogic(){
        uuid = QUuid::createUuid().toString(QUuid::WithoutBraces);
    }

    QString controlTypeName();
    QString symbolSummary();
    void setThreshold(qreal val){minValue = val;}
    qreal getThreshold(){return minValue;}
    QPair<qreal,qreal> getRange(){return {minValue, maxValue};}
    void setRange(qreal min, qreal max){minValue = min;maxValue = max;}
    /**
     * @brief testLogic 测试逻辑
     * @param data 用于测试的数据
     * @return true 成功，false 失败
     */
    bool testLogic(QVariant data);
    void setSwitchStateAction(int id, const QString &name);
    QPair<int, QString> getSwitchStateAction();
    QString actionString();
private:
    QString uuid;
    // 逻辑操作符
    LogicSymbol symbol;
    // 最小值，预设值
    qreal minValue;
    // 最大值
    qreal maxValue;
    // 控制类型
    ControlType controlType;
    // 执行动作
    QVariant action;

    JSONFIELD(uuid, Uuid)
    JSONFIELD(symbol, symbol)
    JSONFIELD(minValue, MinValue)
    JSONFIELD(maxValue, MaxValue)
    JSONFIELD(controlType, ControlType)
    JSONFIELD(action, Action)
};

class ControlAction : public Serializable, public AbstractAction
{
    Q_GADGET
    SERIALIZE(ControlAction)
public:
    ControlAction(){}
    static QList<EnumInfo> logicSymbolList();
    static QList<EnumInfo> controlTypeList();

    void addControlLogic(ControlLogic logic){logicList.append(logic);}
    bool removeControlLogic(ControlLogic logic){
        int count = logicList.removeIf([&](ControlLogic item){
            return item.getUuid().compare(logic.getUuid()) == 0;
        });
        return count > 0;
    }
    // AbstractAction interface
    void triggerAction(QVariant data, QGraphicsItem *graphic) override;
    QString summary() override;
private:
    // 数据
    QList<ControlLogic> logicList;

    JSONFIELD(logicList, LogicList)
};

REGISTER_ACTION(ControlAction)

inline QList<EnumInfo> ControlAction::logicSymbolList(){
    QList<EnumInfo> symbols;
    symbols << EnumInfo{int(LogicSymbol::EQUAL), "=", QCoreApplication::tr("等于")}
            << EnumInfo{int(LogicSymbol::GREAT), ">", QCoreApplication::tr("大于")}
            << EnumInfo{int(LogicSymbol::GREATE_EQUAL), "≧", QCoreApplication::tr("大于")}
            << EnumInfo{int(LogicSymbol::RANGE), "[]", QCoreApplication::tr("范围")}
            << EnumInfo{int(LogicSymbol::LESS), "<", QCoreApplication::tr("小于")}
            << EnumInfo{int(LogicSymbol::LESS_EQUAL), "≦", QCoreApplication::tr("小于等于")}
            << EnumInfo{int(LogicSymbol::UNEQUAL), "≠", QCoreApplication::tr("不等于")};
    return symbols;
}

inline QList<EnumInfo> ControlAction::controlTypeList(){
    QList<EnumInfo> types;
    types << EnumInfo{int(ControlType::PLAY_ANIMATION),
                      QCoreApplication::tr("播放动画"),
                      QCoreApplication::tr("播放图元中预定的动画")}
          << EnumInfo{int(ControlType::SWITCH_STATE),
                      QCoreApplication::tr("切换状态"),
                      QCoreApplication::tr("将图元切换到指定状态")}
          << EnumInfo{int(ControlType::SET_PROPERTY),
                      QCoreApplication::tr("设置属性"),
                      QCoreApplication::tr("为图元指定属性设置指定值")};
    return types;
}

inline QString ControlLogic::controlTypeName()
{
    QString name{""};
    auto controlTypeList = ControlAction::controlTypeList();
    foreach (auto it, controlTypeList) {
        if (it.getId() == int(controlType)) {
            name = it.getName();
            break;
        }
    }
    return name;
}

inline QString ControlLogic::symbolSummary()
{
    QString summary{""};
    auto symbolList = ControlAction::logicSymbolList();
    if (symbol == LogicSymbol::RANGE) {
        summary = QString("in[%1,%2]").arg(minValue).arg(maxValue);
    }else{
        foreach (auto it, symbolList) {
            if (it.getId() == int(symbol)) {
                summary = QString("%1 %2").arg(it.getName()).arg(minValue);
                break;
            }
        }
    }
    return summary;
}

inline bool ControlLogic::testLogic(QVariant data){
    if (!data.canConvert(QMetaType::fromType<qreal>())) {
        return false;
    }
    auto value = data.toReal();
    bool trigger{false};
    switch (symbol) {
    case LogicSymbol::GREAT:
        trigger = value > minValue;
        break;
    case LogicSymbol::GREATE_EQUAL:
        trigger = value >= minValue;
        break;
    case LogicSymbol::RANGE:
        trigger = (value >= minValue) && (value <= maxValue);
        break;
    case LogicSymbol::LESS:
        trigger = value < minValue;
        break;
    case LogicSymbol::LESS_EQUAL:
        trigger = value <= minValue;
        break;
    case LogicSymbol::EQUAL:
        trigger = value == minValue;
        break;
    case LogicSymbol::UNEQUAL:
        trigger = value != minValue;
        break;
    default:
        trigger = false;
        break;
    }
    return trigger;
}

inline void ControlLogic::setSwitchStateAction(int id, const QString &name)
{
    if (controlType != ControlType::SWITCH_STATE) {
        return;
    }
    action = QVariant::fromValue(QPair{id, name});
}

inline QPair<int, QString> ControlLogic::getSwitchStateAction()
{
    if (controlType != ControlType::SWITCH_STATE) {
         return QPair<int, QString>{};
    }
    return action.value<QPair<int, QString>>();
}

inline QString ControlLogic::actionString()
{
    switch (controlType) {
    case ControlType::PLAY_ANIMATION:
        return action.toString();
        break;
    case ControlType::SWITCH_STATE:
        return getSwitchStateAction().second;
        break;
    case ControlType::SET_PROPERTY:
        return action.value<AssignAction>().summary();
        break;
    }
    return "";
}

inline void ControlAction::triggerAction(QVariant data, QGraphicsItem *graphic){
    foreach (auto logic, logicList) {
        bool flag = logic.testLogic(data);

        if (!flag) {
            continue;
        }
        auto controlType = logic.getControlType();
        auto action = logic.getAction();
        switch (controlType) {
        case ControlType::PLAY_ANIMATION:
            playAnimation(graphic, action.toString());
            break;
        case ControlType::SWITCH_STATE:
            switchState(graphic, action.toString());
            break;
        case ControlType::SET_PROPERTY:
            action.value<AssignAction>().triggerAction(data, graphic);
            break;
        }
    }
}

inline QString ControlAction::summary()
{
    QList<QString> result;
    foreach (auto logic, logicList) {
        result << logic.controlTypeName();
    }
    return result.join(" / ");
}

#endif // CONTROLACTION_H
