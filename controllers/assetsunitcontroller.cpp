#include "assetsunitcontroller.h"

#include <assetsunit.h>
#include <marketingunit.h>
#include <QDate>
#include <TSqlQuery>
#include <TActionController>
#include <auoperationrecord.h>

AssetsunitController::AssetsunitController(const AssetsunitController &)
    : ApplicationController()
{ }

void AssetsunitController::index()
{
    QString operatorID = session()["operatorID"].toString();
    texport(operatorID);
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
    render("AUTransfer");
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
    if(value.isNull() || value.isEmpty()) {
        query.exec("select aum.managerID, assetsUnitID, assetsUnitShortname from CMS.assetsunitmanager as aum, CMS.assetsUnit as au \
                   where aum.managerID = au.managerID" + sort);  // Query execution
    }else if(category == "managerID"){
        query.exec("select aum.managerID, assetsUnitID, assetsUnitShortname from CMS.assetsunitmanager as aum, CMS.assetsUnit as au \
                   where aum.managerID = au.managerID and aum.managerID = " + value);
    }else if(category == "assetsUnitID"){
        query.exec("select aum.managerID, assetsUnitID, assetsUnitShortname from CMS.assetsunitmanager as aum, CMS.assetsUnit as au \
                   where aum.managerID = au.managerID and assetsUnitID = " + value);
    }else if(category == "assetsUnitShortname"){
        query.exec("select aum.managerID, assetsUnitID, assetsUnitShortname from CMS.assetsunitmanager as aum, CMS.assetsUnit as au \
                   where aum.managerID = au.managerID and assetsUnitShortname = '" + value + "'");
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
    QString result;

    if (!assetsunit.isNull()) {
        result = "成功";
    } else {
        result = "失败";
    }

    operationLog("资产单元添加", result, "创建资产单元: ID: " + form["assetsUnitID"].toString() + ", 名称变更: " + form["assetsUnitShortname"].toString());
    renderText(QString("创建" + result));
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
    QString result;

    au.setAssetsUnitShortname(name);

    if(au.save()) {
        result = "成功";
    }else{
        result = "失败";
    }

    operationLog("资产单元修改", result, "修改资产单元: ID: " + QString(id) + ", 名称更改: " + name);
    renderText(QString("修改" + result));
}

void AssetsunitController::removeAssetsUnit()
{
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    QString id = httpRequest().formItemValue("assetsUnitID");
    AssetsUnit au = AssetsUnit::get(id.toInt());
    QString result;

    if(au.remove()) {
        result = "成功";
    }else {
        result = "失败";
    }

    operationLog("资产单元删除", result, "删除资产单元: ID: " + QString(id));
    renderText(QString("删除" + result));
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

    if(value.isNull() || value.isEmpty()) {
        query.exec("select SrcUnitID,MUid, MUsname from CMS.marketingunit as mu  \
                    order by SrcUnitID");  // Query execution
    }else if(category == "m_assetsUnitID"){
        query.exec("select SrcUnitID,MUid, MUsname from CMS.marketingunit as mu  \
                   where  tr.SrcUnitID = " + value);
    }else if(category == "marketingUnitID"){
        query.exec("select SrcUnitID,MUid, MUsname from CMS.marketingunit as mu \
                   where  mu.MUid = " + value);
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
    QString result;

    mu.setMusname(name);

    if(mu.save()) {
        result = "成功";
    }else{
        result = "失败";
    }

    operationLog("交易单元修改", result, "修改交易单元: ID: " + QString(id) + ", 名称变更: " + name);
    renderText(QString("修改" + result));
}

void AssetsunitController::assetsTransfer(){
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    QVariantMap form = httpRequest().formItems("assetsTransfer");
    if(form["muname"].isNull()) form["muname"] = "";
	form["operaotrID"] = session()["operatorID"].toInt();
    Marketingunit marketingunit = Marketingunit::create(form);
    QString result;

    if(!marketingunit.isNull()){
        result = "成功";
    }else{
        result = "失败";
    }

    operationLog("资产调拨", result, "从资产单元 " + form["srcUnitID"].toString() + "到 " + form["destUnitID"].toString() + ", 金额: " + form["muvalue"].toString());
    renderText(QString("调拨" + result));
}

void AssetsunitController::operationLog(QString type, QString result, QString remarks)
{
    QString operatorID = session()["operatorID"].toString();

    AuoperationRecord::create(operatorID, type, result, remarks);
}

bool AssetsunitController::preFilter()
{
    QString operatorID = session()["operatorID"].toString();

    if(operatorID.isNull() || operatorID.isEmpty()){
        redirect(url("cms", "index"));
        return false;
    }

    return true;
}

// Don't remove below this line
T_REGISTER_CONTROLLER(assetsunitcontroller)
