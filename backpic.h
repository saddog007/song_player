#ifndef BACKPIC_H
#define BACKPIC_H

#include <QDialog>
#include <QSignalMapper>

namespace Ui {
class BackPic;
}

class BackPic : public QDialog
{
    Q_OBJECT

public:
    explicit BackPic(QWidget *parent = 0);
    ~BackPic();

	QSignalMapper *signalmapper;

public slots:
	void close_window();
	void setSlidervalue(int value);  //设置透明度进度条

signals:
	void back_pic_id(QString);
	void list_bk_trans(int);         //列表透明度

private:
    Ui::BackPic *ui;

};

#endif // BACKPIC_H
