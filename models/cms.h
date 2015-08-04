#ifndef CMS_H
#define CMS_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class CmsObject;
class QJsonArray;


class T_MODEL_EXPORT Cms : public TAbstractModel
{
public:
    Cms();
    Cms(const Cms &other);
    Cms(const CmsObject &object);
    ~Cms();

    QString numberID() const;
    void setNumberID(const QString &numberID);
    QString name() const;
    void setName(const QString &name);
    QString nickname() const;
    void setNickname(const QString &nickname);
    QString password() const;
    void setPassword(const QString &password);
    QString id() const;
    void setId(const QString &id);
    double phone() const;
    void setPhone(double phone);
    QString belong() const;
    void setBelong(const QString &belong);
    QString userNumber() const;
    void setUserNumber(const QString &userNumber);
    double role() const;
    void setRole(double role);
    Cms &operator=(const Cms &other);

    bool create() { return TAbstractModel::create(); }
    bool update() { return TAbstractModel::update(); }
    bool save()   { return TAbstractModel::save(); }
    bool remove() { return TAbstractModel::remove(); }

    static Cms create(const QString &numberID, const QString &name, const QString &nickname, const QString &password, const QString &id, double phone, const QString &belong, const QString &userNumber, double role);
    static Cms create(const QVariantMap &values);
    static bool adminlogin(const QVariantMap &values);
    static bool operatorlogin(const QVariantMap &values);
    static bool insert_connection(const QString &adminID, const QString &operatorID);
    static bool remove_connection(const QString &adminID, const QString &operatorID);
    static bool delete_operator(const QString &operatorID);
    static bool change_status(const QString &operatorID);
    static bool cgstatus(const QString &managerID);
    static bool checkoperatorID(const QString &operatorID);
    static Cms get(const QString &numberID);
    static int count();
    static QList<Cms> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<CmsObject> d;

    TModelObject *modelData();
    const TModelObject *modelData() const;
};

Q_DECLARE_METATYPE(Cms)
Q_DECLARE_METATYPE(QList<Cms>)

#endif // CMS_H
