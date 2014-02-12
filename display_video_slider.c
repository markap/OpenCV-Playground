#include "highgui.h"
#include "cv.h"


int g_slider_position = 0;
CvCapture* g_capture = NULL;

void onTrackbarSlide(int pos) {

    cvSetCaptureProperty(
        g_capture,
        CV_CAP_PROP_POS_FRAMES,
        pos
    );
}

int main(int argc, char** argv) {

    const char *title = argc > 2 ? argv[2] : "Ghost";

    cvNamedWindow(title, CV_WINDOW_AUTOSIZE);

    g_capture = cvCreateFileCapture(argv[1]);

    int frames = (int) cvGetCaptureProperty(
        g_capture,
        CV_CAP_PROP_FRAME_COUNT
    );

    if (frames != 0) {
        cvCreateTrackbar(
            "Position",
            title,
            &g_slider_position,
            frames,
            onTrackbarSlide
        );
    }

    IplImage* frame;

    while(1) {
        frame = cvQueryFrame(g_capture);
        if (!frame) break;
        cvSetTrackbarPos("Position", title, ++g_slider_position);

        cvShowImage(title, frame);
        char c = cvWaitKey(5);
        if (c == 27) break;
    }

    cvReleaseCapture(&g_capture);
    cvDestroyWindow(title);

    return(0);
}
