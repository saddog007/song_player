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
	QString play_model;  //����ģʽ
};

#endif // MAINWINDOW_H
