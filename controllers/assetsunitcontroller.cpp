#include "assetsunitcontroller.h"

#include <assetsunit.h>
#include<marketingunit.h>
#include <TSqlQuery>
#include <TActionController>

AssetsunitController::AssetsunitController(const AssetsunitController &)
    : ApplicationController()
{ }

void AssetsunitController::index()
{
    render();
}

void AssetsunitController::AUManagment()
{
    render("AUManagment");
}

void AssetsunitController::AUAccountManagment()
{
    // write code
}

void AssetsunitController::AUView()
{
    // write code
}

void AssetsunitController::AUTransfer()
{
    // write code
}

void AssetsunitController::AUOptLog()
{
    // write code
}

void AssetsunitController::AUStatisticsReport()
{
    // write code
}

void AssetsunitController::AURiskControl()
{
    // write code
}

void AssetsunitController::getAssetsUnitManagerList()
{
    QJsonArray array;
    QJsonObject json;
    int i = 0;

    QString category = httpRequest().queryItemValue("category");
    QString value = httpRequest().queryItemValue("value");
    QString sort = httpRequest().queryItemValue("order");
    sort = sort.isNull() ? "" : " order by aum.managerID " + sort;

    TSqlQuery query;
//    query.exec("select aum.managerID, assetsUnitID, assetsUnitShortname from CMS.assetsUnitMmanager as aum, CMS.assetsUnit as au \
//               where aum.managerID = au.managerID");  // Query execution
    if(value.isNull() || value.isEmpty()) {
        query.exec("select aum.managerID, assetsUnitID, assetsUnitShortname from CMS.assetsUnitMmanager as aum, CMS.assetsUnit as au \
                   where aum.managerID = au.managerID" + sort);  // Query execution
    }else if(category == "managerID"){
        query.exec("select aum.managerID, assetsUnitID, assetsUnitShortname from CMS.assetsUnitMmanager as aum, CMS.assetsUnit as au \
                   where aum.managerID = au.managerID and aum.managerID = " + value);
    }else if(category == "assetsUnitID"){
        query.exec("select aum.managerID, assetsUnitID, assetsUnitShortname from CMS.assetsUnitMmanager as aum, CMS.assetsUnit as au \
                   where aum.managerID = au.managerID and assetsUnitID = " + value);
    }

    while (query.next()) {
        QJsonObject obj;
        obj.insert("managerID", query.value(0).toInt());
        obj.insert("assetsUnitID", query.value(1).toInt());
        obj.insert("assetsUnitShortname", query.value(2).toString());
        array.insert(i++, obj);
    }

    json.insert("total", i);
    json.insert("rows", array);

    renderJson(json);
}

void AssetsunitController::createAssetsUnit()
{
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    auto form = httpRequest().formItems("assetsUnit");
    auto assetsunit = AssetsUnit::create(form);

    if (!assetsunit.isNull()) {
		renderText("Ok");
    } else {
    }
}

void AssetsunitController::editAssetsUnit()
{
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    QVariantMap assetsUnit = httpRequest().formItems("assetsUnit");
    int id = assetsUnit["assetsUnitID"].toInt();
    QString name = assetsUnit["assetsUnitShortname"].toString();
    AssetsUnit au = AssetsUnit::get(id);

    au.setAssetsUnitShortname(name);

    if(au.save()) {
        renderText("Ok");
    }else{

    }
}

void AssetsunitController::removeAssetsUnit()
{
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    QString id = httpRequest().formItemValue("assetsUnitID");
    AssetsUnit au = AssetsUnit::get(id.toInt());
    if(au.remove()) {
        renderText("Ok");
    }else {

    }
}
void AssetsunitController::getMarketingUnitList(){
    QJsonArray array;
    QJsonObject json;
    int i = 0;

    QString category = httpRequest().queryItemValue("category");
    QString value = httpRequest().queryItemValue("value");
    QString sort = httpRequest().queryItemValue("order");
    sort = sort.isNull() ? "" : " order by mu.SrcUnitID " + sort;
    TSqlQuery query;
/*    query.exec("select SrcUnitID,mu.MUid, MUsname from CMS.marketingunit as mu, CMS.tradeRecord as tr \
               where  mu.MUid = tr.MUid");  // Query executio*/

    if(value.isNull() || value.isEmpty()) {
        query.exec("select SrcUnitID,mu.MUid, MUsname from CMS.marketingunit as mu, CMS.tradeRecord as tr \
                   where  mu.MUid = tr.MUid order by SrcUnitID");  // Query execution
    }else if(category == "m_assetsUnitID"){
        query.exec("select SrcUnitID,mu.MUid, MUsname from CMS.marketingunit as mu, CMS.tradeRecord as tr \
                   where  mu.MUid = tr.MUid and tr.SrcUnitID = " + value);
    }else if(category == "marketingUnitID"){
        query.exec("select SrcUnitID,mu.MUid, MUsname from CMS.marketingunit as mu, CMS.tradeRecord as tr \
                   where  mu.MUid = tr.MUid and mu.MUid = " + value);
    }


    while (query.next()) {
        QJsonObject obj;
        obj.insert("m_assetsUnitID", query.value(0).toInt());
        obj.insert("marketingUnitID", query.value(1).toInt());
        obj.insert("marketingUnitShortname", query.value(2).toString());
        array.insert(i++, obj);
    }

    json.insert("total", i);
    json.insert("rows", array);

    renderJson(json);
}
void AssetsunitController::editMarketingUnit(){
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    QVariantMap marketingUnit = httpRequest().formItems("marketingUnit");
    int id = marketingUnit["marketingUnitID"].toInt();
    QString name = marketingUnit["marketingUnitShortname"].toString();
    Marketingunit mu = Marketingunit::get(id);

    mu.setMusname(name);
//    mu.setMuname(name);

    if(mu.save()) {
        renderText("Ok");
    }else{

    }
}

// Don't remove below this line
T_REGISTER_CONTROLLER(assetsunitcontroller)
