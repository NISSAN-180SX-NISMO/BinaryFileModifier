// FileModifier.cpp
#include "FileModifier.h"

QMutex mutex;

inline bool openFileForReading(QFile &file) {
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    return true;
}

inline QByteArray readAndModifyFileContent(QFile &file, uint64_t binaryOperand) {
    QByteArray byteArray = file.readAll();
    for (int i = 0; i < byteArray.size(); i += 8) {
        uint64_t *block = reinterpret_cast<uint64_t *>(byteArray.data() + i);
        *block ^= binaryOperand;
    }
    return byteArray;
}

inline QString handleFileCollision(QFile &outFile, const ModificationSettings &settings) {
    if (outFile.exists()) {
        switch (settings.collisionResolutionType) {
            case COLLISION_RESOLUTION_TYPE::OVERWRITE:
                mutex.lock();
                outFile.remove();
                mutex.unlock();
                break;
            case COLLISION_RESOLUTION_TYPE::MODIFY:
                int counter = 0;
                QString baseName = QFileInfo(outFile).baseName();
                QString suffix = QFileInfo(outFile).suffix();
                QString newFileName;

                do {
                    newFileName =
                            settings.saveDirPath + "/"
                            + baseName
                            + "(" + QString::number(++counter) + ")."
                            + suffix;
                } while (QFile::exists(newFileName));

                return newFileName;
        }
    }
    return outFile.fileName();
}

inline bool writeToFile(QFile &outFile, const QByteArray &byteArray) {
    mutex.lock();
    if (!outFile.open(QIODevice::WriteOnly)) {
        return false;
    }
    outFile.write(byteArray);
    outFile.close();
    mutex.unlock();
    return true;
}

inline void removeSourceFileIfRequired(QFile &file, bool needRemoveSourceFiles) {
    if (needRemoveSourceFiles) {
        mutex.lock();
        file.remove();
        mutex.unlock();
    }
}

void FileModifier::startProcessing() {
    logger->log("Processing " + QString::number(++this->i) + " started...");
    QThreadPool::globalInstance()->start([this]() { processDirectory(); });
    if (settings.ExecutionPeriod == QTime(0, 0, 0)) {
        timer->stop();
        QThreadPool::globalInstance()->waitForDone();
        emit processingFinished();
    }
}

void FileModifier::processDirectory() {
    emit processingStarted();
    QDir dir(settings.sourceDirPath);
    QStringList files = dir.entryList(QStringList() << (settings.fileNameMask + settings.fileExtensionMask),
                                      QDir::Files);
    for (const auto &file: files) {
        logger->log("Processing file: " + file);
        processFile(dir.absoluteFilePath(file));
    }
}

#include <windows.h>

bool isFileWritable(const std::string& fileName)
{
    std::wstring wFileName = std::wstring(fileName.begin(), fileName.end());
    HANDLE hFile = CreateFile(wFileName.c_str(), GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        return false;
    }
    CloseHandle(hFile);
    return true;
}

void FileModifier::processFile(const QString &filePath) {
    QFile file(filePath);
    if (!isFileWritable(filePath.toStdString())) {
        logger->log("File is open in another program, skipping: " + filePath);
        return;
    }

    if (!openFileForReading(file)) {
        logger->log("Cannot open file for reading: " + file.errorString());
        return;
    }

    QByteArray byteArray = readAndModifyFileContent(file, settings.binaryOperand);

    // Save the modified file
    QFile outFile(settings.saveDirPath + "/" + QFileInfo(file).fileName());
    QString newFileName = handleFileCollision(outFile, settings);
    outFile.setFileName(newFileName);

    if (!writeToFile(outFile, byteArray)) {
        logger->log("Cannot open file for writing: " + outFile.errorString());
        return;
    }

    // Remove the source file if needed
    removeSourceFileIfRequired(file, settings.needRemoveSourceFiles);
}

void FileModifier::setupFileModifier(ModificationSettings settings, ThreadSafeLogger *logger) {
    this->settings = settings;
    this->logger = logger;
    this->i = 0;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &FileModifier::startProcessing);
    if (settings.ExecutionPeriod != QTime(0, 0, 0)) {
        timer->start(settings.ExecutionPeriod.msecsSinceStartOfDay());
    }
}

void FileModifier::stopProcessing() {
    timer->stop();
    QThreadPool::globalInstance()->waitForDone();
    emit processingFinished();
}
