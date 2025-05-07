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
 * 使用方法：
 * 1. 子类继承 Serializable
 * 2. 子类中须使用宏 Q_GADGET
 * 3. 子类中使用宏 SERIALIZE(className) 开启序列化功能
 * 4. 子类中使用 JSONFIELD(field, alias, ...) 指定哪些字段需要序列化
 * 5. 使用Q_DECLARE_METATYPE(className)注册元数据类型
 * 说明：
 * 1. 使用 SERIALIZE 会自动生成拷贝构造函数
 * 2.使用 JSONFIELD 指定的字段会自动生成 get和set函数，不必单独声明
 * 举例：
 * class Student : public Serializable
 * {
 *  Q_GADGET
 *  SERIALIZE(Student)
 *  public:
 *      Student();
 *      ~Student();
 *  private:
 *      QString name;
 *      int age;
 *
 *      JSONFIELD(name, Name)
 *      JSONFIELD(age, Age)
 * };
 * Q_DECLARE_METATYPE(Cunstom)
 *
 * Student的使用方法：
 * Student student;
 * student.setName("li");
 * student.setAge(15);
 * qDebug() << student;
 * QByteArray array;
 * QDataStream stream(&array, QIODeviceBase::WriteOnly);
 * stream << student;
 */
#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "qjsonobject.h"

#include <QObject>
#include <QMetaObject>
#include <QMetaProperty>
#include <QDebug>
#include <QFile>

#include <QtWidgets/QMessageBox>

// SERIALIZE 宏内不能包含 Q_GADGET ，必须在子类中单独使用 Q_GADGET，
// 因为 moc 时不引入其它头文件，此处定义Q_GADGET对子类无效，子类不会生成moc文件
//const_cast<className&>(explicit
#define SERIALIZE(className) \
Q_CLASSINFO("base", "Serializable") \
public: \
className(const className &other) { \
    copy(other, *this); \
} \
inline const QMetaObject* getMetaInfo() const override{ \
    return &staticMetaObject; \
}

#ifndef Q_MOC_RUN
// define the tag text as empty, so the compiler doesn't see it
#  define JSON_FLAG
#endif
#define VAR_TYPE(var) decltype(var)

#ifdef CHAIN
#define SETTER(field, alias) \
inline auto set##alias(const __type_##field &value) { \
    field = value; \
return this; \
}
#else
#define SETTER(field, alias) \
inline void set##alias(const __type_##field &value) { \
    field = const_cast<__type_##field>(value); \
}
#endif

#define JSONFIELD(field, alias, ...) \
using __type_##field = decltype(field) ;\
Q_PROPERTY(__type_##field field READ get##alias WRITE set##alias) \
    public: \
    Q_INVOKABLE JSON_FLAG inline QMap<QString, QString> __get##alias##Info__(){ \
        QMap<QString, QString> info; \
        info["name"] = #field; \
        info["alias"] = #alias; \
        info["args"] = QString(#__VA_ARGS__); \
        return info; \
    } \
    inline __type_##field get##alias() const { return field; } \
    inline void set##alias(const __type_##field &value) { \
            field = value; \
    }

class Serializable
{
public:
    Serializable();
    virtual ~Serializable();
    static bool isSubClass(QMetaType type);
    virtual const QMetaObject* getMetaInfo() const = 0;
    void copy(const Serializable &from, Serializable &to);
    void copy(const Serializable &from);
    virtual QString hashCode();
    virtual bool equals(Serializable &obj);
    virtual bool operator==(Serializable &obj);
    virtual QString toString();
    template<typename T>
    T invokeMethod(const QMetaObject *metaInfo, int index);
    virtual QVariant getValue(QString fieldName);
    virtual void setValue(QString fieldName, QVariant value);

    friend QDataStream &operator<<(QDataStream &stream, const Serializable &data);
    friend QDataStream &operator>>(QDataStream &stream, Serializable &data);
    friend QDebug operator<<(QDebug dbg, const Serializable &data);

private:
    QString id;
};

Q_DECLARE_METATYPE(Serializable)

#endif // SERIALIZABLE_H
