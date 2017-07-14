#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	connect(ui->min_btn, SIGNAL(clicked()), this, SLOT(minWindow()));
	connect(ui->close_btn, SIGNAL(clicked()), this, SLOT(closeWindow()));
	connect(ui->back_btn, SIGNAL(clicked()), this, SLOT(backPicshow()));
	WindowStyle();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::WindowStyle()
{
	//�����������ʼ����

	////�����ޱ߿�
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setMouseTracking(true);

	////���ÿ����϶�
	this->setAcceptDrops(true);

	////���ô���Ϊ�̶���С
	this->setFixedSize(this->width(),700);

	//���ñ���Ĭ��ͼƬ
	QString backpic = "background1";
	setBk(backpic);

	//���潥�����
	QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
	animation->setDuration(1000);
	animation->setStartValue(0);
	animation->setEndValue(1);
	animation->start();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		mouse_press = true;
		move_point = event->pos();
	}
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
	if (mouse_press)
	{
		QPoint move_pos = event->globalPos();    //��������Ļ��λ��
		this->move(move_pos - move_point);   //�ƶ�������
	}
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
	mouse_press = false;
}

void MainWindow::minWindow()
{
	this->showMinimized();
}

void MainWindow::closeWindow()
{
	//���浭���ر�
	QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
	animation->setDuration(1000);
	animation->setStartValue(1);
	animation->setEndValue(0);
	animation->start();
	connect(animation, SIGNAL(finished()), this, SLOT(close()));
}

void MainWindow::backPicshow()
{

}
void MainWindow::setBk(QString picname)
{
	QPalette p;
	p.setBrush(QPalette::Background, QBrush(QPixmap(":/images/image/" + picname + ".png")));
	setPalette(p);
}

