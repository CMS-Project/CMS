#ifndef AUOPERATIONRECORDOBJECT_H
#define AUOPERATIONRECORDOBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT AuoperationRecordObject : public TSqlObject, public QSharedData
{
public:
    int opID;
    QString operatorID;
    QString type;
    QString result;
    QDateTime time;
    QString remarks;

    enum PropertyIndex {
        OpID = 0,
        OperatorID,
        Type,
        Result,
        Time,
        Remarks,
    };

    int primaryKeyIndex() const { return OpID; }
    int autoValueIndex() const { return OpID; }
    QString tableName() const { return QLatin1String("AUOperationRecord"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(int opID READ getopID WRITE setopID)
    T_DEFINE_PROPERTY(int, opID)
    Q_PROPERTY(QString operatorID READ getoperatorID WRITE setoperatorID)
    T_DEFINE_PROPERTY(QString, operatorID)
    Q_PROPERTY(QString type READ gettype WRITE settype)
    T_DEFINE_PROPERTY(QString, type)
    Q_PROPERTY(QString result READ getresult WRITE setresult)
    T_DEFINE_PROPERTY(QString, result)
    Q_PROPERTY(QDateTime time READ gettime WRITE settime)
    T_DEFINE_PROPERTY(QDateTime, time)
    Q_PROPERTY(QString remarks READ getremarks WRITE setremarks)
    T_DEFINE_PROPERTY(QString, remarks)
};

#endif // AUOPERATIONRECORDOBJECT_H
