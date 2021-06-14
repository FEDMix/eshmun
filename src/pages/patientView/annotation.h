#ifndef ANNOTATION_H
#define ANNOTATION_H


#include <QDebug>
#include <QDialog>
#include <QLabel>
#include <QDir>
#include <QString>
#include <QPushButton>
#include <QDebug>
#include "../../components/dataloader/imageloader.h"
#include "../../components/AnnotationPreview/annotationpreview.h"

namespace Ui
{
    class Annotation;
}

class Annotation : public QDialog
{
    Q_OBJECT

public:
    explicit Annotation(QWidget *parent = nullptr);
    ~Annotation();
    void LoadData(QString);

private slots:
    void pushButton_initVTK();

private:
    Ui::Annotation *ui;
    ImageLoader *imageloader;
    AnnotationPreview *preview = new AnnotationPreview();
};

#endif // ANNOTATION_H
