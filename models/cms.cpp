#include <TreeFrogModel>
#include "cms.h"
#include "cmsobject.h"
#include "operators.h"
#include "assetsunitmanager.h"

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
   query.exec("SELECT * FROM admins WHERE adminID = '"+t+"' AND adminPassword = '"+b+"' ");
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
    query.exec("SELECT * FROM operators WHERE operatorID = '"+t+"' AND operatorPassword = '"+b+"' ");
   if(query.next()){
       return true;
    }
    return false;
}

bool Cms::checkoperatorID(const QString &operatorID)
{
    TSqlQuery query;
    query.exec("SELEXT operatorID FROM operators where operatorID = '"+operatorID+"'");
    if(query.next()){
        return false;
    }else{
        return true;
    }

}

bool Cms::insert_connection(const QString &adminID, const QString &operatorID)
{
    TSqlQuery query;
    query.prepare("INSERT INTO connection (adminID,operatorID)  VALUE (:adminID, :operatorID)");
    query.bindValue(":adminID",adminID);
    query.bindValue(":operatorID",operatorID);
    if(query.exec())
        return true;
    else
        return false;
}

bool Cms::remove_connection(const QString &adminID, const QString &operatorID)
{
    TSqlQuery query;
    bool result = query.exec("DELETE FROM connection WHERE adminID = '"+adminID+"' AND operatorID = '"+operatorID+"'");
    return result;

}

bool Cms::delete_operator(const QString &operatorID)
{
    TSqlQuery query;
    if( query.exec("DELETE FROM connection WHERE operatorID = '"+operatorID+"'") )
    {
      if( query.exec("DELETE FROM operators WHERE operatorID = '"+operatorID+"'") )
      {
          return true;
      }else{
          return false;
      }
    }else{
        return false;
    }
}

bool Cms::change_status(const QString &operatorID)
{
    QString status = "";
    TSqlQuery query;
    query.exec("SELECT operatorStatus FROM operators WHERE operatorID = '"+operatorID+"'");
    if(query.next()){
        status = query.value(0).toString();
        if(status.compare("正常") == 0){
            status = "冻结";
        }else{
            status  = "正常";
        }
        if( query.exec("UPDATE operators set operatorStatus = '"+status+"' WHERE operatorID = '"+operatorID+"'") )
        {
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

bool Cms::cgstatus(const QString  &managerID)
{

    QString status = "";
    TSqlQuery query;
    query.exec("SELECT managerState FROM assetsunitmanager WHERE managerID = '"+managerID+"'");
    if(query.next()){
        status = query.value(0).toString();
        if(status.compare("可用") == 0){
            status = "冻结";
        }else{
            status  = "可用";
        }
        if( query.exec("UPDATE assetsunitmanager set managerState = '"+status+"' WHERE  managerID = '"+managerID+"'") )
        {
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
//    QString name = "可用";
//    QString sn = "er";
//    TSqlQuery query;
//    if(query.exec("UPDATE assetsunitmanager set managerState = '"+name+"' WHERE managerID = '1'"))
//    {
//        return true;
//    }else{
//        return false;
//    }

}

//void Cms::list_operator(const QString &adminID)
//{
//    QList<Operators> operator_list;
//    TSqlQuery query;
//    query.exec("SELECT * FROM operators left join connection on operators.operatorsID = connection.operatorsID WHERE connection.adminID = '"+adminID+"'");
//    while(query.next()){
//      //  QList<Operators> operator_list;
//        //for()
//      //  {

//       // }
//        Operators a;
//        a.setOperatorID(query.value(1).toString());
//        a.setOperatorName(query.value(2).toString());
//        a.setOperatorNickname(query.value(3).toString());
//        a.setOperatorNumber(query.value(4).toString());
//        a.setOperatorPassword(query.value(5).toString());
//        a.setId(query.value(6).toString());
//        a.setOperatorPhone(query.value(7).toString());
//        a.setOperatorRole(query.value(8).toString());
//        a.setOperatorStatus(query.value(9).toString());

//        operator_list.append(a);

//    }

//  //  return;

//}

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
