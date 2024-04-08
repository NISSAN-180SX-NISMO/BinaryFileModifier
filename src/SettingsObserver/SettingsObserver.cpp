//
// Created by User on 07.04.2024.
//

#include <iostream>
#include "SettingsObserver.h"

void SettingsObserver::onSourceDirPathChanged(const QString &newPath) {
    settings.sourceDirPath = newPath;
    emit settingsChanged(settings);
}

void SettingsObserver::onSaveDirPathChanged(const QString &newPath) {
    settings.saveDirPath = newPath;
    emit settingsChanged(settings);

}

void SettingsObserver::onFileNameMaskChanged(const QString &newMask) {
    settings.fileNameMask = newMask;
    emit settingsChanged(settings);

}

void SettingsObserver::onFileExtensionMaskChanged(const QString &newMask) {
    settings.fileExtensionMask = newMask;
    emit settingsChanged(settings);

}

void SettingsObserver::onExecutionPeriodChanged(const QTime &newPeriod) {
    settings.ExecutionPeriod = newPeriod;
    emit settingsChanged(settings);

}

void SettingsObserver::onNeedRemoveSourceFilesChanged(int state) {
    settings.needRemoveSourceFiles = state == Qt::Checked;
    emit settingsChanged(settings);
}

void SettingsObserver::onOverwriteRadioButtonClicked() {
    settings.collisionResolutionType = COLLISION_RESOLUTION_TYPE::OVERWRITE;
    emit settingsChanged(settings);
}

void SettingsObserver::onModifyRadioButtonClicked() {
    settings.collisionResolutionType = COLLISION_RESOLUTION_TYPE::MODIFY;
    emit settingsChanged(settings);
}

void SettingsObserver::onBinaryOperandChanged(const QString &newOperand) {
    settings.binaryOperand = newOperand.toULongLong(nullptr, 16);
    emit settingsChanged(settings);
}
