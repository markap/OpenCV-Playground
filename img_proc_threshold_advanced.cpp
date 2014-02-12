#include "highgui.h"
#include "cv.h"
#include "stdio.h"

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

void sum_rgb(IplImage* src, IplImage* dst) {


    const char* window_title_r = "R";

    cvNamedWindow(window_title_r, CV_WINDOW_AUTOSIZE);
    cvMoveWindow(window_title_r, src->width, 0);

    const char* window_title_g = "G";

    cvNamedWindow(window_title_g, CV_WINDOW_AUTOSIZE);
    cvMoveWindow(window_title_g, src->width * 1.5, 0);

    const char* window_title_b = "B";

    cvNamedWindow(window_title_b, CV_WINDOW_AUTOSIZE);
    cvMoveWindow(window_title_b, src->width * 2, 0);

    const char* window_title_s = "Weighted sum";

    cvNamedWindow(window_title_s, CV_WINDOW_AUTOSIZE);
    cvMoveWindow(window_title_s, src->width * 2.5, 0);
    
    IplImage* r = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
    IplImage* g = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
    IplImage* b = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);

    // split/extract the channels
    cvSplit(src, r, g, b, NULL);

    cvShowImage(window_title_r, r);
    cvShowImage(window_title_g, g);
    cvShowImage(window_title_b, b);

    IplImage* s = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);

    cvAddWeighted(r, 1./3., g, 1./3., 0.0, s);
    cvAddWeighted(s, 2./3., b, 1./3., 0.0, s);

    cvShowImage(window_title_s, s);

    cvWaitKey(0);

    cvThreshold(s, dst, 100, 100, CV_THRESH_TRUNC);

    cvReleaseImage(&r);
    cvReleaseImage(&g);
    cvReleaseImage(&b);
    cvReleaseImage(&s);

}



int main(int argc, char** argv) {


    char window_title[] = "original";
    cvNamedWindow(window_title, CV_WINDOW_AUTOSIZE);
    IplImage* img = cvLoadImage(argv[1], 1);
    img = half_size(img);
    cvShowImage(window_title, img);

    IplImage* dst = cvCreateImage(cvGetSize(img), img->depth, 1);

    cvWaitKey(0);

    sum_rgb(img, dst);
    cvShowImage(window_title, dst);
    cvWaitKey(0);


    cvDestroyWindow(window_title);
    cvReleaseImage(&img);

}
