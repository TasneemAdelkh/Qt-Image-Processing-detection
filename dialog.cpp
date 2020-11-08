#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    runimage=new ImageThread(this);
    runimage->start();
    ui->setupUi(this);
    flagwrite=0;

    connect(runimage,&ImageThread::info,this,&Dialog::writegui);
}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::writegui(int cir,int lines,int rect,int tri){
    if(flagwrite==0){
ui->lcdNumber->display(cir);
ui->lcdNumber_2->display(lines);
ui->lcdNumber_3->display(rect);
ui->lcdNumber_4->display(tri);
flagwrite=1;
    }
    else if(flagwrite==1)
    {
        ui->lcdNumber_5->display(cir);
        ui->lcdNumber_6->display(lines);
        ui->lcdNumber_7->display(rect);
        ui->lcdNumber_8->display(tri);
        flagwrite=2;
    }
    else if(flagwrite==2)
    {
        ui->lcdNumber_9->display(cir);
        ui->lcdNumber_10->display(lines);
        ui->lcdNumber_11->display(rect);
        ui->lcdNumber_12->display(tri);
    }
}

