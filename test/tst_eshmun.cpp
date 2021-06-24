#include "../src/pages/selectPatient/mainwindow.h"
#include <QCoreApplication>
#include <QtTest/QtTest>
#include <QtWidgets>
#include <QDebug>
#include <QString>
#include <QDir>

#include "../src/components/dataloader/imageloader.h"
#include "../src/components/VTKWidget/scenewidget.h"
#include "../src/pages/patientView/annotation.h"
#include <QSurfaceFormat>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>

// add necessary includes here

class testEshmun : public QObject {
  Q_OBJECT

public:
  testEshmun();
  ~testEshmun();

private slots:
  void initTestCase();
  // project test cases
  // example test unit test
  void strUpper();
  // example ui test
  void lineEdit();
  void cleanupTestCase();
  //void test_case1();
  void screenshotAndVerify(std::string name, SceneWidget* SceneWidget);
  void test_scene_widget();
  void test_orthogonal_views();
  void test_window_level_syncing();
  void test_imageloader();

private:
  MainWindow main_window;
};

bool compareFiles(const std::string &, const std::string &);

testEshmun::testEshmun() { main_window.show(); }

testEshmun::~testEshmun() {}

void testEshmun::initTestCase() {}

void testEshmun::strUpper() {
  QString strSample = "Eshmun";
  QVERIFY(strSample.toUpper() == "ESHMUN");
}

void testEshmun::lineEdit() {
  QLineEdit lineEdit;
  QTest::keyClicks(&lineEdit, "button pressed");
  QCOMPARE(lineEdit.text(), QString("button pressed"));
}

void testEshmun::cleanupTestCase() {}

void testEshmun::test_imageloader() {
    ImageLoader* imageloader = new ImageLoader();
    QString path = QDir::currentPath();
    QString path_scan = imageloader->image_scan(path);
    QString path_annotation = imageloader->image_annotation(path);
    // path for validation
    QString path_scan_validate = QDir::cleanPath(QDir::currentPath() + QDir::separator()
                                                 + "scans" + QDir::separator()+ "scan_to_annotate");
    QString path_annotation_validate = QDir::cleanPath(QDir::currentPath() + QDir::separator()
                                                       + "annotations");
    // QTest
    QCOMPARE(path_scan, path_scan_validate);
    QCOMPARE(path_annotation, path_annotation_validate);
}

//void testEshmun::test_case1() {
//  QPushButton *ui_selectButton =
//      main_window.findChild<QPushButton *>("buttonSelectSubjects");
//  QPushButton *ui_backButton =
//      main_window.findChild<QPushButton *>("buttonAddPatient");

//  QCOMPARE(ui_backButton->isVisible(), false);
//  QTest::mouseClick(ui_selectButton, Qt::LeftButton);
//  QCOMPARE(ui_backButton->isVisible(), true);
//}

void testEshmun::screenshotAndVerify(std::string name, SceneWidget* sceneWidget) {
    QDir workingDir = QDir{QDir::currentPath()};
    std::cerr << "Working directory: " << workingDir.path().toStdString()
            << std::endl;

    QString currentImagePath = QString::fromStdString(name + ".png");
    std::string imagePath = workingDir.filePath(currentImagePath).toStdString();

    QString refImage =
        workingDir.filePath(QString::fromStdString("../test/reference_images/" + name + ".png"));
    std::string referenceImagePath = QFileInfo{refImage}.absoluteFilePath().toStdString();

//   QSize size = sceneWidget->size();
//   std::cerr << "Original Widget Size: " << size.width() << ", " << size.height()
//             << std::endl;
//   sceneWidget->resize(800, 800);

//   size = sceneWidget->size();
//   std::cerr << "New Widget Size: " << size.width() << ", " << size.height()
//             << std::endl;

    sceneWidget->SaveScreenshot(imagePath);

    QVERIFY(compareFiles(imagePath, referenceImagePath));
}

void testEshmun::test_scene_widget() {
  QSKIP("Skipping vtk test till we have a better test");

  QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());
  Annotation *annotation = new Annotation(&main_window);
  annotation->show();
  SceneWidget *sceneWidget =
      annotation->findChild<SceneWidget *>("mainSceneAxial");
  vtkSmartPointer<vtkImageData> imageData = sceneWidget->GetDummyData();
  sceneWidget->SetImageData(imageData);
  screenshotAndVerify("test_scenewidget", sceneWidget);
}

void testEshmun::test_orthogonal_views() {
    QSKIP("Skipping vtk test till we have a better test");
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());
    Annotation *annotation = new Annotation(&main_window);
    annotation->show();

    // Axial
    SceneWidget *sceneWidget =
        annotation->findChild<SceneWidget *>("mainSceneAxial");
    vtkSmartPointer<vtkImageData> imageData = sceneWidget->GetDummyData();
    sceneWidget->SetImageData(imageData);
    sceneWidget->SetPlaneOrientationToAxial();
    screenshotAndVerify("test_orthogonal_views_axial", sceneWidget);

    // Coronal
    sceneWidget->SetPlaneOrientationToCoronal();
    screenshotAndVerify("test_orthogonal_views_coronal", sceneWidget);

    // Sagittal
    sceneWidget->SetPlaneOrientationToSagittal();
    screenshotAndVerify("test_orthogonal_views_sagittal", sceneWidget);
}

void testEshmun::test_window_level_syncing() {
    QSKIP("Skipping vtk test till we have a better test");
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());
    Annotation *annotation = new Annotation(&main_window);
    annotation->show();

    SceneWidget *sceneWidget =
        annotation->findChild<SceneWidget *>("mainSceneAxial");
    vtkSmartPointer<vtkImageData> imageData = sceneWidget->GetDummyData();
    sceneWidget->SetImageData(imageData);

    SceneWidget* sceneWidget2 =
        annotation->findChild<SceneWidget *>("mainSceneCoronal");
    sceneWidget2->SetImageData(imageData);

    sceneWidget->SetWindowLevel(999, 501);

    screenshotAndVerify("test_set_window_level", sceneWidget);
    screenshotAndVerify("test_sync_window_level", sceneWidget2);
}

bool compareFiles(const std::string &p1, const std::string &p2) {
  std::cerr << "Comparing file: " << p1 << " to " << p2
            << std::endl;

  std::ifstream f1(p1, std::ifstream::binary | std::ifstream::ate);
  std::ifstream f2(p2, std::ifstream::binary | std::ifstream::ate);

  if (f1.fail()) {
    std::cerr << "file 1 or not found for comparison" << std::endl;
    return false; // file problem
  }
  if (f2.fail()) {
    std::cerr << "file 2 not found for comparison" << std::endl;
    return false; // file problem
  }

  if (f1.tellg() != f2.tellg()) {
    std::cerr << "Size mismatch between files: " << f1.tellg() << " v "
              << f2.tellg() << std::endl;
    return false; // size mismatch
  }

  // seek back to beginning and use std::equal to compare contents
  f1.seekg(0, std::ifstream::beg);
  f2.seekg(0, std::ifstream::beg);
  return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                    std::istreambuf_iterator<char>(),
                    std::istreambuf_iterator<char>(f2.rdbuf()));
}

QTEST_MAIN(testEshmun)

#include "tst_eshmun.moc"
