#ifndef RESULT_H
#define RESULT_H

#include <QWidget>

namespace Ui {
class result;
}

class result : public QWidget
{
    Q_OBJECT

public:
    explicit result(QImage img0,QImage img1,QWidget *parent = nullptr);
    QImage Ig0,Ig1; int stat=0;
    ~result();

private:
    Ui::result *ui;
    void saveAction(QImage img);
    void keyPressEvent(QKeyEvent *k);
};

#endif // RESULT_H
