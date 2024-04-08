#ifndef BINARYFILEMODIFIER_FILEMODIFIER_H
#define BINARYFILEMODIFIER_FILEMODIFIER_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QByteArray>
#include <QTextStream>
#include <QTimer>
#include <QThreadPool>
#include "../../model/ModificationSettings/ModificationSettings.h"
#include "../Logger/LoggerInterface.h"
#include "../Logger/TextStreamLogger/TextStreamLogger.h"
#include "../Logger/ThreadSafeLogger/ThreadSafeLogger.h"

class FileModifier : public QObject {
Q_OBJECT
public:
    explicit FileModifier(QObject *parent = nullptr) : QObject(parent) {}
    void setupFileModifier(ModificationSettings settings, ThreadSafeLogger* logger);
public slots:
    void startProcessing();

signals:
    void processingStarted();
    void processingFinished();

private:
    void processFile(const QString& filePath);
    void processDirectory();

    ModificationSettings settings;
    ThreadSafeLogger* logger;
    QTimer* timer;
};

#endif //BINARYFILEMODIFIER_FILEMODIFIER_H