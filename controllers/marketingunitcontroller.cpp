#include "marketingunitcontroller.h"
#include "marketingunit.h"
#include "assetsunitcontroller.h"
#include <assetsunit.h>
#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>
#include <TSqlQuery>
#include <TActionController>

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
    QString val = httpRequest().formItemValue("search");
        QString error=val;
        QString a;
        bool o=false;
        auto marketingunit = Marketingunit::get(val.toInt());
        if (marketingunit.isNull()) {
        TSqlQuery query;
        query.exec("SELECT MUid,MUvalue,MUsname,MUname,MUdate FROM CMS.marketingunit WHERE MUsname = '"+val+"';");  // Query execution
        while (query.next()) {
         a= query.value(0).toString();
         o=true;
        }
        if(o){
            redirect(urla("showsearch", a));
        }else{
            error="can't find";
            tflash(error);
            redirect(urla("index"));
            return;
        }
    }else{
            redirect(urla("showsearch", val));}
}

void MarketingunitController::showsearch(const QString &pk){
    auto marketingunit = Marketingunit::get(pk.toInt());
    texport(marketingunit);
    render();
}

void MarketingunitController::reportform(){
    QList<Marketingunit> marketingunitList = Marketingunit::listofmu();
    texport(marketingunitList);
    render();
}

void MarketingunitController::showform(const QString &pk){
   QString b,c;
    TSqlQuery query;
    query.exec("SELECT srcUnitID,destUnitID FROM CMS.tradeRecord WHERE MUid = '"+pk+"';");
      while (query.next()){
          b=query.value(0).toString();
          c=query.value(1).toString();
          }
    auto asunit=AssetsUnit::get(b.toInt());
    auto marketingunit = Marketingunit::get(pk.toInt());
    auto assunit=AssetsUnit::get(c.toInt());
    texport(marketingunit);
    texport(asunit);
    texport(assunit);
    render();
}

// Don't remove below this line
T_REGISTER_CONTROLLER(marketingunitcontroller)
