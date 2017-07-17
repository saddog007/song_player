/********************************************************************************
** Form generated from reading UI file 'backpicp12896.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef BACKPICP12896_H
#define BACKPICP12896_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BackPic
{
public:
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QToolButton *btn1;
    QToolButton *btn2;
    QToolButton *btn3;
    QToolButton *btn4;
    QToolButton *btn5;
    QFrame *line;
    QFrame *line_2;
    QToolButton *close_btn;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSlider *horizontalSlider;

    void setupUi(QDialog *BackPic)
    {
        if (BackPic->objectName().isEmpty())
            BackPic->setObjectName(QStringLiteral("BackPic"));
        BackPic->resize(290, 380);
        scrollArea = new QScrollArea(BackPic);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(40, 40, 211, 221));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 188, 219));
        btn1 = new QToolButton(scrollAreaWidgetContents);
        btn1->setObjectName(QStringLiteral("btn1"));
        btn1->setGeometry(QRect(25, 10, 140, 35));
        btn1->setStyleSheet(QLatin1String("background-color: rgba(255, 0, 0, 200);\n"
"color: rgba(85, 255, 96, 255);\n"
"font: 12pt \"Arial\";\n"
"border-radius:12px;"));
        btn2 = new QToolButton(scrollAreaWidgetContents);
        btn2->setObjectName(QStringLiteral("btn2"));
        btn2->setGeometry(QRect(25, 50, 140, 35));
        btn2->setStyleSheet(QLatin1String("background-color: rgba(255, 0, 0, 200);\n"
"color: rgba(85, 255, 96, 255);\n"
"font: 12pt \"Arial\";\n"
"border-radius:12px;"));
        btn3 = new QToolButton(scrollAreaWidgetContents);
        btn3->setObjectName(QStringLiteral("btn3"));
        btn3->setGeometry(QRect(25, 90, 140, 35));
        btn3->setStyleSheet(QLatin1String("background-color: rgba(255, 0, 0, 200);\n"
"color: rgba(85, 255, 96, 255);\n"
"font: 12pt \"Arial\";\n"
"border-radius:12px;"));
        btn4 = new QToolButton(scrollAreaWidgetContents);
        btn4->setObjectName(QStringLiteral("btn4"));
        btn4->setGeometry(QRect(25, 130, 140, 35));
        btn4->setStyleSheet(QLatin1String("background-color: rgba(255, 0, 0, 200);\n"
"color: rgba(85, 255, 96, 255);\n"
"font: 12pt \"Arial\";\n"
"border-radius:12px;"));
        btn5 = new QToolButton(scrollAreaWidgetContents);
        btn5->setObjectName(QStringLiteral("btn5"));
        btn5->setGeometry(QRect(25, 170, 140, 35));
        btn5->setStyleSheet(QLatin1String("background-color: rgba(255, 0, 0, 200);\n"
"color: rgba(85, 255, 96, 255);\n"
"font: 12pt \"Arial\";\n"
"border-radius:12px;"));
        scrollArea->setWidget(scrollAreaWidgetContents);
        line = new QFrame(BackPic);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(40, 10, 211, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(BackPic);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(40, 280, 211, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        close_btn = new QToolButton(BackPic);
        close_btn->setObjectName(QStringLiteral("close_btn"));
        close_btn->setGeometry(QRect(265, 0, 21, 21));
        close_btn->setStyleSheet(QStringLiteral("border-image: url(:/images/image/close24.png);"));
        layoutWidget = new QWidget(BackPic);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 310, 211, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QLatin1String("\n"
"color: rgb(255, 0, 0);"));

        horizontalLayout->addWidget(label);

        horizontalSlider = new QSlider(layoutWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSlider);


        retranslateUi(BackPic);

        QMetaObject::connectSlotsByName(BackPic);
    } // setupUi

    void retranslateUi(QDialog *BackPic)
    {
        BackPic->setWindowTitle(QApplication::translate("BackPic", "Dialog", 0));
        btn1->setText(QApplication::translate("BackPic", "\347\273\277\351\207\216\344\273\231\350\270\252", 0));
        btn2->setText(QApplication::translate("BackPic", "\345\271\275\345\244\234\346\232\227\351\246\231", 0));
        btn3->setText(QApplication::translate("BackPic", "\345\244\217\346\227\245\345\277\203\346\203\205", 0));
        btn4->setText(QApplication::translate("BackPic", "\347\276\216\345\245\263\345\207\235\350\247\206", 0));
        btn5->setText(QApplication::translate("BackPic", "\345\217\257\347\210\261\345\212\250\344\272\272", 0));
        close_btn->setText(QString());
        label->setText(QApplication::translate("BackPic", "\345\210\227\350\241\250\351\200\217\346\230\216\345\272\246", 0));
    } // retranslateUi

};

namespace Ui {
    class BackPic: public Ui_BackPic {};
} // namespace Ui

QT_END_NAMESPACE

#endif // BACKPICP12896_H
