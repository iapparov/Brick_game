/********************************************************************************
** Form generated from reading UI file 'snakemainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SNAKEMAINWINDOW_H
#define UI_SNAKEMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SnakeMainWindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SnakeMainWindow)
    {
        if (SnakeMainWindow->objectName().isEmpty())
            SnakeMainWindow->setObjectName("SnakeMainWindow");
        SnakeMainWindow->resize(800, 600);
        centralwidget = new QWidget(SnakeMainWindow);
        centralwidget->setObjectName("centralwidget");
        SnakeMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SnakeMainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 24));
        SnakeMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(SnakeMainWindow);
        statusbar->setObjectName("statusbar");
        SnakeMainWindow->setStatusBar(statusbar);

        retranslateUi(SnakeMainWindow);

        QMetaObject::connectSlotsByName(SnakeMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SnakeMainWindow)
    {
        SnakeMainWindow->setWindowTitle(QCoreApplication::translate("SnakeMainWindow", "SnakeMainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SnakeMainWindow: public Ui_SnakeMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SNAKEMAINWINDOW_H
