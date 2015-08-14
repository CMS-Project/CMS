#include "assetsunitcontroller.h"

#include <assetsunit.h>
#include <marketingunit.h>
#include <QDate>
#include <TSqlQuery>
#include <TActionController>
#include <auoperationrecord.h>
#include <assetsunitmanager.h>
#include <operators.h>

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

    TSqlQuery query;
    if(value.isNull() || value.isEmpty()) {
        query.prepare("select aum.managerID, assetsUnitID, assetsUnitShortname, assetsBalance from assetsunitmanager as aum left join assetsUnit as au \
                   on aum.managerID = au.managerID order by aum.managerID asc");  // Query execution
    }else if(category == "managerID"){
        query.prepare("select managerID, assetsUnitID, assetsUnitShortname, assetsBalance from assetsUnit where managerID = :value order by managerID asc");
        query.bind(":value", value);
    }else if(category == "assetsUnitID"){
        query.prepare("select aum.managerID, assetsUnitID, assetsUnitShortname, assetsBalance from assetsunitmanager as aum, assetsUnit as au \
                    where aum.managerID=au.managerID and assetsUnitID = :value order by aum.managerID asc");
        query.bind(":value", value);
    }else if(category == "assetsUnitShortname"){
        query.prepare("select managerID, assetsUnitID, assetsUnitShortname, assetsBalance from assetsUnit \
                   where assetsUnitShortname like :value order by managerID asc");
        value.prepend("%").append("%");
        query.bind(":value", value);
    }

    query.exec();
    while (query.next()) {
        QJsonObject obj;
        obj.insert("managerID", query.value(0).toInt());
        obj.insert("assetsUnitID", query.value(1).isNull() ? "" : query.value(1).toString());
        obj.insert("assetsUnitShortname", query.value(2).toString());
        obj.insert("assetsBalance", query.value(3).isNull() ? "" : query.value(3).toString());
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

    Assetsunitmanager am = Assetsunitmanager::get(form["managerID"].toString());
    if(am.managerState() != "可用"){
        operationLog("资产单元创建", "失败", "资产管理人managerID: " + am.managerID() + "不可用");
        renderText(QString("资产管理人不可用"));
        return;
    }

    if(!AssetsUnit::get(form["assetsUnitID"].toInt()).isNull()) {
        renderText(QString("资产单元已存在"));
        return;
    }

    if(form["assetsBalance"].toInt() >= 0) {
        auto assetsunit = AssetsUnit::create(form);
        QString result;

        if (!assetsunit.isNull()) {
            result = "成功";
        } else {
            result = "失败";
        }

        operationLog("资产单元添加", result, "创建资产单元: ID: " + form["assetsUnitID"].toString() + ", 名称: " + form["assetsUnitShortname"].toString()+",资金："+form["assetsBalance"].toInt());
        renderText(QString("创建" + result));
    }else {
        operationLog("资产单元添加", "失败", "创建资产单元: ID: " + form["assetsUnitID"].toString() + ", 名称: " + form["assetsUnitShortname"].toString()+",资金："+form["assetsBalance"].toInt());
        renderText(QString("创建失败，请填写正确的资产单元资金金额。" ));
    }
}

void AssetsunitController::editAssetsUnit()
{
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    QVariantMap assetsUnit = httpRequest().formItems("assetsUnit");
    QString auID = assetsUnit["assetsUnitID"].toString();
    QString mgID = assetsUnit["managerID"].toString();
    QString name = assetsUnit["assetsUnitShortname"].toString();

    if(Assetsunitmanager::get(mgID).managerState() != "可用"){
        operationLog("资产单元修改", "失败", "资产管理人managerID: " + mgID + "不可用");
        renderText(QString("资产管理人不可用"));
        return;
    }

    QString result;
    TSqlQuery query;

    query.prepare("update assetsUnit set assetsUnitShortname = :name where assetsUnitID = :auID and managerID = :mgID");
    query.bind(":name", name).bind(":auID", auID).bind(":mgID", mgID);
    query.exec();

    if(query.numRowsAffected() == 1) {
        result = "成功";
    }else{
        rollbackTransaction();
        result = "失败";
    }

    operationLog("资产单元修改", result, "修改资产单元: ID: " + auID + ", managerID: " + mgID + ", 名称更改: " + name);
    renderText(QString("修改" + result));
}

