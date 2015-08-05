#ifndef ASSETSUNITOBJECT_H
#define ASSETSUNITOBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT AssetsUnitObject : public TSqlObject, public QSharedData
{
public:
    int assetsUnitID;
    QString managerID;
    QString assetsUnitShortname;
    double assetsBalance;

    enum PropertyIndex {
        AssetsUnitID = 0,
        ManagerID,
        AssetsUnitShortname,
        AssetsBalance,
    };

    int primaryKeyIndex() const { return AssetsUnitID; }
    int autoValueIndex() const { return -1; }
    QString tableName() const { return QLatin1String("assetsUnit"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(int assetsUnitID READ getassetsUnitID WRITE setassetsUnitID)
    T_DEFINE_PROPERTY(int, assetsUnitID)
    Q_PROPERTY(QString managerID READ getmanagerID WRITE setmanagerID)
    T_DEFINE_PROPERTY(QString, managerID)
    Q_PROPERTY(QString assetsUnitShortname READ getassetsUnitShortname WRITE setassetsUnitShortname)
    T_DEFINE_PROPERTY(QString, assetsUnitShortname)
    Q_PROPERTY(double assetsBalance READ getassetsBalance WRITE setassetsBalance)
    T_DEFINE_PROPERTY(double, assetsBalance)
};

#endif // ASSETSUNITOBJECT_H
