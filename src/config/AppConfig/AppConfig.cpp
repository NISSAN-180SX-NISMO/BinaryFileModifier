//
// Created by User on 08.04.2024.
//

#include "AppConfig.h"
#include <QSettings>

QSettings AppConfig::settings = QSettings("config.ini", QSettings::IniFormat);

QString AppConfig::getLastSourceDir() {
    return settings.value("lastSourceDir", "").toString();
}

void AppConfig::setLastSourceDir(const QString &dir) {
    settings.setValue("lastSourceDir", dir);
}

QString AppConfig::getLastSaveDir() {
    return settings.value("lastSaveDir", "").toString();
}

void AppConfig::setLastSaveDir(const QString &dir) {
    settings.setValue("lastSaveDir", dir);
}
