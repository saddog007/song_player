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
	songs_time = new QTimer(this);   //歌曲数目定时器
	song_tips = new QTimer(this);     //列表歌曲提示信息及无歌设置

	//添加歌词显示界面
	lrcshowedit = new QTextEdit(this);
	lrcshowedit->setStyleSheet("QTextEdit{background:transparent}");
	lrcshowedit->setFrameStyle(QFrame::NoFrame);
	lrcshowedit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	lrcshowedit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	lrcshowedit->setReadOnly(true);
	lrcshowedit->setFont(QFont("微软雅黑", 10, QFont::Thin));
	lrcshowedit->setTextColor(Qt::white);
	lrcshowedit->setContextMenuPolicy(Qt::CustomContextMenu);
	lrcshowedit->setFocusPolicy(Qt::NoFocus);
	lrcshowedit->viewport()->installEventFilter(this);
	lrcshowedit->viewport()->setCursor(QCursor(QPixmap(":/images/image/cursor_hand.png")));
	
	stack = new QStackedWidget(this);
	mytable = new Mymaintable(stack);   //添加widget
	stack->addWidget(lrcshowedit);     //添加歌词显示界面
	stack->addWidget(mytable);        //添加tablewidget主界面
	stack->setGeometry(90, 192, 240, 431);

	mytable->setContextMenuPolicy(Qt::CustomContextMenu);        //右键菜单 

	//列表无歌曲提示信息
	addtips = new QLabel(QStringLiteral("  点击按钮添加\n或拖动文件到界面"), mytable);
	addtips->setGeometry(50, 192, 240, 50);
	addtips->setStyleSheet("color:white;font-size:18px;font-family:微软雅黑");  

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
	QFile fileconfig("config.ini");              //创建退出保存设置文件
	if (!fileconfig.exists())
	{
		if (!fileconfig.open(QFile::WriteOnly | QFile::Text))
		{
			return;
		}
		fileconfig.close();
	}

	connect(ui->min_btn, SIGNAL(clicked()), this, SLOT(minWindow()));
	connect(ui->close_btn, SIGNAL(clicked()), this, SLOT(closeWindow()));
	connect(ui->back_btn, SIGNAL(clicked()), this, SLOT(backPicshow()));
	connect(backpic, SIGNAL(back_pic_id(QString)), this, SLOT(backChange(QString)));
	connect(ui->play_or_suspend, SIGNAL(clicked()), this, SLOT(playOrsuspend()));
	connect(ui->last_song, SIGNAL(clicked()), this, SLOT(lastSong()));
	connect(ui->next_song, SIGNAL(clicked()), this, SLOT(nextSong()));
	connect(ui->volume_progress_bar, SIGNAL(valueChanged(int)), this, SLOT(volPicchange(int)));  //音量图片改变
	connect(ui->volume_progress_bar, SIGNAL(sliderMoved(int)), this, SLOT(volPicchange(int)));
	connect(ui->volume_progress_bar, SIGNAL(valueChanged(int)), player, SLOT(setVolume(int)));  //传递给播放器
	connect(ui->volume_progress_bar, SIGNAL(sliderMoved(int)), player, SLOT(setVolume(int)));
	connect(ui->play_model, SIGNAL(currentIndexChanged(int)), this, SLOT(playModelchange(int)));     //不同的选项执行不通的事件
	connect(m_timer, SIGNAL(timeout()), this, SLOT(songNameshow()));                  //滚动显示歌曲名
	connect(mytable, SIGNAL(itemDoubleClicked(QTableWidgetItem *)), this, SLOT(mytableDoubleclick(QTableWidgetItem*)));   //界面双击播放
	connect(mytable, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(mytableClicked(QTableWidgetItem*)));            //单击触发函数
	connect(ui->add_btn, SIGNAL(clicked()), this, SLOT(addFile()));        //添加歌曲函数
	connect(ui->play_progress_bar, SIGNAL(sliderMoved(int)), this, SLOT(setPosition(int)));   //播放进度改变函数
	connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));    //获取歌曲时长和歌曲匹配
	connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));    //获取歌曲当前播放时间
	connect(ui->volume_label, SIGNAL(clicked()), this, SLOT(volChanged()));     //设置音量是否静音
	connect(songs_time, SIGNAL(timeout()), this, SLOT(showSongnum()));         //实时显示歌曲数量
	connect(song_tips, SIGNAL(timeout()), this, SLOT(showTips()));             //无歌提示
	connect(player, SIGNAL(currentMediaChanged(QMediaContent)), this, SLOT(showPlaylabel(QMediaContent)));  //显示正在播放的歌曲
	connect(ui->search_btn, SIGNAL(clicked()), this, SLOT(searchSong()));      //查找歌曲
	connect(ui->search_close, SIGNAL(clicked()), this, SLOT(searchClose()));    //关闭查找
	connect(ui->search_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(searchItems(QString)));  //查找函数
	connect(backpic, SIGNAL(list_bk_trans(int)), this, SLOT(setListopa(int)));         //设置列表透明度
	connect(mytable, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextmenu(const QPoint&))); //mytable右键点击响应函数
	connect(lrcshowedit, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showlrcMenu(const QPoint&))); //歌词界面右键函数
	connect(ui->listWidget, SIGNAL(currentRowChanged(int)), stack, SLOT(setCurrentIndex(int)));           //左边选择更换右边界面
	connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(autoNextsong(QMediaPlayer::MediaStatus)));   //一曲结束自动下一曲

	systemIcon();   //系统图标设置
	WindowStyle();  //窗口部件设置
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

	//设置音量按钮初始化状态
	vol_change = true;

	//歌曲数量更新开始
	songs_time->start(1000);
	song_tips->start(200);

	ui->widget_search->raise();   //查找界面位于最上层
	ui->widget_search->hide();    //查找界面隐藏

	//读取配置文件
	readConfig();

	//初始设置在本地列表界面
	ui->listWidget->setCurrentRow(1);
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
	saveList();            //退出前保存
	ui->close_btn->setEnabled(false);     //禁止连续点击
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
	back_pic = QString("background") + id;
	setBk(back_pic);
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
		is_play = !is_play;
		if (player->state() == QMediaPlayer::PlayingState)  //正在播放
		{
			player->pause();
		}
	}
	else
	{
		ui->play_or_suspend->setStyleSheet("QToolButton{border-image: url(:/images/image/pause_hover.png);}QToolTip{background-color:white}");
		ui->play_or_suspend->setToolTip(QStringLiteral("暂停"));
		is_play = !is_play;
		//if (player->isAudioAvailable() == true)
		//{
		//	player->play();
		//}
		QTableWidgetItem *item = mytable->item(mytable->nowindex, 0);
		mytable->mysetCurrentMeida(item->row());
		player->setMedia(mytable->myCurrentMedia());
		player->play();
	}
}

