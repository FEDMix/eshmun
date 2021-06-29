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
#ifdef LC_ALL
    // Set locale for reading of DCM images
    setlocale(LC_ALL, "C");
    qInfo("LOCALE %s",std::setlocale(LC_ALL, NULL));
#endif

    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);

    //=========================================================================
    // setup for welcome page
    //=========================================================================
    // texts, images and icons
    // texts
    ui->labelWelcome->setText(text_welcome);
    ui->labelDescription->setText(text_description);
    // images
    QPixmap cover(":/img/assets/cover.png");
    //int width = ui->labelCover->width();
    //int height = ui->labelCover->height();
    //ui->labelCover->setPixmap(cover.scaled(width, height, Qt::KeepAspectRatio));
    ui->labelCover->setPixmap(cover);
    // icons
    QPixmap folder(":/img/assets/icons/open_file.png");
    QIcon buttonFolder(folder);
    ui->buttonAddPatient->setIcon(buttonFolder);
    //ui->buttonSelectSubjects->setIconSize();

    // push button on welcome page
    QPushButton *button_addPatient = MainWindow::findChild<QPushButton *>("buttonAddPatient"); // search for a widget by providing a name
    connect(button_addPatient, SIGNAL(released()), this,
            SLOT(pushButton_addPatient())); // assign signals and slots
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pushButton_addPatient()
{
    // Select path
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select directory with DICOM data"), "",
                                             QFileDialog::ShowDirsOnly
                                             | QFileDialog::DontResolveSymlinks);
    qInfo( "Directory path to patient images: %s", qUtf8Printable(dir));
    // Load the data viewer for this path
    Annotation* annotation = new Annotation(this);
    annotation->show();
    annotation->LoadData(dir);
}
