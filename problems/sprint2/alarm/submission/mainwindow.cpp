#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <prac/QFileDialog>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&timer_one_sec_, &prac::QTimer::timeout, this, &MainWindow::on_timer_timeout);
    timer_one_sec_.start(1000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_time_indicator()
{
    QTime
        now = prac::QTime::currentTime();

    ui->lbl_now->setText(QString("%1:%2:%3")
                             .arg(now.hour(), 2, 10, QChar ('0'))
                            .arg(now.minute(), 2, 10, QChar ('0'))
                            .arg(now.second(), 2, 10, QChar ('0'))
                           );

}

void MainWindow::on_timer_timeout()
{
    int
        estimated_timeout;

    QTime
        now = prac::QTime::currentTime();

    update_time_indicator();

    estimated_timeout = 1000 - now.msec();
    timer_one_sec_.stop();
    timer_one_sec_.start(estimated_timeout);
}
