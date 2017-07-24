#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCodec>
#include <QMediaContent>
#include <QtMultimedia/QMediaPlayer>
#include <QMediaPlaylist>
#include <QToolTip>
#include <QComboBox>
#include <QStackedWidget>
#include <QSystemTrayIcon>
#include <QWidgetAction>
#include <QPushButton>
#include <QAction>
#include <QMenu>
#include <QMessageBox>
#include <QFileDialog>
#include "backpic.h"
#include "mymaintable.h"

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
	QTimer *m_timer;
	QStackedWidget *stack;
	Mymaintable *mytable;
	QSystemTrayIcon *trayicon;
	
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
	void songNameshow();       //歌曲名滚动显示函数
	void mytableDoubleclick(QTableWidgetItem *);  //右边界面双击选择播放
	void systemIcon();              //设置系统图标
	void openWindows();             //系统图标打开界面函数
	void saveList();                //退出前保存函数
	void aboutApp();             //软件介绍函数
	void updateMess();          //检查更新函数
	void trayiconActivated(QSystemTrayIcon::ActivationReason);  //双击系统图标打开菜单函数
	void showLrc();  //系统托盘打开歌词
	void closeLrc();  //系统托盘关闭歌词
	void addFile();   //添加歌曲函数
	void setPosition(int);     //播放进度改变触发函数
	

private:
    Ui::MainWindow *ui;

	bool mouse_press;  //鼠标是否按下
	QPoint move_point; //鼠标移动距离
	bool is_play;    //播放暂停按钮的切换
	int song_amount;     //歌曲总数
	int song_index;      //当前播放歌曲偏移量
	QString song_name;   //当前播放歌曲名字
	int curindex = 0;          //滚动变量
	QString song_name_copy;    //歌曲拷贝
	QString play_model;  //播放模式
};

#endif // MAINWINDOW_H
