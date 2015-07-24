#include <TreeFrogModel>
#include "admins.h"
#include "adminsobject.h"

Admins::Admins()
    : TAbstractModel(), d(new AdminsObject)
{ }

Admins::Admins(const Admins &other)
    : TAbstractModel(), d(new AdminsObject(*other.d))
{ }

Admins::Admins(const AdminsObject &object)
    : TAbstractModel(), d(new AdminsObject(object))
{ }

Admins::~Admins()
{
    // If the reference count becomes 0,
    // the shared data object 'AdminsObject' is deleted.
}

QString Admins::adminID() const
{
    return d->adminID;
}

void Admins::setAdminID(const QString &adminID)
{
    d->adminID = adminID;
}

QString Admins::adminName() const
{
    return d->adminName;
}

void Admins::setAdminName(const QString &adminName)
{
    d->adminName = adminName;
}

QString Admins::adminPassword() const
{
    return d->adminPassword;
}

void Admins::setAdminPassword(const QString &adminPassword)
{
    d->adminPassword = adminPassword;
}

Admins &Admins::operator=(const Admins &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

Admins Admins::create(const QString &adminID, const QString &adminName, const QString &adminPassword)
{
    AdminsObject obj;
    obj.adminID = adminID;
    obj.adminName = adminName;
    obj.adminPassword = adminPassword;
    if (!obj.create()) {
        return Admins();
    }
    return Admins(obj);
}

Admins Admins::create(const QVariantMap &values)
{
    Admins model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

Admins Admins::get(const QString &adminID)
{
    TSqlORMapper<AdminsObject> mapper;
    return Admins(mapper.findByPrimaryKey(adminID));
}

int Admins::count()
{
    TSqlORMapper<AdminsObject> mapper;
    return mapper.findCount();
}

QList<Admins> Admins::getAll()
{
    return tfGetModelListByCriteria<Admins, AdminsObject>(TCriteria());
}

QJsonArray Admins::getAllJson()
{
    QJsonArray array;
    TSqlORMapper<AdminsObject> mapper;

    if (mapper.find() > 0) {
        for (TSqlORMapperIterator<AdminsObject> i(mapper); i.hasNext(); ) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(Admins(i.next()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *Admins::modelData()
{
    return d.data();
}

const TModelObject *Admins::modelData() const
{
    return d.data();
}
