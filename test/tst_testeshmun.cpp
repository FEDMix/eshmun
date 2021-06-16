#include "../src/pages/selectPatient/mainwindow.h"
#include <QCoreApplication>
#include <QtTest/QtTest>
#include <QtWidgets>
#include <QDebug>
#include <QString>
#include <QDir>

#include "../src/pages/patientView/annotation.h"
#include "../src/components/VTKWidget/scenewidget.h"
#include "../src/components/dataloader/imageloader.h"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <QSurfaceFormat>
#include <QVTKOpenGLNativeWidget.h>

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
  //void test_vtk_viewer();
  void test_imageloader();

  private:
      MainWindow main_window;
};

bool compareFiles(const std::string&, const std::string&);

testEshmun::testEshmun() {
    main_window.show();
}

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
                                                       + "annotations" + QDir::separator()+ "annotation1");
    // QTest
    QCOMPARE(path_scan, path_scan_validate);
    QCOMPARE(path_annotation, path_annotation_validate);
}

void testEshmun::test_vtk_viewer() {
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());
    Annotation* annotation = new Annotation(&main_window);
    annotation->show();
    SceneWidget* sceneWidget = annotation->findChild<SceneWidget*>("mainSceneAxial");
    vtkSmartPointer<vtkImageData> imageData = sceneWidget->GetDummyData();
    sceneWidget->SetImageData(imageData);
    sceneWidget->SetPlaneOrientationToAxial();
    std::string referenceImagePath = "../test/reference_images/test_dummy.png";
    std::string currentImagePath = "test/test_dummy.png";
    sceneWidget->SaveScreenshot(currentImagePath);
    QVERIFY(compareFiles(currentImagePath, referenceImagePath));
}

bool compareFiles(const std::string& p1, const std::string& p2) {
  std::ifstream f1(p1, std::ifstream::binary|std::ifstream::ate);
  std::ifstream f2(p2, std::ifstream::binary|std::ifstream::ate);

  if (f1.fail() || f2.fail()) {
    return false; //file problem
  }

  if (f1.tellg() != f2.tellg()) {
    return false; //size mismatch
  }

  //seek back to beginning and use std::equal to compare contents
  f1.seekg(0, std::ifstream::beg);
  f2.seekg(0, std::ifstream::beg);
  return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                    std::istreambuf_iterator<char>(),
                    std::istreambuf_iterator<char>(f2.rdbuf()));
}

QTEST_MAIN(testEshmun)

#include "tst_testeshmun.moc"
