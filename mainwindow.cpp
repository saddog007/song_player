#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	backpic = new BackPic(this);   //�������ý���
	player = new QMediaPlayer;
	connect(ui->min_btn, SIGNAL(clicked()), this, SLOT(minWindow()));
	connect(ui->close_btn, SIGNAL(clicked()), this, SLOT(closeWindow()));
	connect(ui->back_btn, SIGNAL(clicked()), this, SLOT(backPicshow()));
	connect(backpic, SIGNAL(back_pic_id(QString)), this, SLOT(backChange(QString)));
	connect(ui->play_or_suspend, SIGNAL(clicked()), this, SLOT(playOrsuspend()));
	connect(ui->volume_progress_bar, SIGNAL(valueChanged(int)), this, SLOT(volPicchange(int)));  //����ͼƬ�ı�
	connect(ui->volume_progress_bar, SIGNAL(sliderMoved(int)), this, SLOT(volPicchange(int)));
	connect(ui->volume_progress_bar, SIGNAL(valueChanged(int)), player, SLOT(setVolume(int)));  //���ݸ�������
	connect(ui->volume_progress_bar, SIGNAL(sliderMoved(int)), player, SLOT(setVolume(int)));
	connect(ui->play_model, SIGNAL(currentIndexChanged(int)), this, SLOT(playModelchange(int)));     //��ͬ��ѡ��ִ�в�ͨ���¼�

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

	//this->setAttribute(Qt::WA_TranslucentBackground, true);  //����������͸��

	//���ñ���Ĭ��ͼƬ
	QString backpic = "background1";
	setBk(backpic);

	//���ò��ŷ�ʽ������
	ui->play_model->setView(new QListView());
	ui->play_model->addItem(QStringLiteral("˳�򲥷�"));
	ui->play_model->addItem(QStringLiteral("����ѭ��"));
	ui->play_model->addItem(QStringLiteral("�������"));

	ui->play_model->setItemText(0, QStringLiteral("˳�򲥷�"));
	ui->play_model->setItemText(1, QStringLiteral("����ѭ��"));
	ui->play_model->setItemText(2, QStringLiteral("�������"));

	//�趨�������������
	ui->play_progress_bar->installEventFilter(this);   //���Ž���
	ui->volume_progress_bar->installEventFilter(this);   //��������

	//���ó�ʼ���Ű�ťΪ����
	is_play = false;
	//ui->play_or_suspend->setIcon(QIcon(tr(":/images/image/play_hover.png")));
	ui->play_or_suspend->setStyleSheet("QToolButton{border-image: url(:/images/image/play_hover.png);}QToolTip{background-color:white}");
	ui->play_or_suspend->setToolTip(QStringLiteral("����"));

	//���ò��� ��ͣ ��һ��  ��һ����ť��ʾ
	ui->last_song->setStyleSheet("QToolButton{border-image: url(:/images/image/last.png);}QToolTip{background-color:white}");
	ui->next_song->setStyleSheet("QToolButton{border-image: url(:/images/image/next.png);}QToolTip{background-color:white}");

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
	if (backpic->isHidden())
	{
		backpic->show();
		backpic->setGeometry(this->geometry().x() + 20, this->geometry().y()+50, 290, 380);  //���ý���λ��
	}
	else
	{
		backpic->hide();
	}
}

void MainWindow::backChange(QString id)
{
	QString backpicname = QString("background") + id;
	setBk(backpicname);
}

void MainWindow::setBk(QString picname)
{
	QPalette p;
	p.setBrush(QPalette::Background, QBrush(QPixmap(":/images/image/" + picname + ".png")));
	setPalette(p);
}

void MainWindow::playOrsuspend()
{
	if (is_play)
	{
		ui->play_or_suspend->setStyleSheet("QToolButton{border-image: url(:/images/image/play_hover.png);}QToolTip{background-color:white}");
		ui->play_or_suspend->setToolTip(QStringLiteral("����"));
		is_play = false;
	}
	else
	{
		ui->play_or_suspend->setStyleSheet("QToolButton{border-image: url(:/images/image/pause_hover.png);}QToolTip{background-color:white}");
		ui->play_or_suspend->setToolTip(QStringLiteral("��ͣ"));
		is_play = true;
	}
}

void MainWindow::volPicchange(int vol)
{
	if (vol == 0)
	{
		ui->volume_label->setStyleSheet("QLabel{background-color:transparent;}QLabel{border-image:url(:/images/image/volume_shut.png);}");
	}
	else if (vol < 70)
	{
		ui->volume_label->setStyleSheet("QLabel{background-color:transparent;}QLabel{border-image:url(:/images/image/volume_step.png);}");
	}
	else
	{
		ui->volume_label->setStyleSheet("QLabel{background-color:transparent;}QLabel{border-image:url(:/images/image/volume.png);}");
	}
	QToolTip::showText(QCursor::pos(), QString::number(vol));     //ͨ��vol��slidetmove�õ����ֵ���ڴ�ֵ��tooltipʵʱ��ʾ
}

void MainWindow::playModelchange(int index)
{
	qDebug() << index;
}