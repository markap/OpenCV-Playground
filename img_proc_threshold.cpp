#include "highgui.h"
#include "cv.h"

IplImage* half_size(IplImage* image) {

    IplImage* smaller_image = cvCreateImage(
        cvSize(image->width/2, image->height/2),
        image->depth,
        image->nChannels
    );
    cvResize(image, smaller_image, CV_INTER_CUBIC);
    cvReleaseImage(&image);
    return (smaller_image);
}


void threshold(IplImage* image, int thresh, int max_val, int type) {

    const char* window_title = "Threshold";

    cvNamedWindow(window_title, CV_WINDOW_AUTOSIZE);
    cvMoveWindow(window_title, image->width, 0);

    
    IplImage* out_image = cvCreateImage(
                        cvGetSize(image),
                        8,
                        1 
                    );


    cvThreshold(image, out_image, thresh, max_val, type);
    

    cvShowImage(window_title, out_image);

    cvWaitKey(0);
    cvReleaseImage(&out_image);

    cvDestroyWindow(window_title);
}


int main(int argc, char** argv) {


    char window_title[] = "original";
    cvNamedWindow(window_title, CV_WINDOW_AUTOSIZE);
    IplImage* img = cvLoadImage(argv[1], 0);
    img = half_size(img);
    cvShowImage(window_title, img);

    cvWaitKey(0);
    // each pixel > T changed to M, else 0/black 
    threshold(img, 100, 200, CV_THRESH_BINARY);
    cvWaitKey(0);
    // each pixel > T changed to M, else nothing
    threshold(img, 100, 255, CV_THRESH_TRUNC);
    cvWaitKey(0);


    cvDestroyWindow(window_title);
    cvReleaseImage(&img);

}
