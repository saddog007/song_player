#include "mymaintable.h"
#include <QTGui>
#include <QHeaderView>
#include <QDebug>
#include <QGraphicsOpacityEffect>
#include <QScrollBar>

Mymaintable::Mymaintable(QWidget *parent) : QTableWidget(parent)
{
	this->setMouseTracking(true);
	mouse_press = true;
	plist = new QMediaPlaylist;

	previousitem = -1;
	setFrameShadow(QFrame::Plain);   //设置平的样式
	setFrameShape(QFrame::NoFrame);  //设置无边样式
	setFocusPolicy(Qt::NoFocus);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  //水平scrollbar禁用
	setShowGrid(false);   //隐藏线
	this->horizontalHeader()->setVisible(false);
	this->verticalHeader()->setVisible(false);
	setEditTriggers(QTableWidget::NoEditTriggers);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setSelectionMode(QAbstractItemView::SingleSelection);
	setAcceptDrops(true);
	setGeometry(90, 192, 240, 431);//区域

	setContextMenuPolicy(Qt::CustomContextMenu);
	this->insertColumn(0);
	this->insertColumn(1);
	this->horizontalHeader()->resizeSection(0, 100);
	this->horizontalHeader()->setStretchLastSection(true);

	this->setStyleSheet("QTableWidget{background-color:rgb(255, 255, 255,150);}"
		"QTableWidget{font-size : 12px;color: rgb(55, 55, 55);}"
		"QTableWidget{selection-background-color: rgb(25,65,65,150);padding: -1;}"
		"QTableWidget{selection-color: rgb(255, 255, 255);}");
	QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
	this->verticalScrollBar()->setGraphicsEffect(opacityEffect);
	opacityEffect->setOpacity(0.5);

	QScrollBar *vbar = this->verticalScrollBar();
	vbar->setContextMenuPolicy(Qt::NoContextMenu);
	vbar->setStyleSheet("QScrollBar{background:white; width: 10px;margin: 10px 0 10px 0;}"
		"QScrollBar::handle{background:light gray;border-radius:5px;}"
		"QScrollBar::handle:hover{background: rgb(55,55,55);}"
		"QScrollBar::add-line:vertical {background:black; border-image: url(:/image/down.png); height: 10px; subcontrol-position: bottom;subcontrol-origin: margin;}"
		"QScrollBar::sub-line:vertical {background:black; border-image: url(:/image/top.png);height: 10px;subcontrol-position: top;subcontrol-origin: margin;}"
		"QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background:white;}");
	connect(this, SIGNAL(currentItemChanged(QTableWidgetItem*, QTableWidgetItem*)), this, SLOT(currentitemch(QTableWidgetItem*, QTableWidgetItem*)));
	connect(this, SIGNAL(cellEntered(int, int)), this, SLOT(listentered(int, int)));

}

Mymaintable::Mymaintable(bool second)
{
	mouse_press = second;
	setMouseTracking(true);
	setFrameShadow(QFrame::Plain);//设置平的样式
	setFrameShape(QFrame::NoFrame);//设置无边样式
	setFocusPolicy(Qt::NoFocus);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//水平scrollbar禁用
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//垂直scrollbar禁用
	setShowGrid(false);//隐藏线
	verticalHeader()->setVisible(false);//设置不可见
	setEditTriggers(QTableWidget::NoEditTriggers);//不可编辑
	setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为，以行为单位
	setSelectionMode(QAbstractItemView::NoSelection);//单选
	horizontalHeader()->setHighlightSections(false);//不能鼠标点击
	setStyleSheet("QTableWidget{background-color:rgb(255, 255, 255,100);}"
		"QTableWidget{font-size : 12px;color: rgb(65, 65, 65);}"

		"QTableWidget::item:hover{color: red;}");//background-color:rgb(242, 242, 242);// "QTableWidget{selection-background-color: rgb(233,233,233);}"
	insertColumn(0);
	insertColumn(1);
	insertColumn(2);
	QStringList list;
	list << " 歌曲" << " 歌手" << "操作";
	setHorizontalHeaderLabels(list);
	QHeaderView *header = this->horizontalHeader();//调整大小
	header->setStyleSheet("QHeaderView::section{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgb(46,46,46),stop:1 rgb(66,66,66));color: rgb(210,210,210);border: 1px solid #383838;}");//
	header->resizeSection(0, 100);
	header->resizeSection(1, 80);
	header->setStretchLastSection(true);//延展最一个表头
	header->setSectionResizeMode(QHeaderView::Fixed);//不能更改列宽
	this->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft);//第一列表头对齐方式
	this->horizontalHeaderItem(1)->setTextAlignment(Qt::AlignLeft);//第2列表头位置方式
}

