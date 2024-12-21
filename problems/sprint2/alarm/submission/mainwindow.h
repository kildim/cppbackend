#pragma once

#include <QMainWindow>
#include <prac/QTimer>
#include <prac/QMediaPlayer>
#include <prac/QTime>
#include <prac/QDateTime>
#include <QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    prac::QTimer timer_one_sec_{this};
    prac::QMediaPlayer player_{this};
    bool is_alarm_on = false;

    void update_time_indicator();
    void update_timeout_indicator();
private slots:
    void on_timer_timeout ();
    void on_pb_start_stop_clicked();
};
