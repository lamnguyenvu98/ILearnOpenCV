#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const char* keys = {
    "{help h usage | | print this message}"
    "{c camid | 0 | id of camera}"
    "{f file | ../configcolor.yml | file of parameters}"
};

int main(int argc, char** argv)
{
    CommandLineParser args(argc, argv, keys);
    String filepath = args.get<String>("file");
    int camid = args.get<int>("camid");
    if (args.has("help"))
    {
        cout << "Ex: ./<execute_file> -c=0 -f=../configcolor.yml\n\n";        
        return -1;
    }
    VideoCapture cap(camid);
    if (!cap.isOpened())
    {
        cout << "[ERROR] Can't read webcam. Probably you pass wrong id camera...\n";
        return -1;
    }
    FileStorage fs(filepath, FileStorage::READ);
    if (!fs.isOpened())
    {
        cout << "[ERROR] No such file existed in directory...Execute color_detection.cpp to create yml file\n";
        return -1;
    }
    int hmin, smin, vmin;
    int hmax, smax, vmax;
    fs["HueMin"] >> hmin;
    fs["HueMax"] >> hmax;
    fs["SatMin"] >> smin;
    fs["SatMax"] >> smax;
    fs["ValMin"] >> vmin;
    fs["ValMax"] >> vmax;
    Mat output, mask, hsvimg, frame;
    while(waitKey(1) != 27)
    {
        cap >> frame;
        cvtColor(frame, hsvimg, COLOR_BGR2HSV);
        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);
        inRange(hsvimg, lower, upper, mask);
        // use series of dilation and erosions to remove any
        // small blobs left in mask
        erode(mask, mask, Mat(), Point(-1,-1), 2);
        dilate(mask, mask, Mat(), Point(-1,-1), 2);
        bitwise_and(frame, frame, output, mask);
        imshow("Output", output);
        imshow("Mask", mask);
    }
    destroyAllWindows();
    return 0;
}