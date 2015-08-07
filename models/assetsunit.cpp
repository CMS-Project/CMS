#include <TreeFrogModel>
#include "assetsunit.h"
#include "assetsunitobject.h"

AssetsUnit::AssetsUnit()
    : TAbstractModel(), d(new AssetsUnitObject)
{
    d->assetsUnitID = 0;
    d->assetsBalance = 0;
}

AssetsUnit::AssetsUnit(const AssetsUnit &other)
    : TAbstractModel(), d(new AssetsUnitObject(*other.d))
{ }

AssetsUnit::AssetsUnit(const AssetsUnitObject &object)
    : TAbstractModel(), d(new AssetsUnitObject(object))
{ }

AssetsUnit::~AssetsUnit()
{
    // If the reference count becomes 0,
    // the shared data object 'AssetsUnitObject' is deleted.
}

int AssetsUnit::assetsUnitID() const
{
    return d->assetsUnitID;
}

void AssetsUnit::setAssetsUnitID(int assetsUnitID)
{
    d->assetsUnitID = assetsUnitID;
}

QString AssetsUnit::managerID() const
{
    return d->managerID;
}

void AssetsUnit::setManagerID(const QString &managerID)
{
    d->managerID = managerID;
}

QString AssetsUnit::assetsUnitShortname() const
{
    return d->assetsUnitShortname;
}

void AssetsUnit::setAssetsUnitShortname(const QString &assetsUnitShortname)
{
    d->assetsUnitShortname = assetsUnitShortname;
}

int AssetsUnit::assetsBalance() const
{
    return d->assetsBalance;
}

void AssetsUnit::setAssetsBalance(int assetsBalance)
{
    d->assetsBalance = assetsBalance;
}

AssetsUnit &AssetsUnit::operator=(const AssetsUnit &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

AssetsUnit AssetsUnit::create(int assetsUnitID, const QString &managerID, const QString &assetsUnitShortname, int assetsBalance)
{
    AssetsUnitObject obj;
    obj.assetsUnitID = assetsUnitID;
    obj.managerID = managerID;
    obj.assetsUnitShortname = assetsUnitShortname;
    obj.assetsBalance = assetsBalance;
    if (!obj.create()) {
        return AssetsUnit();
    }
    return AssetsUnit(obj);
}

AssetsUnit AssetsUnit::create(const QVariantMap &values)
{
    AssetsUnit model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

AssetsUnit AssetsUnit::get(int assetsUnitID)
{
    TSqlORMapper<AssetsUnitObject> mapper;
    return AssetsUnit(mapper.findByPrimaryKey(assetsUnitID));
}

AssetsUnit AssetsUnit::get(int assetsUnitID, const QString &managerID)
{
    TSqlORMapper<AssetsUnitObject> mapper;
    mapper.find();
    TSqlORMapperIterator<AssetsUnitObject> i(mapper);
    while (i.hasNext()) {
        AssetsUnitObject obj = i.next();
        if(obj.managerID == managerID && obj.assetsUnitID == assetsUnitID)
            return AssetsUnit(obj);
    }
    return AssetsUnit();
}

int AssetsUnit::count()
{
    TSqlORMapper<AssetsUnitObject> mapper;
    return mapper.findCount();
}

QList<AssetsUnit> AssetsUnit::getAll()
{
    return tfGetModelListByCriteria<AssetsUnit, AssetsUnitObject>(TCriteria());
}

QJsonArray AssetsUnit::getAllJson()
{
    QJsonArray array;
    TSqlORMapper<AssetsUnitObject> mapper;

    if (mapper.find() > 0) {
        for (TSqlORMapperIterator<AssetsUnitObject> i(mapper); i.hasNext(); ) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(AssetsUnit(i.next()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *AssetsUnit::modelData()
{
    return d.data();
}

const TModelObject *AssetsUnit::modelData() const
{
    return d.data();
}
