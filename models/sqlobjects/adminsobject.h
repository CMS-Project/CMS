#ifndef ADMINSOBJECT_H
#define ADMINSOBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT AdminsObject : public TSqlObject, public QSharedData
{
public:
    QString adminID;
    QString adminName;
    QString adminPassword;

    enum PropertyIndex {
        AdminID = 0,
        AdminName,
        AdminPassword,
    };

    int primaryKeyIndex() const { return AdminID; }
    int autoValueIndex() const { return -1; }
    QString tableName() const { return QLatin1String("admins"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(QString adminID READ getadminID WRITE setadminID)
    T_DEFINE_PROPERTY(QString, adminID)
    Q_PROPERTY(QString adminName READ getadminName WRITE setadminName)
    T_DEFINE_PROPERTY(QString, adminName)
    Q_PROPERTY(QString adminPassword READ getadminPassword WRITE setadminPassword)
    T_DEFINE_PROPERTY(QString, adminPassword)
};

#endif // ADMINSOBJECT_H
