#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

Mat img;
bool applyGray = false;
bool applyBlur = false;
bool applySobel = false;
int blurAmount = 15;

static void onChange(int pos, void* userInput)
{
    if (pos <= 0) return ;
    Mat imgBlur;
    // get pointer input image
    Mat* img = (Mat*)userInput;
    // apply blur filter
    blur(*img, imgBlur, Size(pos, pos));
    imshow("chicken", imgBlur);
}

void applyFilters(); 

void grayCallback(int state, void* user)
{
    applyGray = true;
    applyFilters();
}

void bgrCallback(int state, void* user)
{
    applyGray = false;
    applyFilters(); 
}

void blurCallback(int state, void* user)
{
    applyBlur = true;
    applyFilters(); 
}

void sobelCallback(int state, void* user)
{
    applySobel = true;
    applyFilters(); 
}

int main(int argc, char** argv)
{
    img = imread("../images/chicken.jpg");
    namedWindow("chicken");

    // create buttons
    createButton("Blur", blurCallback, NULL, QT_CHECKBOX, 0);
    createButton("RGB", bgrCallback, NULL, QT_RADIOBOX, 1);
    createButton("Gray", grayCallback, NULL, QT_RADIOBOX, 0);
    createButton("Sobel", sobelCallback, NULL, QT_PUSH_BUTTON, 0);
    createTrackbar("chicken", "chicken", &blurAmount, 30, onChange, &img);
    waitKey(0);
    destroyAllWindows();
    return 0;
}

void applyFilters()
{
    Mat result;
    img.copyTo(result);
    /* 
        OpenCV works by default with the BGR format, 
        and the color conversion is different for RGB 
        and BGR, even when converted to gray. 
        Some developers think that R+G+B/3 is true for gray,
        but the optimal gray value is called luminosity and has 
        the formula 0,21*R + 0,72*G + 0,07*B.
    */
    if (applyGray)
        onChange(blurAmount, &result);
    if (applyBlur)
        blur(result, result, Size(5,5));
    /*
        The sobel filter is an image derivate obtained using 
        the sobel operator, commonly used to detect edges. 
        OpenCV allows us to generate different derivates 
        with kernel size, but the most common is a 3x3 kernel
        to calculate the x derivates or y derivate.

        The most important sobel parameters are:
            - Input image
            - Output image
            - Output image depth (CV_8U, CV_16U, CV_32F, CV_64F)
            - Order of the derivate x
            - Order of the derivate y
            - Kernel size (a value of 3 by default)
    */
    
    if (applySobel)
        Sobel(result, result, CV_8U, 1, 1);
    imshow("chicken", result);
}