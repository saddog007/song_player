#ifndef BACKPIC_H
#define BACKPIC_H

#include <QDialog>

namespace Ui {
class BackPic;
}

class BackPic : public QDialog
{
    Q_OBJECT

public:
    explicit BackPic(QWidget *parent = 0);
    ~BackPic();

private:
    Ui::BackPic *ui;
};

#endif // BACKPIC_H
