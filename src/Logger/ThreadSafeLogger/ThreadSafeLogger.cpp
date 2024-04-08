//
// Created by User on 09.04.2024.
//

#include "ThreadSafeLogger.h"

void ThreadSafeLogger::log(const QString &message) {
    QMutexLocker locker(&mutex);
    QString threadId = QString::number(reinterpret_cast<quintptr>(QThread::currentThreadId()));
    emit messageLogged(QString("[Thread %1]\t%2").arg(threadId, message));
}
