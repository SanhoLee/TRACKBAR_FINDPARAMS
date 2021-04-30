#include <iostream>
#include <string>
#include <filesystem>
#include <unistd.h>
#include "commonFunction.hpp"
#include "variables.hpp"

using namespace std;

int main(int argc, char **argv)
{
    char curPath[256];
    char imgSrcPath[256];
    char imgReadPath[256];
    char imgOutPath[256];

    char srcDir[100];
    char OutDir[100];

    Mat imgMasked, imgBlur, imgCanny;
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
        memset(OutDir, 0, sizeof(OutDir));

        strcpy(srcDir, "/data/imgSRC/");
        strcpy(OutDir, CANNY_outDIR);

        makeTargetPath(curPath, srcDir, imgSrcPath);
        makeTargetPath(curPath, OutDir, imgOutPath);
        makeTargetPath(imgSrcPath, argv[1], imgReadPath);
    }

    // create window.
    namedWindow(CANNY_TRACKBAR, WINDOW_NORMAL);

    // create new trackbar.
    createTrackbar("lowThres : ", CANNY_TRACKBAR, &lowThres, 200);
    createTrackbar("highThres : ", CANNY_TRACKBAR, &highThres, 200);

    while (true)
    {
        /* read origin img */
        imgMasked = imread(imgReadPath);
        if (isImgEmpty(imgMasked, imgReadPath))
        {
            return 0;
        }

        /* Blur img and Canny Edge function run. */
        GaussianBlur(imgMasked, imgBlur, Size(kernelSize, kernelSize), kernelSize, kernelSize);
        Canny(imgBlur, imgCanny, lowThres, highThres);

        /* show current masking color boundary. */
        show_cannyEdgeValue(lowThres, highThres);

        // show origin and cannyEdge img.
        imshow("imgCanny", imgCanny);
        rtnKey = waitKey(1);

        /* save masked img when esc key is pressed. */
        if (rtnKey == 27)
        {
            strcat(imgOutPath, CANNY_OUTPUT);
            imwrite(imgOutPath, imgCanny);
            return 0;
        }
    }
    return 0;
}