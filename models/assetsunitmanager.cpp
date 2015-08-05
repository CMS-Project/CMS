#include <TreeFrogModel>
#include "assetsunitmanager.h"
#include "assetsunitmanagerobject.h"

Assetsunitmanager::Assetsunitmanager()
    : TAbstractModel(), d(new AssetsunitmanagerObject)
{ }

Assetsunitmanager::Assetsunitmanager(const Assetsunitmanager &other)
    : TAbstractModel(), d(new AssetsunitmanagerObject(*other.d))
{ }

Assetsunitmanager::Assetsunitmanager(const AssetsunitmanagerObject &object)
    : TAbstractModel(), d(new AssetsunitmanagerObject(object))
{ }

Assetsunitmanager::~Assetsunitmanager()
{
    // If the reference count becomes 0,
    // the shared data object 'AssetsunitmanagerObject' is deleted.
}

QString Assetsunitmanager::managerID() const
{
    return d->managerID;
}

void Assetsunitmanager::setManagerID(const QString &managerID)
{
    d->managerID = managerID;
}

QString Assetsunitmanager::managerName() const
{
    return d->managerName;
}

void Assetsunitmanager::setManagerName(const QString &managerName)
{
    d->managerName = managerName;
}

QString Assetsunitmanager::managerShortname() const
{
    return d->managerShortname;
}

void Assetsunitmanager::setManagerShortname(const QString &managerShortname)
{
    d->managerShortname = managerShortname;
}

QString Assetsunitmanager::managerState() const
{
    return d->managerState;
}

void Assetsunitmanager::setManagerState(const QString &managerState)
{
    d->managerState = managerState;
}

Assetsunitmanager &Assetsunitmanager::operator=(const Assetsunitmanager &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

QList<Assetsunitmanager> Assetsunitmanager::list_manager()
{
    QList<Assetsunitmanager> manager_list;
      TSqlQuery query;
      query.exec("SELECT * FROM assetsunitmanager");
      while(query.next()){

          Assetsunitmanager a;  //建立一个对象a
          a.setManagerID(query.value(0).toString());
          a.setManagerName(query.value(1).toString());
          a.setManagerShortname(query.value(2).toString());
          a.setManagerState(query.value(3).toString());

           manager_list.append(a); //将a插入链表中

      }

     return manager_list;
}

Assetsunitmanager Assetsunitmanager::create(const QString &managerID, const QString &managerName, const QString &managerShortname, const QString &managerState)
{
    AssetsunitmanagerObject obj;
    obj.managerID = managerID;
    obj.managerName = managerName;
    obj.managerShortname = managerShortname;
    obj.managerState = managerState;
    if (!obj.create()) {
        return Assetsunitmanager();
    }
    return Assetsunitmanager(obj);
}

Assetsunitmanager Assetsunitmanager::create(const QVariantMap &values)
{
    Assetsunitmanager model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

Assetsunitmanager Assetsunitmanager::get(const QString &managerID)
{
    TSqlORMapper<AssetsunitmanagerObject> mapper;
    return Assetsunitmanager(mapper.findByPrimaryKey(managerID));
}

bool Assetsunitmanager::check_managerID(const QString &managerID)
{
    QSqlQuery query;
    query.exec("SELECT managerID FROM assetsuitmanager WHERE managerID = '"+managerID+"'");
    if(query.next()){
        return false;
    }else{
        return true;
    }
}

bool Assetsunitmanager::new_manager(const QString &adminID, const QString &managerID)
{
    TSqlQuery query;
    QString role = "资产管理人";
    QString way = "新建";
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString now_time= current_date_time.toString("yyyy-MM-dd hh:mm:ss");
    query.prepare("INSERT INTO log (adminID,userID,role,time,way)  VALUE (:adminID, :userID, :role, :time, :way)");
    query.bindValue(":adminID",adminID);
    query.bindValue(":userID",managerID);
    query.bindValue(":role",role);
    query.bindValue(":time",now_time);
    query.bindValue(":way",way);
    if(query.exec())
        return true;
    else
        return false;
}

int Assetsunitmanager::count()
{
    TSqlORMapper<AssetsunitmanagerObject> mapper;
    return mapper.findCount();
}

QList<Assetsunitmanager> Assetsunitmanager::getAll()
{
    return tfGetModelListByCriteria<Assetsunitmanager, AssetsunitmanagerObject>(TCriteria());
}

QJsonArray Assetsunitmanager::getAllJson()
{
    QJsonArray array;
    TSqlORMapper<AssetsunitmanagerObject> mapper;

    if (mapper.find() > 0) {
        for (TSqlORMapperIterator<AssetsunitmanagerObject> i(mapper); i.hasNext(); ) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(Assetsunitmanager(i.next()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *Assetsunitmanager::modelData()
{
    return d.data();
}

const TModelObject *Assetsunitmanager::modelData() const
{
    return d.data();
}