void MainWindow::lastSong()
{
	if (player->isAudioAvailable() == true)           //有音乐输出
	{
		mytable->mysetLast();
		player->setMedia(mytable->myCurrentMedia());
	}
	player->play();
}

void MainWindow::nextSong()
{
	if (player->isAudioAvailable() == true)           //有音乐输出
	{
		mytable->mysetNext();
		player->setMedia(mytable->myCurrentMedia());
	}
	player->play();
}

void MainWindow::volPicchange(int vol)
{
	if (vol == 0)
	{
		ui->volume_label->setStyleSheet("QToolButton{background-color:transparent;}QToolButton{border-image:url(:/images/image/volume_shut.png);}");
	}
	else if (vol < 70)
	{
		ui->volume_label->setStyleSheet("QToolButton{background-color:transparent;}QToolButton{border-image:url(:/images/image/volume_step.png);}");
	}
	else
	{
		ui->volume_label->setStyleSheet("QToolButton{background-color:transparent;}QToolButton{border-image:url(:/images/image/volume.png);}");
	}
	QToolTip::showText(QCursor::pos(), QString::number(vol));     //通过vol的slidetmove得到这个值用于传值给tooltip实时显示
}

void MainWindow::playModelchange(int index)
{
	play_model = index;
	mytable->nowmode = index;
}

