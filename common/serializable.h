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
#include "variantutil.h"

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
className(const className &other){ \
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
    // friend QDataStream &operator<<(QDataStream &stream, const Serializable &data){
    //     Serializable *dataPtr = const_cast<Serializable *>(&data);
    //     const QMetaObject *metaInfo = data.getMetaInfo();
    //     do{
    //         int count = metaInfo->methodCount();
    //         for(int i=0; i< count; i++){
    //             if (QString(metaInfo->method(i).tag()).compare("JSON_FLAG") == 0){
    //                 QMap<QString, QString> jsonInfo;
    //                 jsonInfo = dataPtr->invokeMethod<QMap<QString, QString>>(metaInfo, i);
    //                 QVariant value = dataPtr->getValue(jsonInfo["name"]);
    //                 QMetaProperty fieldType = metaInfo->property(metaInfo->indexOfProperty(jsonInfo["name"].toLocal8Bit()));
    //                 if (fieldType.metaType().id() == QMetaType::QVariant){
    //                     stream << value.metaType().id();
    //                 }
    //                 stream << value;
    //             }
    //         }
    //         metaInfo = metaInfo->superClass();
    //     }while(metaInfo != nullptr);
    //     return stream;
    // }

    // friend QDataStream &operator>>(QDataStream &stream, Serializable &data){
    //     Serializable *dataPtr = const_cast<Serializable *>(&data);
    //     const QMetaObject *metaInfo = data.getMetaInfo();
    //     do{
    //         int count = metaInfo->methodCount();
    //         for(int i=0; i< count; i++){
    //             if (QString(metaInfo->method(i).tag()).compare("JSON_FLAG") == 0){
    //                 QMap<QString, QString> jsonInfo;
    //                 jsonInfo = dataPtr->invokeMethod<QMap<QString, QString>>(metaInfo, i);
    //                 QMetaProperty fieldType = metaInfo->property(metaInfo->indexOfProperty(jsonInfo["name"].toLocal8Bit()));
    //                 QMetaType fieldMeta = fieldType.metaType();
    //                 if (fieldMeta.id() == QMetaType::QVariant) {
    //                     int typeId = 0;
    //                     stream >> typeId;
    //                     fieldMeta = QMetaType(typeId);
    //                 }
    //                 QVariant value(fieldMeta);
    //                 stream >> value;
    //                 dataPtr->setValue(jsonInfo["name"], value);
    //             }
    //         }
    //         metaInfo = metaInfo->superClass();
    //     }while(metaInfo != nullptr);
    //     return stream;
    // }

    // friend QDebug operator<<(QDebug dbg, const Serializable &data){
    //     Serializable *dataPtr = const_cast<Serializable *>(&data);
    //     const QMetaObject *metaInfo = data.getMetaInfo();
    //     auto reg = QRegularExpression("QVariant\\([^,]+, (.+)\\)$");
    //     do{
    //         int count = metaInfo->methodCount();
    //         for(int i=0; i< count; i++){
    //             if (QString(metaInfo->method(i).tag()).compare("JSON_FLAG") == 0){
    //                 QMap<QString, QString> jsonInfo;
    //                 jsonInfo = dataPtr->invokeMethod<QMap<QString, QString>>(metaInfo, i);
    //                 QVariant value = dataPtr->getValue(jsonInfo["name"]);
    //                 QString str = dbg.toString(value);
    //                 str = str.replace(reg, "\\1");
    //                 dbg << jsonInfo["alias"] << ":"
    //                     << str << "; ";
    //             }
    //         }
    //         metaInfo = metaInfo->superClass();
    //     }while(metaInfo != nullptr);
    //     return dbg;
    // }

private:
    QString id;
};

Q_DECLARE_METATYPE(Serializable)

// inline Serializable::Serializable()
// {
//     QUuid uid = QUuid::createUuid();
//     id = uid.toString(QUuid::WithoutBraces);
// }

// inline Serializable::~Serializable()
// {}

// inline bool Serializable::isSubClass(QMetaType type)
// {
//     auto meta = type.metaObject();
//     int infoIndex = meta->indexOfClassInfo("base");
//     bool isSubClass = false;
//     if (infoIndex >= 0) {
//         auto base = meta->classInfo(infoIndex).value();
//         if (QString("Serializable").compare(base) == 0) {
//             isSubClass = true;
//         }
//     }
//     return isSubClass;
// }

