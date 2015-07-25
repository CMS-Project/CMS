#ifndef OPERATORSOBJECT_H
#define OPERATORSOBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT OperatorsObject : public TSqlObject, public QSharedData
{
public:
    QString operatorID;
    QString operatorName;
    QString operatorNickname;
    QString operatorPassword;
    QString operatorPhone;
    QString ID;
    QString operatorRole;
    QString operatorStatus;

    enum PropertyIndex {
        OperatorID = 0,
        OperatorName,
        OperatorNickname,
        OperatorPassword,
        OperatorPhone,
        Id,
        OperatorRole,
        OperatorStatus,
    };

    int primaryKeyIndex() const { return OperatorID; }
    int autoValueIndex() const { return -1; }
    QString tableName() const { return QLatin1String("operators"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(QString operatorID READ getoperatorID WRITE setoperatorID)
    T_DEFINE_PROPERTY(QString, operatorID)
    Q_PROPERTY(QString operatorName READ getoperatorName WRITE setoperatorName)
    T_DEFINE_PROPERTY(QString, operatorName)
    Q_PROPERTY(QString operatorNickname READ getoperatorNickname WRITE setoperatorNickname)
    T_DEFINE_PROPERTY(QString, operatorNickname)
    Q_PROPERTY(QString operatorPassword READ getoperatorPassword WRITE setoperatorPassword)
    T_DEFINE_PROPERTY(QString, operatorPassword)
    Q_PROPERTY(QString operatorPhone READ getoperatorPhone WRITE setoperatorPhone)
    T_DEFINE_PROPERTY(QString, operatorPhone)
    Q_PROPERTY(QString ID READ getID WRITE setID)
    T_DEFINE_PROPERTY(QString, ID)
    Q_PROPERTY(QString operatorRole READ getoperatorRole WRITE setoperatorRole)
    T_DEFINE_PROPERTY(QString, operatorRole)
    Q_PROPERTY(QString operatorStatus READ getoperatorStatus WRITE setoperatorStatus)
    T_DEFINE_PROPERTY(QString, operatorStatus)
};

#endif // OPERATORSOBJECT_H
