#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QDir>
#include <QString>
#include <QDebug>

class ImageLoader : public QObject
{
    Q_OBJECT

public:
    QString image_scan(QString);
    QString image_annotation(QString);
};

#endif // IMAGELOADER_H

