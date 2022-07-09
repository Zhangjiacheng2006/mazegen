#include "result.h"
#include "ui_result.h"

result::result(QImage img0,QImage img1,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::result)
{
    ui->setupUi(this);
    Ig0=img0; Ig1=img1;
    this->resize(img0.width()+4,img0.height()+4);
    ui->label->resize(img0.width(),img0.height());
    ui->label->setPixmap(QPixmap::fromImage(img0));
}

result::~result()
{
    delete ui;
}

#include<QFileDialog>
void result::saveAction(QImage img){
    QString fileName=QFileDialog::getSaveFileName(this,"保存",QCoreApplication::applicationFilePath(),tr("Lossless compression (*.png *.bpm);;Lossy compression (*.jpg *.jpeg);;Images (*.png *.bpm *.jpg *.jpeg)"));
    if(fileName.isEmpty()) return;
    img.save(fileName);
}
#include<QKeyEvent>
void result::keyPressEvent(QKeyEvent *k){
    if(k->modifiers()==Qt::ControlModifier && k->key()==Qt::Key_S){
        saveAction(stat==0?Ig0:Ig1);
    }
    if(k->key()==Qt::Key_Right){
        stat=1;ui->label->setPixmap(QPixmap::fromImage(Ig1));
    }
    if(k->key()==Qt::Key_Left){
        stat=0;ui->label->setPixmap(QPixmap::fromImage(Ig0));
    }
}
