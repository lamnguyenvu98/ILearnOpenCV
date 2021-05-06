#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

const char* keys =
{
    "{help h usage ? | | print this message}"
};

int main(int argc, char** argv)
{
    /*        
        Can create a new matrix linking with a stored buffer
        from third party libraries without copying data using
        this constructor: Mat(size, type, pointer_to_buffer).

        Type of matrix using CV_number_typeC(n) where:
            - number_type is 8 bits unsigned (8U) to 64 float (64F)
            - n is the number of channels (the number of channels
                permitted ranges from 1 to CV_CN_MAX).

        ost common type of matrix:
            CV_8UC1 
            CV_8UC3 
            CV_8UC4 
            CV_32FC1 
            CV_32FC3 
            CV_32FC4 
    */

    CommandLineParser args(argc, argv, keys);
    if (args.has("help"))
    {
        cout << "[HELP] ./<execute_file> ";
        return -1;
    }

    Mat a = Mat(Size(5,5), CV_32F);
    cout << "Matrix a: \n" << a << endl;

    // intialize matrix with 0 or 1 values
    Mat mz = Mat::zeros(Size(5,5), CV_32F);
    cout << "\nMatrix ones mz: \n" << mz << endl;
    Mat mo = Mat::ones(5, 5, CV_32F);
    cout << "\nMatrix zeros mo: \n" << mo << endl;

    // ============ matrix operations ========================

    // we can add or subtract 2 matrices of the same size using
    // + and - operator
    Mat a1 = Mat::eye(3, 2, CV_32F); // identity matrix 3x2
    cout << "\nIdentity Matrix 3x2 a1: \n" << a1 << endl;

    Mat a2 = Mat::ones(3, 2, CV_32F); // ones matrix 3x2
    cout << "\nOnes matrix 3x2 a2: \n" << a2 << endl;

    Mat add_result = a1 + a2;
    cout << "\na1 + a2 = \n" << add_result << endl;

    Mat sub_result = a1 - a2;
    cout << "\na1 - a2 = \n" << sub_result << endl;

    // Multiply by a scalar using * operator or matrix
    // per element using ' mul ' function
    Mat a3 = Mat::eye(2, 3, CV_32F); // 2x3 identity matrix
    Mat a4 = Mat::ones(3, 2, CV_32F); // 3x2 ones matrix
    cout << "\nIdentity matrix 2x3 a3: \n" << a3 << endl;
    cout << "\nOnes matrix 3x2 a4: \n" << a4 << endl;
    // Scalar by matrix
    cout << "\na3 * 2 = \n" << a3*2 << endl;
    // matrix per element multiplication (element-wise)
    cout << "\n(a3 + 1) * (a3 + 3) = \n" << (a3+1).mul(a3+3) << endl;
    // matrix multiplication (dot operation) 2x3 dot 3x2 = 2x2 matrix
    cout << "\nSize a3 = " << a3.size() << ", size a4" << a4.size() \
        << ", size of (a3 dot a4) = " << (a3*a4).size() << endl;
    cout << "\na3 * a4 (a3 dot a4) = \n" << a3*a4 << endl;

    // tranpose and inverse matrix
    // create random matrix
    Mat1d a5(2, 8);
    randu(a5, Scalar(0), Scalar(300)); // data in range (0, 300)
    double stddev = 300.0 / 30.0; // 30% of values will be inside (0, 300)
    randn(a5, 0.0, stddev);
    cout << "\nRandom matrix a5: \n" << a5 << endl;
    cout << "\nTranpose a5: \n" << a5.t() << endl;

    a5 = a5.reshape(4, 4); // reshape a5 to 4x4
    cout << "\nNew shape a5: " << a5.size() << endl;
    // inverse matrix (matrix need to size n x n)
    cout << "\nInverse a5: \n" << a5.inv() << endl;

    // find min and max in matrix
    // minMaxLoc will return location and value
    float data[] = {1, 0, 9, 4, 8, 6}; 
    Mat a6(2, 3, CV_32F, &data); // wrap array data to Mat matrix
    cout << "\na6: \n" << a6 << endl;
    double min_val, max_val;
    Point idx_min, idx_max;
    minMaxLoc(a6, &min_val, &max_val, &idx_min, &idx_max);
    cout << "\nMax value in a6: " << max_val << endl;
    cout << "\nMin value in a6: " << min_val << endl;
    cout <<"\nLocation of max value in a6: " << idx_max << endl;
    cout <<"\nLocation of min value in a6: " << idx_min << endl;

    // count non zero
    int number_of_nonzero = countNonZero(a6);
    cout << "\nNumber of non zero element in matrix a6: " << number_of_nonzero << endl;

    // ============= find min max in multidimension matrix ==========
    // create multidim matrix :)
    int shape[3] = {4, 3, 2};
    Mat a7(3, shape, CV_8UC1, Scalar::all(1)); // Mat (ndim, shape, type)
    cout << "\na7 shape : \n" << a7.size << endl; // matrix shape (4 x 3 x 2)
    // visualize matrix ndim
    // a7 has shape of 4x3x2
    // visualize a7 [1, :, :]
    a7.at<uchar>(1,0,0) = 2; // set element at index a7 [1,0,0] = 2
    Mat slice_mat;
    cout << "\n";
    // access index of 3D matrix by create a slice 2d matrix 
    // a7 has shape 4 x 3 x 2
    // create slice_mat with shape 3 x 2 and take data at a7[1]
    // using a7.ptr<uchar>(1)
    slice_mat = Mat(3, 2, CV_8UC1, a7.ptr<uchar>(1));
    cout << "\nSlice matrix a7[1,:,:] \n" << slice_mat << endl;

    // find min max in multidim matrix using minMaxIdx
    int minIdx[3], maxIdx[3];
    double minval, maxval;
    minMaxIdx(a7, &minval, &maxval, minIdx, maxIdx, Mat());
    cout << minval << " " << maxval << " [" << minIdx[0] << " " << minIdx[1] \
        << " " << minIdx[2] << "]  [" << maxIdx[0] << " " << maxIdx[1] \
        << " " << maxIdx[2] << "]" << endl;

    // caculate mean and standard deviation
    Mat mean, stdd;
    meanStdDev(slice_mat, mean, stdd);
    cout << "\nMean: \n" << mean << endl;
    cout << "\nStandard deviation: \n" << stdd << endl;

    return 0;
}