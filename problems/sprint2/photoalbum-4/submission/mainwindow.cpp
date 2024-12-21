#include "mainwindow.h"
#include "ui_mainwindow.h"


const QString IMAGE_DIRECTORY_PATH = ":/cats/images/";


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

    // Подключаем сигнал таймера к слоту on_timer_timeout.
    connect(&timer_, &prac::QTimer::timeout, this, &MainWindow::on_timer_timeout);

    ui->menuBar->hide();
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QMainWindow::customContextMenuRequested,
            this, &MainWindow::slotCustomMenuRequested);
    connect(ui->action_up_windows, &QAction::triggered, this, &MainWindow::slotClickUpWindows);
    connect(ui->action_0sec, &QAction::triggered, this, &MainWindow::slotClickTimer0sec);
    connect(ui->action_1sec, &QAction::triggered, this, &MainWindow::slotClickTimer1sec);
    connect(ui->action_5sec, &QAction::triggered, this, &MainWindow::slotClickTimer5sec);
    connect(ui->action_10sec, &QAction::triggered, this, &MainWindow::slotClickTimer10sec);
    connect(ui->action_close_mainwindow, &QAction::triggered, this, &MainWindow::slotClickCloseMainWindow);
    connect(ui->action_choose_dir, &QAction::triggered, this, &MainWindow::slotClickSelectDirectory);
    connect(ui->action_use_resources, &QAction::triggered, this, &MainWindow::slotClickUseResources);


    SetFolder(IMAGE_DIRECTORY_PATH);
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
    std::pair<QPixmap, int> pair;
    current_folder_ = d;
    cur_file_index_ = 0;
    //UpdateEnabled();
    //SetPixmap(GetCurrentFile());
    pair = FindNextImage(cur_file_index_, +1);
    active_pixmap = pair.first;
    cur_file_index_ = pair.second;
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

void MainWindow::slotClickTimer0sec()
{
    timer_.stop();

    period_ = 0;
    updateFlagsInMenuTimer();
    updateFlagsInMenuTimer();
}

void MainWindow::slotClickTimer1sec()
{
    timer_.stop();

    period_ = 1000;
    timer_.start(period_);
    updateFlagsInMenuTimer();
}

/*

void MainWindow::UpdateEnabled()
{
    // Количество изображений в папке.
    int max_images = QDir(current_folder_).entryList().size();

    // Устанавливаем активность кнопки «влево».
    ui->btn_left->setEnabled(cur_file_index_ > 0);

    // Устанавливаем активность кнопки «вправо».
    ui->btn_right->setEnabled(cur_file_index_ < max_images - 1);
}

*/

void MainWindow::on_btn_right_clicked()
{
    std::pair<QPixmap, int> pair;

    timer_.stop();
    period_ = 0;

    ++cur_file_index_;
    //UpdateEnabled();
    //lbl_new_.setPixmap(GetCurrentFile());
    pair = FindNextImage(cur_file_index_, +1);
    active_pixmap = pair.first;
    cur_file_index_ = pair.second;
    FitImage();
}


void MainWindow::on_btn_left_clicked()
{
    std::pair<QPixmap, int> pair;

    timer_.stop();
    period_ = 0;

    --cur_file_index_;
    //UpdateEnabled();
    //lbl_new_.setPixmap(GetCurrentFile());

    pair = FindNextImage(cur_file_index_, -1);
    active_pixmap = pair.first;
    cur_file_index_ = pair.second;
    FitImage();
}

void MainWindow::on_timer_timeout()
{
    std::pair<QPixmap, int> pair;

    ++cur_file_index_;
    pair = FindNextImage(cur_file_index_, +1);
    active_pixmap = pair.first;
    cur_file_index_ = pair.second;
    FitImage();
}

void MainWindow::slotClickTimer5sec()
{
    timer_.stop();

    period_ = 5000;
    timer_.start(period_);
    updateFlagsInMenuTimer();
}

void MainWindow::slotClickTimer10sec()
{
    timer_.stop();

    period_ = 10000;
    timer_.start(period_);
    updateFlagsInMenuTimer();
}

void MainWindow::slotClickUseResources()
{
    SetFolder(IMAGE_DIRECTORY_PATH);
    FitImage();
}

void MainWindow::slotCustomMenuRequested(QPoint pos) {
    // Метод ui->menu->popup открывает меню в заданном месте.
    // Используем метод mapToGlobal, чтобы преобразовать
    // координаты точки на форме в координаты точки экрана.
    ui->menu_mainwindow->popup(this->mapToGlobal(pos));
}

void MainWindow::slotClickUpWindows(bool checked)
{
    bool state = checked;
    setWindowFlags(windowFlags().setFlag(Qt::WindowStaysOnTopHint, state));
}

void MainWindow::slotClickCloseMainWindow()
{
    this->close();
}

void MainWindow::slotClickSelectDirectory()
{
    QString dir = QFileDialog::getExistingDirectory(this,
                                                    QString("Открыть папку"),
                                                    QDir::currentPath(),
                                                    QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
    SetFolder(dir);
    FitImage();
}

QPixmap MainWindow::GetImageByPath(QString path) const {
    QFileInfo file_info(path);
    if (!file_info.isFile()) {
        return {};
    }
    return QPixmap(path);
}

std::pair<QPixmap, int> MainWindow::FindNextImage(int start_index, int direction) const {
    QDir dir(current_folder_);
    auto file_list = dir.entryList();

    int count = file_list.size();
    int cur_image = start_index;

    for(int steps = 0; steps < count; ++steps, cur_image += direction) {
        cur_image = ((cur_image % count) + count) % count;

        auto pixmap = GetImageByPath(dir.filePath(file_list[cur_image]));
        if (!pixmap.isNull()) {
            return {pixmap, cur_image};
        }
    }
    return {{}, -1};
}

void MainWindow::updateFlagsInMenuTimer() {
    ui->action_0sec->setChecked(period_ == 0);
    ui->action_1sec->setChecked(period_ == 1000);
    ui->action_5sec->setChecked(period_ == 5000);
    ui->action_10sec->setChecked(period_ == 10000);
};
