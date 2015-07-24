#include "assetsunitcontroller.h"

#include <assetsunit.h>
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

    TSqlQuery query;
    query.exec("select aum.managerID, assetsUnitID, assetsUnitShortname from CMS.assetsUnitMmanager as aum, CMS.assetsUnit as au \
               where aum.managerID = au.managerID");  // Query execution
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

// Don't remove below this line
T_REGISTER_CONTROLLER(assetsunitcontroller)
