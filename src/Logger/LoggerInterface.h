//
// Created by User on 08.04.2024.
//

#ifndef BINARYFILEMODIFIER_LOGGERINTERFACE_H
#define BINARYFILEMODIFIER_LOGGERINTERFACE_H

#include <QObject>
#include "../../model/ModificationSettings/ModificationSettings.h"

class Logger : public QObject {
Q_OBJECT

public:
    explicit Logger(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~Logger() = default;
    virtual void log(const QString &message) = 0;
public slots:
    virtual void onSettingsChanged(const ModificationSettings &settings) = 0;
    void onOtherThreadMessageLogged(const QString &message) {
        log(message);
    }
};

#endif //BINARYFILEMODIFIER_LOGGERINTERFACE_H
