#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

const char* keys =
{
    "{help h usage ? | | print this message}"
    "{f file | test.yml | path to file yml}"
};

int main(int argc, char** argv)
{
    CommandLineParser args(argc, argv, keys);
    if (args.has("help"))
    {
        cout << "[HELP] ./<execute_file> -f=path/to/image\nBy defaut, it will create test.yml\n";
        cout << "===> Example: ./basic_op -f=hello.yml\n";
        return -1;
    }
    String filepath = args.get<String>("file");
    // create writer
    FileStorage fs(filepath, FileStorage::WRITE);
    // save an int
    int fps = 5;
    fs << "fps" << fps;
    // create mat samples
    Mat m1 = Mat::eye(2,3,CV_32F);
    Mat m2 = Mat::ones(3,2,CV_32F);
    Mat result = (m1+1).mul(m1+3);
    // write result
    fs << "result" << result;
    // release the file
    fs.release();

    FileStorage fs2(filepath, FileStorage::READ);
    Mat r;
    int fpsr;
    fs2["result"] >> r;
    fs2["fps"] >> fpsr;
    cout << "result: \n" << r << endl;
    cout << "\nfps: " << fpsr << endl;
    fs2.release();
    return 0;
}