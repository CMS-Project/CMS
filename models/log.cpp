#include <TreeFrogModel>
#include "log.h"
#include "logobject.h"

Log::Log()
    : TAbstractModel(), d(new LogObject)
{ }

Log::Log(const Log &other)
    : TAbstractModel(), d(new LogObject(*other.d))
{ }

Log::Log(const LogObject &object)
    : TAbstractModel(), d(new LogObject(object))
{ }

Log::~Log()
{
    // If the reference count becomes 0,
    // the shared data object 'LogObject' is deleted.
}

QString Log::adminID() const
{
    return d->adminID;
}

void Log::setAdminID(const QString &adminID)
{
    d->adminID = adminID;
}

QString Log::userID() const
{
    return d->userID;
}

void Log::setUserID(const QString &userID)
{
    d->userID = userID;
}

QString Log::role() const
{
    return d->role;
}

void Log::setRole(const QString &role)
{
    d->role = role;
}

QString Log::time() const
{
    return d->time;
}

void Log::setTime(const QString &time)
{
    d->time = time;
}

QString Log::way() const
{
    return d->way;
}

void Log::setWay(const QString &way)
{
    d->way = way;
}

Log &Log::operator=(const Log &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

Log Log::create(const QString &adminID, const QString &userID, const QString &role, const QString &time, const QString &way)
{
    LogObject obj;
    obj.adminID = adminID;
    obj.userID = userID;
    obj.role = role;
    obj.time = time;
    obj.way = way;
    if (!obj.create()) {
        return Log();
    }
    return Log(obj);
}

Log Log::create(const QVariantMap &values)
{
    Log model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

Log Log::get(const QString &adminID, const QString &userID, const QString &role, const QString &time, const QString &way)
{
    TCriteria cri;
    cri.add(LogObject::AdminID, adminID);
    cri.add(LogObject::UserID, userID);
    cri.add(LogObject::Role, role);
    cri.add(LogObject::Time, time);
    cri.add(LogObject::Way, way);
    TSqlORMapper<LogObject> mapper;
    return Log(mapper.findFirst(cri));
}

int Log::count()
{
    TSqlORMapper<LogObject> mapper;
    return mapper.findCount();
}

QList<Log> Log::list_log(const QString &adminID)
{
//    QList<Operators> operator_list;
//    TSqlQuery query;
//    query.exec("SELECT * FROM operators join connection on operators.operatorID = connection.operatorID WHERE connection.adminID = '"+adminID+"' AND connection.operatorID = '"+operatorID+"'");
//    while(query.next()){
//        Operators a;  //建立一个对象a
//        a.setOperatorID(query.value(0).toString());
//        a.setOperatorName(query.value(1).toString());
//        a.setOperatorNickname(query.value(2).toString());
//        a.setOperatorPassword(query.value(3).toString());
//       // a.setOperatorNumber(query.value(4).toString());
//        a.setOperatorPhone(query.value(4).toString());
//        a.setId(query.value(5).toString());
//        a.setOperatorRole(query.value(6).toString());
//        a.setOperatorStatus(query.value(7).toString());  //设置对象a中的相关值

//        operator_list.append(a); //将a插入链表中
//    }
//    return operator_list;
    QList<Log> log_list;
    TSqlQuery query;
    query.exec("SELECT * FROM log where adminID = '"+adminID+"' ORDER BY time DESC");
    while(query.next()){
        Log a;
        a.setAdminID(query.value(0).toString());
        a.setUserID(query.value(1).toString());
        a.setRole(query.value(2).toString());
        a.setTime(query.value(3).toString());
        a.setWay(query.value(4).toString());
        log_list.append(a);
    }
    return log_list;
}

QList<Log> Log::getAll()
{
    return tfGetModelListByCriteria<Log, LogObject>(TCriteria());
}

QJsonArray Log::getAllJson()
{
    QJsonArray array;
    TSqlORMapper<LogObject> mapper;

    if (mapper.find() > 0) {
        for (TSqlORMapperIterator<LogObject> i(mapper); i.hasNext(); ) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(Log(i.next()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *Log::modelData()
{
    return d.data();
}

const TModelObject *Log::modelData() const
{
    return d.data();
}
