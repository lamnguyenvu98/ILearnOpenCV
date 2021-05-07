#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

// Variable to save position
int blurAmount = 15;

// trackbar call back function
static void onChange(int pos, void* userInput);

// mouse callback
static void onMouse(int event, int x, int y, int, void* userInput);

int main(int argc, char** argv)
{
    Mat chicken = imread("../images/chicken.jpg");
    if (!chicken.data)
    {
        cout << "Can't read chicken image\n";
        return -1;
    }
    namedWindow("Chicken");

    // create trackbar
    createTrackbar("Chicken", "Chicken", &blurAmount, 30, onChange, &chicken);

    setMouseCallback("Chicken", onMouse, &chicken);

    onChange(blurAmount, &chicken);

    waitKey(0);

    destroyAllWindows();

    return 0;
}

static void onChange(int pos, void* userInput)
{
    if (pos <= 0) return ;
    Mat imgBlur;
    // get pointer input image
    Mat* img = (Mat*)userInput;
    // apply blur filter
    blur(*img, imgBlur, Size(pos, pos));
    imshow("Chicken", imgBlur);
}

static void onMouse(int event, int x, int y, int, void* userInput)
{
    if (event != EVENT_LBUTTONDOWN)
        return ;
    Mat* img = (Mat*)userInput;
    circle(*img, Point(x,y), 10, Scalar(0,0,255), 3);
    //Call on change to get blurred image
    onChange(blurAmount, img); // pass img address (it's a pointer here remember?)
}