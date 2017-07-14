#include "backpic.h"
#include "ui_backpic.h"

BackPic::BackPic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BackPic)
{
    ui->setupUi(this);
}

BackPic::~BackPic()
{
    delete ui;
}
