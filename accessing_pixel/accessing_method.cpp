#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

using namespace std;
using namespace cv;

void Chuyen_Doi_Gamma(Mat& out, double gamma, double c)
{
    for (int row=0; row < out.rows; row++)
    {   
        uchar* ptrRow = out.ptr<uchar>(row);
        for (int col=0; col < out.cols; col++)
        {
            //ptrRow[col] = 255 - ptrRow[col];
            ptrRow[col] = c * pow(ptrRow[col], gamma);
        }
    }
}

void Dao_Anh(Mat& out)
{
    for (int row=0; row < out.rows; row++)
    {   
        uchar* ptrRow = out.ptr<uchar>(row);
        for (int col=0; col < out.cols; col++)
        {
            ptrRow[col] = 255 - ptrRow[col];
        }
    }
}

void Chuyen_Doi_Logarit(Mat& out, float c)
{
    for (int row=0; row < out.rows; row++)
    {   
        uchar* ptrRow = out.ptr<uchar>(row);
        for (int col=0; col < out.cols; col++)
        {
            ptrRow[col] = c * log(1 + ptrRow[col]);
        }
    }
}

// threshold image
// Using LUT opencv
enum mode_thresh {
    BINARY = 0,
    BINARY_INV = 1
};
void Cat_Nguong1(const Mat& input, Mat& output, int thresh, int mode)
{
    Mat lut(1, 256, CV_8UC1);
    for (int i=0; i < 256; i++)
    {
        //float x = (float)i / 256.0;
        lut.at<uchar>(i) = (mode == BINARY) ? ((i < thresh) ? 0 : 255) : ((i < thresh) ? 255 : 0);
    }
    LUT(input, lut, output);
}

// traditional
void Cat_Nguong2(Mat& src, Mat& output, int threshold, bool inverted=false)
{
    // if (src.channels() == 3)
    //     cvtColor(src, output, COLOR_BGR2GRAY);
    Mat temp = Mat(src.rows, src.cols, CV_8UC1);
    for (int row = 0; row<src.rows; row++)
    {
        uchar* ptrRowSrc = src.ptr<uchar>(row);
        uchar* ptrRowOut = temp.ptr<uchar>(row);
        for (int col = 0; col < src.cols; col++)
        {
            if (ptrRowSrc[col] < threshold)
                ptrRowOut[col] = inverted ? 255 : 0;
            else ptrRowOut[col] = inverted ? 0 : 255;
        }
    }
    output = temp;
}

int main(int, char** argv)
{
    Mat img = imread(argv[1]);
    Mat src;
    int gamma = 0, c = 0;
    float ratio = 500.0 / img.size().width;
    resize(img, img, Size(500, (int)(ratio * img.size().height)));
    //src.copyTo(result);
    cvtColor(img, src, COLOR_BGR2GRAY);
    Mat thres;
    threshold(src, thres, 100, 255, THRESH_BINARY);
    imshow("Thresh", thres);
    //Chuyen_Doi_Gamma(src, 0.8, 1);
    //Chuyen_Doi_Logarit(src, 0.2);

    Mat result1;
    Cat_Nguong1(src, result1, 100, BINARY);
    imshow("Result 1", result1);
    Mat result2;
    Cat_Nguong2(src, result2, 100, false);
    imshow("Result 2", result2);
    waitKey(0);
    return 0;
}