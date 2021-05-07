#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;

int main(int argc, char** argv)
{
    // Read images
    Mat chicken = imread("../images/chicken.jpg");
    if (!chicken.data)
    {
        cout << "Can't read chicken image\n";
        return -1;
    }
    Mat beach = imread("../images/beach.jpg");
    if (!beach.data)
    {
        cout << "Can't read beach image\n";
        return -1;
    }
    namedWindow("Chicken", WINDOW_NORMAL);
    namedWindow("Beach", WINDOW_AUTOSIZE);

    resizeWindow("Chicken", 520, 520); // work for windows non autosize

    // move windows on desktop
    moveWindow("Chicken", 10, 10); // 10 pixels to left, 10 pixels up
    moveWindow("Beach", 520, 10); // 520 pixels to left, 10 pixels up

    imshow("Chicken", chicken);
    imshow("Beach", beach);

    waitKey(0);
    destroyWindow("Chicken");
    destroyWindow("Beach");

    // Create 10 windows
    for (int i=0; i < 10; i++)
    {
        ostringstream ss;
        ss << "Beach" << i;
        namedWindow(ss.str());
        moveWindow(ss.str(), 20*i, 20*i);
        imshow(ss.str(), beach);
    }
    waitKey(0);
    destroyAllWindows();
    return 0;
}