// inline void Serializable::copy(const Serializable &from, Serializable &to)
// {
//     auto fromMeta = from.getMetaInfo();
//     auto toMeta = to.getMetaInfo();
//     if (QString(fromMeta->className()).compare(
//             toMeta->className()) != 0){
//         return;
//     }
//     do{
//         int count = fromMeta->methodCount();
//         for(int i=0; i< count; i++){
//             if (QString(fromMeta->method(i).tag()).compare("JSON_FLAG") == 0){
//                 QMap<QString, QString> jsonInfo;
//                 jsonInfo = invokeMethod<QMap<QString, QString>>(fromMeta, i);
//                 QVariant value = const_cast<Serializable&>(from).getValue(jsonInfo["name"]);
//                 to.setValue(jsonInfo["name"], value);
//             }
//         }
//         fromMeta = fromMeta->superClass();
//     }while(fromMeta != nullptr);
// }

// inline void Serializable::copy(const Serializable &from){
//     auto fromMeta = from.getMetaInfo();
//     auto toMeta = this->getMetaInfo();
//     if (QString(fromMeta->className()).compare(
//             toMeta->className()) != 0){
//         return;
//     }
//     do{
//         int count = fromMeta->methodCount();
//         QMap<QString, QMetaMethod> methodMap;
//         for(int i=0; i< count; i++){
//             methodMap[fromMeta->method(i).name()] = fromMeta->method(i);
//         }
//         for(int i=0; i< count; i++){
//             if (QString(fromMeta->method(i).tag()).compare("JSON_FLAG") == 0){
//                 QMap<QString, QString> jsonInfo;
//                 jsonInfo = invokeMethod<QMap<QString, QString>>(fromMeta, i);
//                 QVariant value = const_cast<Serializable&>(from).getValue(jsonInfo["name"]);
//                 this->setValue(jsonInfo["name"], value);
//             }
//         }
//         fromMeta = fromMeta->superClass();
//     }while(fromMeta != nullptr);
// }

// inline QString Serializable::hashCode()
// {
//     return id;
// }

// inline bool Serializable::equals(Serializable &obj)
// {
//     if (hashCode() != obj.hashCode()) {
//         return false;
//     }
//     auto metaInfo = getMetaInfo();
//     if (QString(metaInfo->className()).compare(
//             obj.getMetaInfo()->className()) != 0){
//         return false;
//     }
//     if (toString() != obj.toString()){
//         return false;
//     }
//     return true;
// }

// inline bool Serializable::operator==(Serializable &obj)
// {
//     return equals(obj);
// }

// inline QString Serializable::toString()
// {
//     QString fieldStr;
//     QTextStream stream(&fieldStr);
//     const QMetaObject *metaInfo = getMetaInfo();
//     do{
//         int count = metaInfo->methodCount();
//         for(int i=0; i< count; i++){
//             if (QString(metaInfo->method(i).tag()).compare("JSON_FLAG") == 0){
//                 QMap<QString, QString> jsonInfo;
//                 jsonInfo = invokeMethod<QMap<QString, QString>>(metaInfo, i);
//                 QVariant value = getValue(jsonInfo["name"]);
//                 bool isObject = Serializable::isSubClass(value.metaType());
//                 QString str;
//                 if (isObject) {
//                     // Serializable子类递归转为字符串
//                     str = reinterpret_cast<Serializable*>(
//                         const_cast<void*>(value.constData())
//                               )->toString();
//                 } else {
//                     // 普通QVariant，通过工具类转换
//                     str = VariantUtil::toString(value);
//                 }
//                 stream << jsonInfo["name"] << ":"
//                        << (isObject?"{":"")
//                        << str
//                        << (isObject?"}":"")
//                        << ";";
//             }
//         }

//         metaInfo = metaInfo->superClass();
//     }while(metaInfo != nullptr);
//     return fieldStr;
// }

// inline void Serializable::setValue(QString fieldName, QVariant value)
// {
//     const QMetaObject *metaInfo = getMetaInfo();
//     int index = metaInfo->indexOfProperty(fieldName.toLocal8Bit());
//     QMetaProperty field = metaInfo->property(index);

//     QObject *objPtr = reinterpret_cast<QObject*>(this);
//     field.write(objPtr, value);
// }

// inline QVariant Serializable::getValue(QString fieldName)
// {
//     const QMetaObject *metaInfo = getMetaInfo();
//     int index = metaInfo->indexOfProperty(fieldName.toLocal8Bit().constData());
//     QMetaProperty field = metaInfo->property(index);
//     QObject *objPtr = reinterpret_cast<QObject*>(this);
//     return field.read(objPtr);
// }

// template<typename T>
// T Serializable::invokeMethod(const QMetaObject *metaInfo, int index){
//     T result;
//     void** voidPtr = new void*();
//     *voidPtr = reinterpret_cast<void *>(&result);
//     metaInfo->static_metacall(QMetaObject::InvokeMetaMethod, index, voidPtr);
//     delete voidPtr;
//     return result;
// }
#endif // SERIALIZABLE_H