void Mymaintable::mysetNext()
{
	if (nowmode == 0)
	{
		if (nowindex == plist->mediaCount() - 1)   //顺序播放到尾巴上  从头再来
		{
			nowindex = 0;
			QTableWidgetItem *item = this->item(nowindex, 0);
			this->setCurrentItem(item);
			return;
		}
		nowindex += 1;
		QTableWidgetItem *item = this->item(nowindex, 0);
		this->setCurrentItem(item);
	}
	if (nowmode == 1)
	{
		return;
	}
	if (nowmode == 2)
	{
		QTime time;
		time = QTime::currentTime();
		qsrand(time.msec() + time.second() * 1000);
		int x = qrand() % plist->mediaCount();
		nowindex = x;
		QTableWidgetItem *item = this->item(nowindex, 0);
		this->setCurrentItem(item);
	}
}
void Mymaintable::mysetLast()
{
	if (nowmode == 0)
	{
		if (nowindex == 0)//顺序列表播放头上再按上一曲， 从头播放第一首
		{
			nowindex = 0;
			return;
		}
		nowindex -= 1;
		QTableWidgetItem *item = this->item(nowindex, 0);
		this->setCurrentItem(item);
	}
	if (nowmode == 1)
	{
		return;
	}
	if (nowmode == 2)
	{
		QTime time;
		time = QTime::currentTime();
		qsrand(time.msec() + time.second() * 1000);
		int xxx = qrand() % plist->mediaCount();
		nowindex = xxx;
		this->setCurrentCell(nowindex, 0);
	}
}

void Mymaintable::listentered(int row, int column)
{
	//qDebug() << row << column;
}

void Mymaintable::currentitemch(QTableWidgetItem*, QTableWidgetItem*)
{

}

void Mymaintable::mouseMoveEvent(QMouseEvent *event)
{
	if (!mouse_press)
	{
		return;
	}
	QTableWidgetItem *itemss = this->item(previousitem, 0);
	QModelIndex index = this->indexAt(this->mapFromGlobal(QCursor::pos()));
	int nowrow = index.row();
	if (itemss != Q_NULLPTR)
	{
		this->item(previousitem, 0)->setBackgroundColor(Qt::transparent);
		this->item(previousitem, 1)->setBackgroundColor(Qt::transparent);
	}
	if (this->itemAt(this->mapFromGlobal(QCursor::pos())) != NULL&&nowrow != currentRow())
	{
		this->item(nowrow, 0)->setBackgroundColor(QColor(25, 65, 65, 50));
		this->item(nowrow, 1)->setBackgroundColor(QColor(25, 65, 65, 50));
		previousitem = nowrow;
	}
}

void Mymaintable::leaveEvent(QEvent *)
{
	QTableWidgetItem *itemss = this->item(previousitem, 0);
	if (itemss != Q_NULLPTR)//如果itemss不为空
	{
		this->item(previousitem, 0)->setBackgroundColor(Qt::transparent);
		this->item(previousitem, 1)->setBackgroundColor(Qt::transparent);
	}
}

void Mymaintable::mysetCurrentMeida(int nosong)
{
	nowindex = nosong;
}

QUrl Mymaintable::myCurrentMedia()
{
	return plist->media(nowindex).canonicalUrl();
}

void Mymaintable::myDelitem(int index)
{
	if (index < nowindex)
	{
		plist->removeMedia(index);
		nowindex--;
		QTableWidgetItem *item = this->item(nowindex, 0);
		this->setCurrentItem(item);
		return;
	}
	if (index == nowindex)
	{
		plist->removeMedia(index);
		nowindex++;
		QTableWidgetItem *item = this->item(nowindex, 0);
		this->setCurrentItem(item);
		return;
	}
	if (index > nowindex)
	{
		plist->removeMedia(index);
		QTableWidgetItem *item = this->item(nowindex, 0);
		this->setCurrentItem(item);
		return;
	}
}