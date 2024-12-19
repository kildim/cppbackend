#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIntValidator>
#include "magic_horoscope.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_year->setValidator(new QIntValidator(0, 9999, this));
    ui->cb_month->addItems(MONTHS);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_le_year_textChanged(const QString &arg1)
{
    MakeMagic();
}

void MainWindow::MakeMagic()
{
    QString
        calendar_message    = "Введите год",
        horoscope_message   = "Ввод даты отключён";

    bool
        isYearInputValid    = ui->le_year->hasAcceptableInput(),
        isDateInputChecked  = ui->cb_is_date->isChecked();


    if (isYearInputValid) {
        calendar_message
            = compose_calendar_message();

        if (isDateInputChecked)
            horoscope_message
                = compose_horoscope_message();
    }

    ui->lbl_calendar->setText(calendar_message);
    ui->lbl_horoscope->setText(horoscope_message);
}

QString MainWindow::compose_calendar_message()
{
    QString
        year_text_value = ui->le_year->text(),
        year_animal,
        year_element,
        result;

    switch (calendar_) {
    case Calendar::kEastern:
        year_animal = GetAnimalForEasternCalendar(year_text_value.toInt());
        year_element = GetElementForEasternCalendar(year_text_value.toInt());
        result = QString("%1 — это год %2. Стихия/цвет — %3")
                     .arg(year_text_value)
                     .arg(year_animal)
                     .arg(year_element);
        break;
    case Calendar::kTibetan:
        year_animal = GetAnimalForTibetanCalendar(year_text_value.toInt());
        result = QString("%1 — это год %2").arg(year_text_value).arg(year_animal);
        break;
    case Calendar::kZoroastrian:
        year_animal = GetAnimalForZoroastrianCalendar(year_text_value.toInt());
        result = QString("%1 — это год %2").arg(year_text_value).arg(year_animal);
        break;
    }

    return result;
}

QString MainWindow::compose_horoscope_message()
{
    QString
        year_text_value     = ui->le_year->text(),
        month_text_value    = ui->cb_month->currentText(),
        day_text_value      = ui->sb_day->text(),

        year_sign,
        result;
    int
        day = day_text_value.toInt(),
        month = ui->cb_month->currentIndex(),
        year    = ui->le_year->text().toInt();

    if (!isMonthDayCorrect(day, month + 1, year)) return QString("Такой даты не существует");

    switch (horoscope_) {
    case Horoscope::kDruid:
        year_sign = GetTree(day, month, year);
        result = getFormatedDate(day, month) + " - ваше тотемное дерево " + year_sign + " по гороскопу дридов";
        break;
    case Horoscope::kZodiac:
        year_sign = GetZodiac(day, month, year);
        result = QString("%1.%2 — ваш знак зодиака %3 по зодиакальному гороскопу")
            .arg(day, 2, 10, QChar('0')).arg(month + 1, 2, 10, QChar('0')).arg(year_sign);
        break;
    }

    return result;
}

bool MainWindow::isMonthDayCorrect(int day, int month, int year)
{
    return (day > 0) && (day <= DaysPerMonth(month, year));
}


void MainWindow::on_rb_eastern_clicked()
{
    calendar_ = Calendar::kEastern;
    MakeMagic();
}


void MainWindow::on_rb_tibetan_clicked()
{
    calendar_ = Calendar::kTibetan;
    MakeMagic();
}


void MainWindow::on_rb_zoroastrian_clicked()
{
    calendar_ = Calendar::kZoroastrian;
    MakeMagic();
}


void MainWindow::on_cb_is_date_clicked(bool checked)
{
    ui->gb_horoscope ->setEnabled(checked);
    ui->lb_day->setEnabled(checked);
    ui->lb_month->setEnabled(checked);
    ui->sb_day->setEnabled(checked);
    ui->cb_month->setEnabled(checked);
    MakeMagic();
}


void MainWindow::on_cb_month_currentIndexChanged(int index)
{
     MakeMagic();
}


void MainWindow::on_sb_day_textChanged(const QString &arg1)
{
    MakeMagic();
}

