#include <TreeFrogModel>
#include "auoperationrecord.h"
#include "auoperationrecordobject.h"

AuoperationRecord::AuoperationRecord()
    : TAbstractModel(), d(new AuoperationRecordObject)
{
    d->opID = 0;
}

AuoperationRecord::AuoperationRecord(const AuoperationRecord &other)
    : TAbstractModel(), d(new AuoperationRecordObject(*other.d))
{ }

AuoperationRecord::AuoperationRecord(const AuoperationRecordObject &object)
    : TAbstractModel(), d(new AuoperationRecordObject(object))
{ }

AuoperationRecord::~AuoperationRecord()
{
    // If the reference count becomes 0,
    // the shared data object 'AuoperationRecordObject' is deleted.
}

int AuoperationRecord::opID() const
{
    return d->opID;
}

QString AuoperationRecord::operatorID() const
{
    return d->operatorID;
}

void AuoperationRecord::setOperatorID(const QString &operatorID)
{
    d->operatorID = operatorID;
}

QString AuoperationRecord::type() const
{
    return d->type;
}

void AuoperationRecord::setType(const QString &type)
{
    d->type = type;
}

QString AuoperationRecord::result() const
{
    return d->result;
}

void AuoperationRecord::setResult(const QString &result)
{
    d->result = result;
}

QDateTime AuoperationRecord::time() const
{
    return d->time;
}

void AuoperationRecord::setTime(const QDateTime &time)
{
    d->time = time;
}

QString AuoperationRecord::remarks() const
{
    return d->remarks;
}

void AuoperationRecord::setRemarks(const QString &remarks)
{
    d->remarks = remarks;
}

AuoperationRecord &AuoperationRecord::operator=(const AuoperationRecord &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

AuoperationRecord AuoperationRecord::create(const QString &operatorID, const QString &type, const QString &result, const QString &remarks)
{
    AuoperationRecordObject obj;
    obj.operatorID = operatorID;
    obj.type = type;
    obj.result = result;
    obj.time = QDateTime::currentDateTime();
    obj.remarks = remarks;
    if (!obj.create()) {
        return AuoperationRecord();
    }
    return AuoperationRecord(obj);
}

AuoperationRecord AuoperationRecord::create(const QVariantMap &values)
{
    AuoperationRecord model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

AuoperationRecord AuoperationRecord::get(int opID)
{
    TSqlORMapper<AuoperationRecordObject> mapper;
    return AuoperationRecord(mapper.findByPrimaryKey(opID));
}

int AuoperationRecord::count()
{
    TSqlORMapper<AuoperationRecordObject> mapper;
    return mapper.findCount();
}

QList<AuoperationRecord> AuoperationRecord::getAll()
{
    return tfGetModelListByCriteria<AuoperationRecord, AuoperationRecordObject>(TCriteria());
}

QJsonArray AuoperationRecord::getAllJson()
{
    QJsonArray array;
    TSqlORMapper<AuoperationRecordObject> mapper;

    if (mapper.find() > 0) {
        for (TSqlORMapperIterator<AuoperationRecordObject> i(mapper); i.hasNext(); ) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(AuoperationRecord(i.next()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *AuoperationRecord::modelData()
{
    return d.data();
}

const TModelObject *AuoperationRecord::modelData() const
{
    return d.data();
}
