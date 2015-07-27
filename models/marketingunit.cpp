#include <TreeFrogModel>
#include "marketingunit.h"
#include "marketingunitobject.h"

Marketingunit::Marketingunit()
    : TAbstractModel(), d(new MarketingunitObject)
{
    d->MUid = 0;
    d->MUvalue = 0;
}

Marketingunit::Marketingunit(const Marketingunit &other)
    : TAbstractModel(), d(new MarketingunitObject(*other.d))
{ }

Marketingunit::Marketingunit(const MarketingunitObject &object)
    : TAbstractModel(), d(new MarketingunitObject(object))
{ }

Marketingunit::~Marketingunit()
{
    // If the reference count becomes 0,
    // the shared data object 'MarketingunitObject' is deleted.
}

int Marketingunit::muid() const
{
    return d->MUid;
}

int Marketingunit::muvalue() const
{
    return d->MUvalue;
}

void Marketingunit::setMuvalue(int muvalue)
{
    d->MUvalue = muvalue;
}

QString Marketingunit::musname() const
{
    return d->MUsname;
}

void Marketingunit::setMusname(const QString &musname)
{
    d->MUsname = musname;
}

QString Marketingunit::muname() const
{
    return d->MUname;
}

void Marketingunit::setMuname(const QString &muname)
{
    d->MUname = muname;
}

QDate Marketingunit::mudate() const
{
    return d->MUdate;
}

void Marketingunit::setMudate(const QDate &mudate)
{
    d->MUdate = mudate;
}

Marketingunit &Marketingunit::operator=(const Marketingunit &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

Marketingunit Marketingunit::create(int muvalue, const QString &musname, const QString &muname, const QDate &mudate)
{
    MarketingunitObject obj;
    obj.MUvalue = muvalue;
    obj.MUsname = musname;
    obj.MUname = muname;
    obj.MUdate = mudate;
    if (!obj.create()) {
        return Marketingunit();
    }
    return Marketingunit(obj);
}

Marketingunit Marketingunit::create(const QVariantMap &values)
{
    Marketingunit model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

Marketingunit Marketingunit::get(int muid)
{
    TSqlORMapper<MarketingunitObject> mapper;
    return Marketingunit(mapper.findByPrimaryKey(muid));
}

int Marketingunit::count()
{
    TSqlORMapper<MarketingunitObject> mapper;
    return mapper.findCount();
}

QList<Marketingunit> Marketingunit::getAll()
{
    return tfGetModelListByCriteria<Marketingunit, MarketingunitObject>(TCriteria());
}

QJsonArray Marketingunit::getAllJson()
{
    QJsonArray array;
    TSqlORMapper<MarketingunitObject> mapper;

    if (mapper.find() > 0) {
        for (TSqlORMapperIterator<MarketingunitObject> i(mapper); i.hasNext(); ) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(Marketingunit(i.next()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *Marketingunit::modelData()
{
    return d.data();
}

const TModelObject *Marketingunit::modelData() const
{
    return d.data();
}