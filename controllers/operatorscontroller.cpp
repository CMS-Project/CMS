#include "operatorscontroller.h"
#include "operators.h"


OperatorsController::OperatorsController(const OperatorsController &)
    : ApplicationController()
{ }

void OperatorsController::index()
{
    QList<Operators> operatorsList = Operators::getAll();
    texport(operatorsList);
    render();
}

void OperatorsController::show(const QString &pk)
{
    auto operators = Operators::get(pk);
    texport(operators);
    render();
}

void OperatorsController::entry()
{
    renderEntry();
}

void OperatorsController::create()
{
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    auto form = httpRequest().formItems("operators");
    auto operators = Operators::create(form);
    if (!operators.isNull()) {
        QString notice = "Created successfully.";
        tflash(notice);
        redirect(urla("show", operators.operatorID()));
    } else {
        QString error = "Failed to create.";
        texport(error);
        renderEntry(form);
    }
}

void OperatorsController::renderEntry(const QVariantMap &operators)
{
    texport(operators);
    render("entry");
}

void OperatorsController::edit(const QString &pk)
{
    auto operators = Operators::get(pk);
    if (!operators.isNull()) {
        renderEdit(operators.toVariantMap());
    } else {
        redirect(urla("entry"));
    }
}

void OperatorsController::save(const QString &pk)
{
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    QString error;
    auto operators = Operators::get(pk);
    if (operators.isNull()) {
        error = "Original data not found. It may have been updated/removed by another transaction.";
        tflash(error);
        redirect(urla("edit", pk));
        return;
    }

    auto form = httpRequest().formItems("operators");
    operators.setProperties(form);
    if (operators.save()) {
        QString notice = "Updated successfully.";
        tflash(notice);
        redirect(urla("show", pk));
    } else {
        error = "Failed to update.";
        texport(error);
        renderEdit(form);
    }
}

void OperatorsController::renderEdit(const QVariantMap &operators)
{
    texport(operators);
    render("edit");
}

void OperatorsController::remove(const QString &pk)
{
    if (httpRequest().method() != Tf::Post) {
        return;
    }

    auto operators = Operators::get(pk);
    operators.remove();
    redirect(urla("index"));
}


// Don't remove below this line
T_REGISTER_CONTROLLER(operatorscontroller)
