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
	Mymaintable(bool second);   //�ڶ����캯��
	QUrl myCurrentMedia();      //���ŵĸ�������
	void mysetCurrentMeida(int);  //���ŵĸ���ƫ����
	void mysetNext();            //��һ������
	void mysetLast();             //��һ������

	QMediaPlaylist *plist;

	int nowindex;    //����ƫ����
	int nowmode;     //��������ģʽ
private:
	bool mouse_press;    //����������
	int previousitem;
public slots:
	void listentered(int, int);
	void currentitemch(QTableWidgetItem*, QTableWidgetItem*);
	void mouseMoveEvent(QMouseEvent *event);
	void leaveEvent(QEvent *);
};

#endif // MYMAINTABLE_H
