#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
#ifdef LC_ALL
    // Set locale for reading of DCM images
    setlocale(LC_ALL, "C");
    qInfo("LOCALE %s",std::setlocale(LC_ALL, NULL));
#endif

    //=========================================================================
    // setup for welcome page
    //=========================================================================
    // push button on welcome page
    ui->setupUi(this);
    QPushButton *button_addPatient = MainWindow::findChild<QPushButton *>("buttonAddPatient"); // search for a widget by providing a name
    connect(button_addPatient, SIGNAL(released()), this,
            SLOT(pushButton_addPatient())); // assign signals and slots

    button_addPatient->setStyleSheet(
       "QPushButton { background-color: #525252; font-size: 18px; color:#ebebeb; border-radius:5px;}"
    );
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

void MainWindow::on_pageSelect_windowTitleChanged(const QString &title)
{

}


void MainWindow::on_pageSelect_customContextMenuRequested(const QPoint &pos)
{

}

