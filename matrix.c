#include "stdio.h"
#include "highgui.h"
#include "cv.h"


int main(int argc, char** argv) {

    float vals[] = {0.866025, -0.5, 0.5, 0.866025};

    CvMat rotmat;

    cvInitMatHeader(
        &rotmat,
        2,
        2,
        CV_32FC1,
        vals,
        CV_AUTOSTEP
    );


    printf("type is %d\n", cvGetElemType(&rotmat));

    printf("elem 1 1: %f\n", CV_MAT_ELEM(rotmat, float, 0, 0));


    CvMat* mat = cvCreateMat(5, 5, CV_32FC1);
    *((float*)CV_MAT_ELEM_PTR(*mat, 3,2)) = 7.7;
    printf("elem 3 2: %f\n", CV_MAT_ELEM(*mat, float, 3, 2));
    printf("elem 3 2: %f\n", cvGet2D(mat, 3, 2));

}
