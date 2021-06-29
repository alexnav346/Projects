#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtWidgets>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void getButtonInput();


    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QTimer *timer;

    QString name[8] = {"Alex", "Brendan", "Dad", "Doctor", "Grandma", "Mom", "Sister", "Zaid"};
    QString phoneNumber[8] = {"2482006905", "313555555", "2484567890", "2481234567", "3133133131",
                              "248906758", "2486678756", "3134511044"};

private slots:
    void numPressed();

    void on_pushButton_14_released();

    void timerFunction();

    void contactCall();
    void on_pushButton_13_released();

    void toMedia();
    void toMedia2();
    void toSettings();
};
#endif // MAINWINDOW_H
