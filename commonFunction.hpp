#ifndef __COMMON_HEADER__
#define __COMMON_HEADER__

#include "CV_header.hpp"

using namespace cv;

int isImgEmpty(Mat imgSrc, char *imgReadPath);
void makeTargetPath(char *path1, char *path2, char *dstPath);

void show_cannyEdgeValue(int lowThres,
                         int highThres);

void show_HLSValue(int hmin,
                   int lmin,
                   int smin,
                   int hmax,
                   int lmax,
                   int smax);

#endif