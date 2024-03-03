#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class cv2ImageProcessing {
public:
	void SplitAlpha(cv::Mat& Foreground);
	cv::Mat& blend(Mat& alpha, Mat& Foreground, Mat& background, Mat& outImage);

	cv::Mat foreground;
	cv::Mat background;
	cv::Mat alpha;
};
