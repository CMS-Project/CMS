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

void MarketingunitController::searching(){
        QString val = httpRequest().formItemValue("search");
        QString error;
        if(val.isEmpty()){
            error="请输入查询关键字";
            tflash(error);
            redirect(urla("index"));
            return;
        }

        QList<Marketingunit> list1;
        TSqlQuery query;
        query.exec("SELECT * FROM CMS.marketingunit WHERE MUid LIKE '%"+val+"%';");
        while(query.next()){
            Marketingunit a;
            a.setMuid(query.value(0).toInt());
            a.setMuname(query.value(1).toString());
            a.setMusname(query.value(2).toString());
            a.setMuvalue(query.value(3).toInt());
            a.setMudate(query.value(4).toDate());
            a.setSrcUnitID(query.value(5).toInt());
            a.setDestUnitID(query.value(6).toInt());
            a.setOperatorID(query.value(7).toString());
            list1.append(a);
        }
        QList<Marketingunit> list2;
        TSqlQuery query2;
        query2.exec("SELECT * FROM CMS.marketingunit WHERE MUsname LIKE '%"+val+"%';");
        while(query2.next()){
            Marketingunit b;
            b.setMuid(query2.value(0).toInt());
            b.setMuname(query2.value(1).toString());
            b.setMusname(query2.value(2).toString());
            b.setMuvalue(query2.value(3).toInt());
            b.setMudate(query2.value(4).toDate());
            b.setSrcUnitID(query2.value(5).toInt());
            b.setDestUnitID(query2.value(6).toInt());
            b.setOperatorID(query2.value(7).toString());
            list2.append(b);
        }
        if(list1.isEmpty()&&list2.isEmpty()){
            error="can't find";
            tflash(error);
            redirect(urla("index"));
            return;
        }else{
            texport(list1);
            texport(list2);
            render();
        }
        }
void MarketingunitController::reportform(){
  render();
}

void MarketingunitController::showform(){
    QString start = httpRequest().formItemValue("start");
    QString end = httpRequest().formItemValue("end");
     QString error;
    if(start.isEmpty()||end.isEmpty()){
        error="请输入日期";
        tflash(error);
        redirect(urla("reportform"));
        return;
    }

     if(start>end){
        error="起始日期应小于截止日期";
        tflash(error);
        redirect(urla("reportform"));
        return;
    }
    int c=0;
    QList<Marketingunit> list;
    TSqlQuery query;
    query.exec("SELECT * FROM CMS.marketingunit WHERE MUdate BETWEEN '"+start+"' AND '"+end+"' ORDER BY MUdate;");
    while(query.next()){
        Marketingunit a;
        a.setMuid(query.value(0).toInt());
        a.setMuvalue(query.value(1).toInt());
        a.setMusname(query.value(2).toString());
        a.setMuname(query.value(3).toString());


        a.setMudate(query.value(4).toDate());
        a.setSrcUnitID(query.value(5).toInt());
        a.setDestUnitID(query.value(6).toInt());
        a.setOperatorID(query.value(7).toString());
        c=a.muvalue()+c;
        list.append(a);
    }
    texport(list);
    texport(c);
    render();
}


// Don't remove below this line
T_REGISTER_CONTROLLER(marketingunitcontroller)
