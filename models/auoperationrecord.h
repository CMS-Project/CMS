#ifndef AUOPERATIONRECORD_H
#define AUOPERATIONRECORD_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class AuoperationRecordObject;
class QJsonArray;


class T_MODEL_EXPORT AuoperationRecord : public TAbstractModel
{
public:
    AuoperationRecord();
    AuoperationRecord(const AuoperationRecord &other);
    AuoperationRecord(const AuoperationRecordObject &object);
    ~AuoperationRecord();

    int opID() const;
    QString operatorID() const;
    void setOperatorID(const QString &operatorID);
    QString type() const;
    void setType(const QString &type);
    QString result() const;
    void setResult(const QString &result);
    QDateTime time() const;
    void setTime(const QDateTime &time);
    QString remarks() const;
    void setRemarks(const QString &remarks);
    AuoperationRecord &operator=(const AuoperationRecord &other);

    bool create() { return TAbstractModel::create(); }
    bool update() { return TAbstractModel::update(); }
    bool save()   { return TAbstractModel::save(); }
    bool remove() { return TAbstractModel::remove(); }

    static AuoperationRecord create(const QString &operatorID, const QString &type, const QString &result, const QString &remarks);
    static AuoperationRecord create(const QVariantMap &values);
    static AuoperationRecord get(int opID);
    static int count();
    static QList<AuoperationRecord> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<AuoperationRecordObject> d;

    TModelObject *modelData();
    const TModelObject *modelData() const;
};

Q_DECLARE_METATYPE(AuoperationRecord)
Q_DECLARE_METATYPE(QList<AuoperationRecord>)

#endif // AUOPERATIONRECORD_H
