#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <memory>
#include <QButtonGroup>
#include <QVBoxLayout>
#include "Factory/dataprocessor.h"
#include "Factory/fileprocessor.h"
#include "Factory/networkprocessor.h"
#include "Factory/sqlprocessor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createUi();
    setupConnection();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createUi()
{
    QButtonGroup* group = new QButtonGroup(this);
    QVBoxLayout* layout = new QVBoxLayout(this);
    QHBoxLayout* radioLayout = new QHBoxLayout(this);

    QStringList sources = {"TXT файл", "HTTP запрос", "SQLite база"};

    _sqlButton = new QRadioButton(sources[2], this);
    _fileButton = new QRadioButton(sources[0], this);
    _networkButton = new QRadioButton(sources[1], this);
    _loadButton = new QPushButton("Загрузить",this);
    _textEdit = new QPlainTextEdit(this);

    _textEdit->setReadOnly(true);

    radioLayout->addWidget(_sqlButton);
    radioLayout->addWidget(_fileButton);
    radioLayout->addWidget(_networkButton);

    layout->addLayout(radioLayout);
    layout->addWidget(_loadButton);
    layout->addWidget(_textEdit);

    group->addButton(_sqlButton, 0);
    group->addButton(_fileButton, 1);
    group->addButton(_networkButton, 2);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    resize(400, 400);
}

void MainWindow::setupConnection()
{
    connect(_loadButton, &QPushButton::clicked, this, &MainWindow::onLoadData);
}

void MainWindow::onLoadData()
{
    std::unique_ptr<DataProcessor> processor;
    QString path;

    if(_sqlButton->isChecked())
    {
        processor = std::make_unique<SqlProcessor>(this);
        path = "database.db";
    }
    else if(_networkButton->isChecked())
    {
        processor = std::make_unique<NetworkProcessor>(this);
         path = "http://httpbin.org/get";
    }
    else if(_fileButton->isChecked())
    {
        processor = std::make_unique<FileProcessor>(this);
        path = "../../../out/test.txt";
    }

    if (processor) {
        QList<QString> data = processor->loadData(path);
        displayData(data);
    }
}

void MainWindow::displayData(QList<QString> data)
{
    _textEdit->clear();

    if (data.isEmpty()) {
        _textEdit->appendPlainText("Нет данных для отображения.");
        return;
    }

    for (const QString& line : data) {
        _textEdit->appendPlainText(line);
    }
}
