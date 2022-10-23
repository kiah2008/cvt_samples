/*
 *
 * cvout_sample just demonstrates the serial out capabilities of cv::Mat
 *  That is, cv::Mat M(...); cout << M;  Now works.
 *
 */

#include "opencv2/core.hpp"
#include <iostream>

using namespace std;
using namespace cv;

static void help(char** argv)
{
    cout
    << "\n------------------------------------------------------------------\n"
    << " This program shows the serial out capabilities of cv::Mat\n"
    << "That is, cv::Mat M(...); cout << M;  Now works.\n"
    << "Output can be formatted to OpenCV, matlab, python, numpy, csv and \n"
    << "C styles Usage:\n"
    << argv[0]
    << "\n------------------------------------------------------------------\n\n"
    << endl;
}


int main(int argc, char** argv)
{
    cv::CommandLineParser parser(argc, argv, "{help h||}");
    if (parser.has("help"))
    {
        help(argv);
        return 0;
    }
    Mat I = Mat::eye(4, 4, CV_64F);
    //cv::Mat left&top
    I.at<double>(1,1) = CV_PI;
    cout << "I = \n" << I << ";" << endl << endl;

    //mat(rows, cols)
    Mat r = Mat(10, 3, CV_8UC3);
    randu(r, Scalar::all(0), Scalar::all(255));

    cout << "r (default) = \n" << r << ";" << endl << endl;
    cout << "r (matlab) = \n" << format(r, Formatter::FMT_MATLAB) << ";" << endl << endl;
    cout << "r (python) = \n" << format(r, Formatter::FMT_PYTHON) << ";" << endl << endl;
    cout << "r (numpy) = \n" << format(r, Formatter::FMT_NUMPY) << ";" << endl << endl;
    cout << "r (csv) = \n" << format(r, Formatter::FMT_CSV) << ";" << endl << endl;
    cout << "r (c) = \n" << format(r, Formatter::FMT_C) << ";" << endl << endl;

    Point2f p(5, 1);
    cout << "p = " << p << ";" << endl;

    Point3f p3f(2, 6, 7);
    cout << "p3f = " << p3f << ";" << endl;

    vector<float> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    cv::Mat shortVec = Mat(v);
    cout << "shortvec = " << shortVec <<", wxh="<< shortVec.cols <<"x"<<shortVec.rows << shortVec.dims << endl;
    /* rows first
    shortvec = [1;
    2;
    3], wxh=1x3
    */
   cv::Mat shortVecT = shortVec.t();
   cout << "shortVecT = " << shortVecT <<", wxh="<< shortVecT.cols <<"x"<<shortVecT.rows << ",d"<< shortVecT.dims <<endl;
   /*
   shortVecT = [1, 2, 3], wxh=3x1,d2
   */
   cv::Mat shortVec31 = shortVec.reshape(1, 3);
   cout << "shortVec31 = " << shortVec31 <<", wxh="<< shortVec31.cols <<"x"<<shortVec31.rows <<",d"<< shortVec31.dims <<endl;
    /*
    shortVec31 = [1;
    2;
    3], wxh=1x3,d2
    */
    vector<Point2f> points(20);
    for (size_t i = 0; i < points.size(); ++i)
        points[i] = Point2f((float)(i * 5), (float)(i % 7));

    cout << "points = " << points << ";" << endl;
    return 0;
}
