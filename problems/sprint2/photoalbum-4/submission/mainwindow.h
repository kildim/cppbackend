// Возьмите решение предыдущей задачи
// о фотоальбоме в качестве заготовки.

// Решение предыдущей задачи
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QDir>
#include <QPixmap>
#include <prac/QTimer>
#include <prac/QFileDialog>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SetPixmap(const QString path) {
        active_pixmap = QPixmap(path);
    }

    void FitImage();
    void SetFolder(const QString& d);
    QString GetCurrentFile();


    QPixmap GetImageByPath(QString path) const;
    std::pair<QPixmap, int> FindNextImage(int start_index, int direction) const;

private slots:
    void on_btn_right_clicked();
    void on_btn_left_clicked();

    void on_timer_timeout();
    void slotClickTimer0sec();
    void slotClickTimer1sec();
    void slotClickTimer5sec();
    void slotClickTimer10sec();

    void slotCustomMenuRequested(QPoint pos);
    void slotClickUpWindows(bool checked);
private:
    void resizeEvent(QResizeEvent *event) override;
    void UpdateEnabled();
    void updateFlagsInMenuTimer();


private:
    Ui::MainWindow *ui;
    QLabel lbl_new_{this};
    QPixmap active_pixmap;
    QString current_folder_;
    int cur_file_index_ = 0;
    prac::QTimer timer_;
    int period_;
};
#endif // MAINWINDOW_H
