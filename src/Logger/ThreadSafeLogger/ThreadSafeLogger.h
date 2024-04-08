//
// Created by User on 09.04.2024.
//

#ifndef BINARYFILEMODIFIER_THREADSAFELOGGER_H
#define BINARYFILEMODIFIER_THREADSAFELOGGER_H


#include <QtCore>
#include "../LoggerInterface.h"

class ThreadSafeLogger : public QObject {
Q_OBJECT

public:

    explicit ThreadSafeLogger(QObject *parent = nullptr) : QObject(parent) {}
    void log(const QString &message);

signals:

    void messageLogged(const QString &message);

private:
    QMutex mutex;
};


#endif //BINARYFILEMODIFIER_THREADSAFELOGGER_H
