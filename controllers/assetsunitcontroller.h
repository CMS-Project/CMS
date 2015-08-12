#ifndef ASSETSUNITCONTROLLER_H
#define ASSETSUNITCONTROLLER_H

#include "applicationcontroller.h"


class T_CONTROLLER_EXPORT AssetsunitController : public ApplicationController
{
    Q_OBJECT
public:
    AssetsunitController() { }
    AssetsunitController(const AssetsunitController &other);

public slots:
    void index();
    void AUManagment();
    void AUTransfer();
    void AUOptLog();
    void getAssetsUnitManagerList();
    void createAssetsUnit();
    void editAssetsUnit();
    void removeAssetsUnit();
    void getMarketingUnitList();
    void editMarketingUnit();
    void assetsTransfer();
    void assetsAllot();
    void getAUOptLogList();

private:
    void operationLog(QString type, QString result, QString remarks);

protected:
    bool preFilter();
};

T_DECLARE_CONTROLLER(AssetsunitController, assetsunitcontroller)

#endif // ASSETSUNITCONTROLLER_H
