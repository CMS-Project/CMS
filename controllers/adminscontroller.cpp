#include "adminscontroller.h"
#include "admins.h"


AdminsController::AdminsController(const AdminsController &)
    : ApplicationController()
{ }

void AdminsController::index()
{
    QList<Admins> adminsList = Admins::getAll();
    texport(adminsList);
    render();
}

void AdminsController::show(const QString &pk)
{
    auto admins = Admins::get(pk);
    texport(admins);
    render();
}

void AdminsController::entry()
{
    renderEntry();
}

void AdminsController::create()
{
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    auto form = httpRequest().formItems("admins");
    auto admins = Admins::create(form);
    if (!admins.isNull()) {
        QString notice = "Created successfully.";
        tflash(notice);
        redirect(urla("show", admins.adminID()));
    } else {
        QString error = "Failed to create.";
        texport(error);
        renderEntry(form);
    }
}

void AdminsController::renderEntry(const QVariantMap &admins)
{
    texport(admins);
    render("entry");
}

void AdminsController::edit(const QString &pk)
{
    auto admins = Admins::get(pk);
    if (!admins.isNull()) {
        renderEdit(admins.toVariantMap());
    } else {
        redirect(urla("entry"));
    }
}

void AdminsController::save(const QString &pk)
{
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    QString error;
    auto admins = Admins::get(pk);
    if (admins.isNull()) {
        error = "Original data not found. It may have been updated/removed by another transaction.";
        tflash(error);
        redirect(urla("edit", pk));
        return;
    }

    auto form = httpRequest().formItems("admins");
    admins.setProperties(form);
    if (admins.save()) {
        QString notice = "Updated successfully.";
        tflash(notice);
        redirect(urla("show", pk));
    } else {
        error = "Failed to update.";
        texport(error);
        renderEdit(form);
    }
}

void AdminsController::renderEdit(const QVariantMap &admins)
{
    texport(admins);
    render("edit");
}

void AdminsController::remove(const QString &pk)
{
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    auto admins = Admins::get(pk);
    admins.remove();
    redirect(urla("index"));
}


// Don't remove below this line
T_REGISTER_CONTROLLER(adminscontroller)
