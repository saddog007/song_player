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

signals:
	void back_pic_id(QString);

private:
    Ui::BackPic *ui;

};

#endif // BACKPIC_H
