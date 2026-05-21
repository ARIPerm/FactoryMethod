#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
#include <QPushButton>
#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    QRadioButton* _sqlButton;
    QRadioButton* _fileButton;
    QRadioButton* _networkButton;
    QPushButton* _loadButton;
    QPlainTextEdit* _textEdit;

    void createUi();
    void setupConnection();

private slots:
    void onLoadData();
    void displayData(QList<QString> data);
};
#endif // MAINWINDOW_H
