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
	m_timer = new QTimer(this);    //����ʵ�ֹ���Ч���Ķ�ʱ��
	songs_time = new QTimer(this);   //������Ŀ��ʱ��
	song_tips = new QTimer(this);     //�б������ʾ��Ϣ���޸�����

	//��Ӹ����ʾ����
	lrcshowedit = new QTextEdit(this);
	lrcshowedit->setStyleSheet("QTextEdit{background:transparent}");
	lrcshowedit->setFrameStyle(QFrame::NoFrame);
	lrcshowedit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	lrcshowedit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	lrcshowedit->setReadOnly(true);
	lrcshowedit->setFont(QFont("΢���ź�", 10, QFont::Thin));
	lrcshowedit->setTextColor(Qt::white);
	lrcshowedit->setContextMenuPolicy(Qt::CustomContextMenu);
	lrcshowedit->setFocusPolicy(Qt::NoFocus);
	lrcshowedit->viewport()->installEventFilter(this);
	lrcshowedit->viewport()->setCursor(QCursor(QPixmap(":/images/image/cursor_hand.png")));
	
	stack = new QStackedWidget(this);
	mytable = new Mymaintable(stack);   //���widget
	stack->addWidget(lrcshowedit);     //��Ӹ����ʾ����
	stack->addWidget(mytable);        //���tablewidget������
	stack->setGeometry(90, 192, 240, 431);

	mytable->setContextMenuPolicy(Qt::CustomContextMenu);        //�Ҽ��˵� 

	//�б��޸�����ʾ��Ϣ
	addtips = new QLabel(QStringLiteral("  �����ť���\n���϶��ļ�������"), mytable);
	addtips->setGeometry(50, 192, 240, 50);
	addtips->setStyleSheet("color:white;font-size:18px;font-family:΢���ź�");  

	QDir dir0("G://saddog//song_lyrics");   //��������ļ���
	if (!dir0.exists())
	{
		dir0.mkdir("G://saddog//song_lyrics");
	}
	QDir dir1("G://saddog//song_list");   //���������ļ���
	if (!dir1.exists())
	{
		dir1.mkdir("G://saddog//song_list");
	}
	QDir dir2("G://saddog//song_pic");   //����������Ƭ�ļ���
	if (!dir2.exists())
	{
		dir2.mkdir("G://saddog//song_pic");
	}
	QFile fileconfig("config.ini");              //�����˳����������ļ�
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
	connect(ui->volume_progress_bar, SIGNAL(valueChanged(int)), this, SLOT(volPicchange(int)));  //����ͼƬ�ı�
	connect(ui->volume_progress_bar, SIGNAL(sliderMoved(int)), this, SLOT(volPicchange(int)));
	connect(ui->volume_progress_bar, SIGNAL(valueChanged(int)), player, SLOT(setVolume(int)));  //���ݸ�������
	connect(ui->volume_progress_bar, SIGNAL(sliderMoved(int)), player, SLOT(setVolume(int)));
	connect(ui->play_model, SIGNAL(currentIndexChanged(int)), this, SLOT(playModelchange(int)));     //��ͬ��ѡ��ִ�в�ͨ���¼�
	connect(m_timer, SIGNAL(timeout()), this, SLOT(songNameshow()));                  //������ʾ������
	connect(mytable, SIGNAL(itemDoubleClicked(QTableWidgetItem *)), this, SLOT(mytableDoubleclick(QTableWidgetItem*)));   //����˫������
	connect(mytable, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(mytableClicked(QTableWidgetItem*)));            //������������
	connect(ui->add_btn, SIGNAL(clicked()), this, SLOT(addFile()));        //��Ӹ�������
	connect(ui->play_progress_bar, SIGNAL(sliderMoved(int)), this, SLOT(setPosition(int)));   //���Ž��ȸı亯��
	connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));    //��ȡ����ʱ���͸���ƥ��
	connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));    //��ȡ������ǰ����ʱ��
	connect(ui->volume_label, SIGNAL(clicked()), this, SLOT(volChanged()));     //���������Ƿ���
	connect(songs_time, SIGNAL(timeout()), this, SLOT(showSongnum()));         //ʵʱ��ʾ��������
	connect(song_tips, SIGNAL(timeout()), this, SLOT(showTips()));             //�޸���ʾ
	connect(player, SIGNAL(currentMediaChanged(QMediaContent)), this, SLOT(showPlaylabel(QMediaContent)));  //��ʾ���ڲ��ŵĸ���
	connect(ui->search_btn, SIGNAL(clicked()), this, SLOT(searchSong()));      //���Ҹ���
	connect(ui->search_close, SIGNAL(clicked()), this, SLOT(searchClose()));    //�رղ���
	connect(ui->search_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(searchItems(QString)));  //���Һ���
	connect(backpic, SIGNAL(list_bk_trans(int)), this, SLOT(setListopa(int)));         //�����б�͸����
	connect(mytable, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextmenu(const QPoint&))); //mytable�Ҽ������Ӧ����
	connect(lrcshowedit, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showlrcMenu(const QPoint&))); //��ʽ����Ҽ�����
	connect(ui->listWidget, SIGNAL(currentRowChanged(int)), stack, SLOT(setCurrentIndex(int)));           //���ѡ������ұ߽���
	connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(autoNextsong(QMediaPlayer::MediaStatus)));   //һ�������Զ���һ��

	systemIcon();   //ϵͳͼ������
	WindowStyle();  //���ڲ�������
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

	//��ʼ����������ʾ
	song_name = QStringLiteral("��ӭ����saddog�Ĳ�����!");
	m_timer->start(100);

	//���ò��Ž��������slider����
	ui->play_progress_bar->installEventFilter(this);

	//����������ť��ʼ��״̬
	vol_change = true;

	//�����������¿�ʼ
	songs_time->start(1000);
	song_tips->start(200);

	ui->widget_search->raise();   //���ҽ���λ�����ϲ�
	ui->widget_search->hide();    //���ҽ�������

	//��ȡ�����ļ�
	readConfig();

	//��ʼ�����ڱ����б����
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
	saveList();            //�˳�ǰ����
	ui->close_btn->setEnabled(false);     //��ֹ�������
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
		ui->play_or_suspend->setToolTip(QStringLiteral("����"));
		is_play = !is_play;
		if (player->state() == QMediaPlayer::PlayingState)  //���ڲ���
		{
			player->pause();
		}
	}
	else
	{
		ui->play_or_suspend->setStyleSheet("QToolButton{border-image: url(:/images/image/pause_hover.png);}QToolTip{background-color:white}");
		ui->play_or_suspend->setToolTip(QStringLiteral("��ͣ"));
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
	if (player->isAudioAvailable() == true)           //���������
	{
		mytable->mysetLast();
		player->setMedia(mytable->myCurrentMedia());
	}
	player->play();
}

