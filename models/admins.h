#ifndef ADMINS_H
#define ADMINS_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class AdminsObject;
class QJsonArray;


class T_MODEL_EXPORT Admins : public TAbstractModel
{
public:
    Admins();
    Admins(const Admins &other);
    Admins(const AdminsObject &object);
    ~Admins();

    QString adminID() const;
    void setAdminID(const QString &adminID);
    QString adminName() const;
    void setAdminName(const QString &adminName);
    QString adminPassword() const;
    void setAdminPassword(const QString &adminPassword);
    Admins &operator=(const Admins &other);

    bool create() { return TAbstractModel::create(); }
    bool update() { return TAbstractModel::update(); }
    bool save()   { return TAbstractModel::save(); }
    bool remove() { return TAbstractModel::remove(); }

    static Admins create(const QString &adminID, const QString &adminName, const QString &adminPassword);
    static Admins create(const QVariantMap &values);
    static Admins get(const QString &adminID);
    static int count();
    static QList<Admins> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<AdminsObject> d;

    TModelObject *modelData();
    const TModelObject *modelData() const;
};

Q_DECLARE_METATYPE(Admins)
Q_DECLARE_METATYPE(QList<Admins>)

#endif // ADMINS_H
