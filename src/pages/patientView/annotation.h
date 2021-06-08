#ifndef ANNOTATION_H
#define ANNOTATION_H

#include <QDialog>
#include <QLabel>
#include <QDir>
#include <QString>
#include <QPixmap>
#include <QPushButton>
#include <QDebug>

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
    void LoadData(std::string);

private slots:
    void pushButton_initVTK();

private:
    Ui::Annotation *ui;
};

#endif // ANNOTATION_H
