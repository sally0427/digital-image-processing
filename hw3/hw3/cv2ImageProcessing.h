
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#define IMAGE1_PATH "SourceImage.jpg"
#define IMAGE2_PATH "ReferenceImage.jpg"

using namespace std;
using namespace cv;

class cv2ImageProcessing
{
private:
	int histSize[1]; // 项的数量
	float hranges[2]; // 统计像素的最大值和最小值
	const float* ranges[1];
	int channels; // 仅计算一个通道

public:
	void GrayHistogram()
	{
		// 准备1D直方图的参数
		histSize[0] = 256;
		hranges[0] = 0.0f;
		hranges[1] = 255.0f;
		ranges[0] = hranges;
		channels = 0;
	}
	void ColorHistogram()
	{
		// 准备3D直方图的参数
		histSize[0] = 768;
		hranges[0] = 0.0f*3;
		hranges[1] = 255.0f*3;
		ranges[0] = hranges;
		channels = 0;
	}

	Mat calculateOneChannelHistogram(const Mat& image);
	Mat grawGrayHistogram(const Mat& hist);
	Mat grawColorHistogram(const vector<Mat>& hist);
	//void EqualizeImage(const Mat& src, const Mat& hist, Mat& dst);
	void HistSpecify(const Mat& src, const Mat& ref, Mat& result);
	void Gray(const Mat& image_1, const Mat& image_2);
	void HSVgetHistogram(const Mat& imag1, const Mat& imag2, vector<Mat>  Imag1channels, vector<Mat>  Imag2channels);
	void HSVequal(const Mat& imag1, vector<Mat>  Imag1channels, vector<Mat>  Imag2channels);
	void HSVSpec(const Mat& imag1, const Mat& imag2, vector<Mat>  Imag1channels, vector<Mat>  Imag2channels);
	void HSV(const Mat& image_1, const Mat& image_2);
	void YUV(const Mat& image_1, const Mat& image_2);
	void YUVgetHistogram(const Mat& imag1, const Mat& imag2, vector<Mat>  Imag1channels, vector<Mat>  Imag2channels);
	void YUVequal(const Mat& imag1, vector<Mat>  Imag1channels, vector<Mat>  Imag2channels);
	void YUVSpec(const Mat& imag1, const Mat& imag2, vector<Mat>  Imag1channels, vector<Mat>  Imag2channels);
};
