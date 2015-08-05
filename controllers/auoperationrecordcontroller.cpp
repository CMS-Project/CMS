#include "auoperationrecordcontroller.h"
#include "auoperationrecord.h"


AuoperationRecordController::AuoperationRecordController(const AuoperationRecordController &)
    : ApplicationController()
{ }

void AuoperationRecordController::index()
{
    QList<AuoperationRecord> auoperationRecordList = AuoperationRecord::getAll();
    texport(auoperationRecordList);
    render();
}

void AuoperationRecordController::show(const QString &pk)
{
    auto auoperationRecord = AuoperationRecord::get(pk.toInt());
    texport(auoperationRecord);
    render();
}

void AuoperationRecordController::entry()
{
    renderEntry();
}

void AuoperationRecordController::create()
{
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    auto form = httpRequest().formItems("auoperationRecord");
    auto auoperationRecord = AuoperationRecord::create(form);
    if (!auoperationRecord.isNull()) {
        QString notice = "Created successfully.";
        tflash(notice);
        redirect(urla("show", auoperationRecord.opID()));
    } else {
        QString error = "Failed to create.";
        texport(error);
        renderEntry(form);
    }
}

void AuoperationRecordController::renderEntry(const QVariantMap &auoperationRecord)
{
    texport(auoperationRecord);
    render("entry");
}

void AuoperationRecordController::edit(const QString &pk)
{
    auto auoperationRecord = AuoperationRecord::get(pk.toInt());
    if (!auoperationRecord.isNull()) {
        renderEdit(auoperationRecord.toVariantMap());
    } else {
        redirect(urla("entry"));
    }
}

void AuoperationRecordController::save(const QString &pk)
{
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    QString error;
    auto auoperationRecord = AuoperationRecord::get(pk.toInt());
    if (auoperationRecord.isNull()) {
        error = "Original data not found. It may have been updated/removed by another transaction.";
        tflash(error);
        redirect(urla("edit", pk));
        return;
    }

    auto form = httpRequest().formItems("auoperationRecord");
    auoperationRecord.setProperties(form);
    if (auoperationRecord.save()) {
        QString notice = "Updated successfully.";
        tflash(notice);
        redirect(urla("show", pk));
    } else {
        error = "Failed to update.";
        texport(error);
        renderEdit(form);
    }
}

void AuoperationRecordController::renderEdit(const QVariantMap &auoperationRecord)
{
    texport(auoperationRecord);
    render("edit");
}

void AuoperationRecordController::remove(const QString &pk)
{
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    auto auoperationRecord = AuoperationRecord::get(pk.toInt());
    auoperationRecord.remove();
    redirect(urla("index"));
}


// Don't remove below this line
T_REGISTER_CONTROLLER(auoperationrecordcontroller)
