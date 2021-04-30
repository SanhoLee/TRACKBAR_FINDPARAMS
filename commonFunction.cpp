#include <iostream>
#include "commonFunction.hpp"

using namespace std;

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

void show_cannyEdgeValue(int lowThres,
                         int highThres)
{
    cout << "lowThres : " << lowThres
         << "\thighThres : " << highThres
         << endl;
}

void show_HLSValue(int hmin,
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

void makeTargetPath(char *path1, char *path2, char *dstPath)
{
    strcpy(dstPath, path1);
    strcat(dstPath, path2);
}