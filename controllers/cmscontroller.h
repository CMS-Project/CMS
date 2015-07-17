#ifndef CMSCONTROLLER_H
#define CMSCONTROLLER_H

#include "applicationcontroller.h"


class T_CONTROLLER_EXPORT CmsController : public ApplicationController
{
    Q_OBJECT
public:
    CmsController() { }
    CmsController(const CmsController &other);

public slots:
    void index();
    void show(const QString &pk);
    void entry();
    void create();
    void admin_login();
    void adminlogin();
    void admin_center();
    void operator_login();
    void operatorlogin();
    void operator_center();
    void edit(const QString &pk);
    void save(const QString &pk);
    void remove(const QString &pk);

private:
    void renderEntry(const QVariantMap &cms = QVariantMap());
    void renderEdit(const QVariantMap &cms = QVariantMap());
};

T_DECLARE_CONTROLLER(CmsController, cmscontroller)

#endif // CMSCONTROLLER_H
