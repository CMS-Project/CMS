#ifndef MARKETINGUNIT_H
#define MARKETINGUNIT_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class MarketingunitObject;
class QJsonArray;


class T_MODEL_EXPORT Marketingunit : public TAbstractModel
{
public:
    Marketingunit();
    Marketingunit(const Marketingunit &other);
    Marketingunit(const MarketingunitObject &object);
    ~Marketingunit();

    int muid() const;
    void setMuid(int muid);
    int muvalue() const;
    void setMuvalue(int muvalue);
    QString musname() const;
    void setMusname(const QString &musname);
    QString muname() const;
    void setMuname(const QString &muname);
    QDate mudate() const;
    void setMudate(const QDate &mudate);
    int srcUnitID() const;
    void setSrcUnitID(int srcUnitID);
    int destUnitID() const;
    void setDestUnitID(int destUnitID);
    QString operatorID() const;
    void setOperatorID(const QString &operatorID);
    Marketingunit &operator=(const Marketingunit &other);

    bool create() { return TAbstractModel::create(); }
    bool update() { return TAbstractModel::update(); }
    bool save()   { return TAbstractModel::save(); }
    bool remove() { return TAbstractModel::remove(); }

    static Marketingunit create(int muvalue, const QString &musname, const QString &muname, const QDate &mudate, int srcUnitID, int destUnitID, const QString &operatorID);
    static Marketingunit create(const QVariantMap &values);
    static Marketingunit get(int muid);
    static int count();
    static QList<Marketingunit> getAll();
    static QJsonArray getAllJson();
    static QList<Marketingunit> listofmu();


private:
    QSharedDataPointer<MarketingunitObject> d;

    TModelObject *modelData();
    const TModelObject *modelData() const;
};

Q_DECLARE_METATYPE(Marketingunit)
Q_DECLARE_METATYPE(QList<Marketingunit>)

#endif // MARKETINGUNIT_H
