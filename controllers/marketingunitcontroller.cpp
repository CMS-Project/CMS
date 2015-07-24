#include "marketingunitcontroller.h"
#include "marketingunit.h"


MarketingunitController::MarketingunitController(const MarketingunitController &)
    : ApplicationController()
{ }

void MarketingunitController::index()
{
    QList<Marketingunit> marketingunitList = Marketingunit::getAll();
    texport(marketingunitList);
    render();
}

void MarketingunitController::show(const QString &pk)
{
    auto marketingunit = Marketingunit::get(pk.toInt());
    texport(marketingunit);
    render();
}

void MarketingunitController::entry()
{
    renderEntry();
}

void MarketingunitController::create()
{
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    auto form = httpRequest().formItems("marketingunit");
    auto marketingunit = Marketingunit::create(form);
    if (!marketingunit.isNull()) {
        QString notice = "Created successfully.";
        tflash(notice);
        redirect(urla("show", marketingunit.muid()));
    } else {
        QString error = "Failed to create.";
        texport(error);
        renderEntry(form);
    }
}

void MarketingunitController::renderEntry(const QVariantMap &marketingunit)
{
    texport(marketingunit);
    render("entry");
}

void MarketingunitController::edit(const QString &pk)
{
    auto marketingunit = Marketingunit::get(pk.toInt());
    if (!marketingunit.isNull()) {
        renderEdit(marketingunit.toVariantMap());
    } else {
        redirect(urla("entry"));
    }
}

void MarketingunitController::save(const QString &pk)
{
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    QString error;
    auto marketingunit = Marketingunit::get(pk.toInt());
    if (marketingunit.isNull()) {
        error = "Original data not found. It may have been updated/removed by another transaction.";
        tflash(error);
        redirect(urla("edit", pk));
        return;
    }

    auto form = httpRequest().formItems("marketingunit");
    marketingunit.setProperties(form);
    if (marketingunit.save()) {
        QString notice = "Updated successfully.";
        tflash(notice);
        redirect(urla("show", pk));
    } else {
        error = "Failed to update.";
        texport(error);
        renderEdit(form);
    }
}

void MarketingunitController::renderEdit(const QVariantMap &marketingunit)
{
    texport(marketingunit);
    render("edit");
}

void MarketingunitController::remove(const QString &pk)
{
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    auto marketingunit = Marketingunit::get(pk.toInt());
    marketingunit.remove();
    redirect(urla("index"));
}

void MarketingunitController::index2(){
    render();
}

void MarketingunitController::searching(){
    QString val = httpRequest().formItemValue("muid");
     QString error;
    auto marketingunit = Marketingunit::get(val.toInt());
    if (marketingunit.isNull()) {
        error = "关键字不存在";
        tflash(error);
        redirect(urla("index"));
        return;
    }else{
    redirect(urla("showsearch", val));}
}

void MarketingunitController::showsearch(const QString &pk){
    auto marketingunit = Marketingunit::get(pk.toInt());
    texport(marketingunit);
    render();
}

// Don't remove below this line
T_REGISTER_CONTROLLER(marketingunitcontroller)
