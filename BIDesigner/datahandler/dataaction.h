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
#ifndef DATAACTION_H
#define DATAACTION_H

#include "datasource/datamarketdo.h"
#include "datasource/datasourcedo.h"
#include "abstractaction.h"
#include "enuminfo.h"
#include "serializable.h"

#include <QCoreApplication>

// 数据执行动作类型
enum class ActionType{
    CONTROL_GRAPHIC, ASSIGN_PROPERTY
};

class DataAction :public Serializable
{
    Q_GADGET
    SERIALIZE(DataAction)
public:
    DataAction(){actionType = ActionType::CONTROL_GRAPHIC;}
    ~DataAction(){}
    void copy(const Serializable &from, Serializable &to) override;
    void copy(const Serializable &from) override;
    static QList<EnumInfo> actionTypeList(){
        QList<EnumInfo> types;
        types << EnumInfo{int(ActionType::CONTROL_GRAPHIC),
                          QCoreApplication::tr("控制图元"),
                          QCoreApplication::tr("通过对数据的逻辑判断来控制图元进行相应的动作")}
              << EnumInfo{int(ActionType::ASSIGN_PROPERTY),
                          QCoreApplication::tr("属性赋值"),
                          QCoreApplication::tr("将图元的指定属性的值设置为数据指定值")};
        return types;
    }
    DataSourceDO getDataSource(){return data.getDataSource();}
    DataMarketDO getData(){return data;}
    void setData(DataMarketDO dataMarket){
        data = dataMarket;
        dataId = dataMarket.get_uuid();
        sourceId = dataMarket.getDataSource().get_uuid();
    }
    /**
     * @brief typeToString 动作类型的文字描述
     * @return 文字描述
     */
    QString typeToString();
    /**
     * @brief actionToString 动作的文字描述
     * @return 文字描述
     */
    QString actionToString();
private:
    // 图元ID
    QString graphicId;
    // 数据源ID
    QString sourceId;
    // 数据ID
    QString dataId;
    // 动作类型
    ActionType actionType;
    // 动作
    QVariant action;
    // 数据
    DataMarketDO data;

    JSONFIELD(graphicId, GraphicId)
    JSONFIELD(sourceId, SourceId)
    JSONFIELD(dataId, DataId)
    JSONFIELD(actionType, ActionType)
    JSONFIELD(action, Action)
};

inline void DataAction::copy(const Serializable &from, Serializable &to)
{
    auto f = const_cast<DataAction*>(dynamic_cast<const DataAction*>(&from));
    auto t = dynamic_cast<DataAction*>(&to);
    // 先设置data，如果此时data为空页不会影响SourceId和dataid
    t->setData(f->getData());
    t->setGraphicId(f->getGraphicId());
    t->setSourceId(f->getSourceId());
    t->setDataId(f->getDataId());
    t->setActionType(f->getActionType());
    t->setAction(f->getAction());
}

inline void DataAction::copy(const Serializable &from)
{
    copy(from, *this);
}

inline QString DataAction::typeToString(){
    auto typeList = actionTypeList();
    foreach(auto item, typeList){
        if (item.getId() == int(actionType)) {
            return item.getName();
        }
    }
    return QCoreApplication::tr("未知");
}

inline QString DataAction::actionToString()
{
    if (!action.isValid()) {
        return "";
    }
    auto act = AbstractAction::fromVariant(&action);
    if (act) {
        return act->summary();
    }
    return "";
}

#endif // DATAACTION_H
