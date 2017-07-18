#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCodec>
#include <QMediaContent>
#include <QtMultimedia/QMediaPlayer>
#include <QMediaPlaylist>
#include <QToolTip>
#include <QComboBox>
#include "backpic.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

	BackPic *backpic;
	QMediaPlayer *player;

public slots:
	void backChange(QString id);   //界面改变id信号
	void volPicchange(int vol);   //音量图片改变

private slots:
	void WindowStyle();
	void minWindow();
	void closeWindow();
	void backPicshow();
	void setBk(QString picname);   //设置背景函数
	void playOrsuspend();      //播放暂停函数
	void mousePressEvent(QMouseEvent *event);  //压下
	void mouseMoveEvent(QMouseEvent *event);   //移动
	void mouseReleaseEvent(QMouseEvent *event);  //释放
	void playModelchange(int);            //播放模式选择
	

private:
    Ui::MainWindow *ui;

	bool mouse_press;  //鼠标是否按下
	QPoint move_point; //鼠标移动距离
	bool is_play;    //播放暂停按钮的切换
};

#endif // MAINWINDOW_H
