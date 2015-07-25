#ifndef CONNECTION_H
#define CONNECTION_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class ConnectionObject;
class QJsonArray;


class T_MODEL_EXPORT Connection : public TAbstractModel
{
public:
    Connection();
    Connection(const Connection &other);
    Connection(const ConnectionObject &object);
    ~Connection();

    QString adminID() const;
    void setAdminID(const QString &adminID);
    QString operatorID() const;
    void setOperatorID(const QString &operatorID);
    Connection &operator=(const Connection &other);

    bool create() { return TAbstractModel::create(); }
    bool update() { return TAbstractModel::update(); }
    bool save()   { return TAbstractModel::save(); }
    bool remove() { return TAbstractModel::remove(); }

    static Connection create(const QString &adminID, const QString &operatorID);
    static Connection create(const QVariantMap &values);
    static Connection get(const QString &adminID, const QString &operatorID);
    static int count();
    static QList<Connection> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<ConnectionObject> d;

    TModelObject *modelData();
    const TModelObject *modelData() const;
};

Q_DECLARE_METATYPE(Connection)
Q_DECLARE_METATYPE(QList<Connection>)

#endif // CONNECTION_H
