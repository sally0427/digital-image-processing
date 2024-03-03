#include "cv2ImageProcessing.h"

void cv2ImageProcessing::SplitAlpha(cv::Mat& Foreground)
{
	Mat bgra[4];
	cv::split(Foreground, bgra);//split png foreground

	// Save the foregroung RGB content into a single Mat
	vector<Mat> foregroundChannels;
	foregroundChannels.push_back(bgra[0]);
	foregroundChannels.push_back(bgra[1]);
	foregroundChannels.push_back(bgra[2]);
	foreground = Mat::zeros(Foreground.size(), CV_8UC3);
	cv::merge(foregroundChannels, foreground);

	// Save the alpha information into a single Mat
	vector<Mat> alphaChannels;
	alphaChannels.push_back(bgra[3]);
	alphaChannels.push_back(bgra[3]);
	alphaChannels.push_back(bgra[3]);
	alpha = Mat::zeros(Foreground.size(), CV_8UC3);
	cv::merge(alphaChannels, alpha);
}

// Alpha blending using multiply and add functions
cv::Mat& cv2ImageProcessing::blend(Mat& alpha, Mat& Foreground, Mat& background, Mat& outImage)
{
	Mat fore, back;
	multiply(alpha, Foreground, Foreground);
	multiply(Scalar::all(1.0) - alpha, background, background);
	add(Foreground, background, outImage);

	return outImage;
}

int main(int argc, char** argv)
{
	cv2ImageProcessing Function;

	// Read in the png foreground asset file that contains both rgb and alpha information
	Mat foreGroundImage = imread("D:/cat1.png", -1);
	resize(foreGroundImage, foreGroundImage, Size(970, 650), (0, 0), (0, 0), INTER_LINEAR);

	//split(foreGroundImage, bgra);
	Function.SplitAlpha(foreGroundImage);

	// Read background image
	Function.background = imread("D:/girl.png");
	resize(Function.background, Function.background, Size(970, 650), (0, 0), (0, 0), INTER_LINEAR);

	// Convert Mat to float data type
	Function.foreground.convertTo(Function.foreground, CV_32FC3);
	Function.background.convertTo(Function.background, CV_32FC3);
	Function.alpha.convertTo(Function.alpha, CV_32FC3, 1.0 / 255); // keeps the alpha values betwen 0 and 1

	// Alpha blending using functions multiply and add
	Mat outImage = Mat::zeros(Function.foreground.size(), Function.foreground.type());
	outImage = Function.blend(Function.alpha, Function.foreground, Function.background, outImage);

	imshow("alpha blended image", outImage / 255);
	waitKey(0);

	return 0;
}
