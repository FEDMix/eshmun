#ifndef ANNOTATIONPREVIEW_H
#define ANNOTATIONPREVIEW_H

#include <QWidget>
#include <QDir>
#include <QString>
#include <QDebug>
#include <QPixmap>
#include <QListView>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include "../../components/dataloader/imageloader.h"
#include "../../components/VTKWidget/scenewidget.h"
namespace Ui {
class AnnotationPreview;
}

class AnnotationPreview : public QWidget
{
    Q_OBJECT

public:
    explicit AnnotationPreview(QWidget *parent = nullptr);
    ~AnnotationPreview();
     void loadPreview(QString);

private slots:
    void on_prevScan_clicked();
    void update(const QModelIndex &current, const QModelIndex &previous);
    void on_nextScan_clicked();

private:
    Ui::AnnotationPreview *ui;
    QStandardItemModel *model;
    QSortFilterProxyModel *proxyModel;
    QItemSelectionModel    *selectionModel;
    QStringList thumbnails;
    SceneWidget *scene;
};

#endif // ANNOTATIONPREVIEW_H
