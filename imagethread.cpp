#include "imagethread.h"
#include <QString>
ImageThread::ImageThread(QObject *parent)   //using threads to display the gui with the photos altogether
       :QThread(parent)
{

}
void ImageThread :: run(){
    image=imread("D:\\Tasneem\\Qt\\OpenCVtask\\test1.png");
    test2=imread("D:\\Tasneem\\Qt\\OpenCVtask\\test2.png");
    test3=imread("D:\\Tasneem\\Qt\\OpenCVtask\\test3.png");
    if(!image.data){
       qDebug()<<"image not found";
       return;
    }
    image1=image.clone();   //setting clones for each image to use them in colordetect function
    test21=test2.clone();
    test31=test3.clone();
    minblue=Scalar(200,0,0);  //setting the min and max ranges for the colors
    maxblue=Scalar(255,20,20);
    minred=Scalar(0,0,200);
    maxred=Scalar(20,20,255);
    mingreen=Scalar(0,200,0);
    maxgreen=Scalar(20,255,20);
    minyellow=Scalar(0,200,200);
    maxyellow=Scalar(20,255,255);

    cir=0;
    tri=0;
    rectn=0;
    line=0;

    qDebug()<<"photo1: ";   //calling functions for first photo
    shapDetect(image);
    obj1.Direction(image);       //calling the direction function from LANE class to detect directions of lanes
    colorDetect(image1,minblue,maxblue,imageB,"BLUE",image);  //color detection for each colour
    colorDetect(image1,minred,maxred,imageR,"RED",image);
    colorDetect(image1,mingreen,maxgreen,imageG,"GREEN",image);
    colorDetect(image1,minyellow,maxyellow,imageY,"YELLOW",image);
    imshow("Detected1",image);      //showing image

    qDebug()<<"photo2: ";
    shapDetect(test2);
    obj2.Direction(test2);
    colorDetect(test21,minblue,maxblue,imageB,"BLUE",test2);
    colorDetect(test21,minred,maxred,imageR,"RED",test2);
    colorDetect(test21,mingreen,maxgreen,imageG,"GREEN",test2);
    colorDetect(test21,minyellow,maxyellow,imageY,"YELLOW",test2);
    imshow("Detected2",test2);

    qDebug()<<"photo3: ";
    shapDetect(test3);
    obj2.Direction(test3);
    colorDetect(test31,minblue,maxblue,imageB,"BLUE",test3);
    colorDetect(test31,minred,maxred,imageR,"RED",test3);
    colorDetect(test31,mingreen,maxgreen,imageG,"GREEN",test3);
    colorDetect(test31,minyellow,maxyellow,imageY,"YELLOW",test3);
    imshow("Detected3",test3);


 waitKey(0);
    //destroyWindow("testimage");
    destroyAllWindows();

}
///////////////////////////////////////////
void ImageThread::setLabel(cv::Mat& im, const std::string label, std::vector<cv::Point>& contour)  //setting labels for shapes at center of polygon
{
    int fontface = cv::FONT_HERSHEY_SIMPLEX;
    double scale = 0.5;
    int thickness = 1;
    int baseline = 0;

    cv::Size text = cv::getTextSize(label, fontface, scale, thickness, &baseline);
    cv::Rect r = cv::boundingRect(contour);
   // baseline+=thickness;
    cv::Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
    cv::rectangle(im, pt + cv::Point(0, baseline), pt + cv::Point(text.width, -text.height), CV_RGB(255,255,255), FILLED);
    cv::putText(im, label, pt, fontface, scale, CV_RGB(0,0,0), thickness, LINE_AA);
}
///////////////////////////////////////////
void ImageThread::setLabelC(cv::Mat& im, const std::string label, std::vector<cv::Point>& contour) //setting labels for colors
{
    int fontface = cv::FONT_HERSHEY_SIMPLEX;
    double scale = 0.5;
    int thickness = 1;
    int baseline = 0;

    cv::Size text = cv::getTextSize(label, fontface, scale, thickness, &baseline);
    cv::Rect r = cv::boundingRect(contour);
   // baseline+=thickness;
    cv::Point pt(r.x + ((r.width - text.width) / 2), (r.y+22) + ((r.height + text.height) / 2));
    cv::rectangle(im, pt + cv::Point(0, baseline), pt + cv::Point(text.width, -text.height), CV_RGB(255,255,255), FILLED);
    cv::putText(im, label, pt, fontface, scale, CV_RGB(0,0,0), thickness, LINE_AA);
}

////////////////////////////////////////////
void ImageThread::colorDetect(Mat img,Scalar min,Scalar max,Mat dst,String color,Mat imgOr){

    inRange(img,min,max,dst);
    Canny(dst,dst,50,255,5);
    vector<vector<Point>>contoursC;
    findContours(dst,contoursC,RETR_EXTERNAL,CHAIN_APPROX_NONE);
    for(size_t k=0;k<contoursC.size();k++)
    {

        setLabelC(imgOr,color,contoursC[k]);

}
}

/////////////////////////////////////////////
void ImageThread::shapDetect(Mat img){
    Canny(img,dstf,50,255,7);
   // Canny(image,dst,0,50,5);
    //finding contours
    vector<vector<Point>> contours;
    findContours(dstf,contours,RETR_EXTERNAL,CHAIN_APPROX_NONE);
    //drawContours(image,contours,-1,CV_RGB(180,0,180),3);
   vector<Point> approx;

   for(size_t i=0;i<contours.size();i++){
       approxPolyDP(Mat(contours[i]),approx,arcLength(Mat(contours[i]),true)*0.02,true);
   if(fabs(contourArea(contours[i]))<100) //||!isContourConvex(approx)
    continue;
   if(approx.size()==3)
   {    setLabel(img,"TRI",contours[i]);

       tri++;
   }
   else if(approx.size()==4)
   {
       Rect r=boundingRect(contours[i]);
       double rect=abs(1-(double)r.width/r.height);
       if(rect<=0.02)
       {setLabel(img,"RECT",contours[i]);  //square -_-
           rectn++;
       }
       else {setLabel(img,"LINE",contours[i]); //rectangle -_-
           line++;
       }
   }
   else {setLabel(img,"CIRCLE",contours[i]);
       cir++;
   }
   //else qDebug()<<"not found"<<i;
   }
   qDebug()<<"cir: "<<cir;
   qDebug()<<"lines: "<<line;
   qDebug()<<"rectangles: "<<rectn;
   qDebug()<<"triangles: "<<tri;
   emit info(cir,line,rectn,tri);
   cir=0;
   line=0;
   rectn=0;
   tri=0;
}
