#include <TreeFrogModel>
#include "connection.h"
#include "connectionobject.h"

Connection::Connection()
    : TAbstractModel(), d(new ConnectionObject)
{ }

Connection::Connection(const Connection &other)
    : TAbstractModel(), d(new ConnectionObject(*other.d))
{ }

Connection::Connection(const ConnectionObject &object)
    : TAbstractModel(), d(new ConnectionObject(object))
{ }

Connection::~Connection()
{
    // If the reference count becomes 0,
    // the shared data object 'ConnectionObject' is deleted.
}

QString Connection::adminID() const
{
    return d->adminID;
}

void Connection::setAdminID(const QString &adminID)
{
    d->adminID = adminID;
}

QString Connection::operatorID() const
{
    return d->operatorID;
}

void Connection::setOperatorID(const QString &operatorID)
{
    d->operatorID = operatorID;
}

Connection &Connection::operator=(const Connection &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

Connection Connection::create(const QString &adminID, const QString &operatorID)
{
    ConnectionObject obj;
    obj.adminID = adminID;
    obj.operatorID = operatorID;
    if (!obj.create()) {
        return Connection();
    }
    return Connection(obj);
}

Connection Connection::create(const QVariantMap &values)
{
    Connection model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

Connection Connection::get(const QString &adminID, const QString &operatorID)
{
    TCriteria cri;
    cri.add(ConnectionObject::AdminID, adminID);
    cri.add(ConnectionObject::OperatorID, operatorID);
    TSqlORMapper<ConnectionObject> mapper;
    return Connection(mapper.findFirst(cri));
}

int Connection::count()
{
    TSqlORMapper<ConnectionObject> mapper;
    return mapper.findCount();
}

QList<Connection> Connection::getAll()
{
    return tfGetModelListByCriteria<Connection, ConnectionObject>(TCriteria());
}

QJsonArray Connection::getAllJson()
{
    QJsonArray array;
    TSqlORMapper<ConnectionObject> mapper;

    if (mapper.find() > 0) {
        for (TSqlORMapperIterator<ConnectionObject> i(mapper); i.hasNext(); ) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(Connection(i.next()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *Connection::modelData()
{
    return d.data();
}

const TModelObject *Connection::modelData() const
{
    return d.data();
}
