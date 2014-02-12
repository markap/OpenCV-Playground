#include "highgui.h"
#include "cv.h"
#include "stdio.h"
#include "math.h"

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

IplImage *img = 0;
IplImage *img_threshold;
IplImage *img_adaptive_threshold;


int main(int argc, char** argv) {


    char window_title[] = "original";
    cvNamedWindow(window_title, CV_WINDOW_AUTOSIZE);
    img = cvLoadImage(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    img = half_size(img);
    cvShowImage(window_title, img);

    double threshold = 100.0;
    int threshold_type = CV_THRESH_BINARY;
    int adaptive_method = CV_ADAPTIVE_THRESH_MEAN_C; //CV_ADAPTIVE_THRESH_GAUSSIAN_C

    int block_size = 5;
    double offset = 5.5;

    cvWaitKey(0);

    img_threshold = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
    img_adaptive_threshold = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);

    char window_title_threshold[] = "threshold";
    cvNamedWindow(window_title_threshold, CV_WINDOW_AUTOSIZE);
    cvMoveWindow(window_title_threshold, img->width, 0);
    char window_title_adaptive_threshold[] = "adaptive threshold";
    cvNamedWindow(window_title_adaptive_threshold, CV_WINDOW_AUTOSIZE);
    cvMoveWindow(window_title_adaptive_threshold, img->width *2, 0);

    // thresholds
    cvThreshold(img, img_threshold, threshold, 255, threshold_type);
    cvAdaptiveThreshold(img, img_adaptive_threshold, 255,
                adaptive_method, threshold_type, block_size, offset);

    cvShowImage(window_title_threshold, img_threshold);
    cvShowImage(window_title_adaptive_threshold, img_adaptive_threshold);

    cvWaitKey(0);


    cvReleaseImage(&img);
    cvReleaseImage(&img_threshold);
    cvReleaseImage(&img_adaptive_threshold);

    cvDestroyWindow(window_title);
    cvDestroyWindow(window_title_threshold);
    cvDestroyWindow(window_title_adaptive_threshold);

    cvReleaseImage(&img);

}
