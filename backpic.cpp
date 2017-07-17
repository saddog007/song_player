#include "backpic.h"
#include "ui_backpic.h"
#include <QDebug>


BackPic::BackPic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BackPic)
{
    ui->setupUi(this);
	this->setWindowFlags(Qt::FramelessWindowHint| Qt::Tool | Qt::X11BypassWindowManagerHint);
	this->setFixedSize(this->width(), 380);
	QPalette p;
	p.setBrush(QPalette::Background, QBrush(QPixmap(":/images/image/bg1.jpg")));
	setPalette(p);

	signalmapper = new QSignalMapper(this);

	//建立无参数连接
	connect(ui->btn1, SIGNAL(clicked()), signalmapper, SLOT(map()));
	connect(ui->btn2, SIGNAL(clicked()), signalmapper, SLOT(map()));
	connect(ui->btn3, SIGNAL(clicked()), signalmapper, SLOT(map()));
	connect(ui->btn4, SIGNAL(clicked()), signalmapper, SLOT(map()));
	connect(ui->btn5, SIGNAL(clicked()), signalmapper, SLOT(map()));

	//把无参数信号转为带参数信号
	signalmapper->setMapping(ui->btn1, QString("1"));
	signalmapper->setMapping(ui->btn2, QString("2"));
	signalmapper->setMapping(ui->btn3, QString("3"));
	signalmapper->setMapping(ui->btn4, QString("4"));
	signalmapper->setMapping(ui->btn5, QString("5"));

	connect(signalmapper, SIGNAL(mapped(QString)), this, SIGNAL(back_pic_id(QString)));
	connect(ui->close_btn, SIGNAL(clicked()), this, SLOT(close_window()));
}

BackPic::~BackPic()
{
    delete ui;
}

void BackPic::close_window()
{
	this->close();
}
