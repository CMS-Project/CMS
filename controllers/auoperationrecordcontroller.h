#ifndef AUOPERATIONRECORDCONTROLLER_H
#define AUOPERATIONRECORDCONTROLLER_H

#include "applicationcontroller.h"


class T_CONTROLLER_EXPORT AuoperationRecordController : public ApplicationController
{
    Q_OBJECT
public:
    AuoperationRecordController() { }
    AuoperationRecordController(const AuoperationRecordController &other);

public slots:
    void index();
    void show(const QString &pk);
    void entry();
    void create();
    void edit(const QString &pk);
    void save(const QString &pk);
    void remove(const QString &pk);

private:
    void renderEntry(const QVariantMap &auoperationRecord = QVariantMap());
    void renderEdit(const QVariantMap &auoperationRecord = QVariantMap());
};

T_DECLARE_CONTROLLER(AuoperationRecordController, auoperationrecordcontroller)

#endif // AUOPERATIONRECORDCONTROLLER_H
