#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	backpic = new BackPic(this);   //背景设置界面
	player = new QMediaPlayer;
	connect(ui->min_btn, SIGNAL(clicked()), this, SLOT(minWindow()));
	connect(ui->close_btn, SIGNAL(clicked()), this, SLOT(closeWindow()));
	connect(ui->back_btn, SIGNAL(clicked()), this, SLOT(backPicshow()));
	connect(backpic, SIGNAL(back_pic_id(QString)), this, SLOT(backChange(QString)));
	connect(ui->play_or_suspend, SIGNAL(clicked()), this, SLOT(playOrsuspend()));
	connect(ui->volume_progress_bar, SIGNAL(valueChanged(int)), this, SLOT(volPicchange(int)));  //音量图片改变
	connect(ui->volume_progress_bar, SIGNAL(sliderMoved(int)), this, SLOT(volPicchange(int)));
	connect(ui->volume_progress_bar, SIGNAL(valueChanged(int)), player, SLOT(setVolume(int)));  //传递给播放器
	connect(ui->volume_progress_bar, SIGNAL(sliderMoved(int)), player, SLOT(setVolume(int)));
	connect(ui->play_model, SIGNAL(currentIndexChanged(int)), this, SLOT(playModelchange(int)));     //不同的选项执行不通的事件

	WindowStyle();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::WindowStyle()
{
	//设置主界面初始属性

	////设置无边框
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setMouseTracking(true);

	////设置可以拖动
	this->setAcceptDrops(true);

	////设置窗体为固定大小
	this->setFixedSize(this->width(),700);

	//this->setAttribute(Qt::WA_TranslucentBackground, true);  //设置主窗口透明

	//设置背景默认图片
	QString backpic = "background1";
	setBk(backpic);

	//设置播放方式下拉框
	ui->play_model->setView(new QListView());
	ui->play_model->addItem(QStringLiteral("顺序播放"));
	ui->play_model->addItem(QStringLiteral("单曲循环"));
	ui->play_model->addItem(QStringLiteral("随机播放"));

	ui->play_model->setItemText(0, QStringLiteral("顺序播放"));
	ui->play_model->setItemText(1, QStringLiteral("单曲循环"));
	ui->play_model->setItemText(2, QStringLiteral("随机播放"));

	//设定进度条点击即到
	ui->play_progress_bar->installEventFilter(this);   //播放进度
	ui->volume_progress_bar->installEventFilter(this);   //声音进度

	//设置初始播放按钮为播放
	is_play = false;
	//ui->play_or_suspend->setIcon(QIcon(tr(":/images/image/play_hover.png")));
	ui->play_or_suspend->setStyleSheet("QToolButton{border-image: url(:/images/image/play_hover.png);}QToolTip{background-color:white}");
	ui->play_or_suspend->setToolTip(QStringLiteral("播放"));

	//设置播放 暂停 上一曲  下一曲按钮提示
	ui->last_song->setStyleSheet("QToolButton{border-image: url(:/images/image/last.png);}QToolTip{background-color:white}");
	ui->next_song->setStyleSheet("QToolButton{border-image: url(:/images/image/next.png);}QToolTip{background-color:white}");

	//界面渐变出现
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
		QPoint move_pos = event->globalPos();    //鼠标相对屏幕的位置
		this->move(move_pos - move_point);   //移动主窗体
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
	//界面淡出关闭
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
		backpic->setGeometry(this->geometry().x() + 20, this->geometry().y()+50, 290, 380);  //设置界面位置
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
		ui->play_or_suspend->setToolTip(QStringLiteral("播放"));
		is_play = false;
	}
	else
	{
		ui->play_or_suspend->setStyleSheet("QToolButton{border-image: url(:/images/image/pause_hover.png);}QToolTip{background-color:white}");
		ui->play_or_suspend->setToolTip(QStringLiteral("暂停"));
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
	QToolTip::showText(QCursor::pos(), QString::number(vol));     //通过vol的slidetmove得到这个值用于传值给tooltip实时显示
}

void MainWindow::playModelchange(int index)
{
	qDebug() << index;
}