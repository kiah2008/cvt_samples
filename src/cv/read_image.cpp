#include<opencv2/opencv.hpp>   
#include<opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include <unistd.h>
#include <string>
#include <cvt_base.h>

using namespace std;
using namespace cv;

void print_usage() {
	LOGD("nnnn\n");
}

int main(int argc, char** argv)
{
	if (argc < 2) {
		print_usage();
		return 1;
	} else {
		std::string fileName = argv[1];
		int fpos = fileName.find_last_of('/');
		if (fpos != std::string::npos) {
			fileName = fileName.substr(fpos+1);
		}
		LOGD("good %s\n", fileName.c_str());
	}
	const char* pic_file = argv[1];

	if(access(pic_file, 0) != 0) {
		LOGD("fail to load %s\n", pic_file);
		return 1;
	}
	
	Mat image = imread(argv[1], cv::IMREAD_GRAYSCALE); //注意了，必须是载入灰度图
	if (image.empty())
	{
		cout << "read image failure" << endl;
		return -1;
	}

	// 全局二值化
	int th = 100;
	Mat global;
	threshold(image, global, th, 255, cv::THRESH_BINARY_INV);

	// 局部二值化
	int blockSize = 25;
	int constValue = 10;
	Mat local;
	adaptiveThreshold(image, local, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY_INV, blockSize, constValue);

	imshow("全局二值化", global);
	imshow("局部二值化", local);

	waitKey(0);
	return 0;
}