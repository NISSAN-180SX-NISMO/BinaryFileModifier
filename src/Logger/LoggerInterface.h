//
// Created by User on 08.04.2024.
//

#ifndef BINARYFILEMODIFIER_LOGGERINTERFACE_H
#define BINARYFILEMODIFIER_LOGGERINTERFACE_H

#include <QObject>
#include "../../model/ModificationSettings/ModificationSettings.h"

class LoggerInterface : public QObject {
Q_OBJECT

public:
    explicit LoggerInterface(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~LoggerInterface() = default;
    virtual void log(const QString &message) = 0;
public slots:
    virtual void onSettingsChanged(const ModificationSettings &settings) = 0;
};

#endif //BINARYFILEMODIFIER_LOGGERINTERFACE_H
