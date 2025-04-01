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

#ifndef XMLHELPER_H
#define XMLHELPER_H

#include "qdebug.h"
#include <QXmlStreamReader>


class QString;
class XmlHelper{

public:
    /**
     * @brief 读取xml当前节点的原始文本
     * @param xml QXmlStreamReader 指针
     * @param onlyContent true 只包含该节点的内容，false 包含节点本身
     * @return xml当前节点的原始文本
     */
    static QString rawText(QXmlStreamReader *xml, bool onlyContent = true){
        auto start = xml->characterOffset();
        // auto name = xml->name();
        // 读取当前图元的xml内容
        xml->skipCurrentElement();
        auto end = xml->characterOffset();
        if (xml->hasError()) {
            qDebug() << "XML read Raw text error:" << xml->errorString();
            return nullptr;
        }
        // 建立还原点
        auto device = xml->device();
        device->startTransaction();
        QString data = "";
        device->seek(0);
        data = QString::fromUtf8(device->readAll());
        // 还原
        device->rollbackTransaction();
        if (onlyContent){
            if (end == start) {
                return data;
            }
            // 查找结束点
            end = data.lastIndexOf("<", end - 1);
        }else{
            // 查找当前节点的起始位置
            start = data.lastIndexOf("<", start - 1);
        }
        data = data.mid(start, end - start);

        return data;
    }
};

#endif // XMLHELPER_H
