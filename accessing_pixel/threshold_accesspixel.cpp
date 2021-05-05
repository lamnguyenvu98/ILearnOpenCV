#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void ResizeWithRatio(Mat& src, Mat& output, int size, int mode)
{
    float ratio;
    switch(mode)
    {
        case 0:
            ratio = (float)size / src.size().width;
            resize(src, output, Size(size, int(ratio * src.size().height)));
            break;
    
        case 1:
            ratio = (float)size / src.size().height;
            resize(src, output, Size(int(ratio  * src.size().width), size));
            break;
        default:
            cout<<"[ERROR] Pick right mode:\n[+] 0: Scale image with width = size\n[+] 1: Scale image with height = size"<<endl;
    }
}

void Cat_Nguong(Mat& src, Mat& output, int threshold, bool inverted=false)
{
    if (src.channels() == 3)
        cvtColor(src, output, COLOR_BGR2GRAY);
    for (int row = 0; row<output.rows; row++)
    {
        uchar* ptrRow = output.ptr<uchar>(row);
        for (int col = 0; col<output.cols; col++)
        {
            // if (inverted)
            // {
            //     if (ptrRow[col] < threshold)
            //         ptrRow[col] = 255;
            //     else ptrRow[col] = 0;
            // }
            // else
            // {
            //     if (ptrRow[col] < threshold)
            //         ptrRow[col] = 0;
            //     else ptrRow[col] = 255;
            // }
            if (ptrRow[col] < threshold)
                ptrRow[col] = inverted ? 255 : 0;
            else ptrRow[col] = inverted ? 0 : 255;
        }
    }
}

int main(int argc, char** argv)
{
    if (argc < 4)
    {
        cerr<<"[ERROR] You should pass all required command\n./<program> <path of image> <size want to scale> <mode to scale>\n[+] 0: Scale respectively with width\n[+] 1: Scale respectively with height"<<endl;
        return -1;
    }
    Mat img = imread(argv[1]);
    Mat out;
    char *size = argv[2];
    char *mode = argv[3];
    //cvtColor(img, img, COLOR_BGR2GRAY);
    Cat_Nguong(img, out, 70, true);
    ResizeWithRatio(out, out, atoi(size), atoi(mode));
    imshow(argv[1], out);
    waitKey(0);
    return 0;
}