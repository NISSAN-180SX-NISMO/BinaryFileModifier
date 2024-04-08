//
// Created by User on 08.04.2024.
//

#include "TextStreamLogger.h"

void TextStreamLogger::onSettingsChanged(const ModificationSettings &settings) {
    (*m_textStream) << printSettings(settings) << "\n";
}

void TextStreamLogger::log(const QString &message) {
    (*m_textStream) << message << "\n";
}
