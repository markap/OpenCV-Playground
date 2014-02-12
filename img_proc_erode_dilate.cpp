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


/**
    dilate 
    computes maximal pixel value and replace the image pixel below 
    anchor point with maximal pixel value

    because white is max, more white than black
*/
void dilatefilter(IplImage* image) {

    const char* window_title = "Dilate";

    cvNamedWindow(window_title, CV_WINDOW_AUTOSIZE);
    cvMoveWindow(window_title, image->width, 0);

    
    IplImage* out_image = cvCreateImage(
                        cvGetSize(image),
                        8,
                        3 
                    );

    cvDilate(image, out_image);

    cvShowImage(window_title, out_image);

    cvWaitKey(0);
    cvReleaseImage(&out_image);

    cvDestroyWindow(window_title);
}


/**
    erode 
    computes minimum pixel value and replace the image pixel below 
    anchor point with minimum pixel value

    because black is min, more black than white
*/
void erodefilter(IplImage* image) {

    const char* window_title = "Erode";

    cvNamedWindow(window_title, CV_WINDOW_AUTOSIZE);
    cvMoveWindow(window_title, image->width, 0);

    
    IplImage* out_image = cvCreateImage(
                        cvGetSize(image),
                        8,
                        3 
                    );

    IplConvKernel* kernel = cvCreateStructuringElementEx(
        25,
        25,
        12, 
        7,
        CV_SHAPE_RECT
    );

    cvErode(image, out_image, kernel);
    
    cvReleaseStructuringElement(&kernel);

    cvShowImage(window_title, out_image);

    cvWaitKey(0);
    cvReleaseImage(&out_image);

    cvDestroyWindow(window_title);
}


int main(int argc, char** argv) {


    char window_title[] = "original";
    cvNamedWindow(window_title, CV_WINDOW_AUTOSIZE);
    IplImage* img = cvLoadImage(argv[1], 1);
    img = half_size(img);
    cvShowImage(window_title, img);

    cvWaitKey(0);
    erodefilter(img);
    cvWaitKey(0);
    dilatefilter(img);
    cvWaitKey(0);


    cvDestroyWindow(window_title);
    cvReleaseImage(&img);

}
