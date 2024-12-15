#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    UpdateSizeLabel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UpdateSizeLabel() {
    // Доработайте этот метод.
    QLabel* label = ui->lbl_size;
    int
        width  = this->width(),
        height = this->height();

    auto new_text = std::to_string(width) + "x" + std::to_string(height);
    label->setText(QString::fromStdString(new_text));

    label->resize(width, height);
    label->move(0, 0);

}
