/********************************************************************************
** Form generated from reading UI file 'mainwindownZ7796.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOWNZ7796_H
#define MAINWINDOWNZ7796_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSlider>
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
    QLabel *label;
    QLabel *label_2;
    QSlider *play_progress_bar;
    QLabel *time_show;
    QLabel *label_3;
    QCheckBox *lyrics_check;
    QSlider *volume_progress_bar;
    QLabel *volume_label;
    QLabel *label_4;
    QFrame *line;
    QListWidget *listWidget;
    QFrame *line_5;
    QFrame *line_6;
    QFrame *line_7;
    QFrame *line_2;
    QToolButton *play_or_suspend;
    QToolButton *last_song;
    QToolButton *next_song;
    QToolButton *add_btn;
    QToolButton *search_btn;
    QToolButton *local_btn;
    QToolButton *playmode_btn;
    QComboBox *play_model;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(330, 700);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setToolTipDuration(-1);
        MainWindow->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(260, 0, 71, 31));
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
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(1, 5, 20, 20));
        label->setStyleSheet(QStringLiteral("border-image: url(:/images/image/music.png);"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(25, 5, 160, 20));
        label_2->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"font: 10pt \"Arial\";"));
        play_progress_bar = new QSlider(centralWidget);
        play_progress_bar->setObjectName(QStringLiteral("play_progress_bar"));
        play_progress_bar->setGeometry(QRect(10, 50, 221, 22));
        play_progress_bar->setOrientation(Qt::Horizontal);
        time_show = new QLabel(centralWidget);
        time_show->setObjectName(QStringLiteral("time_show"));
        time_show->setGeometry(QRect(240, 65, 85, 18));
        time_show->setStyleSheet(QString::fromUtf8("font: 8pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);\n"
"background:transparent;"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 85, 80, 80));
        label_3->setStyleSheet(QStringLiteral("border-image: url(:/images/image/musichead.ico);"));
        lyrics_check = new QCheckBox(centralWidget);
        lyrics_check->setObjectName(QStringLiteral("lyrics_check"));
        lyrics_check->setGeometry(QRect(100, 90, 71, 21));
        lyrics_check->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        volume_progress_bar = new QSlider(centralWidget);
        volume_progress_bar->setObjectName(QStringLiteral("volume_progress_bar"));
        volume_progress_bar->setGeometry(QRect(240, 90, 80, 20));
        volume_progress_bar->setOrientation(Qt::Horizontal);
        volume_label = new QLabel(centralWidget);
        volume_label->setObjectName(QStringLiteral("volume_label"));
        volume_label->setGeometry(QRect(217, 89, 20, 20));
        volume_label->setStyleSheet(QLatin1String("border-image: url(:/images/image/volume_step.png);\n"
"border-image: url(:/images/image/volume.png);\n"
"border-image: url(:/images/image/volume_shut.png);"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(5, 670, 80, 20));
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(0, 191, 330, 2));
        line->setStyleSheet(QLatin1String("color: rgb(0, 0, 0);\n"
"background:transparent;"));
        line->setFrameShadow(QFrame::Plain);
        line->setFrameShape(QFrame::HLine);
        listWidget = new QListWidget(centralWidget);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/image/lyric.png"), QSize(), QIcon::Normal, QIcon::Off);
        QFont font;
        font.setPointSize(10);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(listWidget);
        __qlistwidgetitem->setFont(font);
        __qlistwidgetitem->setIcon(icon);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(listWidget);
        __qlistwidgetitem1->setFont(font);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(listWidget);
        __qlistwidgetitem2->setFont(font);
        QListWidgetItem *__qlistwidgetitem3 = new QListWidgetItem(listWidget);
        __qlistwidgetitem3->setFont(font);
        QListWidgetItem *__qlistwidgetitem4 = new QListWidgetItem(listWidget);
        __qlistwidgetitem4->setFont(font);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(0, 192, 90, 451));
        listWidget->setFocusPolicy(Qt::NoFocus);
        listWidget->setStyleSheet(QLatin1String("background-color:transparent;\n"
"color: rgb(255, 255, 255);"));
        listWidget->setFrameShape(QFrame::NoFrame);
        listWidget->setFrameShadow(QFrame::Plain);
        listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget->setSelectionMode(QAbstractItemView::NoSelection);
        listWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        line_5 = new QFrame(centralWidget);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(329, 191, 2, 451));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(line_5->sizePolicy().hasHeightForWidth());
        line_5->setSizePolicy(sizePolicy1);
        line_5->setFrameShadow(QFrame::Plain);
        line_5->setFrameShape(QFrame::VLine);
        line_6 = new QFrame(centralWidget);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setGeometry(QRect(0, 641, 330, 2));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(line_6->sizePolicy().hasHeightForWidth());
        line_6->setSizePolicy(sizePolicy2);
        line_6->setFrameShadow(QFrame::Plain);
        line_6->setFrameShape(QFrame::HLine);
        line_7 = new QFrame(centralWidget);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setGeometry(QRect(88, 192, 2, 451));
        sizePolicy1.setHeightForWidth(line_7->sizePolicy().hasHeightForWidth());
        line_7->setSizePolicy(sizePolicy1);
        line_7->setFrameShadow(QFrame::Plain);
        line_7->setFrameShape(QFrame::VLine);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(0, 0, 1, 642));
        line_2->setFrameShadow(QFrame::Plain);
        line_2->setFrameShape(QFrame::VLine);
        play_or_suspend = new QToolButton(centralWidget);
        play_or_suspend->setObjectName(QStringLiteral("play_or_suspend"));
        play_or_suspend->setGeometry(QRect(150, 130, 50, 50));
        play_or_suspend->setAutoRaise(true);
        last_song = new QToolButton(centralWidget);
        last_song->setObjectName(QStringLiteral("last_song"));
        last_song->setGeometry(QRect(95, 135, 40, 40));
        last_song->setStyleSheet(QStringLiteral(""));
        last_song->setAutoRaise(true);
        next_song = new QToolButton(centralWidget);
        next_song->setObjectName(QStringLiteral("next_song"));
        next_song->setGeometry(QRect(215, 135, 40, 40));
        next_song->setStyleSheet(QStringLiteral(""));
        next_song->setCheckable(false);
        next_song->setAutoRaise(true);
        add_btn = new QToolButton(centralWidget);
        add_btn->setObjectName(QStringLiteral("add_btn"));
        add_btn->setGeometry(QRect(90, 650, 40, 40));
        add_btn->setStyleSheet(QLatin1String("border-image: url(:/images/image/add_hover.png);\n"
""));
        add_btn->setAutoRaise(true);
        search_btn = new QToolButton(centralWidget);
        search_btn->setObjectName(QStringLiteral("search_btn"));
        search_btn->setGeometry(QRect(150, 650, 40, 40));
        search_btn->setStyleSheet(QStringLiteral("border-image: url(:/images/image/search_hover.png);"));
        search_btn->setAutoRaise(true);
        local_btn = new QToolButton(centralWidget);
        local_btn->setObjectName(QStringLiteral("local_btn"));
        local_btn->setGeometry(QRect(210, 650, 40, 40));
        local_btn->setStyleSheet(QStringLiteral("border-image: url(:/images/image/location_hover.png);"));
        local_btn->setAutoRaise(true);
        playmode_btn = new QToolButton(centralWidget);
        playmode_btn->setObjectName(QStringLiteral("playmode_btn"));
        playmode_btn->setGeometry(QRect(270, 650, 40, 40));
        playmode_btn->setStyleSheet(QStringLiteral("border-image: url(:/images/image/playmode_hover.png);"));
        playmode_btn->setAutoRaise(true);
        play_model = new QComboBox(centralWidget);
        play_model->setObjectName(QStringLiteral("play_model"));
        play_model->setGeometry(QRect(260, 150, 70, 22));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(7);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        play_model->setFont(font1);
        play_model->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"font: 7pt \"Arial\";\n"
"background-color:transparent;"));
        play_model->setIconSize(QSize(10, 20));
        MainWindow->setCentralWidget(centralWidget);
        listWidget->raise();
        layoutWidget->raise();
        label->raise();
        label_2->raise();
        play_progress_bar->raise();
        time_show->raise();
        label_3->raise();
        lyrics_check->raise();
        volume_progress_bar->raise();
        volume_label->raise();
        label_4->raise();
        line->raise();
        line_5->raise();
        line_6->raise();
        line_7->raise();
        line_2->raise();
        play_or_suspend->raise();
        last_song->raise();
        next_song->raise();
        add_btn->raise();
        search_btn->raise();
        local_btn->raise();
        playmode_btn->raise();
        play_model->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        back_btn->setText(QString());
        min_btn->setText(QString());
        close_btn->setText(QString());
        label->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "saddog\347\232\204\351\237\263\344\271\220\346\222\255\346\224\276\345\231\250", 0));
        time_show->setText(QApplication::translate("MainWindow", "00:00/00:00", 0));
        label_3->setText(QString());
        lyrics_check->setText(QApplication::translate("MainWindow", "\346\255\214\350\257\215", 0));
        volume_label->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "\346\255\214\346\233\262\346\225\260:0", 0));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("MainWindow", " \346\255\214  \350\257\215", 0));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("MainWindow", " \346\234\254\345\234\260\345\210\227\350\241\250", 0));
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("MainWindow", " \347\275\221\347\273\234\345\210\227\350\241\250", 0));
        QListWidgetItem *___qlistwidgetitem3 = listWidget->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("MainWindow", " \346\255\214\346\233\262\346\220\234\347\264\242", 0));
        QListWidgetItem *___qlistwidgetitem4 = listWidget->item(4);
        ___qlistwidgetitem4->setText(QApplication::translate("MainWindow", " \344\270\213\350\275\275\347\256\241\347\220\206", 0));
        listWidget->setSortingEnabled(__sortingEnabled);

        play_or_suspend->setText(QString());
#ifndef QT_NO_TOOLTIP
        last_song->setToolTip(QApplication::translate("MainWindow", "\344\270\212\344\270\200\346\233\262", 0));
#endif // QT_NO_TOOLTIP
        last_song->setText(QString());
#ifndef QT_NO_TOOLTIP
        next_song->setToolTip(QApplication::translate("MainWindow", "\344\270\213\344\270\200\346\233\262", 0));
#endif // QT_NO_TOOLTIP
        next_song->setText(QString());
        add_btn->setText(QString());
        search_btn->setText(QString());
        local_btn->setText(QString());
        playmode_btn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOWNZ7796_H
