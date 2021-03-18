#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QWidget>
#include <QPixmap>
#include <QMainWindow>
#include <QLabel>
namespace Ui {
class HomeScreen;
}

class HomeScreen : public QWidget
{
    Q_OBJECT

public:
    explicit HomeScreen(QWidget *parent = nullptr);
    ~HomeScreen();

private:
    Ui::HomeScreen *ui;
};

#endif // HOMESCREEN_H
