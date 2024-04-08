// TextBrowserLogger.h
#ifndef BINARYFILEMODIFIER_TEXTBROWSERLOGGER_H
#define BINARYFILEMODIFIER_TEXTBROWSERLOGGER_H

#include <QTextBrowser>
#include "../LoggerInterface.h"

class TextBrowserLogger : public LoggerInterface {
public:
    explicit TextBrowserLogger(QTextBrowser* textBrowser, QObject *parent = nullptr)
            : LoggerInterface(parent), m_textBrowser(textBrowser) {}

    void log(const QString &message) override;

public slots:
    void onSettingsChanged(const ModificationSettings &settings) override;

private:
    QTextBrowser* m_textBrowser;
};

#endif //BINARYFILEMODIFIER_TEXTBROWSERLOGGER_H