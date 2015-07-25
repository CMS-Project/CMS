#include <TreeFrogModel>
#include "operators.h"
#include "operatorsobject.h"

Operators::Operators()
    : TAbstractModel(), d(new OperatorsObject)
{ }

Operators::Operators(const Operators &other)
    : TAbstractModel(), d(new OperatorsObject(*other.d))
{ }

Operators::Operators(const OperatorsObject &object)
    : TAbstractModel(), d(new OperatorsObject(object))
{ }

Operators::~Operators()
{
    // If the reference count becomes 0,
    // the shared data object 'OperatorsObject' is deleted.
}

QString Operators::operatorID() const
{
    return d->operatorID;
}

void Operators::setOperatorID(const QString &operatorID)
{
    d->operatorID = operatorID;
}

QString Operators::operatorName() const
{
    return d->operatorName;
}

void Operators::setOperatorName(const QString &operatorName)
{
    d->operatorName = operatorName;
}

QString Operators::operatorNickname() const
{
    return d->operatorNickname;
}

void Operators::setOperatorNickname(const QString &operatorNickname)
{
    d->operatorNickname = operatorNickname;
}

QString Operators::operatorPassword() const
{
    return d->operatorPassword;
}

void Operators::setOperatorPassword(const QString &operatorPassword)
{
    d->operatorPassword = operatorPassword;
}

QString Operators::operatorPhone() const
{
    return d->operatorPhone;
}

void Operators::setOperatorPhone(const QString &operatorPhone)
{
    d->operatorPhone = operatorPhone;
}

QString Operators::id() const
{
    return d->ID;
}

void Operators::setId(const QString &id)
{
    d->ID = id;
}

QString Operators::operatorRole() const
{
    return d->operatorRole;
}

void Operators::setOperatorRole(const QString &operatorRole)
{
    d->operatorRole = operatorRole;
}

QString Operators::operatorStatus() const
{
    return d->operatorStatus;
}

void Operators::setOperatorStatus(const QString &operatorStatus)
{
    d->operatorStatus = operatorStatus;
}

Operators &Operators::operator=(const Operators &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

Operators Operators::create(const QString &operatorID, const QString &operatorName, const QString &operatorNickname, const QString &operatorPassword, const QString &operatorPhone, const QString &id, const QString &operatorRole, const QString &operatorStatus)
{
    OperatorsObject obj;
    obj.operatorID = operatorID;
    obj.operatorName = operatorName;
    obj.operatorNickname = operatorNickname;
    obj.operatorPassword = operatorPassword;
    obj.operatorPhone = operatorPhone;
    obj.ID = id;
    obj.operatorRole = operatorRole;
    obj.operatorStatus = operatorStatus;
    if (!obj.create()) {
        return Operators();
    }
    return Operators(obj);
}

QList<Operators> Operators::list_operator(const QString &adminID)
{
    QList<Operators> operator_list;
    TSqlQuery query;
    query.exec("SELECT * FROM operators join connection on operators.operatorID = connection.operatorID WHERE connection.adminID = '"+adminID+"'");
    while(query.next()){

        Operators a;  //建立一个对象a
        a.setOperatorID(query.value(0).toString());
        a.setOperatorName(query.value(1).toString());
        a.setOperatorNickname(query.value(2).toString());
        a.setOperatorPassword(query.value(3).toString());
       // a.setOperatorNumber(query.value(4).toString());
        a.setOperatorPhone(query.value(4).toString());
        a.setId(query.value(5).toString());
        a.setOperatorRole(query.value(6).toString());
        a.setOperatorStatus(query.value(7).toString());  //设置对象a中的相关值

        operator_list.append(a); //将a插入链表中

    }

   return operator_list;

}

Operators Operators::create(const QVariantMap &values)
{
    Operators model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

Operators Operators::get(const QString &operatorID)
{
    TSqlORMapper<OperatorsObject> mapper;
    return Operators(mapper.findByPrimaryKey(operatorID));
}

int Operators::count()
{
    TSqlORMapper<OperatorsObject> mapper;
    return mapper.findCount();
}

QList<Operators> Operators::getAll()
{
    return tfGetModelListByCriteria<Operators, OperatorsObject>(TCriteria());
}

QJsonArray Operators::getAllJson()
{
    QJsonArray array;
    TSqlORMapper<OperatorsObject> mapper;

    if (mapper.find() > 0) {
        for (TSqlORMapperIterator<OperatorsObject> i(mapper); i.hasNext(); ) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(Operators(i.next()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *Operators::modelData()
{
    return d.data();
}

const TModelObject *Operators::modelData() const
{
    return d.data();
}
