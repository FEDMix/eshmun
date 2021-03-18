#include "../src/mainwindow.h"
#include "../src/tabwindow.h"
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
//  void test_tabs();

  private:
      MainWindow main_window;
      TabWindow tab_window;

};

testEshmun::testEshmun() {
//    main_window.show();
    tab_window.show();
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
//    QPushButton *ui_selectButton = main_window.findChild<QPushButton*>("buttonSelectSubjects");
//    QPushButton *ui_backButton = main_window.findChild<QPushButton*>("buttonGoBack");

//    QCOMPARE(ui_backButton->isVisible(),false);
//    QTest::mouseClick(ui_selectButton, Qt::LeftButton);
//    QCOMPARE(ui_backButton->isVisible(),true);
    // get the main tab window
      QTabWidget *ui_tab_widget = tab_window.findChild<QTabWidget*>("eshmun_tab_widget");
      // check if number of tabs are 3
      QCOMPARE(ui_tab_widget->count(),3);
    // check if the current index is 0
      QCOMPARE(ui_tab_widget->currentIndex(),1);
    // check if the current tab is single view tab
      QWidget *ui_single_view_tab = tab_window.findChild<QWidget*>("single_view_tab");
      QCOMPARE(ui_tab_widget->currentWidget(),ui_single_view_tab);
}

//void testEshmun::test_tabs() {
//    // get the main tab window
//      QTabWidget *ui_tab_widget = tab_window.findChild<QTabWidget*>("eshmun_tab_widget");
//      QCOMPARE(ui_tab_widget->count(),4);
//    // check if the current index is 0
//      QCOMPARE(ui_tab_widget->currentIndex(),1);
//    // check if the current tab is single view tab
//      QWidget *ui_single_view_tab = tab_window.findChild<QWidget*>("single_view_tab");
//      QCOMPARE(ui_tab_widget->currentWidget(),ui_single_view_tab);

//}
QTEST_MAIN(testEshmun)

#include "tst_testeshmun.moc"
