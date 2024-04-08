//
// Created by User on 05.04.2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include <iostream>
#include <QFileDialog>
#include "mainwindow.h"
#include "ui_MainWindow.h"
#include "../../src/Logger/TextBrowserLogger/TextBrowserLogger.h"
#include "../../src/Logger/ThreadSafeLogger/ThreadSafeLogger.h"


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->logger = new TextBrowserLogger(ui->logTextBrowser);
    this->observer = new SettingsObserver(settings);
    fileModifier = new FileModifier;

    connect(fileModifier, &FileModifier::processingStarted, [this](){
        ui->startPushButton->setEnabled(false);
    });
    connect(fileModifier, &FileModifier::processingFinished, [this](){
        ui->startPushButton->setEnabled(true);
    });

    // валидация ввода
    // имя файла
    QRegularExpression fileNameMaskRegExp("[a-zA-Z0-9_\\-\\.\\*\\?\\[\\]\\{\\}\\^\\$\\(\\)\\|\\+\\\\]*");
    QValidator *fileNameMaskValidator = new QRegularExpressionValidator(fileNameMaskRegExp, this);
    ui->fileNameMaskLineEdit->setValidator(fileNameMaskValidator);

    // расширение файла
    QRegularExpression fileExtensionMaskRegExp("\\.[a-zA-Z0-9_\\-\\.\\*\\?\\[\\]\\{\\}\\^\\$\\(\\)\\|\\+\\\\]*");
    QValidator *fileExtensionMaskValidator = new QRegularExpressionValidator(fileExtensionMaskRegExp, this);
    ui->fileExtensionMaskLineEdit->setValidator(fileExtensionMaskValidator);

    // 16-ричное число размером 16 символов
    QRegularExpression binaryOperandRegExp("[0-9A-Fa-f]{16}");
    QValidator *binaryOperandValidator = new QRegularExpressionValidator(binaryOperandRegExp, this);
    ui->binaryOperandLineEdit->setValidator(binaryOperandValidator);

    // подписываемся на сигналы об изменении настроек
    connect(observer, &SettingsObserver::settingsChanged, logger, &Logger::onSettingsChanged);

    // сигналы для обновления настроек
    connect(ui->sourceDirLineEdit, &QLineEdit::textChanged, observer, &SettingsObserver::onSourceDirPathChanged);
    connect(ui->saveDirLineEdit, &QLineEdit::textChanged, observer, &SettingsObserver::onSaveDirPathChanged);
    connect(ui->fileNameMaskLineEdit, &QLineEdit::textChanged, observer, &SettingsObserver::onFileNameMaskChanged);
    connect(ui->fileExtensionMaskLineEdit, &QLineEdit::textChanged, observer,&SettingsObserver::onFileExtensionMaskChanged);
    connect(ui->executionPeriodTimeEdit, &QTimeEdit::timeChanged, observer, &SettingsObserver::onExecutionPeriodChanged);
    connect(ui->needRemoveSourceFilesCheckBox, &QCheckBox::stateChanged, observer, &SettingsObserver::onNeedRemoveSourceFilesChanged);
    connect(ui->overwriteRadioButton, &QRadioButton::clicked, observer, &SettingsObserver::onOverwriteRadioButtonClicked);
    connect(ui->modifyRadioButton, &QRadioButton::clicked, observer, &SettingsObserver::onModifyRadioButtonClicked);
    connect(ui->binaryOperandLineEdit, &QLineEdit::textChanged, observer, &SettingsObserver::onBinaryOperandChanged);

    // сигналы для выбора директорий
    connect(ui->selectSourceDirPushButton, &QPushButton::clicked, this, &MainWindow::onSelectSourceDirPushButtonClicked);
    connect(ui->selectSaveDirPushButton, &QPushButton::clicked, this, &MainWindow::onSelectSaveDirPushButtonClicked);

    // сигналы для запуска обработки файлов
    connect(ui->startPushButton, &QPushButton::clicked, this, &MainWindow::onStartPushButtonClicked);
    connect(this->observer, &SettingsObserver::settingsChanged, [this](){
        ui->startPushButton->setEnabled(isSettingsValid(this->settings));
    });



    // Устанавливаем значения по умолчанию для полей формы
    ui->sourceDirLineEdit->setText(settings.sourceDirPath);
    ui->saveDirLineEdit->setText(settings.saveDirPath);
    ui->fileNameMaskLineEdit->setText(settings.fileNameMask);
    ui->fileExtensionMaskLineEdit->setText(settings.fileExtensionMask);
    ui->executionPeriodTimeEdit->setTime(settings.ExecutionPeriod);
    ui->needRemoveSourceFilesCheckBox->setChecked(this->settings.needRemoveSourceFiles);
    this->settings.collisionResolutionType == COLLISION_RESOLUTION_TYPE::OVERWRITE ?
    ui->overwriteRadioButton->setChecked(true) : ui->modifyRadioButton->setChecked(true);
    ui->binaryOperandLineEdit->setText(QString::number(settings.binaryOperand));

}

void MainWindow::onSelectSourceDirPushButtonClicked() {
    QString dir = QFileDialog::getExistingDirectory(this, tr("Выберите каталог для загрузки файлов"),
                                                    AppConfig::getLastSourceDir(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    ui->sourceDirLineEdit->setText(dir);
    AppConfig::setLastSourceDir(dir);
}

void MainWindow::onSelectSaveDirPushButtonClicked() {
    QString dir = QFileDialog::getExistingDirectory(this, tr("Выберите каталог для сохранения файлов"),
                                                    AppConfig::getLastSaveDir(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    ui->saveDirLineEdit->setText(dir);
    AppConfig::setLastSaveDir(dir);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onStartPushButtonClicked() {
    auto threadSafeLogger = new ThreadSafeLogger;
    connect(threadSafeLogger, &ThreadSafeLogger::messageLogged, logger, &Logger::log);
    fileModifier->setupFileModifier(settings, threadSafeLogger);
    fileModifier->startProcessing();
}
