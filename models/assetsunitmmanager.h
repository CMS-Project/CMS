#ifndef ASSETSUNITMMANAGER_H
#define ASSETSUNITMMANAGER_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class AssetsunitmmanagerObject;
class QJsonArray;


class T_MODEL_EXPORT Assetsunitmmanager : public TAbstractModel
{
public:
    Assetsunitmmanager();
    Assetsunitmmanager(const Assetsunitmmanager &other);
    Assetsunitmmanager(const AssetsunitmmanagerObject &object);
    ~Assetsunitmmanager();

    int managerID() const;
    void setManagerID(int managerID);
    int agentID() const;
    void setAgentID(int agentID);
    QString managerName() const;
    void setManagerName(const QString &managerName);
    QString managerShortname() const;
    void setManagerShortname(const QString &managerShortname);
    int managerState() const;
    void setManagerState(int managerState);
    Assetsunitmmanager &operator=(const Assetsunitmmanager &other);

    bool create() { return TAbstractModel::create(); }
    bool update() { return TAbstractModel::update(); }
    bool save()   { return TAbstractModel::save(); }
    bool remove() { return TAbstractModel::remove(); }

    static Assetsunitmmanager create(int managerID, int agentID, const QString &managerName, const QString &managerShortname, int managerState);
    static Assetsunitmmanager create(const QVariantMap &values);
    static Assetsunitmmanager get(int managerID);
    static int count();
    static QList<Assetsunitmmanager> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<AssetsunitmmanagerObject> d;

    TModelObject *modelData();
    const TModelObject *modelData() const;
};

Q_DECLARE_METATYPE(Assetsunitmmanager)
Q_DECLARE_METATYPE(QList<Assetsunitmmanager>)

#endif // ASSETSUNITMMANAGER_H
