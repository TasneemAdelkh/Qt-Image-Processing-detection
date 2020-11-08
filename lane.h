#ifndef LANE_H
#define LANE_H

#include <QObject>
#include <QtCore>
#include <QImage>
#include <opencv2/core/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include<opencv2/calib3d.hpp>
#include<opencv2/imgcodecs.hpp>
using namespace cv;
using namespace std;
class LANE
{

public:
    LANE();
    void Direction(Mat img);
    void LRlane(String direction,Mat img);  //detecting whether the direction is left or right
private:
    Mat image,dst,lane;
    Scalar minblack,maxblack;
    int x1l1,x2l1,yl1,yl2,x1l2,x2l2;
    int xl1,xl2,y1l1,y2l1,y1l2,y2l2;
    int flagR,flagF;
    Vec4i l;
    Size textlane;
};

#endif // LANE_H
