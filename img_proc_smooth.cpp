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


void smooth_filter(IplImage* image, const char* window_title, 
                    int type, int param1, int param2) {

    cvNamedWindow(window_title, CV_WINDOW_AUTOSIZE);
    cvMoveWindow(window_title, image->width, 0);

    
    IplImage* smoothed_image = cvCreateImage(
                        cvGetSize(image),
                        8,
                        1 
                    );

    cvSmooth(image, smoothed_image, type, param1, param2, 0, 0);

    cvShowImage(window_title, smoothed_image);

    cvWaitKey(0);
    cvReleaseImage(&smoothed_image);

    cvDestroyWindow(window_title);
}


void gaussian_filter(IplImage* image, int param1, int param2) {
    smooth_filter(image, "Gaussian", CV_GAUSSIAN, param1, param2);
}

void blur_filter(IplImage* image, int param1, int param2) {
    smooth_filter(image, "Blur", CV_BLUR, param1, param2);
}

void bilateral_filter(IplImage* image, int param1, int param2) {
    smooth_filter(image, "Bilateral", CV_BILATERAL, param1, param2);
}

void median_filter(IplImage* image, int param1, int param2) {
    smooth_filter(image, "Median", CV_MEDIAN, param1, param2);
}

int main(int argc, char** argv) {


    char window_title[] = "original";
    cvNamedWindow(window_title, CV_WINDOW_AUTOSIZE);
    IplImage* img = cvLoadImage(argv[1], 0);
    img = half_size(img);
    cvShowImage(window_title, img);

    /**
    cvWaitKey(0);
    gaussian_filter(img, 1, 1);
    cvWaitKey(0);
    gaussian_filter(img, 3, 3);
    cvWaitKey(0);
    gaussian_filter(img, 7, 7);
    cvWaitKey(0);
    gaussian_filter(img, 13, 13);
    cvWaitKey(0);
    */
/*
    cvWaitKey(0);
    blur_filter(img, 1, 1);
    cvWaitKey(0);
    blur_filter(img, 3, 3);
    cvWaitKey(0);
    blur_filter(img, 7, 7);
    cvWaitKey(0);
    blur_filter(img, 13, 13);
    cvWaitKey(0);
*/
/*
    cvWaitKey(0);
    bilateral_filter(img, 1, 1);
    cvWaitKey(0);
    bilateral_filter(img, 3, 3);
    cvWaitKey(0);
    bilateral_filter(img, 7, 7);
    cvWaitKey(0);
    bilateral_filter(img, 13, 13);
    cvWaitKey(0);
   */ 
    cvWaitKey(0);
    median_filter(img, 1, 1);
    cvWaitKey(0);
    median_filter(img, 3, 3);
    cvWaitKey(0);
    median_filter(img, 7, 7);
    cvWaitKey(0);
    median_filter(img, 13, 13);
    cvWaitKey(0);

    cvDestroyWindow(window_title);
    cvReleaseImage(&img);

}
