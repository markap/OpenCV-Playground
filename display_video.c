#include "highgui.h"

int main(int argc, char** argv) {

    const char *title = argc > 2 ? argv[2] : "Ghost";

    cvNamedWindow(title, CV_WINDOW_AUTOSIZE);

    CvCapture* capture = cvCreateFileCapture(argv[1]);
    IplImage* frame;

    while(1) {
        frame = cvQueryFrame(capture);
        if (!frame) break;

        cvShowImage(title, frame);
        char c = cvWaitKey(5);
        if (c == 27) break;
    }

    cvReleaseCapture(&capture);
    cvDestroyWindow(title);
}
