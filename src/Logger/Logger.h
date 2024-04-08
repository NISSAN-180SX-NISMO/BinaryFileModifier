//
// Created by User on 08.04.2024.
//

#ifndef BINARYFILEMODIFIER_LOGGER_H
#define BINARYFILEMODIFIER_LOGGER_H


#include <QObject>
#include <QTextBrowser>
#include <utility>
#include "../../model/ModificationSettings/ModificationSettings.h"

class Logger : public QObject {
Q_OBJECT

public:
    explicit Logger(QTextBrowser* textBrowser, QObject *parent = nullptr)
            : QObject(parent), m_textBrowser(textBrowser) {}

public slots:
    void onSettingsChanged(const ModificationSettings &settings);

private:
    QTextBrowser* m_textBrowser;
};


#endif //BINARYFILEMODIFIER_LOGGER_H
