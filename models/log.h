#ifndef LOG_H
#define LOG_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class LogObject;
class QJsonArray;


class T_MODEL_EXPORT Log : public TAbstractModel
{
public:
    Log();
    Log(const Log &other);
    Log(const LogObject &object);
    ~Log();

    QString adminID() const;
    void setAdminID(const QString &adminID);
    QString userID() const;
    void setUserID(const QString &userID);
    QString role() const;
    void setRole(const QString &role);
    QString time() const;
    void setTime(const QString &time);
    QString way() const;
    void setWay(const QString &way);
    Log &operator=(const Log &other);

    bool create() { return TAbstractModel::create(); }
    bool update() { return TAbstractModel::update(); }
    bool save()   { return TAbstractModel::save(); }
    bool remove() { return TAbstractModel::remove(); }

    static Log create(const QString &adminID, const QString &userID, const QString &role, const QString &time, const QString &way);
    static Log create(const QVariantMap &values);
    static Log get(const QString &adminID, const QString &userID, const QString &role, const QString &time, const QString &way);
    static int count();
    static QList<Log> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<LogObject> d;

    TModelObject *modelData();
    const TModelObject *modelData() const;
};

Q_DECLARE_METATYPE(Log)
Q_DECLARE_METATYPE(QList<Log>)

#endif // LOG_H
