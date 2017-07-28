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
#include <QSettings>
#include <string>
#include <QTextEdit>
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
	QTimer *songs_time;
	QTimer *song_tips;
	QStackedWidget *stack;
	Mymaintable *mytable;
	QSystemTrayIcon *trayicon;
	QLabel *addtips;
	QMenu *right_press;
	QTextEdit *lrcshowedit;

	QString play_time;    //歌曲已经播放的时间
	int list_opacity;     //保存列表透明度

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
	void mytableClicked(QTableWidgetItem*);        //单击选择歌曲
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
	void positionChanged(qint64);   //获取歌曲时长并显示，获取歌词状态并匹配
	void durationChanged(qint64);    //获取当前播放的进度时间
	void volChanged();              //静音与恢复函数
	void showSongnum();             //实时显示歌曲数量函数
	void showTips();               //无歌提示
	void lastSong();            //上一曲
	void nextSong();           //下一曲
	void showPlaylabel(QMediaContent);       //显示正在播放的歌曲
	void readConfig();            //读取配置文件
	void searchSong();           //查找歌曲按钮
	void searchClose();          //关闭查找
	void searchItems(QString);        //查找函数
	void setListopa(int);           //设置列表透明度
	void showContextmenu(const QPoint&);         //mytable右键点击响应函数
	void showlrcMenu(const QPoint&);            //歌词界面右键函数
	void delItem();               //删除歌曲
	void emptyList();             //清空列表
	void songItem();         //定位歌曲
	void openList();         //打开文件位置
	void searchLrc();        //搜索歌词
	void copyLrc();          //拷贝歌词
	void openLrc();          //打开歌词
	void autoNextsong(QMediaPlayer::MediaStatus);           //一曲播完下一曲函数

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
	int play_model;  //播放模式
	bool vol_change;      //音量按钮改变  静音或者恢复
	int vol;             //用于音量按钮静音与恢复
	QString back_pic;       //保存背景图片
};

#endif // MAINWINDOW_H
