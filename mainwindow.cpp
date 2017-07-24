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
	m_timer = new QTimer(this);    //设置实现滚动效果的定时器

	stack = new QStackedWidget(this);
	mytable = new Mymaintable(stack);   //添加widget
	stack->addWidget(mytable);        //添加tablewidget主界面
	stack->setGeometry(90, 192, 240, 451);

	ui->widget_search->raise();   //查找界面位于最上层
	ui->widget_search->hide();    //查找界面隐藏


	QDir dir0("G://saddog//song_lyrics");   //创建歌词文件夹
	if (!dir0.exists())
	{
		dir0.mkdir("G://saddog//song_lyrics");
	}
	QDir dir1("G://saddog//song_list");   //创建歌曲文件夹
	if (!dir1.exists())
	{
		dir1.mkdir("G://saddog//song_list");
	}
	QDir dir2("G://saddog//song_pic");   //创建歌手相片文件夹
	if (!dir2.exists())
	{
		dir2.mkdir("G://saddog//song_pic");
	}

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
	connect(m_timer, SIGNAL(timeout()), this, SLOT(songNameshow()));                  //滚动显示歌曲名
	connect(mytable, SIGNAL(itemDoubleClicked(QTableWidgetItem *)), this, SLOT(mytableDoubleclick(QTableWidgetItem*)));   //界面双击播放
	connect(ui->add_btn, SIGNAL(clicked()), this, SLOT(addFile()));        //添加歌曲函数
	connect(ui->play_progress_bar, SIGNAL(sliderMoved(int)), this, SLOT(setPosition(int)));   //播放进度改变函数

	WindowStyle();  //窗口部件设置
	systemIcon();   //系统图标设置
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

	//开始歌曲滚动显示
	song_name = QStringLiteral("欢迎来到saddog的播放器!");
	m_timer->start(100);

	//设置播放进度条点击slider即到
	ui->play_progress_bar->installEventFilter(this);
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
	if (index == 0)
	{
		play_model = "play_order";
	}
	else if (index == 1)
	{
		play_model = "single_cycle";
	}
	else
	{
		play_model = "random_play";
	}
	qDebug() << play_model;
	
	mytable->nowmode = index;
}

void MainWindow::songNameshow()
{
	//static int npos = 0;
	//if (npos > song_name.length())
	//{
	//	npos = 0;
	//}
	//ui->song_show->setText(song_name.mid(npos));
	//npos++;
	int isize = song_name.size();
	if (curindex < 0)
	{
		curindex = isize;
	}
	song_name_copy = song_name;
	if (song_name.size() < 22)
	{
		for (int i = 0; i < 25 ; ++i)
		{
			song_name_copy = " " + song_name_copy;
		}
	}
	ui->song_show->setText(song_name_copy.mid(curindex--));
}

void MainWindow::mytableDoubleclick(QTableWidgetItem *item)
{
	//nowplaylist = 1;   //用于区分正在播放的列表

	mytable->mysetCurrentMeida(item->row());
	player->setMedia(mytable->myCurrentMedia());
	player->play();
}

void MainWindow::systemIcon()
{
	//显示系统图标
	trayicon = new QSystemTrayIcon(this);
	trayicon->setIcon(QIcon(tr(":/images/image/sysicon11.ico")));
	trayicon->show(); 

	//设置系统图标选项
	QAction *aboutapp = new QAction(QStringLiteral("  关于程序"),this);
	QAction *quitapp = new QAction(QIcon(QPixmap(":/images/image/MD-brightness.png")), QStringLiteral("  退出"), this);
	QAction *openapp = new QAction(QStringLiteral("  打开主界面"), this);
	QAction *updateapp = new QAction(QStringLiteral("  检查版本"), this);
	QAction *showlrc = new QAction(QStringLiteral("  打开歌词"), this);
	QAction *closelrc = new QAction(QStringLiteral("  关闭歌词"), this);
	QWidgetAction *playmenuaction = new QWidgetAction(this);
	QPushButton *play_button = new QPushButton(this);
	QPushButton *next_button = new QPushButton(this);
	QPushButton *last_button = new QPushButton(this);
	QLabel *music_name_label = new QLabel(this);
	QWidget *play_widget = new QWidget(this);

	play_button->setCursor(QCursor(Qt::PointingHandCursor));  //设置鼠标样式为手型
	next_button->setCursor(QCursor(Qt::PointingHandCursor));
	last_button->setCursor(QCursor(Qt::PointingHandCursor));

	play_button->setFlat(true);         //设置点下有效果 放上无突出
	last_button->setFlat(true);
	next_button->setFlat(true);

	play_button->setStyleSheet("QPushButton{border-image:url(:/images/image/menuplay.png);}");
	next_button->setStyleSheet("QPushButton{border-image:url(:/images/image/menuforward.png);}");
	last_button->setStyleSheet("QPushButton{border-image:url(:/images/image/menuback.png);}");
	play_button->setFixedSize(26, 26);
	last_button->setFixedSize(21,21);
	next_button->setFixedSize(21,21);

	QHBoxLayout *layout = new QHBoxLayout();    //布局
	layout->addWidget(last_button);     //注意顺序
	layout->addWidget(play_button);
	layout->addWidget(next_button);
	layout->setSpacing(0);                       //设置部件距离
	layout->setContentsMargins(10, 0, 10, 0);    //设置左上右下距离
	QVBoxLayout *layout2 = new QVBoxLayout();
	layout2->addLayout(layout);
	layout2->addWidget(music_name_label, 0, Qt::AlignCenter);     //居中对齐
	layout2->setSpacing(2);
	layout2->setContentsMargins(0, 5, 0, 0);
	music_name_label->setText(QStringLiteral("音乐播放器"));
	music_name_label->setEnabled(false);    //设置不可点击
	play_widget->setLayout(layout2);
	play_widget->setFixedSize(140, 60);
	playmenuaction->setDefaultWidget(play_widget);

	QMenu *trayiconmenu = new QMenu(this);   //连接添加各个按钮
	trayiconmenu->addAction(playmenuaction);
	trayiconmenu->addSeparator();        //添加分隔符
	trayiconmenu->addAction(openapp);
	trayiconmenu->addAction(showlrc);
	trayiconmenu->addAction(closelrc);
	trayiconmenu->addSeparator();
	trayiconmenu->addAction(aboutapp);
	trayiconmenu->addAction(updateapp);
	trayiconmenu->addSeparator();
	trayiconmenu->addAction(quitapp);
	trayiconmenu->setContentsMargins(1, 1, 1, 5);
	trayicon->setContextMenu(trayiconmenu);
	trayicon->setToolTip(QStringLiteral("欢迎使用saddog的音乐播放器"));

	connect(openapp, SIGNAL(triggered(bool)), this, SLOT(openWindows()));           //打开主界面
	connect(quitapp, SIGNAL(triggered()), this, SLOT(saveList()));     //退出前保存列表
	connect(quitapp, SIGNAL(triggered()), qApp, SLOT(quit()));         //退出程序
	connect(aboutapp, SIGNAL(triggered()), this, SLOT(aboutApp()));     //软件介绍
	connect(updateapp, SIGNAL(triggered()), this, SLOT(updateMess()));   //检查更新
	//双击系统图标打开菜单
	connect(trayicon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this, SLOT(trayiconActivated(QSystemTrayIcon::ActivationReason)));
	
	connect(showlrc, SIGNAL(triggered()), this, SLOT(showLrc()));   //打开歌词
	connect(closelrc, SIGNAL(triggered()), this, SLOT(closeLrc()));  //关闭歌词
	//连接函数和界面播放函数
	connect(play_button, SIGNAL(clicked(bool)), ui->play_or_suspend, SIGNAL(clicked(bool)));
	connect(last_button ,SIGNAL(clicked(bool)), ui->last_song, SIGNAL(clicked(bool)));
	connect(next_button,SIGNAL(clicked(bool)), ui->next_song, SIGNAL(clicked(bool)));   
}

