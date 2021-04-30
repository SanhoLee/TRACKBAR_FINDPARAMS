#include <iostream>
#include <string>
#include <filesystem>
#include <unistd.h>
#include "CV_header.hpp"
#include "HLS_trackbar.hpp"

using namespace std;
using namespace cv;

int isImgEmpty(Mat imgSrc, char *imgReadPath);
void makeTargetPath(char *path1, char *path2, char *dstPath);
void show_currentValue(int hmin,
                       int lmin,
                       int smin,
                       int hmax,
                       int lmax,
                       int smax);

int main(int argc, char **argv)
{
    char curPath[256];
    char imgSrcPath[256];
    char imgReadPath[256];
    char imgOutPath[256];

    char srcDir[100];
    char hlsOutDir[100];

    Mat img, imgHLS, imgMasked;
    int rtnKey = 0;

    memset(curPath, 0, sizeof(curPath));
    getcwd(curPath, sizeof(curPath));

    // get filename.
    if (argc == 0)
    {
        cout << " INPUT ERROR :: ARGUMENT NUMBER : 0 " << endl;
        return -1;
    }
    else if (argc != 2)
    {
        cout << " INPUT ERROR :: ARGUMENT NUMBER SHOULD BE 2. " << endl;
        cout << " INPUT ERROR :: ARGUMENT NUMBER : " << argc << endl;
        return -1;
    }
    else
    {
        memset(imgSrcPath, 0, sizeof(imgSrcPath));
        memset(imgReadPath, 0, sizeof(imgReadPath));
        memset(imgOutPath, 0, sizeof(imgOutPath));
        memset(srcDir, 0, sizeof(srcDir));
        memset(hlsOutDir, 0, sizeof(hlsOutDir));

        strcpy(srcDir, "/data/imgSRC/");
        strcpy(hlsOutDir, "/data/HLS/");

        makeTargetPath(curPath, srcDir, imgSrcPath);
        makeTargetPath(curPath, hlsOutDir, imgOutPath);
        makeTargetPath(imgSrcPath, argv[1], imgReadPath);
    }

    // create window.
    namedWindow(trackbarName, WINDOW_NORMAL);

    // create new trackbar.
    createTrackbar("hmin : ", trackbarName, &hmin, 179);
    createTrackbar("lmin : ", trackbarName, &lmin, 255);
    createTrackbar("smin : ", trackbarName, &smin, 255);
    createTrackbar("hmax : ", trackbarName, &hmax, 179);
    createTrackbar("lmax : ", trackbarName, &lmax, 255);
    createTrackbar("smax : ", trackbarName, &smax, 255);

    while (true)
    {
        // read origin img
        img = imread(imgReadPath);
        if (isImgEmpty(img, imgReadPath))
        {
            return 0;
        }

        // convert color space to HLS.
        cvtColor(img, imgHLS, COLOR_BGR2HLS);

        // masking img with specific color elements.
        Scalar lowerb_(hmin, lmin, smin);
        Scalar upperb_(hmax, lmax, smax);
        inRange(imgHLS, lowerb_, upperb_, imgMasked);

        // show current masking color boundary.
        show_currentValue(hmin, lmin, smin, hmax, lmax, smax);

        // show masked img.
        imshow("imgMasked", imgMasked);
        rtnKey = waitKey(1);

        // save masked img when esc key is pressed.
        if (rtnKey == 27)
        {
            strcat(imgOutPath, outputImgName);
            imwrite(imgOutPath, imgMasked);
            return 0;
        }
    }
    return 0;
}

/* -------------- DEFINE FUNCTION. -------------- */

void show_currentValue(int hmin,
                       int lmin,
                       int smin,
                       int hmax,
                       int lmax,
                       int smax)
{
    cout << "hmin : " << hmin
         << "\tlmin : " << lmin
         << "\tsmin : " << smin
         << "\thmax : " << hmax
         << "\tlmax : " << lmax
         << "\tsmax : " << smax
         << endl;
}

int isImgEmpty(Mat imgSrc, char *imgReadPath)
{
    if (imgSrc.empty())
    {
        cout << "IMG LOADED FAILED :: CHECK imgSRC Folder." << endl;
        cout << "ENTERED IMG PATH :: " << imgReadPath << endl;
        return 100;
    }
    else
    {
        return 0;
    }
}

void makeTargetPath(char *path1, char *path2, char *dstPath)
{
    strcpy(dstPath, path1);
    strcat(dstPath, path2);
}