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

	QString play_time;    //�����Ѿ����ŵ�ʱ��
	int list_opacity;     //�����б�͸����

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
	void songNameshow();       //������������ʾ����
	void mytableDoubleclick(QTableWidgetItem *);  //�ұ߽���˫��ѡ�񲥷�
	void mytableClicked(QTableWidgetItem*);        //����ѡ�����
	void systemIcon();              //����ϵͳͼ��
	void openWindows();             //ϵͳͼ��򿪽��溯��
	void saveList();                //�˳�ǰ���溯��
	void aboutApp();             //������ܺ���
	void updateMess();          //�����º���
	void trayiconActivated(QSystemTrayIcon::ActivationReason);  //˫��ϵͳͼ��򿪲˵�����
	void showLrc();  //ϵͳ���̴򿪸��
	void closeLrc();  //ϵͳ���̹رո��
	void addFile();   //��Ӹ�������
	void setPosition(int);     //���Ž��ȸı䴥������
	void positionChanged(qint64);   //��ȡ����ʱ������ʾ����ȡ���״̬��ƥ��
	void durationChanged(qint64);    //��ȡ��ǰ���ŵĽ���ʱ��
	void volChanged();              //������ָ�����
	void showSongnum();             //ʵʱ��ʾ������������
	void showTips();               //�޸���ʾ
	void lastSong();            //��һ��
	void nextSong();           //��һ��
	void showPlaylabel(QMediaContent);       //��ʾ���ڲ��ŵĸ���
	void readConfig();            //��ȡ�����ļ�
	void searchSong();           //���Ҹ�����ť
	void searchClose();          //�رղ���
	void searchItems(QString);        //���Һ���
	void setListopa(int);           //�����б�͸����
	void showContextmenu(const QPoint&);         //mytable�Ҽ������Ӧ����
	void showlrcMenu(const QPoint&);            //��ʽ����Ҽ�����
	void delItem();               //ɾ������
	void emptyList();             //����б�
	void songItem();         //��λ����
	void openList();         //���ļ�λ��
	void searchLrc();        //�������
	void copyLrc();          //�������
	void openLrc();          //�򿪸��
	void autoNextsong(QMediaPlayer::MediaStatus);           //һ��������һ������

private:
    Ui::MainWindow *ui;

	bool mouse_press;  //����Ƿ���
	QPoint move_point; //����ƶ�����
	bool is_play;    //������ͣ��ť���л�
	int song_amount;     //��������
	int song_index;      //��ǰ���Ÿ���ƫ����
	QString song_name;   //��ǰ���Ÿ�������
	int curindex = 0;          //��������
	QString song_name_copy;    //��������
	int play_model;  //����ģʽ
	bool vol_change;      //������ť�ı�  �������߻ָ�
	int vol;             //����������ť������ָ�
	QString back_pic;       //���汳��ͼƬ
};

#endif // MAINWINDOW_H
