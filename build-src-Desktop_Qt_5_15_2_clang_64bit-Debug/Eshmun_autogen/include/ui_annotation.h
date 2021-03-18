/********************************************************************************
** Form generated from reading UI file 'annotation.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANNOTATION_H
#define UI_ANNOTATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Annotation
{
public:
    QTabWidget *tabWidget;
    QWidget *SingleView;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *Difference;

    void setupUi(QDialog *Annotation)
    {
        if (Annotation->objectName().isEmpty())
            Annotation->setObjectName(QString::fromUtf8("Annotation"));
        Annotation->resize(1083, 699);
        tabWidget = new QTabWidget(Annotation);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 1051, 671));
        SingleView = new QWidget();
        SingleView->setObjectName(QString::fromUtf8("SingleView"));
        gridLayoutWidget = new QWidget(SingleView);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 10, 791, 451));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label, 0, 1, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        scrollArea = new QScrollArea(gridLayoutWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy1);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 390, 447));
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 0, 2, 1);

        tabWidget->addTab(SingleView, QString());
        Difference = new QWidget();
        Difference->setObjectName(QString::fromUtf8("Difference"));
        tabWidget->addTab(Difference, QString());

        retranslateUi(Annotation);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Annotation);
    } // setupUi

    void retranslateUi(QDialog *Annotation)
    {
        Annotation->setWindowTitle(QCoreApplication::translate("Annotation", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Annotation", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("Annotation", "TextLabel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(SingleView), QCoreApplication::translate("Annotation", "SingleView", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Difference), QCoreApplication::translate("Annotation", "Difference", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Annotation: public Ui_Annotation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANNOTATION_H
