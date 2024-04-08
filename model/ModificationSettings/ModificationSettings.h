#ifndef BINARYFILEMODIFIER_MODIFICATIONSETTINGS_H
#define BINARYFILEMODIFIER_MODIFICATIONSETTINGS_H

#include <QString>
#include <QTime>

enum COLLISION_RESOLUTION_TYPE: bool {
    OVERWRITE,
    MODIFY
};

struct ModificationSettings {
    QString sourceDirPath                               = "";
    QString saveDirPath                                 = "";
    QString fileNameMask                                = "*";
    QString fileExtensionMask                           = ".*";
    bool needRemoveSourceFiles                          = false;
    COLLISION_RESOLUTION_TYPE collisionResolutionType   = COLLISION_RESOLUTION_TYPE::OVERWRITE;
    QTime ExecutionPeriod                               = QTime(0, 0, 0);
    uint64_t binaryOperand                              = 0x0000000000000000;
};

bool isSettingsValid(const ModificationSettings &settings);
QString printSettings(const ModificationSettings &settings);
#endif //BINARYFILEMODIFIER_MODIFICATIONSETTINGS_H
