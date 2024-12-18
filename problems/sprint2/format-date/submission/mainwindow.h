#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

static const std::vector<QString> months = {
    QStringLiteral("января"), QStringLiteral("февраля"),
    QStringLiteral("марта"), QStringLiteral("апреля"),
    QStringLiteral("мая"), QStringLiteral("июня"),
    QStringLiteral("июля"), QStringLiteral("августа"),
    QStringLiteral("сентября"), QStringLiteral("октября"),
    QStringLiteral("ноября"), QStringLiteral("декабря"),
};

int CalculateDaysFromStartYear(int day, int month, int year);
int DaysPerMonth(int month, int year);

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QString GetFormatType1(int day, int month, int year);
    QString GetFormatType2(int day, int month, int year);
    QString GetFormatType3(int day, int month, int year);
    QString GetStrNumDays(int num_days, int year);
    void ShowFormattedDate()
    {
        if(!ui->le_day->hasAcceptableInput() ||
            !ui->le_month->hasAcceptableInput() ||
            !ui->le_year->hasAcceptableInput() ) {
            SetError("Некорректная дата");

            return;
        }

        // Отобразим результаты.
        // Используйте DaysPerMonth для определения количества дней в месяце.
        // Используйте CalculateDaysFromStartYear для определения номера дня в году.

        // Используйте GetFormatType1, GetFormatType2, GetFormatType3 и GetStrNumDays
        // для определения надписей, которые нужно вывести пользователю.
        // Эти методы реализуйте самостоятельно.

        int day = ui->le_day->text().toInt();
        int month = ui->le_month->text().toInt();
        int year = ui->le_year->text().toInt();

        if (month > 12 || day > DaysPerMonth(month, year)) {
            SetError("Такой даты не существует");
            return;
        };

        ui->lbl_format_type1->setText(GetFormatType1(day, month, year));
        ui->lbl_format_type2->setText(GetFormatType2(day, month, year));
        ui->lbl_format_type3->setText(GetFormatType3(day, month, year));
        int days_count =CalculateDaysFromStartYear(day, month, year);
        ui->lbl_message->setText(GetStrNumDays(days_count, year));

    }
    void SetError(const QString& err_text);
    void UpdateDateLineEditText();

private slots:
    void on_le_date_textChanged(const QString&);
    void on_le_day_textChanged(const QString&);
    void on_le_month_textChanged(const QString&);
    void on_le_year_textChanged(const QString&);

private:
    Ui::MainWindow *ui;
    bool editing_now_ = false;
};
#endif // MAINWINDOW_H