void AssetsunitController::removeAssetsUnit()
{
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    QString auID = httpRequest().formItemValue("assetsUnitID");
    QString mgID = httpRequest().formItemValue("managerID");
    QString result;
    TSqlQuery query;

    query.prepare("delete from assetsUnit where assetsUnitID = :auID and managerID = :mgID");
    query.bind(":auID", auID).bind(":mgID", mgID);
    query.exec();

    if(query.numRowsAffected() == 1) {
        result = "成功";
    }else {
        rollbackTransaction();
        result = "失败";
    }

    operationLog("资产单元删除", result, "删除资产单元: ID: " + auID + ", managerID: " + mgID);
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
                   where  mu.SrcUnitID = " + value);
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

    form["destUnitID"] = form["srcUnitID"];
    form["operatorID"] = session()["operatorID"].toString();

    int unitID = form["srcUnitID"].toInt();
    int muvalue = form["muvalue"].toInt();
    AssetsUnit srcAU = AssetsUnit::get(unitID, form["srcAUManager"].toString());
    AssetsUnit destAU = AssetsUnit::get(unitID, form["destAUManager"].toString());

    if(!srcAU.isNull()) {
        if(destAU.isNull()) {
            AssetsUnit::create(unitID, form["destAUManager"].toString(), srcAU.assetsUnitShortname(), 0);
            destAU = AssetsUnit::get(unitID, form["destAUManager"].toString());
        }

        int srcValue = srcAU.assetsBalance();
        int destValue = destAU.assetsBalance();

        if(muvalue <= srcValue && muvalue > 0) {
            Marketingunit mu = Marketingunit::create(form);
            QString result;
            TSqlQuery query;

            query.prepare("update assetsUnit set assetsBalance = :srcVal where assetsUnitID = :srcUnitID and managerID = :srcMgID; \
                            update assetsUnit set assetsBalance = :destVal where assetsUnitID = :destUnitID and managerID = :destMgID;");
            query.bind(":srcVal", srcValue - muvalue).bind(":srcUnitID", unitID).bind(":srcMgID", form["srcAUManager"].toString()).
                  bind(":destVal", destValue + muvalue).bind(":destUnitID", unitID).bind(":destMgID", form["destAUManager"].toString());
            query.exec();

            if(!mu.isNull() && query.numRowsAffected() != 0) {
                result = "成功";
            }else{
                result = "失败";
                rollbackTransaction();
            }

            // WARN: Log失败
            operationLog("资产划转", result, "资产划转：资产单元" + QString(unitID) + ", 从资产管理人: " + form["srcAUManager"].toString() + "到" + form["destAUManager"].toString() + ", 金额" + QString(muvalue));
            renderText(QString("划转" + result));
        }else{
            operationLog("资产划转", "失败", "资产划转：资产单元" + QString(unitID) + ", 从资产管理人: " + form["srcAUManager"].toString() + "到" + form["destAUManager"].toString() + ", 金额" + QString(muvalue));
            renderText(QString("金额非法"));
        }
    }else{
        operationLog("资产划转", "失败", "资产划转：资产单元" + QString(unitID) + ", 从资产管理人: " + form["srcAUManager"].toString() + "到" + form["destAUManager"].toString() + ", 金额" + QString(muvalue));
        renderText(QString("划转失败"));
    }
}

void AssetsunitController::assetsAllot()
{
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    QVariantMap form = httpRequest().formItems("assetsAllot");
    QString auID = form["assetsUnitID"].toString();
    QString mgID = form["managerID"].toString();
    QString value = form["value"].toString();
    QString remarks = form["remarks"].toString();

    if(Assetsunitmanager::get(mgID).managerState() != "可用"){
        operationLog("资产单元修改", "失败", "资产管理人managerID: " + mgID + "不可用");
        renderText(QString("资产管理人不可用"));
        return;
    }

    if(value.toInt() > 0) {
        QString result;
        TSqlQuery query;

        query.prepare("update assetsUnit set assetsBalance = :value where assetsUnitID = :assetsUnitID and managerID = :managerID;");
        query.bind(":value", value).bind(":assetsUnitID", auID).bind(":managerID", mgID);
        query.exec();

        if(query.numRowsAffected() == 1) {
            result = "成功";
        }else{
            result = "失败";
            rollbackTransaction();
        }

        operationLog("资产调拨", result, "资产调拨：资产单元" + auID + "资产管理人" + mgID + ", 金额调整到：" + value + "备注：" + remarks);
        renderText("调拨" + result);
    }else{
        operationLog("资产调拨", "失败", "资产调拨：资产单元" + auID + "资产管理人" + mgID + ", 金额调整到：" + value + "备注：" + remarks);
        renderText("金额非法");
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

    if(operatorID.isNull() || operatorID.isEmpty() || Operators::get(operatorID).operatorStatus() != "正常"){
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
