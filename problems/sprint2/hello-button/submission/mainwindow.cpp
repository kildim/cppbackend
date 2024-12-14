#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_btn_setName_clicked(bool checked)
{
    QString
        name = this->ui->le_name->text();

    std::string
        message_text = "Привет из Qt, " + name.toStdString() + "!";

    QString
        message = QString::fromStdString(message_text);

    this->ui->lbl_result->setText(message);

}

