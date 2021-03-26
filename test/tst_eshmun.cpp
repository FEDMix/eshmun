#include "../src/pages/selectPatient/mainwindow.h"
#include <QCoreApplication>
#include <QtTest/QtTest>
#include <QtWidgets>

<<<<<<< HEAD:test/tst_eshmun.cpp
=======
#include "../src/pages/patientView/annotation.h"
#include "../src/components/VTKWidget/scenewidget.h"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <QSurfaceFormat>
#include <QVTKOpenGLNativeWidget.h>

>>>>>>> main:test/tst_testeshmun.cpp
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
  void test_case1();
  void test_vtk_viewer();

private:
  MainWindow main_window;
};

<<<<<<< HEAD:test/tst_eshmun.cpp
testEshmun::testEshmun() { main_window.show(); }
=======
bool compareFiles(const std::string&, const std::string&);



testEshmun::testEshmun() {
    main_window.show();
}
>>>>>>> main:test/tst_testeshmun.cpp

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

void testEshmun::test_case1() {
  QPushButton *ui_selectButton =
      main_window.findChild<QPushButton *>("buttonSelectSubjects");
  QPushButton *ui_backButton =
      main_window.findChild<QPushButton *>("buttonGoBack");

  QCOMPARE(ui_backButton->isVisible(), false);
  QTest::mouseClick(ui_selectButton, Qt::LeftButton);
  QCOMPARE(ui_backButton->isVisible(), true);
}

void testEshmun::test_vtk_viewer() {
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());
    Annotation* annotation = new Annotation(&main_window);
    annotation->show();
    SceneWidget* sceneWidget = annotation->findChild<SceneWidget*>("sceneWidget");
    vtkSmartPointer<vtkImageData> imageData = sceneWidget->GetDummyData();
    sceneWidget->SetImageData(imageData);
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

#include "tst_eshmun.moc"
