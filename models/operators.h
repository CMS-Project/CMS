#ifndef OPERATORS_H
#define OPERATORS_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class OperatorsObject;
class QJsonArray;


class T_MODEL_EXPORT Operators : public TAbstractModel
{
public:
    Operators();
    Operators(const Operators &other);
    Operators(const OperatorsObject &object);
    ~Operators();

    QString operatorID() const;
    void setOperatorID(const QString &operatorID);
    QString operatorName() const;
    void setOperatorName(const QString &operatorName);
    QString operatorNickname() const;
    void setOperatorNickname(const QString &operatorNickname);
    QString operatorPassword() const;
    void setOperatorPassword(const QString &operatorPassword);
    QString operatorPhone() const;
    void setOperatorPhone(const QString &operatorPhone);
    QString id() const;
    void setId(const QString &id);
    QString operatorRole() const;
    void setOperatorRole(const QString &operatorRole);
    QString operatorStatus() const;
    void setOperatorStatus(const QString &operatorStatus);
    Operators &operator=(const Operators &other);

    bool create() { return TAbstractModel::create(); }
    bool update() { return TAbstractModel::update(); }
    bool save()   { return TAbstractModel::save(); }
    bool remove() { return TAbstractModel::remove(); }

    static Operators create(const QString &operatorID, const QString &operatorName, const QString &operatorNickname, const QString &operatorPassword, const QString &operatorPhone, const QString &id, const QString &operatorRole, const QString &operatorStatus);
    static Operators create(const QVariantMap &values);
    static Operators get(const QString &operatorID);
    static QList<Operators> list_operator(const QString &adminID);
    static int count();
    static QList<Operators> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<OperatorsObject> d;

    TModelObject *modelData();
    const TModelObject *modelData() const;
};

Q_DECLARE_METATYPE(Operators)
Q_DECLARE_METATYPE(QList<Operators>)

#endif // OPERATORS_H
