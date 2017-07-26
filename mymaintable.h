#ifndef MYMAINTABLE_H
#define MYMAINTABLE_H

#include <QObject>
#include <QTableWidget>
#include <QModelIndex>
#include <QtMultimedia/QMediaPlaylist>


class Mymaintable : public QTableWidget
{
    Q_OBJECT
public:
    explicit Mymaintable(QWidget *parent = 0);
	Mymaintable(bool second);   //第二构造函数
	QUrl myCurrentMedia();      //播放的歌曲链接
	void mysetCurrentMeida(int);  //播放的歌曲偏移量
	void mysetNext();            //下一曲播放
	void mysetLast();             //上一曲播放

	QMediaPlaylist *plist;

	int nowindex;    //歌曲偏移量
	int nowmode;     //歌曲播放模式
private:
	bool mouse_press;    //开关鼠标控制
	int previousitem;
public slots:
	void listentered(int, int);
	void currentitemch(QTableWidgetItem*, QTableWidgetItem*);
	void mouseMoveEvent(QMouseEvent *event);
	void leaveEvent(QEvent *);
};

#endif // MYMAINTABLE_H