void MainWindow::songNameshow()
{
	int isize = song_name.size();
	if (curindex < 0)
	{
		curindex = isize;
	}
	song_name_copy = song_name;
	if (song_name.size() < 22)
	{
		for (int i = 0; i < 36-song_name.size() ; ++i)
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
	player->setVolume(0);           //初始播放无声音
	ui->play_or_suspend->setStyleSheet("QToolButton{border-image: url(:/images/image/pause_hover.png);}QToolTip{background-color:white}");
	ui->play_or_suspend->setToolTip(QStringLiteral("暂停"));    //设置播放按钮改变
	is_play = !is_play;

	player->play();
}

void MainWindow::mytableClicked(QTableWidgetItem*item)
{
	mytable->mysetCurrentMeida(item->row());
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
    
	QSettings *m_set_ini = new QSettings("config.ini", QSettings::IniFormat);
	m_set_ini->setValue("/background/backpic", back_pic);       //背景
	m_set_ini->setValue("/volume/vol", player->volume());       //音量
	m_set_ini->setValue("/playmodel/index",play_model);          //播放模式
	m_set_ini->setValue("/listopa/value", list_opacity);          //列表透明度   
	delete m_set_ini;
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
	static QString initfilename = "G:/saddog/song_list/";  //设置默认路径
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

void MainWindow::searchSong()
{
	if (ui->widget_search->isHidden())
	{
		ui->widget_search->show();
		ui->listWidget->setCurrentRow(1);
	}
	else
	{
		ui->widget_search->hide();
		ui->search_lineEdit->clear();
		ui->listWidget->setCurrentRow(1);
	}
}

void MainWindow::searchItems(QString search_word)
{
	int count = mytable->rowCount();
	for (int i = 0; i < count; i++)
	{
		mytable->setRowHeight(i, 0);
		if (mytable->item(i, 0)->text().contains(search_word) || mytable->item(i, 1)->text().contains(search_word))
		{
			mytable->setRowHeight(i, 30);
			continue;
		}
		if (search_word == "")
		{
			mytable->setRowHeight(i, 30);
		}
	}
}

void MainWindow::searchClose()
{
	ui->search_lineEdit->setText("");
	QTableWidgetItem *item = mytable->item(mytable->nowindex, 0);
	mytable->setCurrentItem(item);
	mytable->scrollToItem(item);
	ui->widget_search->hide();
}

void MainWindow::setPosition(int pos)
{
	player->setPosition(pos);
}

void MainWindow::positionChanged(qint64 pos)
{
	ui->play_progress_bar->setValue(pos);    //进度条初始化
	QTime currentTime(0, (pos / 60000) % 60, (pos / 1000) % 60);     //设置实时改变播放信息
	QString format = "mm:ss";
	currentTime.toString(format);
	QString todisplay;
	todisplay = currentTime.toString(format);
	ui->time_show->setText(todisplay + "/" + play_time);
	//qint64 total_time_value = player->duration();                //直接获取该音频文件总时长  单位为毫秒
	//...................

}

void MainWindow::durationChanged(qint64 pos)
{
	ui->play_progress_bar->setRange(0, pos);      //设置值的取值范围
	QTime total_time(0, (pos / 60000) % 60, (pos / 1000) % 60);
	QString format = "mm:ss";
	total_time.toString(format);
	play_time = total_time.toString(format);
}

void MainWindow::volChanged()
{
	if (vol_change == true)
	{
		vol = player->volume();
		ui->volume_label->setStyleSheet("QToolButton{ background - color:transparent; }QToolButton{ border - image:url(: / images / image / volume_shut.png); }");
		ui->volume_progress_bar->setValue(0);
	}
	else
	{
		ui->volume_label->setStyleSheet("QToolButton{ background - color:transparent; }QToolButton{ border - image:url(: / images / image / volume.png); }");
		player->setVolume(vol);
		ui->volume_progress_bar->setValue(vol);
	}
	vol_change = !vol_change;
}

void MainWindow::showSongnum()
{
	//检查歌曲数目
	int songcount = mytable->rowCount();
	ui->label_4->setText(QStringLiteral("歌曲数:") + QString::number(songcount));   //更新歌曲数
}

void MainWindow::showTips()
{
	if (!player->isAudioAvailable())              //不能获取音乐
	{
		ui->play_progress_bar->setMaximum(0);
	}
	//显示提示信息
	if (mytable->rowCount() == 0)
	{
		addtips->show();
	}
	else
	{
		addtips->hide();
	}
}

void MainWindow::showPlaylabel(QMediaContent media)
{
	QFile file(media.canonicalUrl().toString());
	QFileInfo info(file);
	QString name = info.baseName();
	song_name = name;
}

void MainWindow::readConfig()
{
	//读取config.ini及plist.m3u进行设置
	QSettings *read_ini = new QSettings("config.ini", QSettings::IniFormat);
	back_pic = read_ini->value("/background/backpic").toString();
	if (back_pic.split("g")[0] != "back")
	{
		back_pic = "background1";
	}
	setBk(back_pic);
	int vol_old = read_ini->value("/volume/vol").toInt();
	ui->volume_progress_bar->setValue(vol_old);
	int play_old = read_ini->value("/playmodel/index").toInt();
	int list_opa = read_ini->value("/listopa/value").toInt();
	setListopa(list_opa);
	backpic->setSlidervalue(list_opa);
	delete read_ini;

	QFile file1("plist.m3u");
	if (file1.exists())  //文件存在
	{
		file1.open(QIODevice::ReadOnly | QIODevice::Text);
		mytable->plist->load(&file1, "m3u");
	}
	file1.close();
	QFile file2("plist.m3u");
	file2.open(QIODevice::ReadOnly | QIODevice::Text);
	int songcount = mytable->plist->mediaCount();
	QTextStream textinput(&file2);
	int i = 0;
	while (i < songcount)
	{
		QString songurl = textinput.readLine();
		QFile *file = new QFile(songurl);
		QFileInfo info(*file);
		QString barename = info.baseName();
		QString songname;
		QString singer;
		if (!barename.contains("-"))
		{
			songname = barename;
			singer = " ";
		}
		else
		{
			QStringList songlist = barename.split("-");
			singer = songlist.at(0);
			songname = songlist.at(1);
		}
		int rowcount = mytable->rowCount();
		mytable->insertRow(rowcount);
		mytable->setItem(rowcount, 0, new QTableWidgetItem(songname));
		mytable->setItem(rowcount, 1, new QTableWidgetItem(singer));
		mytable->item(rowcount, 1)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		i++;
	}
	file2.close();
}

void MainWindow::setListopa(int value)
{
	list_opacity = value;        //保存列表透明度
	QString style = "QTableWidget{background-color:rgb(255, 255, 255," + QString::number(value)+");}"
		"QTableWidget{selection-background-color: rgb(25,65,65,150);padding: -1;}"
		"QTableWidget{selection-color: rgb(255, 255, 255);}"
		"QTableWidget{font-size : 12px;color: rgb(55, 55, 55);}";
	mytable->setStyleSheet(style);
}

void MainWindow::showContextmenu(const QPoint&pos)
{
	QPoint globalPos = mytable->mapToGlobal(pos);
	right_press = new QMenu(this);
	right_press->setContentsMargins(1, 1, 1, 4);
	QAction *songitem = new QAction(QStringLiteral("  歌曲定位"), this);
	QAction *delsong = new QAction(QStringLiteral("  删除歌曲"), this);
	QAction *openlist = new QAction(QStringLiteral("  打开文件夹"), this);
	QAction *emptylist = new QAction(QStringLiteral("  清空列表"), this);
	if (mytable->itemAt(mytable->mapFromGlobal(QCursor::pos())) != NULL)   //选定的有歌曲
	{
		right_press->addAction(songitem);
		right_press->addAction(delsong);
		right_press->addAction(openlist);
	}
	right_press->addAction(emptylist);                //空白地方也可清空列表
	connect(songitem, SIGNAL(triggered()), this, SLOT(songItem()));
	connect(delsong, SIGNAL(triggered()), this, SLOT(delItem()));
	connect(openlist, SIGNAL(triggered()), this, SLOT(openList()));
	connect(emptylist, SIGNAL(triggered()), this, SLOT(emptyList()));
	right_press->exec(globalPos);               //以点击位置为起点显示
}

void MainWindow::songItem()
{
	QTableWidgetItem *item = mytable->item(mytable->nowindex, 0);
	mytable->setCurrentItem(item);
	mytable->scrollToItem(item);
}

void MainWindow::delItem()
{
	int index = mytable->currentRow();          //当前选择偏移量
	if (index == mytable->nowindex)           //如果选择为当前播放歌曲
	{
		mytable->mysetNext();            //播放下一首
		player->setMedia(mytable->plist->media(mytable->nowindex));
		player->play();
	}
	mytable->myDelitem(index);
	mytable->removeRow(index);
}

void MainWindow::openList()
{
	QUrl url = mytable->plist->media(mytable->currentRow()).canonicalUrl();  //获取地址
	QString fileall = url.toLocalFile();
	fileall.replace("/", "\\");           //切换斜线
	QString heads = "/select,";
	QString selectfile = heads + fileall;            
	LPCTSTR str = selectfile.toLocal8Bit().constData();
	ShellExecuteA(0, "open", "explorer.exe", str, NULL, true);        //利用windows自带explorer文档管理器打开文件所在位置
}

void MainWindow::emptyList()
{
	if (player->isAudioAvailable() == true)
	{
		playOrsuspend();           //改变按钮形式
	}
	player->pause();
	player->stop();
	player->dumpObjectInfo();
	mytable->setRowCount(0);
	mytable->plist->clear();
	mytable->clearContents();         //清理连接
	song_name = "";
	ui->time_show->clear();
	ui->time_show->setText("00:00/00:00");
}

void MainWindow::showlrcMenu(const QPoint&)
{
	QMenu *menu = new QMenu(this);
	menu->setContentsMargins(1, 1, 1, 4);
	QAction *searchlrc = new QAction(QStringLiteral("手动搜索歌词"),this);
	QAction *openlrc = new QAction(QStringLiteral("打开以保存歌词"), this);
	QAction *copylrc = new QAction(QStringLiteral("复制全部歌词"), this);
	menu->addAction(searchlrc);
	menu->addAction(openlrc);
	menu->addAction(copylrc);

	if (player->currentMedia().canonicalUrl().toString() == NULL)         //没有播放的歌曲
	{
		searchlrc->setDisabled(true);
	}
	else
	{
		searchlrc->setEnabled(true);
	}
	connect(searchlrc, SIGNAL(triggered()), this, SLOT(searchLrc()));
	connect(openlrc, SIGNAL(triggered()), this, SLOT(openLrc()));
	connect(copylrc, SIGNAL(triggered()), this, SLOT(copyLrc()));
	menu->exec(QCursor::pos());
}

void MainWindow::searchLrc()
{

}

void MainWindow::openLrc()
{
	QString path("G://saddog//song_lyrics");
	QDesktopServices open;
	open.openUrl(QUrl(path));
}

void MainWindow::copyLrc()
{
	lrcshowedit->selectAll();
	lrcshowedit->copy();
	QToolTip::showText(QCursor::pos(), QStringLiteral("已复制到粘贴板"));
}

void MainWindow::autoNextsong(QMediaPlayer::MediaStatus start)
{
	if (start == QMediaPlayer::EndOfMedia)
	{
		mytable->mysetNext();
		player->setMedia(mytable->myCurrentMedia());
		player->play();
	}
}