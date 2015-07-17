#include <TreeFrogModel>
#include "cms.h"
#include "cmsobject.h"

Cms::Cms()
    : TAbstractModel(), d(new CmsObject)
{
    d->phone = 0;
    d->role = 0;
}

Cms::Cms(const Cms &other)
    : TAbstractModel(), d(new CmsObject(*other.d))
{ }

Cms::Cms(const CmsObject &object)
    : TAbstractModel(), d(new CmsObject(object))
{ }

Cms::~Cms()
{
    // If the reference count becomes 0,
    // the shared data object 'CmsObject' is deleted.
}

QString Cms::numberID() const
{
    return d->numberID;
}

void Cms::setNumberID(const QString &numberID)
{
    d->numberID = numberID;
}

QString Cms::name() const
{
    return d->name;
}

void Cms::setName(const QString &name)
{
    d->name = name;
}

QString Cms::nickname() const
{
    return d->nickname;
}

void Cms::setNickname(const QString &nickname)
{
    d->nickname = nickname;
}

QString Cms::password() const
{
    return d->password;
}

void Cms::setPassword(const QString &password)
{
    d->password = password;
}

QString Cms::id() const
{
    return d->ID;
}

void Cms::setId(const QString &id)
{
    d->ID = id;
}

double Cms::phone() const
{
    return d->phone;
}

void Cms::setPhone(double phone)
{
    d->phone = phone;
}

QString Cms::belong() const
{
    return d->belong;
}

void Cms::setBelong(const QString &belong)
{
    d->belong = belong;
}

QString Cms::userNumber() const
{
    return d->user_number;
}

void Cms::setUserNumber(const QString &userNumber)
{
    d->user_number = userNumber;
}

double Cms::role() const
{
    return d->role;
}

void Cms::setRole(double role)
{
    d->role = role;
}

Cms &Cms::operator=(const Cms &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

bool Cms::adminlogin(const QVariantMap &values)
{
    QString t = values["numberID"].toString();
    QString b = values["password"].toString();
    TSqlQuery query;
    query.exec("SELECT * FROM cms WHERE numberID = '"+t+"' AND password = '"+b+"' AND role = '"+0+"'");
   if(query.next()){
       return true;
    }
    return false;
}

bool Cms::operatorlogin(const QVariantMap &values)
{
    QString t = values["numberID"].toString();
    QString b = values["password"].toString();
    TSqlQuery query;
    query.exec("SELECT * FROM cms WHERE numberID = '"+t+"' AND password = '"+b+"' AND role ='"+1+"'");
   if(query.next()){
       return true;
    }
    return false;
}

Cms Cms::create(const QString &numberID, const QString &name, const QString &nickname, const QString &password, const QString &id, double phone, const QString &belong, const QString &userNumber, double role)
{
    CmsObject obj;
    obj.numberID = numberID;
    obj.name = name;
    obj.nickname = nickname;
    obj.password = password;
    obj.ID = id;
    obj.phone = phone;
    obj.belong = belong;
    obj.user_number = userNumber;
    obj.role = role;
    if (!obj.create()) {
        return Cms();
    }
    return Cms(obj);
}

Cms Cms::create(const QVariantMap &values)
{
    Cms model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

Cms Cms::get(const QString &numberID)
{
    TSqlORMapper<CmsObject> mapper;
    return Cms(mapper.findByPrimaryKey(numberID));
}

int Cms::count()
{
    TSqlORMapper<CmsObject> mapper;
    return mapper.findCount();
}

QList<Cms> Cms::getAll()
{
    return tfGetModelListByCriteria<Cms, CmsObject>(TCriteria());
}

QJsonArray Cms::getAllJson()
{
    QJsonArray array;
    TSqlORMapper<CmsObject> mapper;

    if (mapper.find() > 0) {
        for (TSqlORMapperIterator<CmsObject> i(mapper); i.hasNext(); ) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(Cms(i.next()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *Cms::modelData()
{
    return d.data();
}

const TModelObject *Cms::modelData() const
{
    return d.data();
}
