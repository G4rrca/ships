#include "images.h"

Images::Images() :
    isLoaded_(false)
{
}

void Images::load()
{
    if (isLoaded_)
        return;

    images.insert("background", QImage(":/img/background1.png"));
    images.insert("field", QImage(":/img/field.png"));
    // Додайте інші зображення, які вам потрібні

    isLoaded_ = true;
}

QImage& Images::get(const QString& imgName)
{
    QMap<QString, QImage>::iterator i = images.find(imgName);

    if (i == images.end())
        throw 1;  // Або додайте обробку помилки, якщо зображення не знайдено

    return i.value();
}

bool Images::isLoaded()
{
    return isLoaded_;
}
