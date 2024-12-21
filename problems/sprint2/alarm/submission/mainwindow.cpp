#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <prac/QFileDialog>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player_.setAudioOutput(&audio_output_);
    audio_output_.setVolume(100);

    timer_one_sec_.setSingleShot(true);
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

void MainWindow::update_timeout_indicator()
{
    prac::QDateTime
        alarm,
        now = prac::QDateTime::currentDateTime();

    int
        hours,
        minutes,
        seconds,
        seconds_attaining;

    if (!is_alarm_on) {
        ui->lbl_timeout->setText("Установите будильник");
        return;
    };

    if (!is_playing_alarm_) {
        alarm = now;
        alarm.setTime(QTime(
            ui->sb_hour->text().toInt(),
            ui->sb_min->text().toInt(),
            ui->sb_sec->text().toInt()
            ));
        if (alarm < now) {
            alarm = alarm.addDays(1);
        };

        seconds_attaining = ((alarm - now).count() + 500) / 1000;

        if (seconds_attaining == 86400) seconds_attaining = 0;


        hours = seconds_attaining/3600;
        minutes = seconds_attaining%3600/60;
        seconds = seconds_attaining%3600%60;

        ui->lbl_timeout->setText(
            QString("%1:%2:%3")
                .arg(hours, 2, 10, QChar ('0'))
                .arg(minutes, 2, 10, QChar ('0'))
                .arg(seconds, 2, 10, QChar ('0'))
        );

        if (seconds_attaining == 0) {
            is_playing_alarm_ = true;
            ui->lbl_timeout->setText("Пора вставать");
            if (!file_name_.isEmpty()) {
                player_.setSource(QUrl::fromLocalFile(file_name_));
                player_.play();
            }
        }
    }
}

void MainWindow::on_timer_timeout()
{
    int
        estimated_timeout;

    QTime
        now = prac::QTime::currentTime();

    update_time_indicator();
    update_timeout_indicator();

    estimated_timeout = 1000 - now.msec();
    //timer_one_sec_.stop();
    timer_one_sec_.start(estimated_timeout);
}

void MainWindow::on_pb_start_stop_clicked()
{
    QString
        button_text;

    button_text = is_alarm_on ? QString("Старт") : QString("Стоп");
    ui->pb_start_stop->setText(button_text);
    is_alarm_on = !is_alarm_on;

    if (is_playing_alarm_) {
        player_.stop();
        is_playing_alarm_ = false;
    };

    update_timeout_indicator();
}



void MainWindow::on_action_load_file_triggered()
{
    file_name_ = prac::QFileDialog::getOpenFileName(this,
                                                           QString::fromUtf8("Открыть файл"),
                                                           QDir::currentPath(),
                                                           "*.wav;*.mp3");
    if (!file_name_.isEmpty()) {
        ui->lbl_melody->setText(file_name_);
    }
}

