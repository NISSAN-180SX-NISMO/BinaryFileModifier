//
// Created by User on 08.04.2024.
//

#ifndef BINARYFILEMODIFIER_TEXTSTREAMLOGGER_H
#define BINARYFILEMODIFIER_TEXTSTREAMLOGGER_H


#include <QTextStream>
#include "../LoggerInterface.h"

class TextStreamLogger : public LoggerInterface {
public:
    explicit TextStreamLogger(QTextStream* textStream, QObject *parent = nullptr)
            : LoggerInterface(parent), m_textStream(textStream) {}

    void log(const QString &message) override;

public slots:
    void onSettingsChanged(const ModificationSettings &settings) override;

private:
    QTextStream* m_textStream;
};


#endif //BINARYFILEMODIFIER_TEXTSTREAMLOGGER_H