void MainWindow::openWindows()
{
	this->showNormal();
	this->activateWindow();
}

void MainWindow::saveList()
{
	QFile file("plist.m3u");
	file.resize(0);   //从新写入
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	mytable->plist->save(&file, "m3u");
	file.close();
}

void MainWindow::aboutApp()
{
	this->showNormal();
	if (QMessageBox::Ok == QMessageBox::information(this, QStringLiteral("关于saddog的音乐播放器"), QStringLiteral("本程序仅供学习使用\n实现的功能有:\n1.程序列表自动保存\n2.drag和drop事件，即托动文件到程序即可添加至播放列表\n3.网络自动获取歌词文件,并保存至D://song_lyrics\n4.多线程处理歌词"),QMessageBox::Ok));
	{
		return;
	}
}

void MainWindow::updateMess()
{
	if (QMessageBox::Ok == QMessageBox::information(this, QStringLiteral("检查更新"), QStringLiteral("已是最新版,敬请期待后续版本!"), QMessageBox::Ok));
	{
		return;
	}
}
void MainWindow::trayiconActivated(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason)
	{
		case QSystemTrayIcon::Trigger:
		case QSystemTrayIcon::DoubleClick:
			this->showNormal();
			this->setWindowState(Qt::WindowActive);   //窗口有最小化激活
			this->activateWindow();       //激活窗口在最上层
			this->raise();
			break;
		default:
			break;
	}
}

void MainWindow::showLrc()
{
	if (ui->lyrics_check->checkState() == Qt::Checked)
	{
		return;
	}
	ui->lyrics_check->click();
}

void MainWindow::closeLrc()
{
	if (ui->lyrics_check->checkState() == Qt::Unchecked)
	{
		return;
	}
	ui->lyrics_check->click();
}

void MainWindow::addFile()
{
	static QString initfilename = "G:/";  //设置默认路径
	QStringList files = QFileDialog::getOpenFileNames(this, QStringLiteral("选择文件"), initfilename, tr("*.mp3"));  //获取打开文件路径
	if (files.isEmpty())
	{
		return;
	}
	int i = 0;
	while (i < files.count())
	{
		QString path = QDir::toNativeSeparators(files.at(i));   //转换为本地格式  可兼容系统
		if (!path.isEmpty())
		{
			mytable->plist->addMedia(QMediaContent(QUrl::fromLocalFile(path)));      //添加到列表
		}
		QFileInfo info(files[i]);
		QString m_name = info.completeBaseName();
		QString songname;
		QString singer;
		if (m_name.contains("-"))     //如果遍历时包含-这个字符
		{
			QStringList list = m_name.split("-");
			songname = list.at(1);
			singer = list.at(0);
		}
		else
		{
			songname = m_name;
			singer = " ";
		}
		int rowcount = mytable->rowCount();
		mytable->insertRow(rowcount);
		mytable->setItem(rowcount, 0, new QTableWidgetItem(songname));
		mytable->setItem(rowcount, 1, new QTableWidgetItem(singer));
		mytable->item(rowcount, 1)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		i++;
	}
	ui->listWidget->setCurrentRow(1);   //跳回播放列表
}

void MainWindow::setPosition(int pos)
{
	player->setPosition(pos);
}