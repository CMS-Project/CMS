#include "cmscontroller.h"
#include "cms.h"
#include "operators.h"
#include "admins.h"
#include "assetsunitmanagercontroller.h"
#include "assetsunitmanager.h"
#include "operatorscontroller.h"
#include "log.h"
#include <QSqlQuery>
#include <qsqlquery.h>
#include <QDateTime>
#include <qdatetime.h>

CmsController::CmsController(const CmsController &)
    : ApplicationController()
{ }

void CmsController::index()
{
    QList<Cms> cmsList = Cms::getAll();
    texport(cmsList);
    render();
}

void CmsController::show_operator(const QString &operatorID)
{
    QString adminID = session().value("adminID").toString();
    Operators a;
    QList<Operators> operator_list = a.search_operator(operatorID,adminID);
    if(operator_list.isEmpty()){
        QString error = "无相关操作员!";
        texport(error);
        texport(adminID);
        texport(operator_list);
        render();
    }else{
        texport(adminID);
        texport(operator_list);
        render("show_operator");
    }

}

void CmsController::show_manager(const QString &managerID)
{
    Assetsunitmanager a;
    QList<Assetsunitmanager> b = a.searching(managerID);
    if(b.isEmpty()){
        QString error = "该资产管理人不存在!";
        texport(error);
        texport(b);
        render();
    }else{
        texport(b);
        render();
        }
}

void CmsController::entry()
{
    renderEntry();
}

void CmsController::newmanager()
{
    render("newmanager");
}

void CmsController::createmanager()
{
    QString adminID = session().value("adminID").toString();
    if (httpRequest().method() != Tf::Post) {
        return;
    }
   auto form = httpRequest().formItems("assetsunitmanager");
   QString managerID = form["managerID"].toString();
   Assetsunitmanager a;
   auto assetsunitmanager = a.create(form);
   if(!assetsunitmanager.isNull() && a.new_manager(adminID,managerID)){
       redirect(urla("list_manager"));
   }else{
       QString error = "资产管理人编号已经存在!";
       texport(error);
       renderEntry2(form);
   }

}

void CmsController::create()
{
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    auto form = httpRequest().formItems("operators");
    QString ID = form["operatorID"].toString();
    auto operators = Operators::create(form);
    Cms cms;
    if (!operators.isNull() && cms.checkoperatorID(ID)) {
        QString adminID = session().value("adminID").toString();
        QString notice  = form["operatorID"].toString();

       if(cms.insert_connection(adminID,notice)){
            redirect(urla("list_operator", adminID));
       }
    } else {
        QString error = "操作员编号已经存在!";
        texport(error);
        renderEntry(form);
    }
}

void CmsController::admin_login()
{
    render("admin_login");
}

void CmsController::adminlogin()
{
    if(httpRequest().method() != Tf::Post){
        return;
    }
    auto form = httpRequest().formItems("cms");
    Cms cms;
    if(cms.adminlogin(form)){
        b = form["numberID"].toString();
        session().insert("adminID",b);
        redirect(urla("admin_center",b));
    }else{
        QString error = "NumberID or Password Error";
        tflash(error);
        redirect(urla("admin_login"));
    }
}

void CmsController::admin_center(const QString &adminID)
{
    //if(session.value("adminID").toString() == "")
    QString ID = session().value("adminID").toString();
    if(adminID.compare(ID) == 0)
    {
        texport(adminID);
        render("admin_center"); //在该页面能够正常显示adminID
    }else{
        redirect(urla("index"));
    }
}

void CmsController::operator_login()
{
    render("operator_login");
}

void CmsController::operatorlogin()
{
    if(httpRequest().method() != Tf::Post){
        return;
    }
    auto form = httpRequest().formItems("cms");
    Cms cms;
    int c = cms.operatorlogin(form);
    if(c == 1){
        a = form["numberID"].toString();
        session().insert("operatorID",a);
        redirect(url("assetsunit","index"));
    }else if(c == 2){
        QString error = "账号已被冻结";
        tflash(error);
        redirect(urla("operator_login"));
    }else{
        QString error = "NumberID or Password Error";
        tflash(error);
        redirect(urla("operator_login"));
    }
}
void CmsController::operatorlogout(){

   session().remove("operatorID");
   redirect(url("Cms","index"));
}


void CmsController::operator_center(const QString &operatorID)
{
    texport(operatorID);
    render("operator_center");
}

void CmsController::renderEntry(const QVariantMap &cms)
{
    QString adminID = session().value("adminID").toString();
    texport(cms);
    texport(adminID);
    render("entry");
}

void CmsController::renderEntry2(const QVariantMap &assetsunitmanager)
{
    texport(assetsunitmanager);
    render("newmanager");
}

