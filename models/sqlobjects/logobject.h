#ifndef LOGOBJECT_H
#define LOGOBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT LogObject : public TSqlObject, public QSharedData
{
public:
    QString adminID;
    QString userID;
    QString role;
    QString time;
    QString way;

    enum PropertyIndex {
        AdminID = 0,
        UserID,
        Role,
        Time,
        Way,
    };

    int primaryKeyIndex() const { return -1; }
    int autoValueIndex() const { return -1; }
    QString tableName() const { return QLatin1String("log"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(QString adminID READ getadminID WRITE setadminID)
    T_DEFINE_PROPERTY(QString, adminID)
    Q_PROPERTY(QString userID READ getuserID WRITE setuserID)
    T_DEFINE_PROPERTY(QString, userID)
    Q_PROPERTY(QString role READ getrole WRITE setrole)
    T_DEFINE_PROPERTY(QString, role)
    Q_PROPERTY(QString time READ gettime WRITE settime)
    T_DEFINE_PROPERTY(QString, time)
    Q_PROPERTY(QString way READ getway WRITE setway)
    T_DEFINE_PROPERTY(QString, way)
};

#endif // LOGOBJECT_H
