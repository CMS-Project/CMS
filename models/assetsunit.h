#ifndef ASSETSUNIT_H
#define ASSETSUNIT_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class AssetsUnitObject;
class QJsonArray;


class T_MODEL_EXPORT AssetsUnit : public TAbstractModel
{
public:
    AssetsUnit();
    AssetsUnit(const AssetsUnit &other);
    AssetsUnit(const AssetsUnitObject &object);
    ~AssetsUnit();

    int assetsUnitID() const;
    void setAssetsUnitID(int assetsUnitID);
    QString managerID() const;
    void setManagerID(const QString &managerID);
    QString assetsUnitShortname() const;
    void setAssetsUnitShortname(const QString &assetsUnitShortname);
    int assetsBalance() const;
    void setAssetsBalance(int assetsBalance);
    AssetsUnit &operator=(const AssetsUnit &other);

    bool create() { return TAbstractModel::create(); }
    bool update() { return TAbstractModel::update(); }
    bool save()   { return TAbstractModel::save(); }
    bool remove() { return TAbstractModel::remove(); }

    static AssetsUnit create(int assetsUnitID, const QString &managerID, const QString &assetsUnitShortname, int assetsBalance);
    static AssetsUnit create(const QVariantMap &values);
    static AssetsUnit get(int assetsUnitID);
    static AssetsUnit get(int assetsUnitID, const QString &managerID);
    static int count();
    static QList<AssetsUnit> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<AssetsUnitObject> d;

    TModelObject *modelData();
    const TModelObject *modelData() const;
};

Q_DECLARE_METATYPE(AssetsUnit)
Q_DECLARE_METATYPE(QList<AssetsUnit>)

#endif // ASSETSUNIT_H
