#ifndef TABWINDOW_H
#define TABWINDOW_H

#include <QWidget>

namespace Ui {
class TabWindow;
}

class TabWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TabWindow(QWidget *parent = nullptr);
    ~TabWindow();

private:
    Ui::TabWindow *ui;
};

#endif // TABWINDOW_H
