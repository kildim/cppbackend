// Решение предыдущей задачи
#include "mainwindow.h"
#include "ui_mainwindow.h"

const QString IMAGE_PATH = ":/cats/images/cat1.jpg";


// Функция подгоняет изображение под нужный размер окна.
QPixmap ResizeImgToFit(const QPixmap &src, int window_width, int window_height) {
    int img_w = src.width();
    int img_h = src.height();

    double w_ratio = double(img_w) / window_width;
    double h_ratio = double(img_h) / window_height;



     if ( w_ratio < h_ratio ) {
        return src.scaledToWidth(window_width);
    } else {
        return src.scaledToHeight(window_height);
    }

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SetPixmap(IMAGE_PATH /* подставьте сюда путь до ресурса */);
    FitImage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::FitImage()
{
    QLabel*
        label = ui->lbl_img;
    QPixmap
        label_pixmap;
    int
        window_width = this->width(),
        window_height = this->height();

    Q_ASSERT(!active_pixmap.isNull());


    label_pixmap = ResizeImgToFit(active_pixmap, window_width, window_height);

    label->setPixmap(label_pixmap);
    //label->setPixmap(active_pixmap);
    label->resize(label_pixmap.width(), label_pixmap.height());
    // win_w, win_h — размеры окна.
    // img_w, img_h — размеры изображения.
    int lbl_x = (window_width - label->width()) / 2; // Координата x.
    int lbl_y = (window_height - label->height()) / 2; // Координата y.
    label->move(lbl_x, lbl_y);

    // Напишите этот метод.
    // 1. Вызовите ResizeImgToFit.
    // 2. Поместите изображение в lbl_img.
    // 3. Измените размер lbl_img.
    // 4. Переместите lbl_img, пользуясь формулами из условия.

}

void MainWindow::resizeEvent(QResizeEvent*)
{
    FitImage();
}
