#ifndef MAZEGEN_H
#define MAZEGEN_H

#include <QMainWindow>
#include "result.h"

QT_BEGIN_NAMESPACE
namespace Ui { class mazegen; }
QT_END_NAMESPACE

class mazegen : public QMainWindow
{
    Q_OBJECT

public:
    mazegen(QWidget *parent = nullptr);
    ~mazegen();
    void genmz(int val);
    QImage pork,beef;
    void keyPressEvent(QKeyEvent *k);

private slots:
    void on_Bstart_clicked();
    void on_Isz_editingFinished();
    void on_In_editingFinished();
    void on_Im_editingFinished();
    void on_BTview_clicked();
    void on_BTsav_clicked();
    void on_BTsvans_clicked();

private:
    Ui::mazegen *ui;
    void saveAction(QImage img);
};
#endif // MAZEGEN_H
