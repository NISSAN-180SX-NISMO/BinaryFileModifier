//
// Created by User on 07.04.2024.
//

#ifndef BINARYFILEMODIFIER_SETTINGSOBSERVER_H
#define BINARYFILEMODIFIER_SETTINGSOBSERVER_H


#include <QObject>
#include "../../model/ModificationSettings/ModificationSettings.h"

class SettingsObserver : public QObject {
Q_OBJECT

public:
    explicit SettingsObserver(ModificationSettings &settings, QObject *parent = nullptr)
            : QObject(parent), settings(settings) {}

public slots:
    void onSourceDirPathChanged(const QString &newPath);
    void onSaveDirPathChanged(const QString &newPath);
    void onFileNameMaskChanged(const QString &newMask);
    void onFileExtensionMaskChanged(const QString &newMask);
    void onExecutionPeriodChanged(const QTime &newPeriod);
    void onNeedRemoveSourceFilesChanged(int state);
    void onOverwriteRadioButtonClicked();
    void onModifyRadioButtonClicked();
    void onBinaryOperandChanged(const QString &newOperand);
signals:
    void settingsChanged(const ModificationSettings &settings);

private:
    ModificationSettings &settings;
};


#endif //BINARYFILEMODIFIER_SETTINGSOBSERVER_H
