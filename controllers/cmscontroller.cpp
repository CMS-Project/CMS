#include "cmscontroller.h"
#include "cms.h"


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

    auto form = httpRequest().formItems("cms");
    auto cms = Cms::create(form);
    if (!cms.isNull()) {
        QString notice = "Created successfully.";
        tflash(notice);
        redirect(urla("show", cms.numberID()));
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
        QString notice = "Welcom "+form["numberID"].toString()+"";
        tflash(notice);
        redirect(urla("admin_center"));
    }else{
        QString error = "NumberID or Password Error";
        tflash(error);
        redirect(urla("admin_login"));
    }
}

void CmsController::admin_center()
{
    render("admin_center");
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
        QString notice = "Welcome "+form["numberID"].toString()+"";
        tflash(notice);
        redirect(urla("operator_center"));
    }else{
        QString error = "NumberID or Password Error";
        tflash(error);
        redirect(urla("operator_login"));
    }
}

void CmsController::operator_center()
{
    render("operator_center");
}

void CmsController::renderEntry(const QVariantMap &cms)
{
    texport(cms);
    render("entry");
}

void CmsController::edit(const QString &pk)
{
    auto cms = Cms::get(pk);
    if (!cms.isNull()) {
        renderEdit(cms.toVariantMap());
    } else {
        redirect(urla("entry"));
    }
}

void CmsController::save(const QString &pk)
{
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    QString error;
    auto cms = Cms::get(pk);
    if (cms.isNull()) {
        error = "Original data not found. It may have been updated/removed by another transaction.";
        tflash(error);
        redirect(urla("edit", pk));
        return;
    }

    auto form = httpRequest().formItems("cms");
    cms.setProperties(form);
    if (cms.save()) {
        QString notice = "Updated successfully.";
        tflash(notice);
        redirect(urla("show", pk));
    } else {
        error = "Failed to update.";
        texport(error);
        renderEdit(form);
    }
}

void CmsController::renderEdit(const QVariantMap &cms)
{
    texport(cms);
    render("edit");
}

void CmsController::remove(const QString &pk)
{
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    auto cms = Cms::get(pk);
    cms.remove();
    redirect(urla("index"));
}


// Don't remove below this line
T_REGISTER_CONTROLLER(cmscontroller)
