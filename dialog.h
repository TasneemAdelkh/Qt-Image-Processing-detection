#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <imagethread.h>
#include <QtCore>
#include <QImage>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE
class ImageThread;
class Dialog : public QDialog
{
    Q_OBJECT

public:
     Dialog(QWidget *parent = nullptr);
    ~Dialog();
private slots:
     void writegui(int cir,int lines,int rect,int tri);

private:
    Ui::Dialog *ui;
    ImageThread *runimage;
    int flagwrite;
};
#endif // DIALOG_H
