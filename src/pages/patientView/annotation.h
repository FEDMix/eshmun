#ifndef ANNOTATION_H
#define ANNOTATION_H


#include <QDebug>
#include <QDialog>
#include <QLabel>
#include <QDir>
#include <QString>
#include <QPushButton>
#include <QDebug>
#include <QListWidgetItem>
#include "../../components/dataloader/imageloader.h"
#include "../../components/PreviewAnnotation/previewannotation.h"

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
    void SyncPreview(QString);

private:
    Ui::Annotation *ui;
    ImageLoader *imageloader;
    PreviewAnnotation *preview = new PreviewAnnotation();
};

#endif // ANNOTATION_H
