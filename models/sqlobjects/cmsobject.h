#ifndef CMSOBJECT_H
#define CMSOBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT CmsObject : public TSqlObject, public QSharedData
{
public:
    QString numberID;
    QString name;
    QString nickname;
    QString password;
    QString ID;
    double phone;
    QString belong;
    QString user_number;
    double role;

    enum PropertyIndex {
        NumberID = 0,
        Name,
        Nickname,
        Password,
        Id,
        Phone,
        Belong,
        UserNumber,
        Role,
    };

    int primaryKeyIndex() const { return NumberID; }
    int autoValueIndex() const { return -1; }
    QString tableName() const { return QLatin1String("cms"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(QString numberID READ getnumberID WRITE setnumberID)
    T_DEFINE_PROPERTY(QString, numberID)
    Q_PROPERTY(QString name READ getname WRITE setname)
    T_DEFINE_PROPERTY(QString, name)
    Q_PROPERTY(QString nickname READ getnickname WRITE setnickname)
    T_DEFINE_PROPERTY(QString, nickname)
    Q_PROPERTY(QString password READ getpassword WRITE setpassword)
    T_DEFINE_PROPERTY(QString, password)
    Q_PROPERTY(QString ID READ getID WRITE setID)
    T_DEFINE_PROPERTY(QString, ID)
    Q_PROPERTY(double phone READ getphone WRITE setphone)
    T_DEFINE_PROPERTY(double, phone)
    Q_PROPERTY(QString belong READ getbelong WRITE setbelong)
    T_DEFINE_PROPERTY(QString, belong)
    Q_PROPERTY(QString user_number READ getuser_number WRITE setuser_number)
    T_DEFINE_PROPERTY(QString, user_number)
    Q_PROPERTY(double role READ getrole WRITE setrole)
    T_DEFINE_PROPERTY(double, role)
};

#endif // CMSOBJECT_H
