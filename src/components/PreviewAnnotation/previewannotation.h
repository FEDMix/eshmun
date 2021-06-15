#ifndef PREVIEWANNOTATION_H
#define PREVIEWANNOTATION_H

#include <QWidget>
#include <QDir>
#include <QString>
#include <QDebug>
namespace Ui {
class PreviewAnnotation;
}

class PreviewAnnotation : public QWidget
{
    Q_OBJECT

public:
    explicit PreviewAnnotation(QWidget *parent = nullptr);
    ~PreviewAnnotation();
    void loadPreview(QString);

private:
    Ui::PreviewAnnotation *ui;
    QStringList thumbnails;
};

#endif // PREVIEWANNOTATION_H
