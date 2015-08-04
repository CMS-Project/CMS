#ifndef ASSETSUNITMANAGERCONTROLLER_H
#define ASSETSUNITMANAGERCONTROLLER_H

#include "applicationcontroller.h"


class T_CONTROLLER_EXPORT AssetsunitmanagerController : public ApplicationController
{
    Q_OBJECT
public:
    AssetsunitmanagerController() { }
    AssetsunitmanagerController(const AssetsunitmanagerController &other);

public slots:
    void index();
    void show(const QString &pk);
    void entry();
    void create();
    void edit(const QString &pk);
    void save(const QString &pk);
    void remove(const QString &pk);

private:
    void renderEntry(const QVariantMap &assetsunitmanager = QVariantMap());
    void renderEdit(const QVariantMap &assetsunitmanager = QVariantMap());
};

T_DECLARE_CONTROLLER(AssetsunitmanagerController, assetsunitmanagercontroller)

#endif // ASSETSUNITMANAGERCONTROLLER_H
