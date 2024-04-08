//
// Created by User on 08.04.2024.
//

#include "TextBrowserLogger.h"

void TextBrowserLogger::log(const QString &message) {
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    m_textBrowser->append("[" + timestamp + "]\t" +message);
}

void TextBrowserLogger::onSettingsChanged(const ModificationSettings &settings) {
    m_textBrowser->clear();
    m_textBrowser->append(printSettings(settings));
}