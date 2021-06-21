#ifndef PREVIEWANNOTATION_H
#define PREVIEWANNOTATION_H

#include <QWidget>
#include <QListWidget>
#include <QDir>
#include <QString>
#include <QDebug>
#include <QItemSelectionModel>

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

private slots:
    void on_nextButton_clicked();
    void on_prevButton_clicked();
    void update(const QModelIndex &current, const QModelIndex &previous);
    void on_previewWidget_itemClicked(QListWidgetItem *item);

signals:
    void sync_path_signal(QString);

private:
    Ui::PreviewAnnotation *ui;
    QStringList thumbnails;
    QItemSelectionModel *selectionModel;
};

#endif // PREVIEWANNOTATION_H
