#include <opencv2/core.hpp>
#include <opencv2/core/opencl/opencl_info.hpp>

#include <iostream>

using namespace std;

int main() {
 std::cout << cv::getBuildInformation()<< std::endl;
 cv::dumpOpenCLInformation();
}