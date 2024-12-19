#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum class Calendar {
    kEastern,
    kTibetan,
    kZoroastrian
};

enum class Horoscope {
    kZodiac,
    kDruid
};

const QStringList MONTHS = {
    "январь",
    "февраль",
    "март",
    "апрель",
    "май",
    "июнь",
    "июль",
    "август",
    "сентябрь",
    "октябрь",
    "ноябрь",
    "декабрь"
};

inline int DaysPerMonth(int month, int year)
{
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            return 29; // February in a leap year.
        } else {
            return 28; // February in a non-leap year.
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30; // April, June, September, November have 30 days.
    } else {
        return 31; // All other months have 31 days.
    }
};

inline QString getFormatedDate(int day, int month){
    return QString("%1.%2").arg(day, 2, 10, QChar('0')).arg(month, 2, 10, QChar('0'));
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_le_year_textChanged(const QString &arg1);

    void on_rb_eastern_clicked();

    void on_rb_tibetan_clicked();

    void on_rb_zoroastrian_clicked();

    void on_cb_is_date_clicked(bool checked);

    void on_cb_month_currentIndexChanged(int index);

    void on_sb_day_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Calendar calendar_ = Calendar::kEastern;
    Horoscope horoscope_ = Horoscope::kZodiac;

    void MakeMagic();
    inline QString compose_calendar_message();
    inline QString compose_horoscope_message();
    inline bool isMonthDayCorrect(int day, int month, int year);
};
#endif // MAINWINDOW_H
