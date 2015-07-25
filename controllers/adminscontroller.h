#ifndef ADMINSCONTROLLER_H
#define ADMINSCONTROLLER_H

#include "applicationcontroller.h"


class T_CONTROLLER_EXPORT AdminsController : public ApplicationController
{
    Q_OBJECT
public:
    AdminsController() { }
    AdminsController(const AdminsController &other);

public slots:
    void index();
    void show(const QString &pk);
    void entry();
    void create();
    void edit(const QString &pk);
    void save(const QString &pk);
    void remove(const QString &pk);

private:
    void renderEntry(const QVariantMap &admins = QVariantMap());
    void renderEdit(const QVariantMap &admins = QVariantMap());
};

T_DECLARE_CONTROLLER(AdminsController, adminscontroller)

#endif // ADMINSCONTROLLER_H
