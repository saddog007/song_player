#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCodec>
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

public slots:
	void back_change(QString id);   //����ı�id�ź�

private slots:
	void WindowStyle();
	void minWindow();
	void closeWindow();
	void backPicshow();
	void setBk(QString picname);

	void mousePressEvent(QMouseEvent *event);  //ѹ��
	void mouseMoveEvent(QMouseEvent *event);   //�ƶ�
	void mouseReleaseEvent(QMouseEvent *event);  //�ͷ�

private:
    Ui::MainWindow *ui;

	bool mouse_press;  //����Ƿ���
	QPoint move_point; //����ƶ�����
};

#endif // MAINWINDOW_H
