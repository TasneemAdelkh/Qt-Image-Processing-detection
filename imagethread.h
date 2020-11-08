#ifndef IMAGETHREAD_H
#define IMAGETHREAD_H

#include <QObject>
#include <QThread>
#include <QtCore>
#include <QImage>
#include "lane.h"
#include <opencv2/core/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include<opencv2/calib3d.hpp>
#include<opencv2/imgcodecs.hpp>
#include <QFont>
#include<QtFontDatabaseSupport/qtfontdatabasesupportversion.h>
using namespace cv;
using namespace std;
class ImageThread : public QThread
{
    Q_OBJECT
public:
    ImageThread(QObject *parent=nullptr);
   void setLabel(cv::Mat& im, const std::string label, std::vector<cv::Point>& contour);
   void setLabelC(cv::Mat& im, const std::string label, std::vector<cv::Point>& contour);
   void colorDetect(Mat img,Scalar min,Scalar max,Mat dst,String color,Mat imgOr);
   void shapDetect(Mat img);
protected:
    void run();
signals:
    void info(int cir,int lines,int rect,int tri);
private:
    Mat image,image1,imageG,imageB,imageY,imageR,dstf,dst,test2,test21,test3,test31;
    Rect boundrect;
    Scalar minblack;
    Scalar maxblack;
    Scalar minred,maxred;
    Scalar mingreen,maxgreen,minblue,maxblue,minyellow,maxyellow;

    int tri,cir,rectn,line;
    LANE obj1,obj2,obj3;
};

#endif // IMAGETHREAD_H
