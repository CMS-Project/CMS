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

void AssetsunitController::AUTransfer()
{
    render("AUTransfer");
}

void AssetsunitController::AUOptLog()
{
    render("AUOptLog");
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
        query.exec("select aum.managerID, assetsUnitID, assetsUnitShortname,assetsBalance from CMS.assetsunitmanager as aum, CMS.assetsUnit as au \
                   where aum.managerID = au.managerID" + sort);  // Query execution
    }else if(category == "managerID"){
        query.exec("select aum.managerID, assetsUnitID, assetsUnitShortname assetsBalance from CMS.assetsunitmanager as aum, CMS.assetsUnit as au \
                   where aum.managerID = au.managerID and aum.managerID = " + value);
    }else if(category == "assetsUnitID"){
        query.exec("select aum.managerID, assetsUnitID, assetsUnitShortname assetsBalance from CMS.assetsunitmanager as aum, CMS.assetsUnit as au \
                   where aum.managerID = au.managerID and assetsUnitID = " + value);
    }else if(category == "assetsUnitShortname"){
        query.exec("select aum.managerID, assetsUnitID, assetsUnitShortname assetsBalance from CMS.assetsunitmanager as aum, CMS.assetsUnit as au \
                   where aum.managerID = au.managerID and assetsUnitShortname = '" + value + "'");
    }

    while (query.next()) {
        QJsonObject obj;
        obj.insert("managerID", query.value(0).toInt());
        obj.insert("assetsUnitID", query.value(1).toInt());
        obj.insert("assetsUnitShortname", query.value(2).toString());
        obj.insert("assetsBalance",query.value(3).toDouble());
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

    if(form["assetsBalance"].toInt()>=0)
   { auto assetsunit = AssetsUnit::create(form);
    QString result;
    if (!assetsunit.isNull()) {
            result = "成功";
        } else {
            result = "失败";
        }

        operationLog("资产单元添加", result, "创建资产单元: ID: " + form["assetsUnitID"].toString() + ", 名称: " + form["assetsUnitShortname"].toString()+",资金："+form["assetsBalance"].toInt());
        renderText(QString("创建" + result));
    }
    else {
        operationLog("资产单元添加", "失败", "创建资产单元: ID: " + form["assetsUnitID"].toString() + ", 名称: " + form["assetsUnitShortname"].toString()+",资金："+form["assetsBalance"].toInt());
        renderText(QString("创建失败，请填写正确的资产单元资金金额。" ));
        return;
    }


}

void AssetsunitController::editAssetsUnit()
{
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    QVariantMap assetsUnit = httpRequest().formItems("assetsUnit");
    QString id = assetsUnit["assetsUnitID"].toString();
    QString name = assetsUnit["assetsUnitShortname"].toString();
    AssetsUnit au = AssetsUnit::get(id.toInt());
    QString result;

    au.setAssetsUnitShortname(name);

    if(au.save()) {
        result = "成功";
    }else{
        result = "失败";
    }

    operationLog("资产单元修改", result, "修改资产单元: ID: " + id + ", 名称更改: " + name);
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
    QString id = marketingUnit["marketingUnitID"].toString();
    QString name = marketingUnit["marketingUnitShortname"].toString();
    Marketingunit mu = Marketingunit::get(id.toInt());
    QString result;

    mu.setMusname(name);

    if(mu.save()) {
        result = "成功";
    }else{
        result = "失败";
    }

    operationLog("交易单元修改", result, "修改交易单元: ID: " + id + ", 名称变更: " + name);
    renderText(QString("修改" + result));
}

void AssetsunitController::assetsTransfer(){
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    QVariantMap form = httpRequest().formItems("assetsTransfer");
    //if(form["muname"].isNull()) form["muname"] = "";
	form["operaotrID"] = session()["operatorID"].toInt();
    QString result;

    int SassetsUnit =form["srcUnitID"].toInt();
    int DassetsUnit=form["destUnitID"].toInt();
    int muvalue=form["muvalue"].toInt();
    AssetsUnit srcAU = AssetsUnit::get(SassetsUnit);
    AssetsUnit destAU = AssetsUnit::get(DassetsUnit);
    double srcValue=srcAU.assetsBalance();
    double destValue=destAU.assetsBalance();
    if(muvalue<=srcValue){
        Marketingunit marketingunit = Marketingunit::create(form);
        if(!marketingunit.isNull()){
            result = "成功";

            double nowSvalue =double(srcValue-muvalue);
            srcAU.setAssetsBalance(nowSvalue);
            if(srcAU.save()){
                double nowDvalue =double(destValue+muvalue);
                destAU.setAssetsBalance(nowDvalue);
                if(destAU.save()) result = "成功";
                else result = "失败";
            }else
                result = "失败";
        }else{
            result = "失败";
        }

        operationLog("资产调拨", result, "从资产单元ID:" + form["srcUnitID"].toString() + "到ID:" + form["destUnitID"].toString() + ", 金额:" + form["muvalue"].toString());
        renderText(QString("调拨" + result));
    }else{
        operationLog("资产调拨", "失败", "从资产单元ID:" + form["srcUnitID"].toString() + "到ID:" + form["destUnitID"].toString() + ", 金额:" + form["muvalue"].toString());
        renderText(QString("金额超过资产单元资金，调拨失败，请输入正确调拨金额。"));
    }
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

void AssetsunitController::getAUOptLogList()
{
    int page = httpRequest().queryItemValue("page").toInt();
    int rows = httpRequest().queryItemValue("rows").toInt();

    TSqlQuery query;
    QJsonArray array;
    QJsonObject json;

    query.prepare("select * from CMS.AUOperationRecord limit :offset, :rows;");
    query.bind(":offset", (page - 1) * rows).bind(":rows", rows);
    query.exec();

    while (query.next()) {
        QJsonObject obj;
        obj.insert("operatorID", query.value(1).toInt());
        obj.insert("type", query.value(2).toString());
        obj.insert("result", query.value(3).toString());
        obj.insert("time", query.value(4).toString());
        obj.insert("remarks", query.value(5).toString());
        array.append(obj);
    }

    json.insert("total", AuoperationRecord::count());
    json.insert("rows", array);

    renderJson(json);
}

// Don't remove below this line
T_REGISTER_CONTROLLER(assetsunitcontroller)
