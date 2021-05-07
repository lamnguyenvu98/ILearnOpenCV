#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace cv;

int main(int argc, char** argv)
{
    Mat img = imread(argv[1]);
    float ratio = 500.0 / img.size().width;
    resize(img , img, Size(500, (int)(ratio * img.size().height)));
    Mat stackimg;
    Mat src, yuv_img;
    img.copyTo(src);
    // change to gray using aceesing pixel
    for (int row = 0; row < img.rows; ++row)
    {
        Vec3b* ptrRow = img.ptr<Vec3b>(row);
        for (int col = 0; col < img.cols; ++col)
        {
            // optimal gray value called luminosity has formula:
            // 0.21*R + 0.72*G + 0.07*B
            // in implementation opencv format is BGR
            uchar med = 0.07*ptrRow[col][0] + 0.72*ptrRow[col][1] + 0.21*ptrRow[col][2];
            ptrRow[col] = {med, med, med};
        }
    }

    /*
        Another method is convert bgr channel to yuv
            - Y: the brightness present in image its value can range 
            from 0 to 255.
            - U and V: the chroma, or color, component. Its value 
            range from -128 to +127 (signed integers) or from 0 to
            255 (unsigned integers)

        Use split to split 3 slices of yuv_img (YUV image)
        First slice is Y space in YUV => gray image.
    */
    cvtColor(img, yuv_img, COLOR_BGR2YUV);
    Mat splitimg[3];
    split(yuv_img, splitimg);
    std::cout << "Img channels : " << img.channels() << std::endl;
    hconcat(src, img, stackimg);
    Mat yuv_split;
    hconcat(splitimg[0], splitimg[1], yuv_split);
    hconcat(yuv_split, splitimg[2], yuv_split);
    imshow("Y (grayscale) | U | V", yuv_split);
    imshow("Left: Source Image | Right: grayscale (first method)", stackimg);
    waitKey(0);
    return 0;
}