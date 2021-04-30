#ifndef __HLS_HEADER__
#define __HLS_HEADER__

#define HLS_TRACKBAR "HLS_trackbar"
#define CANNY_TRACKBAR "CANNY_trackbar"

#define HLS_outDIR "/data/HLS/"
#define CANNY_outDIR "/data/CANNYEDGE/"

#define HLS_OUTPUT "HLS_maskedImg.jpg"
#define CANNY_OUTPUT "CANNY_Img.jpg"

// HLS min, max value initializing.
int hmin = 0;
int lmin = 0;
int smin = 0;
int hmax = 179;
int lmax = 255;
int smax = 255;
// hmin : 34	lmin : 205	smin : 15	hmax : 63	lmax : 255	smax : 65

// cannyEdge Threshold value initializing.
int lowThres = 50;
int highThres = 150;
// lowThres : 33	highThres : 176

int kernelSize = 11;

#endif
