#ifndef ASSETSUNITMANAGEROBJECT_H
#define ASSETSUNITMANAGEROBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT AssetsunitmanagerObject : public TSqlObject, public QSharedData
{
public:
    QString managerID;
    QString managerName;
    QString managerShortname;
    QString managerState;

    enum PropertyIndex {
        ManagerID = 0,
        ManagerName,
        ManagerShortname,
        ManagerState,
    };

    int primaryKeyIndex() const { return ManagerID; }
    int autoValueIndex() const { return -1; }
    QString tableName() const { return QLatin1String("assetsunitmanager"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(QString managerID READ getmanagerID WRITE setmanagerID)
    T_DEFINE_PROPERTY(QString, managerID)
    Q_PROPERTY(QString managerName READ getmanagerName WRITE setmanagerName)
    T_DEFINE_PROPERTY(QString, managerName)
    Q_PROPERTY(QString managerShortname READ getmanagerShortname WRITE setmanagerShortname)
    T_DEFINE_PROPERTY(QString, managerShortname)
    Q_PROPERTY(QString managerState READ getmanagerState WRITE setmanagerState)
    T_DEFINE_PROPERTY(QString, managerState)
};

#endif // ASSETSUNITMANAGEROBJECT_H