void CmsController::list_operator(const QString &adminID)
{
    //QList<Operators> list_operator();
    Operators form;
    QList<Operators> operator_list = form.list_operator(adminID);
    texport(operator_list);
    //QString adminID = session().value("adminID").toString();
    texport(adminID);
    render("list_operator");

}

void CmsController::list_log(const QString &adminID)
{
    Log log;
    QList<Log> log_list = log.list_log(adminID);
    texport(log_list);
    texport(adminID);
    render("list_log");
}

void CmsController::search_operator()
{
    if(httpRequest().method() != Tf::Post){
        return;
    }
    //QString operatorID = httpRequest().formItemValue("operators");
    auto form = httpRequest().formItems("operators");
    QString operatorID = form["operatorID"].toString();
    redirect(urla("show_operator", operatorID));

}

void CmsController::search_manager()
{
    if(httpRequest().method() != Tf::Post){
        return;
    }
    auto form = httpRequest().formItems("assetsunitmanager");
    QString managerID = form["managerID"].toString();
    redirect(urla("show_manager", managerID));
}

void CmsController::list_manager()
{
    QString adminID = session().value("adminID").toString();
     Assetsunitmanager form;
     QList<Assetsunitmanager> manager_list = form.list_manager();
     texport(adminID);
     texport(manager_list);
     render("list_manager");
}

void CmsController::edit(const QString &pk)
{
    auto operators = Operators::get(pk);
    if (!operators.isNull()) {
        renderEdit(operators.toVariantMap());
    } else {
        redirect(urla("entry"));
    }
}

void CmsController::changemanager(const QString &managerID)
{
    auto assetsunitmanager = Assetsunitmanager::get(managerID);
    if(!assetsunitmanager.isNull()){
       renderEdit2(assetsunitmanager.toVariantMap());
    }else{
        redirect(urla("change"));
    }
}
void CmsController::change()
{
    renderEntry();
}

void CmsController::save(const QString &pk)
{
    QString adminID = session().value("adminID").toString();
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    QString error;
    auto cms = Operators::get(pk);
    if (cms.isNull()) {
        error = "Original data not found. It may have been updated/removed by another transaction.";
        tflash(error);
        redirect(urla("edit", pk));
        return;
    }
    Cms a;
    if(!a.update_operator(adminID,pk)){
        return;
    }
    auto form = httpRequest().formItems("operators");
    cms.setProperties(form);
    if (cms.save()) {
        redirect(urla("list_operator", adminID));
    } else {
        error = "Failed to update.";
        texport(error);
        renderEdit(form);
    }
}

void CmsController::savemanager(const QString &pk)
{
    QString adminID = session().value("adminID").toString();
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    QString error;
    auto assetsunitmanager = Assetsunitmanager::get(pk);
    if (assetsunitmanager.isNull()) {
        error = "Original data not found. It may have been updated/removed by another transaction.";
        tflash(error);
        redirect(urla("change", pk));
        return;
    }
    Cms a;
    if(!a.update_manager(adminID,pk))
    {
        return;
    }

    auto form = httpRequest().formItems("assetsunitmanager");
    assetsunitmanager.setProperties(form);
    if (assetsunitmanager.save()) {
        redirect(urla("list_manager"));
    } else {
        error = "Failed to update.";
        texport(error);
        renderEdit(form);
    }

}

void CmsController::renderEdit(const QVariantMap &operators)
{
    QString adminID = session().value("adminID").toString();
    texport(operators);
    texport(adminID);
    render("edit");
}

void CmsController::renderEdit2(const QVariantMap &assetsunitmanager)
{
    texport(assetsunitmanager);
    render("change");
}

void CmsController::remove(const QString &pk)
{
    QString adminID = session().value("adminID").toString();
    Cms a;
    if(a.remove_connection(adminID,pk)){
         redirect(urla("list_operator",adminID));
    }
}

void CmsController::delete_operator(const QString &pk)
{
    QString adminID = session().value("adminID").toString();
    Cms cms;
    if(cms.delete_operator(adminID,pk)){
        redirect(urla("list_operator",adminID));
    }
}

void CmsController::change_status(const QString &operatorID)
{
    QString adminID = session().value("adminID").toString();
    Cms cms;
    if(cms.change_status(adminID,operatorID)){
        redirect(urla("list_operator",adminID));
    }
}

void CmsController::cgstatus(const QString &managerID)
{
    QString adminID = session().value("adminID").toString();
    Cms cms;;
    if(cms.cgstatus(adminID,managerID)){
        redirect(urla("list_manager"));
    }
}

void CmsController::refresh()
{
    QString adminID = session().value("adminID").toString();
    redirect(urla("list_operator",adminID));
}


// Don't remove below this line
T_REGISTER_CONTROLLER(cmscontroller)
