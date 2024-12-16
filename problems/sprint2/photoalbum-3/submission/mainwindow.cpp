// Возьмите решение предыдущей задачи
// о фотоальбоме в качестве заготовки.

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
    SetFolder(":/cats/images/");
    //SetPixmap(IMAGE_PATH /* подставьте сюда путь до ресурса */);
    FitImage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::FitImage()
{
    QPixmap
        label_pixmap;
    int
        window_width = this->width(),
        window_height = this->height();

    Q_ASSERT(!active_pixmap.isNull());


    label_pixmap = ResizeImgToFit(active_pixmap, window_width, window_height);

    lbl_new_.setPixmap(label_pixmap);
    lbl_new_.resize(label_pixmap.width(), label_pixmap.height());

    int lbl_x = (window_width - lbl_new_.width()) / 2; // Координата x.
    int lbl_y = (window_height - lbl_new_.height()) / 2; // Координата y.
    lbl_new_.move(lbl_x, lbl_y);


}

void MainWindow::SetFolder(const QString &d)
{
    current_folder_ = d;
    cur_file_index_ = 0;
    SetPixmap(GetCurrentFile());
}

QString MainWindow::GetCurrentFile()
{
    QDir dir(current_folder_);
    QStringList list = dir.entryList();


    // Сохраним количество файлов.
    int total = int(list.size());

    int file_index = std::min(cur_file_index_, total - 1);
    file_index = std::max(0, file_index);

    // Используем file_index, а не cur_file_index_.
    return dir.filePath(list[file_index]);
}

void MainWindow::resizeEvent(QResizeEvent*)
{
    FitImage();
}


