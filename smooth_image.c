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
                        IPL_DEPTH_8U,
                        3
                    );

    cvSmooth(image, smoothed_image, CV_BLUR, 7, 7, 0, 0);

    cvShowImage(out_title, smoothed_image);

    cvReleaseImage(&smoothed_image);

    cvWaitKey(0);
    
    cvDestroyWindow(in_title);
    cvDestroyWindow(out_title);
}

int main(int argc, char** argv) {


    CvCapture* capture = cvCreateFileCapture(argv[1]);
    IplImage* frame;

    while(1) {
        frame = cvQueryFrame(capture);
        if (!frame) break;

        smooth(frame);
        //cvShowImage(title, frame);
        char c = cvWaitKey(15);
        if (c == 27) break;
    }

    cvReleaseCapture(&capture);
}
