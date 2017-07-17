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
	void back_change(QString id);   //界面改变id信号

private slots:
	void WindowStyle();
	void minWindow();
	void closeWindow();
	void backPicshow();
	void setBk(QString picname);

	void mousePressEvent(QMouseEvent *event);  //压下
	void mouseMoveEvent(QMouseEvent *event);   //移动
	void mouseReleaseEvent(QMouseEvent *event);  //释放

private:
    Ui::MainWindow *ui;

	bool mouse_press;  //鼠标是否按下
	QPoint move_point; //鼠标移动距离
};

#endif // MAINWINDOW_H
