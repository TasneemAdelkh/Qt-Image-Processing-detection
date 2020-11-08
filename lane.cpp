#include "lane.h"

LANE::LANE()

{

}
void LANE::Direction(Mat img){
flagR=0;
flagF=0;
/*image=imread(dir);
if(!image.data){
   qDebug()<<"image not found";
   return;
}*/
minblack=Scalar(0,0,0);
maxblack=Scalar(128,128,128);
vector<Vec2f>lines;
inRange(img,minblack,maxblack,lane);
Canny(lane,dst,50,255,3);
cvtColor(lane,lane,COLOR_GRAY2RGB);
vector<Vec4i> linesP; // will hold the results of the detection
HoughLinesP(dst, linesP, 1, CV_PI/180, 50, 50, 10 ); // runs the actual detection
// Draw the lines
for( size_t j = 0; j < linesP.size(); j++ )
{

  l = linesP[j];
   line( lane, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
   if((l[2]-l[0])>0&&(l[3]-l[1])<=0.3&&l[0]!=0)    //for detecting right direction
   {
       LRlane("RIGHT",img);

   }
   if((l[3]-l[1])<0&&(l[2]-l[0])<=0.3){

       textlane=getTextSize("FORWARD",FONT_HERSHEY_SIMPLEX,0.5,1,0);
       if(flagF==0)
       {xl1=l[2];
        y1l1=l[1];
        y2l1=l[3];
       flagF=1;
      // qDebug()<<xl1;
       }
       else {xl2=l[2];
           y1l2=l[1];
           y2l2=l[3];

       flagF=2;}
       if(flagF==2)
       {if(xl2>xl1)  //l2 is left and l1 is right
          { Point pt(xl1+((xl2-xl1)-textlane.width)/2,y1l1+((y2l1-y1l1)+textlane.height)/2);
           rectangle(img,pt,pt+Point(textlane.width, -textlane.height),CV_RGB(0,0,0),FILLED);
           putText(img,"FORWARD",pt,FONT_HERSHEY_SIMPLEX,0.5,CV_RGB(255,255,255),1,LINE_AA);
           flagF=0;
       }
           else if(xl1>xl2){  //l1 is left and l2 is right
               Point pt(xl2+((xl1-xl2)-textlane.width)/2,y1l2+((y2l2-y1l2)+textlane.height)/2);
               rectangle(img,pt,pt+Point(textlane.width, -textlane.height),CV_RGB(0,0,0),FILLED);
               putText(img,"FORWARD",pt,FONT_HERSHEY_SIMPLEX,0.5,CV_RGB(255,255,255),1,LINE_AA);
               flagF=0;
           }
       }
   }
   if((l[2]-l[0])>0&&(l[3]-l[1])<=0.3&&l[0]==0){  //y is constant while x is variable
       LRlane("LEFT",img);
   }
}
/*imshow("lane",lane);
imshow("newimage",image);
waitKey();
destroyAllWindows();}*/
}
///////////////////////////////////////////
void LANE::LRlane(String direction,Mat img){
textlane=getTextSize(direction,FONT_HERSHEY_SIMPLEX,0.5,1,0);
if(flagR==0)  //high line
{yl1=l[3];
 x1l1=l[0];
 x2l1=l[2];
flagR=1;
}
else {yl2=l[3];  //low line
    x1l2=l[0];
    x2l2=l[2];
//qDebug()<<"RIGHT"<<x1l2;

flagR=2;}
if(flagR==2)
{if(yl2>yl1)
   { Point pt(x1l1+((x2l1-x1l1)-textlane.width)/2,yl1+((yl2-yl1)+textlane.height)/2);
    rectangle(img,pt,pt+Point(textlane.width, -textlane.height),CV_RGB(0,0,0),FILLED);
    putText(img,direction,pt,FONT_HERSHEY_SIMPLEX,0.5,CV_RGB(255,255,255),1,LINE_AA);
   }
    else if(yl1>yl2){
        Point pt(x1l1+((x2l1-x1l1)-textlane.width)/2,yl2+((yl1-yl2)+textlane.height)/2);
        rectangle(img,pt,pt+Point(textlane.width, -textlane.height),CV_RGB(0,0,0),FILLED);
        putText(img,direction,pt,FONT_HERSHEY_SIMPLEX,0.5,CV_RGB(255,255,255),1,LINE_AA);
    }
}

}
