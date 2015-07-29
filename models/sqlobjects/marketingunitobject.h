#ifndef MARKETINGUNITOBJECT_H
#define MARKETINGUNITOBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT MarketingunitObject : public TSqlObject, public QSharedData
{
public:
    int MUid;
    int MUvalue;
    QString MUsname;
    QString MUname;
    QDate MUdate;
    int managerID;

    enum PropertyIndex {
        Muid = 0,
        Muvalue,
        Musname,
        Muname,
        Mudate,
        ManagerID,
    };

    int primaryKeyIndex() const { return Muid; }
    int autoValueIndex() const { return Muid; }
    QString tableName() const { return QLatin1String("marketingunit"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(int MUid READ getMUid WRITE setMUid)
    T_DEFINE_PROPERTY(int, MUid)
    Q_PROPERTY(int MUvalue READ getMUvalue WRITE setMUvalue)
    T_DEFINE_PROPERTY(int, MUvalue)
    Q_PROPERTY(QString MUsname READ getMUsname WRITE setMUsname)
    T_DEFINE_PROPERTY(QString, MUsname)
    Q_PROPERTY(QString MUname READ getMUname WRITE setMUname)
    T_DEFINE_PROPERTY(QString, MUname)
    Q_PROPERTY(QDate MUdate READ getMUdate WRITE setMUdate)
    T_DEFINE_PROPERTY(QDate, MUdate)
    Q_PROPERTY(int managerID READ getmanagerID WRITE setmanagerID)
    T_DEFINE_PROPERTY(int, managerID)
};

#endif // MARKETINGUNITOBJECT_H
