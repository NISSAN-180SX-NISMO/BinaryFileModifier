    #ifndef BINARYFILEMODIFIER_MAINWINDOW_H
#define BINARYFILEMODIFIER_MAINWINDOW_H

#include <QMainWindow>
#include "../../model/ModificationSettings/ModificationSettings.h"
#include "../../src/SettingsObserver/SettingsObserver.h"
#include "../../src/config/AppConfig/AppConfig.h"
#include "../../src/Logger/LoggerInterface.h"
#include "../../src/FileModifier/FileModifier.h"

    QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;
public slots:
    void onSelectSourceDirPushButtonClicked();
    void onSelectSaveDirPushButtonClicked();
    void onStartPushButtonClicked();
private:
    Ui::MainWindow *ui;
    ModificationSettings settings;
    SettingsObserver *observer;
    Logger *logger;
    FileModifier *fileModifier;
};


#endif //BINARYFILEMODIFIER_MAINWINDOW_H
