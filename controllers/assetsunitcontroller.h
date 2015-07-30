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
    void AUAccountManagment();
    void AUView();
    void AUTransfer();
    void AUOptLog();
    void AUStatisticsReport();
    void AURiskControl();
    void getAssetsUnitManagerList();
    void createAssetsUnit();
    void editAssetsUnit();
    void removeAssetsUnit();
    void getMarketingUnitList();
    void editMarketingUnit();
    void assetsTransfer();
};

T_DECLARE_CONTROLLER(AssetsunitController, assetsunitcontroller)

#endif // ASSETSUNITCONTROLLER_H
