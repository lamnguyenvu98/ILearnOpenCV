#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

int main(int argc, char** argv)
{
    Mat img = imread(argv[1]);
    float ratio = 500.0 / img.size().width;
    resize(img , img, Size(500, (int)(ratio * img.size().height)));
    Mat stackimg;
    Mat src;
    img.copyTo(src);
    // change to gray using aceesing pixel
    for (int row = 0; row < img.rows; ++row)
    {
        Vec3b* ptrRow = img.ptr<Vec3b>(row);
        for (int col = 0; col < img.cols; ++col)
        {
                uchar med = ptrRow[col][0] + ptrRow[col][1] + ptrRow[col][2];
            
            ptrRow[col] = {med, med, med};
        }
    }
    std::cout << "Img channels : " << img.channels() << std::endl;
    hconcat(src, img, stackimg);
    imshow("Left: Source Image, Right: Image fake to grayscale", stackimg);
    waitKey(0);
    return 0;
}