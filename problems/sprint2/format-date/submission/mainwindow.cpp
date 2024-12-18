#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIntValidator>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

int DaysPerMonth(int month, int year)
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
}


int CalculateDaysFromStartYear(int day, int month, int year)
{
    if(month == 0) {
        return 0;
    }
    int num_days = 0;
    for(size_t num_month = 1; num_month < static_cast<size_t>(month); ++num_month) {
        num_days += DaysPerMonth(num_month, year);
    }
    num_days += day;
    return num_days;
}


QString MainWindow::GetFormatType1(int day, int month, int year)
{
    // Реализуйте метод форматирования даты.
    QString result, formatted;

    result = "%1.%2.%3";
    formatted = result.arg(day, 2, 10, QChar('0')).arg(month, 2, 10, QChar('0')).arg(year);
    return formatted;
}

QString MainWindow::GetFormatType2(int day, int month, int year)
{
    // Реализуйте метод форматирования даты.
    QString result, formatted;

    result = "%1/%2/%3";
    formatted = result.arg(month, 2, 10, QChar('0')).arg(day, 2, 10, QChar('0')).arg(year);
    return formatted;
}

QString MainWindow::GetFormatType3(int day, int month, int year)
{
    // Реализуйте метод форматирования даты.
    QString result, formatted;

    result = "%1 %2 %3 года";
    formatted = result.arg(day, 2, 10, QChar('0')).arg(months[month - 1]).arg(year);
    return formatted;
}

QString MainWindow::GetStrNumDays(int num_days, int year) {
    // Метод должен возвращать текст о номере дня в году.
    QString result, formatted;

    result = "Это %1 день в %2 году";
    formatted = result.arg(num_days).arg(year);
    return formatted;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Установите валидаторы.
    ui->le_day->setValidator(new QIntValidator(1, 31, this));
    ui->le_month->setValidator(new QIntValidator(1, 12, this));
    ui->le_year->setValidator(new QIntValidator(1, 9999, this));


    SetError("Некорректная дата");
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::SetError(const QString& err_text)
{
    ui->lbl_format_type1->clear();
    ui->lbl_format_type2->clear();
    ui->lbl_format_type3->clear();
    ui->lbl_message->setText(err_text);
}

void MainWindow::UpdateDateLineEditText()
{
    int day = ui->le_day->text().toInt();
    int month = ui->le_month->text().toInt();
    int year = ui->le_year->text().toInt();

    ui->le_date->setText(GetFormatType1(day, month, year));
}

void MainWindow::on_le_date_textChanged(const QString&)
{
    // Пользователь изменил дату. Реализуйте слот.
    if (editing_now_) {
        return;
    };

    auto arr = ui->le_date->text().split(".");
    if(arr.size() == 3) {
        editing_now_ = true;
        ui->le_day->setText(arr[0]);
        ui->le_month->setText(arr[1]);
        ui->le_year->setText(arr[2]);
        editing_now_ = false;

    };

    ShowFormattedDate();

}

void MainWindow::on_le_day_textChanged(const QString&)
{
    // Пользователь изменил день. Реализуйте слот.
    if (editing_now_) {
        return;
    };

    UpdateDateLineEditText();
}

void MainWindow::on_le_month_textChanged(const QString&)
{
    // Пользователь изменил месяц. Реализуйте слот.
    if (editing_now_) {
        return;
    };

    UpdateDateLineEditText();
}

void MainWindow::on_le_year_textChanged(const QString&)
{
    // Пользователь изменил год. Реализуйте слот.
    if (editing_now_) {
        return;
    };

    UpdateDateLineEditText();
}
