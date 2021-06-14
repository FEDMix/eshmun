#ifndef ANNOTATION_H
#define ANNOTATION_H


#include <QDebug>
#include <QDialog>
#include <QLabel>
#include <QDir>
#include <QString>
#include <QPixmap>
#include <QPushButton>
#include <QListView>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QDebug>
#include "../../components/dataloader/imageloader.h"

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

    void on_nextScan_clicked();

    void on_prevScan_clicked();
    void update(const QModelIndex &current, const QModelIndex &previous);

private:
    Ui::Annotation *ui;
    QStandardItemModel *model;
    QSortFilterProxyModel *proxyModel;
    QItemSelectionModel    *selectionModel;
    QStringList thumbnails;
    ImageLoader *imageloader;
};

#endif // ANNOTATION_H
