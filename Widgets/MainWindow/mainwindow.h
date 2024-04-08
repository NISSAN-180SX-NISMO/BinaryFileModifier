    #ifndef BINARYFILEMODIFIER_MAINWINDOW_H
#define BINARYFILEMODIFIER_MAINWINDOW_H

#include <QMainWindow>
#include "../../model/ModificationSettings/ModificationSettings.h"
#include "../../src/SettingsObserver/SettingsObserver.h"
#include "../../src/config/AppConfig/AppConfig.h"
#include "../../src/Logger/LoggerInterface.h"

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
private:
    Ui::MainWindow *ui;
    ModificationSettings settings;
    SettingsObserver *observer;
    LoggerInterface *logger;
};


#endif //BINARYFILEMODIFIER_MAINWINDOW_H
