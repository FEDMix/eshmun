#include "mainwindow.h"
#include "./ui_mainwindow.h"

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
    : QMainWindow(parent), ui(new Ui::MainWindow)
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
    // ui->figCover->setPixmap(cover);

    // push button on welcome page
    QPushButton *button_selectSubject = MainWindow::findChild<QPushButton *>("buttonSelectSubjects"); // search for a widget by providing a name
    connect(button_selectSubject, SIGNAL(released()), this,
            SLOT(pushButton_selectSubject())); // assign signals and slots

    //=========================================================================
    // setup for select page
    //=========================================================================
    ui->labelOverview->setText(text_overview);
    // ui->figRealTime->setPixmap(cover);

    // push button on select page
    QPushButton *button_goBack = MainWindow::findChild<QPushButton *>("buttonGoBack"); // search for a widget by providing a name
    connect(button_goBack, SIGNAL(released()), this,
            SLOT(pushButton_goBack())); // assign signals and slots

    // push button on select page
    QPushButton *button_initVTK = MainWindow::findChild<QPushButton *>("initVTK"); // search for a widget by providing a name
    connect(button_initVTK, SIGNAL(released()), this,
            SLOT(pushButton_initVTK())); // assign signals and slots

    // push button for selection
    // patient 1
    QPushButton *button_subject1 = MainWindow::findChild<QPushButton *>("buttonSubject1");
    connect(button_subject1, SIGNAL(released()), this,
            SLOT(pushButton_subject1()));
    // patient 2
    QPushButton *button_subject2 = MainWindow::findChild<QPushButton *>("buttonSubject2");
    connect(button_subject2, SIGNAL(released()), this,
            SLOT(pushButton_subject2()));
    // patient 3
    QPushButton *button_subject3 = MainWindow::findChild<QPushButton *>("buttonSubject3");
    connect(button_subject3, SIGNAL(released()), this,
            SLOT(pushButton_subject3()));

    // add subject
    QPushButton *button_addSubject = MainWindow::findChild<QPushButton *>("buttonAddSubject");
    connect(button_addSubject, SIGNAL(released()), this,
            SLOT(pushButton_addSubject()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pushButton_selectSubject()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::pushButton_goBack()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::pushButton_subject1()
{
    // open a new window and deactivate the old window
    // Annotation annotation;
    // annotation.setModal(true);
    // annotation.exec();

    // open a new window with the old window active
    annotation1 = new Annotation(this);
    annotation1->show();
}

void MainWindow::pushButton_subject2()
{
    annotation2 = new Annotation(this);
    annotation2->show();
}

void MainWindow::pushButton_subject3()
{
    annotation3 = new Annotation(this);
    annotation3->show();
}

void MainWindow::pushButton_addSubject(){
    // Select path
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select directory with DICOM data"), "",
                                             QFileDialog::ShowDirsOnly
                                             | QFileDialog::DontResolveSymlinks);

    // Load the data viewer for this path
    Annotation* annotation1 = new Annotation(this);
    annotation1->show();
    annotation1->LoadData(dir.toStdString());
}