void MainWindow::nextSong()
{
	if (player->isAudioAvailable() == true)           //���������
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
	QToolTip::showText(QCursor::pos(), QString::number(vol));     //ͨ��vol��slidetmove�õ����ֵ���ڴ�ֵ��tooltipʵʱ��ʾ
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
	//nowplaylist = 1;   //�����������ڲ��ŵ��б�

	mytable->mysetCurrentMeida(item->row());
	player->setMedia(mytable->myCurrentMedia());
	player->setVolume(0);           //��ʼ����������
	ui->play_or_suspend->setStyleSheet("QToolButton{border-image: url(:/images/image/pause_hover.png);}QToolTip{background-color:white}");
	ui->play_or_suspend->setToolTip(QStringLiteral("��ͣ"));    //���ò��Ű�ť�ı�
	is_play = !is_play;

	player->play();
}

void MainWindow::mytableClicked(QTableWidgetItem*item)
{
	mytable->mysetCurrentMeida(item->row());
}

void MainWindow::systemIcon()
{
	//��ʾϵͳͼ��
	trayicon = new QSystemTrayIcon(this);
	trayicon->setIcon(QIcon(tr(":/images/image/sysicon11.ico")));
	trayicon->show(); 

	//����ϵͳͼ��ѡ��
	QAction *aboutapp = new QAction(QStringLiteral("  ���ڳ���"),this);
	QAction *quitapp = new QAction(QIcon(QPixmap(":/images/image/MD-brightness.png")), QStringLiteral("  �˳�"), this);
	QAction *openapp = new QAction(QStringLiteral("  ��������"), this);
	QAction *updateapp = new QAction(QStringLiteral("  ���汾"), this);
	QAction *showlrc = new QAction(QStringLiteral("  �򿪸��"), this);
	QAction *closelrc = new QAction(QStringLiteral("  �رո��"), this);
	QWidgetAction *playmenuaction = new QWidgetAction(this);
	QPushButton *play_button = new QPushButton(this);
	QPushButton *next_button = new QPushButton(this);
	QPushButton *last_button = new QPushButton(this);
	QLabel *music_name_label = new QLabel(this);
	QWidget *play_widget = new QWidget(this);

	play_button->setCursor(QCursor(Qt::PointingHandCursor));  //���������ʽΪ����
	next_button->setCursor(QCursor(Qt::PointingHandCursor));
	last_button->setCursor(QCursor(Qt::PointingHandCursor));

	play_button->setFlat(true);         //���õ�����Ч�� ������ͻ��
	last_button->setFlat(true);
	next_button->setFlat(true);

	play_button->setStyleSheet("QPushButton{border-image:url(:/images/image/menuplay.png);}");
	next_button->setStyleSheet("QPushButton{border-image:url(:/images/image/menuforward.png);}");
	last_button->setStyleSheet("QPushButton{border-image:url(:/images/image/menuback.png);}");
	play_button->setFixedSize(26, 26);
	last_button->setFixedSize(21,21);
	next_button->setFixedSize(21,21);

	QHBoxLayout *layout = new QHBoxLayout();    //����
	layout->addWidget(last_button);     //ע��˳��
	layout->addWidget(play_button);
	layout->addWidget(next_button);
	layout->setSpacing(0);                       //���ò�������
	layout->setContentsMargins(10, 0, 10, 0);    //�����������¾���
	QVBoxLayout *layout2 = new QVBoxLayout();
	layout2->addLayout(layout);
	layout2->addWidget(music_name_label, 0, Qt::AlignCenter);     //���ж���
	layout2->setSpacing(2);
	layout2->setContentsMargins(0, 5, 0, 0);
	music_name_label->setText(QStringLiteral("���ֲ�����"));
	music_name_label->setEnabled(false);    //���ò��ɵ��
	play_widget->setLayout(layout2);
	play_widget->setFixedSize(140, 60);
	playmenuaction->setDefaultWidget(play_widget);

	QMenu *trayiconmenu = new QMenu(this);   //������Ӹ�����ť
	trayiconmenu->addAction(playmenuaction);
	trayiconmenu->addSeparator();        //��ӷָ���
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
	trayicon->setToolTip(QStringLiteral("��ӭʹ��saddog�����ֲ�����"));

	connect(openapp, SIGNAL(triggered(bool)), this, SLOT(openWindows()));           //��������
	connect(quitapp, SIGNAL(triggered()), this, SLOT(saveList()));     //�˳�ǰ�����б�
	connect(quitapp, SIGNAL(triggered()), qApp, SLOT(quit()));         //�˳�����
	connect(aboutapp, SIGNAL(triggered()), this, SLOT(aboutApp()));     //�������
	connect(updateapp, SIGNAL(triggered()), this, SLOT(updateMess()));   //������
	//˫��ϵͳͼ��򿪲˵�
	connect(trayicon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this, SLOT(trayiconActivated(QSystemTrayIcon::ActivationReason)));
	
	connect(showlrc, SIGNAL(triggered()), this, SLOT(showLrc()));   //�򿪸��
	connect(closelrc, SIGNAL(triggered()), this, SLOT(closeLrc()));  //�رո��
	//���Ӻ����ͽ��沥�ź���
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
	file.resize(0);   //����д��
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	mytable->plist->save(&file, "m3u");
	file.close();
    
	QSettings *m_set_ini = new QSettings("config.ini", QSettings::IniFormat);
	m_set_ini->setValue("/background/backpic", back_pic);       //����
	m_set_ini->setValue("/volume/vol", player->volume());       //����
	m_set_ini->setValue("/playmodel/index",play_model);          //����ģʽ
	m_set_ini->setValue("/listopa/value", list_opacity);          //�б�͸����   
	delete m_set_ini;
}

