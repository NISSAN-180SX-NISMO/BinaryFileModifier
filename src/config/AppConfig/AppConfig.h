//
// Created by User on 08.04.2024.
//

#ifndef BINARYFILEMODIFIER_APPCONFIG_H
#define BINARYFILEMODIFIER_APPCONFIG_H

#include <QString>
#include <QSettings>

class AppConfig {
private:
    static QSettings settings;
public:
    static QString getLastSourceDir() ;
    static void setLastSourceDir(const QString &dir);

    static QString getLastSaveDir() ;
    static void setLastSaveDir(const QString &dir);
};

#endif //BINARYFILEMODIFIER_APPCONFIG_H
