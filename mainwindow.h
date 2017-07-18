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
	void backChange(QString id);   //����ı�id�ź�
	void volPicchange(int vol);   //����ͼƬ�ı�

private slots:
	void WindowStyle();
	void minWindow();
	void closeWindow();
	void backPicshow();
	void setBk(QString picname);   //���ñ�������
	void playOrsuspend();      //������ͣ����
	void mousePressEvent(QMouseEvent *event);  //ѹ��
	void mouseMoveEvent(QMouseEvent *event);   //�ƶ�
	void mouseReleaseEvent(QMouseEvent *event);  //�ͷ�
	void playModelchange(int);            //����ģʽѡ��
	

private:
    Ui::MainWindow *ui;

	bool mouse_press;  //����Ƿ���
	QPoint move_point; //����ƶ�����
	bool is_play;    //������ͣ��ť���л�
};

#endif // MAINWINDOW_H
