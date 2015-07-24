#ifndef OPERATORSCONTROLLER_H
#define OPERATORSCONTROLLER_H

#include "applicationcontroller.h"


class T_CONTROLLER_EXPORT OperatorsController : public ApplicationController
{
    Q_OBJECT
public:
    OperatorsController() { }
    OperatorsController(const OperatorsController &other);

public slots:
    void index();
    void show(const QString &pk);
    void entry();
    void create();
    void edit(const QString &pk);
    void save(const QString &pk);
    void remove(const QString &pk);

private:
    void renderEntry(const QVariantMap &operators = QVariantMap());
    void renderEdit(const QVariantMap &operators = QVariantMap());
};

T_DECLARE_CONTROLLER(OperatorsController, operatorscontroller)

#endif // OPERATORSCONTROLLER_H
