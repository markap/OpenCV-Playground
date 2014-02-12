#include "highgui.h"
#include "cv.h"



int main(int argc, char** argv) {

    IplImage* src = cvLoadImage(argv[1], 1);
        
    cvLine(
        src,
        cvPoint(3,3),
        cvPoint(src->width, src->height),
        CV_RGB(100, 10, 200),
        10
    );

    cvCircle(
        src,
        cvPoint(src->width/2, src->height/2),
        100,
        CV_RGB(10, 200, 100),
        -1
    );        

    CvPoint points[3] = {
                    cvPoint(50, 30),
                    cvPoint(70, 50),
                    cvPoint(120, 50)
                        };


    CvPoint points2[5] = {
                    cvPoint(200, 200),
                    cvPoint(250, 250),
                    cvPoint(250, 280),
                    cvPoint(300, 200),
                    cvPoint(200, 270)
                        };


    CvPoint* contours[2] = {
        points,
        points2
    };

    int contours_n[2] = {
        3,
        5
    };

    cvFillPoly(
        src,
        contours,
        contours_n,
        2,
        CV_RGB(100, 10, 200)
    );
                

    cvNamedWindow("Line stuff", 1);
    cvShowImage("Line stuff", src);
    cvWaitKey(0);

    return 0;
}
