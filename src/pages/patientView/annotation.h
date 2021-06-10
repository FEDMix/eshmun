#ifndef ANNOTATION_H
#define ANNOTATION_H


#include <QDebug>
#include <QDialog>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QDir>
#include <QListView>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>

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

    void on_nextScan_clicked();

    void on_prevScan_clicked();

private:
    Ui::Annotation *ui;
    QStandardItemModel *model;
    QSortFilterProxyModel *proxyModel;
};

#endif // ANNOTATION_H
