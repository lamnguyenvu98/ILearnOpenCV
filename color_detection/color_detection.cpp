#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const char* keys = {
    "{help h usage | | print this message}"
    "{i image | ../images/car.jpg | path to image}"
    "{f file | ../configcolor.yml | file of parameters}"
    "{t tune | | this enable trackbar to tune parameters}"
};

int hmin, smin, vmin;
int hmax, smax, vmax; 

void createYMLFile(String pathimg, String ffilepath, bool tuner)
{
    if (tuner)
    {
        FileStorage fs1(ffilepath, FileStorage::READ);
        if (!fs1.isOpened())
        {
            cout << "Can't use tuner because yml file not exist\nExecute file without flag -t to create new config yml file\n";
            return ;
        }
        fs1["HueMin"] >> hmin;
        fs1["HueMax"] >> hmax;
        fs1["SatMin"] >> smin;
        fs1["SatMax"] >> smax;
        fs1["ValMin"] >> vmin;
        fs1["ValMax"] >> vmax;

    }
    else {
        hmin = 0; smin = 0; vmin = 0;
        hmax = 0; smax = 0; vmax = 0;
    }
    Mat img = imread(pathimg);
    float ratio = 500.0 / img.size().width;
    resize(img, img, Size(500, ratio * img.size().height));
    Mat hsvimg, mask;
    cvtColor(img, hsvimg, COLOR_BGR2HSV);
    namedWindow("Trackbars", (640,200));
    createTrackbar("Hue Min", "Trackbars", &hmin, 179);
    createTrackbar("Hue Max", "Trackbars", &hmax, 179);
    createTrackbar("Sat Min", "Trackbars", &smin, 255);
    createTrackbar("Sat Max", "Trackbars", &smax, 255);
    createTrackbar("Val Min", "Trackbars", &vmin, 255);
    createTrackbar("Val Max", "Trackbars", &vmax, 255);
    String buff = ffilepath;
    buff.insert(buff.length() - 4, "_buff");
    FileStorage fs(buff, FileStorage::WRITE);
    while (true)
    {
        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);
        inRange(hsvimg, lower, upper, mask);
        erode(mask, mask, Mat(), Point(-1,-1), 2);
        dilate(mask, mask, Mat(), Point(-1,-1), 2);
        imshow("Tune", mask);
        char c = (char) waitKey(1);
        if (c == 's')
        {
            fs = FileStorage(ffilepath, FileStorage::WRITE);
            fs << "HueMin" << hmin;
            fs << "HueMax" << hmax;
            fs << "SatMin" << smin;
            fs << "SatMax" << smax;
            fs << "ValMin" << vmin;
            fs << "ValMax" << vmax;
            fs.release();
            String remove = "rm " + buff;
            system(remove.c_str());
            break;
        }
        else if (c == 27)
        {
            String remove = "rm " + buff;
            system(remove.c_str());
            break;
        }
    }
}

int main(int argc, char** argv)
{
    CommandLineParser args(argc, argv, keys);
    String filepath = args.get<String>("file");
    String imagepath = args.get<String>("image");
    bool tune = args.has("tune");
    FileStorage fs(filepath, FileStorage::READ);
    if (args.has("help"))
    {
        cout << "Ex: ./<execute_file> -f=images/car.jpg -f=configcolor.yml -t\n\n";
        cout << "Flag:\n-i=path/to/image\n\n-f=path/to/file (default:configcolor.yml)\n\n-t : use this flag to tune parameter and when file yml is already existed\n";
        return -1;
    }
    if (!fs.isOpened() || tune)
    {
        //string path(argv[1]);
        //cout<<"Config file does not exist...\n\nCreate new config file by yourself....\n\n";
        createYMLFile(imagepath, filepath, tune);
    }
    else
    {
        Mat output, mask, hsvimg, img = imread(imagepath);
        float ratio = 500.0 / img.size().width;
        resize(img, img, Size(500, ratio * img.size().height));
        cvtColor(img, hsvimg, COLOR_BGR2HSV);
        fs["HueMin"] >> hmin;
        fs["HueMax"] >> hmax;
        fs["SatMin"] >> smin;
        fs["SatMax"] >> smax;
        fs["ValMin"] >> vmin;
        fs["ValMax"] >> vmax;
        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);
        inRange(hsvimg, lower, upper, mask);
        // use series of dilation and erosions to remove any
        // small blobs left in mask
        erode(mask, mask, Mat(), Point(-1,-1), 2);
        dilate(mask, mask, Mat(), Point(-1,-1), 2);
        bitwise_and(img, img, output, mask);
        imshow("Image", output);
        waitKey(0);
    }
    return 0;
}