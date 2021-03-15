#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "annotation.h"

QString text_welcome = "Welcome to the FEDMix Viewer";
QString text_description = "This viewer can be used to browse various\n"
                           "prostate annotations, select the preferred\n"
                           "annotation and export it to DICOM.\n"
                           "\n"
                           "The DICOM can be read by the clinical\n"
                           "annotation software to tune and adjust\n"
                           "in more detail.";
QString text_overview = "Subject Overview";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);

    //=========================================================================
    // setup for welcome page
    //=========================================================================
    ui->labelWelcome->setText(text_welcome);
    ui->labelDescription->setText(text_description);

    QPixmap cover(":/Resources/figs/cover.png");
    //int width = ui->figCover->width();
    //int height = ui->figCover->height();
    //ui->figCover->setPixmap(cover.scaled(width, height, Qt::KeepAspectRatio));
    ui->figCover->setPixmap(cover);


    // push button on welcome page
    QPushButton *button_selectSubject = MainWindow::findChild<QPushButton *>("buttonSelectSubjects"); // search for a widget by providing a name
    connect(button_selectSubject, SIGNAL(released()), this,
            SLOT(pushButton_selectSubject())); // assign signals and slots


    //=========================================================================
    // setup for select page
    //=========================================================================
    ui->labelOverview->setText(text_overview);
    ui->figRealTime->setPixmap(cover);


    // push button on select page
    QPushButton *button_goBack = MainWindow::findChild<QPushButton *>("buttonGoBack"); // search for a widget by providing a name
    connect(button_goBack, SIGNAL(released()), this,
            SLOT(pushButton_goBack())); // assign signals and slots
    // push button for selection
    QPushButton *button_subject1 = MainWindow::findChild<QPushButton *>("buttonSubject1");
    connect(button_subject1, SIGNAL(released()), this,
            SLOT(pushButton_subject1()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pushButton_selectSubject(){
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::pushButton_goBack(){
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::pushButton_subject1(){
    Annotation annotation;
    annotation.setModal(true);
    annotation.exec();
}

