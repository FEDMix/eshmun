#ifndef TABSCREEN_H
#define TABSCREEN_H

#include <QWidget>

namespace Ui {
class tabscreen;
}

class tabscreen : public QWidget
{
    Q_OBJECT

public:
    explicit tabscreen(QWidget *parent = nullptr);
    ~tabscreen();

private:
    Ui::tabscreen *ui;
};

#endif // TABSCREEN_H
