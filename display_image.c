#include "highgui.h"
#include "cv.h"

void smooth(IplImage* image) {

    char in_title[] = "Example-in";
    char out_title[] = "Example-out";

    cvNamedWindow(in_title, CV_WINDOW_AUTOSIZE);
    cvNamedWindow(out_title, CV_WINDOW_AUTOSIZE);

    cvShowImage(in_title, image);
    
    IplImage* smoothed_image = cvCreateImage(
                        cvGetSize(image),
                        8,
                        1 
                    );

    cvSmooth(image, smoothed_image, CV_GAUSSIAN, 3, 3, 0, 0);

    cvShowImage(out_title, smoothed_image);

    cvReleaseImage(&smoothed_image);

    cvWaitKey(0);
    
    cvDestroyWindow(in_title);
    cvDestroyWindow(out_title);
}

IplImage* doPyrDown(IplImage* in) {

    assert(in->width%2 ==0 && in->height%2 == 0);

    IplImage* out = cvCreateImage(
                        cvSize(in->width/2, in->height/2),
                        in->depth,
                        in->nChannels
    );
    cvPyrDown(in, out, CV_GAUSSIAN_5x5);
    return (out);
}

IplImage* doCanny(IplImage* in, double lowThresh, double highThresh, 
                        double aperture) {

    if (in->nChannels != 1) {
        return(0);
    }

    IplImage *out = cvCreateImage(cvGetSize(in),
                        IPL_DEPTH_8U,
                        1);

    cvCanny(in, out, lowThresh, highThresh, aperture);
    return (out);
}




int main(int argc, char** argv) {


    cvNamedWindow("test", CV_WINDOW_AUTOSIZE);
    IplImage* img = cvLoadImage(argv[1], 0);
    IplImage* out = doCanny(img, 10, 50, 3);
    //smooth(img);
    cvShowImage("test", out);
    cvWaitKey(0);
    cvShowImage("test", img);
    cvWaitKey(0);
    cvDestroyWindow("test");
    cvReleaseImage(&img);

}
