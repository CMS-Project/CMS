#ifndef ASSETSUNITMANAGER_H
#define ASSETSUNITMANAGER_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class AssetsunitmanagerObject;
class QJsonArray;


class T_MODEL_EXPORT Assetsunitmanager : public TAbstractModel
{
public:
    Assetsunitmanager();
    Assetsunitmanager(const Assetsunitmanager &other);
    Assetsunitmanager(const AssetsunitmanagerObject &object);
    ~Assetsunitmanager();

    QString managerID() const;
    void setManagerID(const QString &managerID);
    QString managerName() const;
    void setManagerName(const QString &managerName);
    QString managerShortname() const;
    void setManagerShortname(const QString &managerShortname);
    QString managerState() const;
    void setManagerState(const QString &managerState);
    Assetsunitmanager &operator=(const Assetsunitmanager &other);

    bool create() { return TAbstractModel::create(); }
    bool update() { return TAbstractModel::update(); }
    bool save()   { return TAbstractModel::save(); }
    bool remove() { return TAbstractModel::remove(); }

    static Assetsunitmanager create(const QString &managerID, const QString &managerName, const QString &managerShortname, const QString &managerState);
    static Assetsunitmanager create(const QVariantMap &values);
    static Assetsunitmanager get(const QString &managerID);
    static bool check_managerID(const QString &managerID);
    static bool new_manager(const QString &adminID,const QString &managerID);
    static int count();
    static QList<Assetsunitmanager> list_manager();
    static QList<Assetsunitmanager> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<AssetsunitmanagerObject> d;

    TModelObject *modelData();
    const TModelObject *modelData() const;
};

Q_DECLARE_METATYPE(Assetsunitmanager)
Q_DECLARE_METATYPE(QList<Assetsunitmanager>)

#endif // ASSETSUNITMANAGER_H
