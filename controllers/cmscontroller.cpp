#include "cmscontroller.h"
#include "cms.h"
#include "operators.h"
#include "admins.h"


CmsController::CmsController(const CmsController &)
    : ApplicationController()
{ }

void CmsController::index()
{
    QList<Cms> cmsList = Cms::getAll();
    texport(cmsList);
    render();
}

void CmsController::show(const QString &pk)
{
    auto cms = Cms::get(pk);
    texport(cms);
    render();
}

void CmsController::entry()
{
    renderEntry();
}

void CmsController::create()
{
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    auto form = httpRequest().formItems("operators");
    auto operators = Operators::create(form);
    if (!operators.isNull()) {
        QString adminID = session().value("adminID").toString();
        QString notice  = form["operatorID"].toString();
        Cms cms;
       if(cms.insert_connection(adminID,notice)){
           // QString notice = "Created successfully.";

      //  QString notice = b;
     //  texport(opr);
         //texport(notice);
       // tflash(notice);
            redirect(urla("list_operator", adminID));
          // render("index");
        // redirect(urla("index"));
       }
    } else {
        QString error = "Failed to create.";
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
   // renderEntry();
    if(httpRequest().method() != Tf::Post){
        return;
    }
    auto form = httpRequest().formItems("cms");
    Cms cms;
    if(cms.adminlogin(form)){
       // QString notice = "Welcom "+form["numberID"].toString()+"";
        //tflash(notice);
        //session().insert("adminID",form["numberID"].toString());
       // redirect(urla("admin_center",form["numberID"].toString()))
       // Admins a;
       // a.setAdminID(form["numberID"].toString());
      // printf( a.adminID());
        b = form["numberID"].toString();
        session().insert("adminID",b);
        redirect(urla("admin_center",b));

        //renderText(b);
    }else{
        QString error = "NumberID or Password Error";
        tflash(error);
        redirect(urla("admin_login"));
    }
}

void CmsController::admin_center(const QString &adminID)
{
    texport(adminID);
    render("admin_center"); //在该页面能够正常显示adminID
}

void CmsController::operator_login()
{
    render("operator_login");
}

void CmsController::operatorlogin()
{
   //renderEntry();
    if(httpRequest().method() != Tf::Post){
        return;
    }
    auto form = httpRequest().formItems("cms");
    Cms cms;
    if(cms.operatorlogin(form)){
       // QString notice = "Welcome "+form["numberID"].toString()+"";
       // tflash(notice);
        a = form["numberID"].toString();
        session().insert("operatorID",a);
        redirect(urla("operator_center",a));
    }else{
        QString error = "NumberID or Password Error";
        tflash(error);
        redirect(urla("operator_login"));
    }
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

void CmsController::edit(const QString &pk)
{
    auto operators = Operators::get(pk);
    if (!operators.isNull()) {
        renderEdit(operators.toVariantMap());
    } else {
        redirect(urla("entry"));
    }
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

    auto form = httpRequest().formItems("operators");
    cms.setProperties(form);
    if (cms.save()) {
       // QString notice = "Updated successfully.";
        //tflash(notice);
        redirect(urla("list_operator", adminID));
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

void CmsController::remove(const QString &pk)
{
    QString adminID = session().value("adminID").toString();
    if (httpRequest().method() != Tf::Post) {
        return;
    }
    Cms cms;
    if(cms.remove_connection(adminID,pk)){
        redirect(urla("list_operator",adminID));
    }
    //auto cms = Cms::get(pk);
    //cms.remove();
    //redirect(urla("index"));
}

void CmsController::delete_operator(const QString &pk)
{
    QString adminID = session().value("adminID").toString();
    if (httpRequest().method() != Tf::Post) {
        return;
    }
    Cms cms;
    if(cms.delete_operator(pk)){
        redirect(urla("list_operator",adminID));
    }
}

void CmsController::change_status(const QString &operatorID)
{
    QString adminID = session().value("adminID").toString();
    Cms cms;
    if(cms.change_status(operatorID)){
        redirect(urla("list_operator",adminID));
    }
}

void CmsController::refresh()
{
    QString adminID = session().value("adminID").toString();
    redirect(urla("list_operator",adminID));
}


// Don't remove below this line
T_REGISTER_CONTROLLER(cmscontroller)
