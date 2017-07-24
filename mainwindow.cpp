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

	stack = new QStackedWidget(this);
	mytable = new Mymaintable(stack);   //���widget
	stack->addWidget(mytable);        //���tablewidget������
	stack->setGeometry(90, 192, 240, 451);

	ui->widget_search->raise();   //���ҽ���λ�����ϲ�
	ui->widget_search->hide();    //���ҽ�������


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
	connect(m_timer, SIGNAL(timeout()), this, SLOT(songNameshow()));                  //������ʾ������
	connect(mytable, SIGNAL(itemDoubleClicked(QTableWidgetItem *)), this, SLOT(mytableDoubleclick(QTableWidgetItem*)));   //����˫������
	connect(ui->add_btn, SIGNAL(clicked()), this, SLOT(addFile()));        //��Ӹ�������
	connect(ui->play_progress_bar, SIGNAL(sliderMoved(int)), this, SLOT(setPosition(int)));   //���Ž��ȸı亯��

	WindowStyle();  //���ڲ�������
	systemIcon();   //ϵͳͼ������
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

	//��ʼ����������ʾ
	song_name = QStringLiteral("��ӭ����saddog�Ĳ�����!");
	m_timer->start(100);

	//���ò��Ž��������slider����
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
	//nowplaylist = 1;   //�����������ڲ��ŵ��б�

	mytable->mysetCurrentMeida(item->row());
	player->setMedia(mytable->myCurrentMedia());
	player->play();
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
	static QString initfilename = "G:/";  //����Ĭ��·��
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

void MainWindow::setPosition(int pos)
{
	player->setPosition(pos);
}