/********************************************************************************
** Form generated from reading UI file 'backpicmU6460.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef BACKPICMU6460_H
#define BACKPICMU6460_H

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
        scrollArea->setGeometry(QRect(40, 40, 211, 231));
        scrollArea->setStyleSheet(QLatin1String("QWidget{background:white;border-image:NULL}\n"
"QScrollBar{background:white; width: 10px;margin: 10px 0 10px 0;}\n"
"QScrollBar::handle{background:rgb(165,165,165); border:0px solid transparent; border-radius:4px;}\n"
"QScrollBar::handle:hover{background:rgb(77,77,77); border-radius:4px;}\n"
"QScrollBar::add-line:vertical {background:gray;border-image: url(:/images/image/down.png); height: 10px; subcontrol-position: bottom;subcontrol-origin: margin;}\n"
"QScrollBar::sub-line:vertical {background:gray;border-image: url(:/images/image/top.png);height: 10px;subcontrol-position: top;subcontrol-origin: margin;}\n"
"QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background:white;}"));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 199, 229));
        btn1 = new QToolButton(scrollAreaWidgetContents);
        btn1->setObjectName(QStringLiteral("btn1"));
        btn1->setGeometry(QRect(15, 0, 50, 110));
        QFont font;
        font.setFamily(QStringLiteral("SimSun-ExtB"));
        font.setPointSize(12);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        btn1->setFont(font);
        btn1->setStyleSheet(QStringLiteral(""));
        btn1->setAutoRaise(true);
        btn2 = new QToolButton(scrollAreaWidgetContents);
        btn2->setObjectName(QStringLiteral("btn2"));
        btn2->setGeometry(QRect(75, 0, 50, 110));
        QFont font1;
        font1.setPointSize(12);
        btn2->setFont(font1);
        btn2->setToolTipDuration(-1);
        btn2->setStyleSheet(QStringLiteral(""));
        btn2->setAutoRaise(true);
        btn3 = new QToolButton(scrollAreaWidgetContents);
        btn3->setObjectName(QStringLiteral("btn3"));
        btn3->setGeometry(QRect(135, 0, 50, 110));
        btn3->setFont(font1);
        btn3->setStyleSheet(QStringLiteral(""));
        btn3->setAutoRaise(true);
        btn4 = new QToolButton(scrollAreaWidgetContents);
        btn4->setObjectName(QStringLiteral("btn4"));
        btn4->setGeometry(QRect(15, 120, 50, 110));
        btn4->setFont(font1);
        btn4->setStyleSheet(QStringLiteral(""));
        btn4->setAutoRaise(true);
        btn5 = new QToolButton(scrollAreaWidgetContents);
        btn5->setObjectName(QStringLiteral("btn5"));
        btn5->setGeometry(QRect(75, 120, 50, 110));
        btn5->setFont(font1);
        btn5->setStyleSheet(QStringLiteral(""));
        btn5->setAutoRaise(true);
        scrollArea->setWidget(scrollAreaWidgetContents);
        line = new QFrame(BackPic);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(40, 20, 211, 2));
        line->setFrameShadow(QFrame::Plain);
        line->setFrameShape(QFrame::HLine);
        line_2 = new QFrame(BackPic);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(40, 290, 211, 2));
        line_2->setFrameShadow(QFrame::Plain);
        line_2->setFrameShape(QFrame::HLine);
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
        label->setStyleSheet(QLatin1String("color: rgb(85, 0, 255);\n"
""));

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
#ifndef QT_NO_TOOLTIP
        scrollArea->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        btn1->setToolTip(QApplication::translate("BackPic", "\347\273\277\351\207\216\344\273\231\350\270\252", 0));
#endif // QT_NO_TOOLTIP
        btn1->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn2->setToolTip(QApplication::translate("BackPic", "\345\271\275\345\244\234\346\232\227\351\246\231", 0));
#endif // QT_NO_TOOLTIP
        btn2->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn3->setToolTip(QApplication::translate("BackPic", "\345\244\217\346\227\245\345\277\203\346\203\205", 0));
#endif // QT_NO_TOOLTIP
        btn3->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn4->setToolTip(QApplication::translate("BackPic", "\347\276\216\345\245\263\345\207\235\350\247\206", 0));
#endif // QT_NO_TOOLTIP
        btn4->setText(QString());
#ifndef QT_NO_TOOLTIP
        btn5->setToolTip(QApplication::translate("BackPic", "\345\217\257\347\210\261\345\212\250\344\272\272", 0));
#endif // QT_NO_TOOLTIP
        btn5->setText(QString());
        close_btn->setText(QString());
        label->setText(QApplication::translate("BackPic", "\345\210\227\350\241\250\351\200\217\346\230\216\345\272\246", 0));
    } // retranslateUi

};

namespace Ui {
    class BackPic: public Ui_BackPic {};
} // namespace Ui

QT_END_NAMESPACE

#endif // BACKPICMU6460_H