void MainWindow::aboutApp()
{
	this->showNormal();
	if (QMessageBox::Ok == QMessageBox::information(this, QStringLiteral("����saddog�����ֲ�����"), QStringLiteral("���������ѧϰʹ��\nʵ�ֵĹ�����:\n1.�����б��Զ�����\n2.drag��drop�¼������ж��ļ������򼴿�����������б�\n3.�����Զ���ȡ����ļ�,��������D://song_lyrics\n4.���̴߳�����"),QMessageBox::Ok));
	{
		return;
	}
}

void MainWindow::updateMess()
{
	if (QMessageBox::Ok == QMessageBox::information(this, QStringLiteral("������"), QStringLiteral("�������°�,�����ڴ������汾!"), QMessageBox::Ok));
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
			this->setWindowState(Qt::WindowActive);   //��������С������
			this->activateWindow();       //����������ϲ�
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
	static QString initfilename = "G:/saddog/song_list/";  //����Ĭ��·��
	QStringList files = QFileDialog::getOpenFileNames(this, QStringLiteral("ѡ���ļ�"), initfilename, tr("*.mp3"));  //��ȡ���ļ�·��
	if (files.isEmpty())
	{
		return;
	}
	int i = 0;
	while (i < files.count())
	{
		QString path = QDir::toNativeSeparators(files.at(i));   //ת��Ϊ���ظ�ʽ  �ɼ���ϵͳ
		if (!path.isEmpty())
		{
			mytable->plist->addMedia(QMediaContent(QUrl::fromLocalFile(path)));      //��ӵ��б�
		}
		QFileInfo info(files[i]);
		QString m_name = info.completeBaseName();
		QString songname;
		QString singer;
		if (m_name.contains("-"))     //�������ʱ����-����ַ�
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
	ui->listWidget->setCurrentRow(1);   //���ز����б�
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
	ui->play_progress_bar->setValue(pos);    //��������ʼ��
	QTime currentTime(0, (pos / 60000) % 60, (pos / 1000) % 60);     //����ʵʱ�ı䲥����Ϣ
	QString format = "mm:ss";
	currentTime.toString(format);
	QString todisplay;
	todisplay = currentTime.toString(format);
	ui->time_show->setText(todisplay + "/" + play_time);
	//qint64 total_time_value = player->duration();                //ֱ�ӻ�ȡ����Ƶ�ļ���ʱ��  ��λΪ����
	//...................

}

void MainWindow::durationChanged(qint64 pos)
{
	ui->play_progress_bar->setRange(0, pos);      //����ֵ��ȡֵ��Χ
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
	//��������Ŀ
	int songcount = mytable->rowCount();
	ui->label_4->setText(QStringLiteral("������:") + QString::number(songcount));   //���¸�����
}

void MainWindow::showTips()
{
	if (!player->isAudioAvailable())              //���ܻ�ȡ����
	{
		ui->play_progress_bar->setMaximum(0);
	}
	//��ʾ��ʾ��Ϣ
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
	//��ȡconfig.ini��plist.m3u��������
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
	if (file1.exists())  //�ļ�����
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
	list_opacity = value;        //�����б�͸����
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
	QAction *songitem = new QAction(QStringLiteral("  ������λ"), this);
	QAction *delsong = new QAction(QStringLiteral("  ɾ������"), this);
	QAction *openlist = new QAction(QStringLiteral("  ���ļ���"), this);
	QAction *emptylist = new QAction(QStringLiteral("  ����б�"), this);
	if (mytable->itemAt(mytable->mapFromGlobal(QCursor::pos())) != NULL)   //ѡ�����и���
	{
		right_press->addAction(songitem);
		right_press->addAction(delsong);
		right_press->addAction(openlist);
	}
	right_press->addAction(emptylist);                //�հ׵ط�Ҳ������б�
	connect(songitem, SIGNAL(triggered()), this, SLOT(songItem()));
	connect(delsong, SIGNAL(triggered()), this, SLOT(delItem()));
	connect(openlist, SIGNAL(triggered()), this, SLOT(openList()));
	connect(emptylist, SIGNAL(triggered()), this, SLOT(emptyList()));
	right_press->exec(globalPos);               //�Ե��λ��Ϊ�����ʾ
}

void MainWindow::songItem()
{
	QTableWidgetItem *item = mytable->item(mytable->nowindex, 0);
	mytable->setCurrentItem(item);
	mytable->scrollToItem(item);
}

void MainWindow::delItem()
{
	int index = mytable->currentRow();          //��ǰѡ��ƫ����
	if (index == mytable->nowindex)           //���ѡ��Ϊ��ǰ���Ÿ���
	{
		mytable->mysetNext();            //������һ��
		player->setMedia(mytable->plist->media(mytable->nowindex));
		player->play();
	}
	mytable->myDelitem(index);
	mytable->removeRow(index);
}

void MainWindow::openList()
{
	QUrl url = mytable->plist->media(mytable->currentRow()).canonicalUrl();  //��ȡ��ַ
	QString fileall = url.toLocalFile();
	fileall.replace("/", "\\");           //�л�б��
	QString heads = "/select,";
	QString selectfile = heads + fileall;            
	LPCTSTR str = selectfile.toLocal8Bit().constData();
	ShellExecuteA(0, "open", "explorer.exe", str, NULL, true);        //����windows�Դ�explorer�ĵ����������ļ�����λ��
}

void MainWindow::emptyList()
{
	if (player->isAudioAvailable() == true)
	{
		playOrsuspend();           //�ı䰴ť��ʽ
	}
	player->pause();
	player->stop();
	player->dumpObjectInfo();
	mytable->setRowCount(0);
	mytable->plist->clear();
	mytable->clearContents();         //��������
	song_name = "";
	ui->time_show->clear();
	ui->time_show->setText("00:00/00:00");
}

void MainWindow::showlrcMenu(const QPoint&)
{
	QMenu *menu = new QMenu(this);
	menu->setContentsMargins(1, 1, 1, 4);
	QAction *searchlrc = new QAction(QStringLiteral("�ֶ��������"),this);
	QAction *openlrc = new QAction(QStringLiteral("���Ա�����"), this);
	QAction *copylrc = new QAction(QStringLiteral("����ȫ�����"), this);
	menu->addAction(searchlrc);
	menu->addAction(openlrc);
	menu->addAction(copylrc);

	if (player->currentMedia().canonicalUrl().toString() == NULL)         //û�в��ŵĸ���
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
	QToolTip::showText(QCursor::pos(), QStringLiteral("�Ѹ��Ƶ�ճ����"));
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