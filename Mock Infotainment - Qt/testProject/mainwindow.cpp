#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <string>
#include <QDateTime>
#include <QPixmap>
#include <QIcon>
#include <QMovie>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(QSize(840, 479));

    qApp->setWindowIcon(QIcon("///home/alex/testProject/index.png"));

    ui->tabWidget->setCurrentIndex(0);

    //Initializing Phone Tab Buttons

    QPushButton *numButtons[10];
    for (int i = 0; i < 10; i++)
    {
        QString buttonName = "button" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(buttonName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(numPressed()));
    }

    QPushButton *callButtons[8];
    for (int i = 0; i < 8; i++)
    {
        int j = i + 1;
        QString buttonName = "pn" + QString::number(j);
        ui->contacts->setItemText(i, name[i]);
        callButtons[i] = MainWindow::findChild<QPushButton *>(buttonName);
        callButtons[i]->setText(phoneNumber[i]);
        connect(callButtons[i], SIGNAL(released()), this, SLOT(contactCall()));
    }

    //Initializing Home Clock

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerFunction()));
    timer->start(1000);


    //Initializing Home Buttons: Apple Carplay, Andriod Auto, AC Controls + Media Gif

    QPixmap pixmap("///home/alex/testProject/carplay.xpm");
    QIcon ButtonIcon(pixmap);
    ui->carPlay->setIcon(ButtonIcon);
    ui->carPlay->setIconSize(QSize(81, 81));

    QPixmap pixmap2("///home/alex/testProject/Android_robot__2014-2019_.svg.xpm");
    QIcon ButtonIcon2(pixmap2);
    ui->androidAuto->setIcon(ButtonIcon2);
    ui->androidAuto->setIconSize(QSize(81, 81));

    QPixmap pixmap3("///home/alex/testProject/climate.xpm");
    QIcon ButtonIcon3(pixmap3);
    ui->climate->setIcon(ButtonIcon3);
    ui->climate->setIconSize(QSize(81, 81));

    connect(ui->carPlay, SIGNAL(released()), this, SLOT(toMedia()));
    connect(ui->androidAuto, SIGNAL(released()), this, SLOT(toMedia2()));
    connect(ui->climate, SIGNAL(released()), this, SLOT(toSettings()));

    QMovie *qmovie = new QMovie("///home/alex/testProject/200.gif");
    qmovie->setScaledSize(QSize(61, 61));
    qmovie->start();
    ui->media->setMovie(qmovie);
}

void MainWindow::getButtonInput()
{
    cout << "hello world!" << endl;

};

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::numPressed()
{
    QPushButton *button = (QPushButton *)sender();
    QString butValue = button->text();
    QString displayText = ui->display->text() + butValue;
    ui->display->setText(displayText);
}

void MainWindow::contactCall()
{
    QPushButton *button = (QPushButton *)sender();
    QString phoneNumber = button->text();
    ui->display->setText(phoneNumber);
}

void MainWindow::on_pushButton_14_released()
{
    QString temp = ui->display->text();
    if (temp.isEmpty())
    {
        ;
    }
    else
    {
        QString toReturn = "";
        for (int i = 0; i < temp.length() - 1; i++)
        {
            toReturn = toReturn + temp.at(i);
        }
        ui->display->setText(toReturn);
    }
}

void MainWindow::timerFunction()
{
    QTime theTime = QTime::currentTime();
    QString theTimeStr = theTime.toString("hh : mm : ss");
    ui->clockLabel->setText(theTimeStr);
}

void MainWindow::on_pushButton_13_released()
{
    QString temp = ui->display->text();

    if(temp == "")
    {
        ;
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Calling " + temp + " . . .");
        msgBox.exec();
    }

}

void MainWindow::toMedia()  //Apple Carplay
{
    QPixmap pixmap("///home/alex/testProject/carplay-home-screen.xpm");
    ui->media->setPixmap(pixmap.scaled(741, 391));
    ui->tabWidget->setCurrentIndex(2);

}

void MainWindow::toMedia2() //Android Auto
{
    QPixmap pixmap("///home/alex/testProject/aaHome.xpm");
    ui->media->setPixmap(pixmap.scaled(741, 391));
    ui->tabWidget->setCurrentIndex(2);
}

void MainWindow::toSettings()
{
    ui->tabWidget->setCurrentIndex(3);
}
