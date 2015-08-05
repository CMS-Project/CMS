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
    void show_operator(const QString &pk);
    void show_manager(const QString &pk);
    void entry();
    void newmanager();
    void createmanager();
    void changemanager(const QString &managerID);
    void change();
    void cgstatus(const QString &managerID);
    void create();
    void admin_login();
    void adminlogin();
    void admin_center(const QString &adminID);
    void operator_login();
    void operatorlogin();
    void operator_center(const QString &operatorID);
    void list_operator(const QString &adminID);
    void list_log(const QString &adminID);
    void search_operator();
    void search_manager();
    void list_manager();
    void delete_operator(const QString &pk);
    void change_status(const QString &operatorID);
    void refresh();
    void edit(const QString &pk);
    void save(const QString &pk);
    void savemanager(const QString &pk);
    void remove(const QString &pk);

private:
    void renderEntry(const QVariantMap &cms = QVariantMap());
    void renderEdit(const QVariantMap &operators = QVariantMap());
    void renderEdit2(const QVariantMap &assetsunitmanager = QVariantMap());
    void renderEntry2(const QVariantMap &assetsunitmanager = QVariantMap());
    //void renderChange(const QVariantMap &assetsunitmanager = QVariantMap());
};

T_DECLARE_CONTROLLER(CmsController, cmscontroller)

#endif // CMSCONTROLLER_H
