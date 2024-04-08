//
// Created by User on 08.04.2024.
//

#include <iostream>
#include "Logger.h"

void Logger::onSettingsChanged(const ModificationSettings &settings) {
    m_textBrowser->clear();
    m_textBrowser->append(printSettings(settings));
}
