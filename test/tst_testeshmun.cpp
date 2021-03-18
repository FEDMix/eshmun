#include "../src/mainwindow.h"
#include <QCoreApplication>
#include <QtTest/QtTest>
#include <QtWidgets>


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

  private:
      MainWindow main_window;
};

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

void testEshmun::test_case1() {
    QPushButton *ui_selectButton = main_window.findChild<QPushButton*>("buttonSelectSubjects");
    QPushButton *ui_backButton = main_window.findChild<QPushButton*>("buttonGoBack");

    QCOMPARE(ui_backButton->isVisible(),false);
    QTest::mouseClick(ui_selectButton, Qt::LeftButton);
    QCOMPARE(ui_backButton->isVisible(),true);
}

QTEST_MAIN(testEshmun)

#include "tst_testeshmun.moc"
