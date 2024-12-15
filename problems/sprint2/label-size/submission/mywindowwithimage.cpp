#include "mywindowwithimage.h"
#include "ui_mywindowwithimage.h"

#include <QFileInfo>
#include <QDir>

#include <QtGlobal>

// Специальная магия для получения пути изображения.
#define MACRO_TO_STR_INNER(x) #x
#define MACRO_TO_STR(x) MACRO_TO_STR_INNER(x)

MyWindowWithImage::MyWindowWithImage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyWindowWithImage)
{
    ui->setupUi(this);

    // Получим изображение из переменной, которую задали в .pro-файле.
    // Не делайте так в реальных программах.
    QString image_path = MACRO_TO_STR(ILOVEQT_IMAGE_FULL_PATH);
    SetPixmap(ui->lbl_pixmap, image_path);
}

MyWindowWithImage::~MyWindowWithImage()
{
    delete ui;
}

void MyWindowWithImage::SetPixmap(QLabel *label_pix, const QString path)
{
    // Тут нужно вызвать FitToImage.
    // Подумайте, в каком месте метода это лучше сделать.
    QPixmap pix(path);
    Q_ASSERT(!pix.isNull());

    label_pix->setPixmap( pix );
    FitToImage(label_pix);
    label_pix->show();
}

void MyWindowWithImage::FitToImage(QLabel *label)
{
    int
        picture_width,
        picture_height;

    QPixmap
        picture;

    picture
        = label->pixmap();

    picture_width
        = picture.width();
    picture_height
        = picture.height();


    setFixedSize(picture_width, picture_height);

    label->move(0, 0);
    label->setFixedSize(picture_width, picture_height);

}

// Запишите здесь реализацию нового метода.
