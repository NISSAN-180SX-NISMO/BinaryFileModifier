#include <QApplication>
#include "Widgets/MainWindow/mainwindow.h"


#include <QFile>
#include <QByteArray>
#include <QDebug>

#include <QFileDialog>
#include <QDir>

int main(int argc, char *argv[]) {

//    QApplication a(argc, argv);
//
//    QString directory = QFileDialog::getExistingDirectory(nullptr, "Select Directory",
//                                                          "/",
//                                                          QFileDialog::ShowDirsOnly
//                                                          | QFileDialog::DontResolveSymlinks);
//
//    qDebug() << "Selected directory: " << directory;
//
//
//    QString fileMask = "test.*";
//    QDir dir(directory);
//    QStringList files = dir.entryList(QStringList() << fileMask, QDir::Files);
//
//    for (auto &f: files) {
//        QFile file(directory + "/" + f);
//        if (!file.open(QIODevice::ReadOnly)) {
//            qDebug() << "Cannot open file for reading: " << qPrintable(file.errorString());
//        }
//
//        QByteArray byteArray = file.readAll();
//        for (int i = 0; i < byteArray.size(); ++i) {
//            qDebug() << "Byte " << i << ": " << static_cast<char>(byteArray.at(i));
//        }
//    }
//
//    qDebug() << "Files: " << files;
//
//    return QApplication::exec();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
}
