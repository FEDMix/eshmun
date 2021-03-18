/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *pageMain;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *labelWelcome;
    QLabel *labelDescription;
    QSpacerItem *verticalSpacer_2;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_2;
    QPushButton *buttonSelectSubjects;
    QSpacerItem *horizontalSpacer;
    QLabel *figCover;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_4;
    QWidget *pageSelect;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_5;
    QLabel *figRealTime;
    QSpacerItem *verticalSpacer_6;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_3;
    QPushButton *buttonSubject6;
    QPushButton *buttonSubject3;
    QPushButton *buttonSubject4;
    QPushButton *buttonSubject1;
    QPushButton *buttonGoBack;
    QPushButton *buttonSubject5;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_7;
    QLabel *labelOverview;
    QPushButton *buttonSubject2;
    QPushButton *pushButton_8;
    QSpacerItem *horizontalSpacer_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1629, 795);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        pageMain = new QWidget();
        pageMain->setObjectName(QString::fromUtf8("pageMain"));
        verticalLayoutWidget = new QWidget(pageMain);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 641, 711));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 120, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        labelWelcome = new QLabel(verticalLayoutWidget);
        labelWelcome->setObjectName(QString::fromUtf8("labelWelcome"));
        labelWelcome->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	font: 75 22pt \"MS Shell Dlg 2\";\n"
"    padding: 40px\n"
"}"));

        verticalLayout->addWidget(labelWelcome);

        labelDescription = new QLabel(verticalLayoutWidget);
        labelDescription->setObjectName(QString::fromUtf8("labelDescription"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelDescription->sizePolicy().hasHeightForWidth());
        labelDescription->setSizePolicy(sizePolicy);
        labelDescription->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	font: 22pt \"MS Shell Dlg 2\";\n"
"    padding: 40px\n"
"}"));

        verticalLayout->addWidget(labelDescription);

        verticalSpacer_2 = new QSpacerItem(20, 120, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        gridLayoutWidget = new QWidget(pageMain);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(659, 9, 931, 711));
        gridLayout_2 = new QGridLayout(gridLayoutWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        buttonSelectSubjects = new QPushButton(gridLayoutWidget);
        buttonSelectSubjects->setObjectName(QString::fromUtf8("buttonSelectSubjects"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(buttonSelectSubjects->sizePolicy().hasHeightForWidth());
        buttonSelectSubjects->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(buttonSelectSubjects, 2, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 0, 1, 1);

        figCover = new QLabel(gridLayoutWidget);
        figCover->setObjectName(QString::fromUtf8("figCover"));

        gridLayout_2->addWidget(figCover, 1, 0, 1, 2);

        verticalSpacer_3 = new QSpacerItem(20, 120, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer_3, 3, 0, 1, 2);

        verticalSpacer_4 = new QSpacerItem(20, 120, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer_4, 0, 0, 1, 2);

        stackedWidget->addWidget(pageMain);
        pageSelect = new QWidget();
        pageSelect->setObjectName(QString::fromUtf8("pageSelect"));
        verticalLayoutWidget_3 = new QWidget(pageSelect);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(530, 10, 1061, 711));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_5 = new QSpacerItem(20, 80, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_5);

        figRealTime = new QLabel(verticalLayoutWidget_3);
        figRealTime->setObjectName(QString::fromUtf8("figRealTime"));

        verticalLayout_3->addWidget(figRealTime);

        verticalSpacer_6 = new QSpacerItem(20, 280, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_6);

        gridLayoutWidget_2 = new QWidget(pageSelect);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(-1, 9, 521, 711));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        buttonSubject6 = new QPushButton(gridLayoutWidget_2);
        buttonSubject6->setObjectName(QString::fromUtf8("buttonSubject6"));

        gridLayout_3->addWidget(buttonSubject6, 7, 0, 1, 2);

        buttonSubject3 = new QPushButton(gridLayoutWidget_2);
        buttonSubject3->setObjectName(QString::fromUtf8("buttonSubject3"));

        gridLayout_3->addWidget(buttonSubject3, 4, 0, 1, 2);

        buttonSubject4 = new QPushButton(gridLayoutWidget_2);
        buttonSubject4->setObjectName(QString::fromUtf8("buttonSubject4"));

        gridLayout_3->addWidget(buttonSubject4, 5, 0, 1, 2);

        buttonSubject1 = new QPushButton(gridLayoutWidget_2);
        buttonSubject1->setObjectName(QString::fromUtf8("buttonSubject1"));
        sizePolicy1.setHeightForWidth(buttonSubject1->sizePolicy().hasHeightForWidth());
        buttonSubject1->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(buttonSubject1, 2, 0, 1, 2);

        buttonGoBack = new QPushButton(gridLayoutWidget_2);
        buttonGoBack->setObjectName(QString::fromUtf8("buttonGoBack"));

        gridLayout_3->addWidget(buttonGoBack, 0, 0, 1, 1);

        buttonSubject5 = new QPushButton(gridLayoutWidget_2);
        buttonSubject5->setObjectName(QString::fromUtf8("buttonSubject5"));

        gridLayout_3->addWidget(buttonSubject5, 6, 0, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        verticalSpacer_7 = new QSpacerItem(20, 280, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_3->addItem(verticalSpacer_7, 10, 0, 1, 2);

        labelOverview = new QLabel(gridLayoutWidget_2);
        labelOverview->setObjectName(QString::fromUtf8("labelOverview"));
        labelOverview->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	font: 75 24pt \"MS Shell Dlg 2\";\n"
"    padding: 20px\n"
"}"));

        gridLayout_3->addWidget(labelOverview, 1, 0, 1, 2);

        buttonSubject2 = new QPushButton(gridLayoutWidget_2);
        buttonSubject2->setObjectName(QString::fromUtf8("buttonSubject2"));

        gridLayout_3->addWidget(buttonSubject2, 3, 0, 1, 2);

        pushButton_8 = new QPushButton(gridLayoutWidget_2);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));

        gridLayout_3->addWidget(pushButton_8, 9, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(280, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 9, 1, 1, 1);

        stackedWidget->addWidget(pageSelect);

        gridLayout->addWidget(stackedWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1629, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "FEDMix Viewer", nullptr));
        labelWelcome->setText(QCoreApplication::translate("MainWindow", "Welcome", nullptr));
        labelDescription->setText(QCoreApplication::translate("MainWindow", "Description", nullptr));
        buttonSelectSubjects->setText(QCoreApplication::translate("MainWindow", "Select Subjects", nullptr));
        figCover->setText(QString());
        figRealTime->setText(QString());
        buttonSubject6->setText(QCoreApplication::translate("MainWindow", "Subject n", nullptr));
        buttonSubject3->setText(QCoreApplication::translate("MainWindow", "Subject 3", nullptr));
        buttonSubject4->setText(QCoreApplication::translate("MainWindow", "Subject 4", nullptr));
        buttonSubject1->setText(QCoreApplication::translate("MainWindow", "Subject 1", nullptr));
        buttonGoBack->setText(QCoreApplication::translate("MainWindow", "Go Back", nullptr));
        buttonSubject5->setText(QCoreApplication::translate("MainWindow", "Subject n", nullptr));
        labelOverview->setText(QCoreApplication::translate("MainWindow", "Select", nullptr));
        buttonSubject2->setText(QCoreApplication::translate("MainWindow", "Subject 2", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "Add Subjects", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
