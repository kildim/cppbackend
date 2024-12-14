#include "mainwindow.h"

#include "ui_mainwindow.h"
QString Melborp(const QString& input) {
    QString result = "";
    for (QChar symbol : input) result = symbol + result;
    return result;
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pb_do_clicked()
{
    QString
        revert_string,
        string;

    string
        = this->ui->le_input->text();
    revert_string
        = Melborp(string);

    this->ui->le_input->setText(revert_string);
}

