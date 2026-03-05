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
#ifndef HTTPHEADER_H
#define HTTPHEADER_H

#include "serializable.h"
#include <QHttpHeaders>

// HTTP header 类型
enum class HeaderItemType{Known, Custom};
class HttpHeaderItem : public Serializable
{
    Q_GADGET
    SERIALIZE(HttpHeaderItem)
public:
    HttpHeaderItem(){type = HeaderItemType::Custom;}
    static QList<QPair<QString,QHttpHeaders::WellKnownHeader>> knownHeaders(){
        typedef QHttpHeaders::WellKnownHeader Knowns;
        return {
                {"Content-Disposition", Knowns::ContentDisposition},
                {"Content-Type", Knowns::ContentType},
                {"Content-Length", Knowns::ContentLength},
                {"Location", Knowns::Location},
                {"Cookie", Knowns::Cookie},
                {"UserAgent", Knowns::UserAgent},
                {"If-Match", Knowns::IfMatch},
                {"If-None-Match", Knowns::IfNoneMatch}
            };
    }
private:
    HeaderItemType type;
    QVariant key;
    QString value;
    QString note;

    JSONFIELD(type, Type)
    JSONFIELD(key, Key)
    JSONFIELD(value, Value)
    JSONFIELD(note, Note)
};
typedef QList<HttpHeaderItem> HttpHeader;

Q_DECLARE_METATYPE(HttpHeaderItem)
#endif // HTTPHEADER_H
