#include "highgui.h"
#include "cv.h"

void draw_mouse_callback(
    int event, int x, int y, int flags, void* param
);

bool drawing_box = false;

CvPoint starting_point;

void draw_line(IplImage* img, CvPoint ending_point) {

    cvLine(
        img,
        starting_point,
        ending_point,
        CV_RGB(100, 10, 200),
        10
    );

    cvShowImage("Line stuff", img);
    
}


int main(int argc, char** argv) {

    IplImage* src = cvLoadImage(argv[1], 1);
        
    cvNamedWindow("Line stuff", 1);
    cvShowImage("Line stuff", src);

    cvSetMouseCallback("Line stuff", draw_mouse_callback, (void*) src);

    int key = cvWaitKey(0);
    printf("the key is %d\n", key);

    if (key == 115) {
        cvSaveImage("./tmp/image.jpg", src);
    }

    cvReleaseImage(&src);
    cvDestroyWindow("Line stuff");

    return 0;
}

void draw_mouse_callback(int event, int x, int y, int flags, void* param) {

    IplImage *image = (IplImage*)param;


    if (event == CV_EVENT_LBUTTONDOWN) {
        printf("down \n");
        starting_point = cvPoint(x,y);
    } else if (event == CV_EVENT_LBUTTONUP) {
        printf("up \n");
        draw_line(image, cvPoint(x,y));
    }
}
