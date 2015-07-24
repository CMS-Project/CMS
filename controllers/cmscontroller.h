#ifndef CMSCONTROLLER_H
#define CMSCONTROLLER_H

#include "applicationcontroller.h"
#include "admins.h"


class T_CONTROLLER_EXPORT CmsController : public ApplicationController
{
    Q_OBJECT
public:
    CmsController() { }
    CmsController(const CmsController &other);
    QString a;
    QString b;

public slots:
    void index();
    void show(const QString &pk);
    void entry();
    void create();
    void admin_login();
    void adminlogin();
    void admin_center(const QString &adminID);
    void operator_login();
    void operatorlogin();
    void operator_center(const QString &operatorID);
    void list_operator(const QString &adminID);
    void delete_operator(const QString &pk);
    void change_status(const QString &operatorID);
    void refresh();
    void edit(const QString &pk);
    void save(const QString &pk);
    void remove(const QString &pk);

private:
    void renderEntry(const QVariantMap &cms = QVariantMap());
    void renderEdit(const QVariantMap &operators = QVariantMap());
};

T_DECLARE_CONTROLLER(CmsController, cmscontroller)

#endif // CMSCONTROLLER_H
