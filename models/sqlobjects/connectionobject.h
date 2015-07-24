#ifndef CONNECTIONOBJECT_H
#define CONNECTIONOBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT ConnectionObject : public TSqlObject, public QSharedData
{
public:
    QString adminID;
    QString operatorID;

    enum PropertyIndex {
        AdminID = 0,
        OperatorID,
    };

    int primaryKeyIndex() const { return -1; }
    int autoValueIndex() const { return -1; }
    QString tableName() const { return QLatin1String("connection"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(QString adminID READ getadminID WRITE setadminID)
    T_DEFINE_PROPERTY(QString, adminID)
    Q_PROPERTY(QString operatorID READ getoperatorID WRITE setoperatorID)
    T_DEFINE_PROPERTY(QString, operatorID)
};

#endif // CONNECTIONOBJECT_H
