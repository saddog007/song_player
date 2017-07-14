/********************************************************************************
** Form generated from reading UI file 'mainwindowp11352.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOWP11352_H
#define MAINWINDOWP11352_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QHBoxLayout *left_up_layout;
    QToolButton *back_btn;
    QToolButton *min_btn;
    QToolButton *close_btn;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(330, 700);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(270, 0, 62, 22));
        left_up_layout = new QHBoxLayout(layoutWidget);
        left_up_layout->setSpacing(0);
        left_up_layout->setContentsMargins(11, 11, 11, 11);
        left_up_layout->setObjectName(QStringLiteral("left_up_layout"));
        left_up_layout->setContentsMargins(0, 0, 0, 0);
        back_btn = new QToolButton(layoutWidget);
        back_btn->setObjectName(QStringLiteral("back_btn"));
        back_btn->setMinimumSize(QSize(20, 20));
        back_btn->setMaximumSize(QSize(20, 20));
        back_btn->setStyleSheet(QStringLiteral("border-image: url(:/images/image/skinbox.png);"));

        left_up_layout->addWidget(back_btn);

        min_btn = new QToolButton(layoutWidget);
        min_btn->setObjectName(QStringLiteral("min_btn"));
        min_btn->setMinimumSize(QSize(20, 20));
        min_btn->setMaximumSize(QSize(20, 20));
        min_btn->setStyleSheet(QStringLiteral("border-image: url(:/images/image/minimize.png);"));

        left_up_layout->addWidget(min_btn);

        close_btn = new QToolButton(layoutWidget);
        close_btn->setObjectName(QStringLiteral("close_btn"));
        close_btn->setMinimumSize(QSize(20, 20));
        close_btn->setMaximumSize(QSize(20, 20));
        close_btn->setStyleSheet(QStringLiteral("border-image: url(:/images/image/close24.png);"));

        left_up_layout->addWidget(close_btn);

        left_up_layout->setStretch(0, 1);
        left_up_layout->setStretch(1, 1);
        left_up_layout->setStretch(2, 1);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 330, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        back_btn->setText(QString());
        min_btn->setText(QString());
        close_btn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOWP11352_H
