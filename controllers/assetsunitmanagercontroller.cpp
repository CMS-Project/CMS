#include "assetsunitmanagercontroller.h"
#include "assetsunitmanager.h"


AssetsunitmanagerController::AssetsunitmanagerController(const AssetsunitmanagerController &)
    : ApplicationController()
{ }

void AssetsunitmanagerController::index()
{
    QList<Assetsunitmanager> assetsunitmanagerList = Assetsunitmanager::getAll();
    texport(assetsunitmanagerList);
    render();
}

void AssetsunitmanagerController::show(const QString &pk)
{
    auto assetsunitmanager = Assetsunitmanager::get(pk);
    texport(assetsunitmanager);
    render();
}

void AssetsunitmanagerController::entry()
{
    renderEntry();
}

void AssetsunitmanagerController::create()
{
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    auto form = httpRequest().formItems("assetsunitmanager");
    auto assetsunitmanager = Assetsunitmanager::create(form);
    if (!assetsunitmanager.isNull()) {
        QString notice = "Created successfully.";
        tflash(notice);
        redirect(urla("show", assetsunitmanager.managerID()));
    } else {
        QString error = "Failed to create.";
        texport(error);
        renderEntry(form);
    }
}

void AssetsunitmanagerController::renderEntry(const QVariantMap &assetsunitmanager)
{
    texport(assetsunitmanager);
    render("entry");
}

void AssetsunitmanagerController::edit(const QString &pk)
{
    auto assetsunitmanager = Assetsunitmanager::get(pk);
    if (!assetsunitmanager.isNull()) {
        renderEdit(assetsunitmanager.toVariantMap());
    } else {
        redirect(urla("entry"));
    }
}

void AssetsunitmanagerController::save(const QString &pk)
{
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    QString error;
    auto assetsunitmanager = Assetsunitmanager::get(pk);
    if (assetsunitmanager.isNull()) {
        error = "Original data not found. It may have been updated/removed by another transaction.";
        tflash(error);
        redirect(urla("edit", pk));
        return;
    }

    auto form = httpRequest().formItems("assetsunitmanager");
    assetsunitmanager.setProperties(form);
    if (assetsunitmanager.save()) {
        QString notice = "Updated successfully.";
        tflash(notice);
        redirect(urla("show", pk));
    } else {
        error = "Failed to update.";
        texport(error);
        renderEdit(form);
    }
}

void AssetsunitmanagerController::renderEdit(const QVariantMap &assetsunitmanager)
{
    texport(assetsunitmanager);
    render("edit");
}

void AssetsunitmanagerController::remove(const QString &pk)
{
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    auto assetsunitmanager = Assetsunitmanager::get(pk);
    assetsunitmanager.remove();
    redirect(urla("index"));
}


// Don't remove below this line
T_REGISTER_CONTROLLER(assetsunitmanagercontroller)
