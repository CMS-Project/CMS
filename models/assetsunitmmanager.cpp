#include <TreeFrogModel>
#include "assetsunitmmanager.h"
#include "assetsunitmmanagerobject.h"

Assetsunitmmanager::Assetsunitmmanager()
    : TAbstractModel(), d(new AssetsunitmmanagerObject)
{
    d->managerID = 0;
    d->agentID = 0;
    d->managerState = 0;
}

Assetsunitmmanager::Assetsunitmmanager(const Assetsunitmmanager &other)
    : TAbstractModel(), d(new AssetsunitmmanagerObject(*other.d))
{ }

Assetsunitmmanager::Assetsunitmmanager(const AssetsunitmmanagerObject &object)
    : TAbstractModel(), d(new AssetsunitmmanagerObject(object))
{ }

Assetsunitmmanager::~Assetsunitmmanager()
{
    // If the reference count becomes 0,
    // the shared data object 'AssetsunitmmanagerObject' is deleted.
}

int Assetsunitmmanager::managerID() const
{
    return d->managerID;
}

void Assetsunitmmanager::setManagerID(int managerID)
{
    d->managerID = managerID;
}

int Assetsunitmmanager::agentID() const
{
    return d->agentID;
}

void Assetsunitmmanager::setAgentID(int agentID)
{
    d->agentID = agentID;
}

QString Assetsunitmmanager::managerName() const
{
    return d->managerName;
}

void Assetsunitmmanager::setManagerName(const QString &managerName)
{
    d->managerName = managerName;
}

QString Assetsunitmmanager::managerShortname() const
{
    return d->managerShortname;
}

void Assetsunitmmanager::setManagerShortname(const QString &managerShortname)
{
    d->managerShortname = managerShortname;
}

int Assetsunitmmanager::managerState() const
{
    return d->managerState;
}

void Assetsunitmmanager::setManagerState(int managerState)
{
    d->managerState = managerState;
}

Assetsunitmmanager &Assetsunitmmanager::operator=(const Assetsunitmmanager &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

Assetsunitmmanager Assetsunitmmanager::create(int managerID, int agentID, const QString &managerName, const QString &managerShortname, int managerState)
{
    AssetsunitmmanagerObject obj;
    obj.managerID = managerID;
    obj.agentID = agentID;
    obj.managerName = managerName;
    obj.managerShortname = managerShortname;
    obj.managerState = managerState;
    if (!obj.create()) {
        return Assetsunitmmanager();
    }
    return Assetsunitmmanager(obj);
}

Assetsunitmmanager Assetsunitmmanager::create(const QVariantMap &values)
{
    Assetsunitmmanager model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

Assetsunitmmanager Assetsunitmmanager::get(int managerID)
{
    TSqlORMapper<AssetsunitmmanagerObject> mapper;
    return Assetsunitmmanager(mapper.findByPrimaryKey(managerID));
}

int Assetsunitmmanager::count()
{
    TSqlORMapper<AssetsunitmmanagerObject> mapper;
    return mapper.findCount();
}

QList<Assetsunitmmanager> Assetsunitmmanager::getAll()
{
    return tfGetModelListByCriteria<Assetsunitmmanager, AssetsunitmmanagerObject>(TCriteria());
}

QJsonArray Assetsunitmmanager::getAllJson()
{
    QJsonArray array;
    TSqlORMapper<AssetsunitmmanagerObject> mapper;

    if (mapper.find() > 0) {
        for (TSqlORMapperIterator<AssetsunitmmanagerObject> i(mapper); i.hasNext(); ) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(Assetsunitmmanager(i.next()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *Assetsunitmmanager::modelData()
{
    return d.data();
}

const TModelObject *Assetsunitmmanager::modelData() const
{
    return d.data();
}
