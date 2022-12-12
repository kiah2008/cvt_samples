#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#ifdef HAVE_OPENCV_XFEATURES2D
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/core/ocl.hpp"

#include "cvt_base.h"

using namespace cv;
using namespace cv::xfeatures2d;
using std::cout;
using std::endl;

const char *keys =
    "{ help h |                  | Print help message. }"
    "{ @input1 | box.png          | Path to input image 1. }"
    "{ @input2 | box_in_scene.png | Path to input image 2. }";

template <typename type = Feature2D >
cv::Mat featureDetector(const char* hint, InputArray img1)
{
    //-- Step 1: Detect the keypoints using SURF Detector, compute the descriptors
    char chint[128] = {0};
    snprintf(chint, sizeof(chint), "%s featureDetector", hint);
    
    Mat img_matches;
    std::vector<KeyPoint> keypoints1;
    {
        TIME_LOG(chint);
        Ptr<type> detector = type::create();
        detector->detect(img1, keypoints1);
    }

    cv::drawKeypoints(img1, keypoints1, img_matches);

    int baseLine = 0;
    int thickness = 2;
    cv::Size textSize = cv::getTextSize(hint, 1, 2, thickness, &baseLine);
    const char* writeStr = "@Kiah";
    cv::Size writeBy = cv::getTextSize(writeStr, 1, 2, thickness, &baseLine);
    cv::putText(img_matches, hint, {(textSize.width)/2, img_matches.rows - (textSize.height)*3/2}, 1, 3, cv::Scalar(128,0,128),thickness);
    cv::putText(img_matches, writeStr, {(textSize.width)*2, img_matches.rows - (textSize.height)*3/2}, 1, 3, cv::Scalar(255,255,255),thickness);

    assert(!img_matches.empty());
    return img_matches;
}

template <typename type>
cv::Mat featureDetectorMatch(const char* hint, InputArray img1, InputArray img2)
{
    //-- Step 1: Detect the keypoints using SURF Detector, compute the descriptors
    char chint[128] = {0};
    snprintf(chint, sizeof(chint), "%s featureDetectorMatch", hint);
    
    Mat img_matches;
    std::vector<KeyPoint> keypoints1, keypoints2;
    Mat descriptors1, descriptors2;
    std::vector<DMatch> matches;
    {
    TIME_LOG(chint);

    Ptr<type> detector = type::create();

    detector->detectAndCompute(img1, noArray(), keypoints1, descriptors1);
    detector->detectAndCompute(img2, noArray(), keypoints2, descriptors2);
    //-- Step 2: Matching descriptor vectors with a brute force matcher
    // Since SURF is a floating-point descriptor NORM_L2 is used
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);
    matcher->match(descriptors1, descriptors2, matches);
    }

        
    //-- Draw matches
    drawMatches(img1, keypoints1, img2, keypoints2, matches, img_matches);

    int baseLine = 0;
    int thickness = 2;
    cv::Size textSize = cv::getTextSize(hint, 1, 2, thickness, &baseLine);
    const char* writeStr = "@Kiah";
    cv::Size writeBy = cv::getTextSize(writeStr, 1, 2, thickness, &baseLine);
    cv::putText(img_matches, hint, {(textSize.width)/2, img_matches.rows - (textSize.height)*3/2}, 1, 3, cv::Scalar(128,0,128),thickness);
    cv::putText(img_matches, writeStr, {(textSize.width)*2, img_matches.rows - (textSize.height)*3/2}, 1, 3, cv::Scalar(255,255,255),thickness);

    return img_matches;
}

int main(int argc, char *argv[])
{
    CommandLineParser parser(argc, argv, keys);
    UMat img1,img2;
    imread(samples::findFile(parser.get<String>("@input1")), IMREAD_GRAYSCALE).copyTo(img1);
    imread(samples::findFile(parser.get<String>("@input2")), IMREAD_GRAYSCALE).copyTo(img2);
    if (img1.empty() || img2.empty())
    {
        cout << "Could not open or find the image!\n"
             << endl;
        parser.printMessage();
        return -1;
    }

    
    if(cv::ocl::useOpenCL()) {
        cv::ocl::setUseOpenCL(false);
    }
    LOGD("runing %s opencl", cv::ocl::useOpenCL()?"with":"without");

    
    Mat img_detects, img_matches;
    //-- Show detected matches
    std::vector<Mat> imgs, imgs2;

#define TEST_DETECT_MATCH(x) imgs.push_back(featureDetectorMatch<x>(#x, img1, img2));

    TEST_DETECT_MATCH(SIFT);
    TEST_DETECT_MATCH(SURF);
    // TEST_DETECT_MATCH(StarDetector);
    TEST_DETECT_MATCH(ORB);

    TEST_DETECT_MATCH(BRISK);
    TEST_DETECT_MATCH(KAZE);
    TEST_DETECT_MATCH(AKAZE);
    
    cv::hconcat(imgs, img_matches);

    imshow("Matches", img_matches);


#define TEST_DETECT(x) imgs2.push_back(featureDetector<x>(#x, img1));
    TEST_DETECT(SIFT);
    TEST_DETECT(SURF);
    TEST_DETECT(StarDetector);
    TEST_DETECT(ORB);

    TEST_DETECT(BRISK);
    TEST_DETECT(KAZE);
    TEST_DETECT(AKAZE);
    cv::hconcat(imgs2, img_detects);

    imshow("Detects", img_detects);

    while(waitKey() != 27) {
        continue;
    }
    return 0;
}
#else
int main()
{
    std::cout << "This tutorial code needs the xfeatures2d contrib module to be run." << std::endl;
    return 0;
}
#endif