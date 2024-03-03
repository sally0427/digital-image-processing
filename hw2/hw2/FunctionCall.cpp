#include "cv2ImageProcessing.h"

void cv2ImageProcessing::Gray(const Mat& image_1, const Mat& image_2)
{
	/***********計算與繪製SourceImage和ReferenceImage的直方圖************/
	Mat imag1,imag2;
	cvtColor(image_1, imag1, COLOR_RGB2GRAY);
	//imshow("Image1", imag1);
	Mat histImg1 = calculateOneChannelHistogram(imag1);
	histImg1 = grawGrayHistogram(histImg1);
	imwrite("GrayHistogram1.png", histImg1);
	//imshow("Histogram1", histImg1);

	cvtColor(image_2, imag2, COLOR_BGR2GRAY);
	//imshow("Image2", imag2);
	Mat histImg2 = calculateOneChannelHistogram(imag2);
	histImg2 = grawGrayHistogram(histImg2);
	imwrite("GrayHistogram2.png", histImg2);
	//imshow("Histogram2", histImg2);

	/***********SourceImage直方圖等化************/
	Mat equImg = Mat::zeros(imag1.rows, imag1.cols, imag1.type());
	equalizeHist(imag1, equImg);
	Mat equImg1_hist = calculateOneChannelHistogram(equImg);
	equImg1_hist = grawGrayHistogram(equImg1_hist);
	imwrite("GrayequImg1_hist.png", equImg1_hist);
	//imshow("EquImag1", equImg);
	//imshow("equImg1_hist", equImg1_hist);

	/*****************直方圖匹配*******************/
	Mat specifyImg = Mat::zeros(imag2.rows, imag2.cols, imag2.type());
	HistSpecify(imag1, imag2, specifyImg);
	Mat specifyImg_hust = calculateOneChannelHistogram(specifyImg);
	specifyImg_hust = grawGrayHistogram(specifyImg_hust);

	//namedWindow("Specify Image", 0);
	//resizeWindow("Specify Image", specifyImg.rows / 8, specifyImg.cols / 8);
	//imshow("Specify Image", specifyImg);
	imwrite("GraySpecifyImag.png", specifyImg);
	imwrite("GrayspecifyImg_hust.png", specifyImg_hust);
	//imshow("specifyImg_hust", specifyImg_hust);
}

void cv2ImageProcessing::HSV(const Mat& image_1, const Mat& image_2) //(只改V)
{
	Mat imag1, imag2;
	cvtColor(image_1, imag1, COLOR_RGB2HSV);
	cvtColor(image_2, imag2, COLOR_RGB2HSV);
	imwrite("HSVImage1.png", imag1);
	imwrite("HSVImage2.png", imag2);

	vector<Mat>  Imag1channels;
	split(imag1, Imag1channels);
	vector<Mat>  Imag2channels;
	split(imag2, Imag2channels);

	HSVgetHistogram(imag1, imag2, Imag1channels, Imag2channels);//計算與繪製直方圖
	HSVequal(imag1, Imag1channels, Imag2channels);//直方圖等化
	HSVSpec(imag1, imag2, Imag1channels, Imag2channels);//直方圖匹配

}
void cv2ImageProcessing::YUV(const Mat& image_1, const Mat& image_2) //只改Y
{
	Mat imag1, imag2;
	cvtColor(image_1, imag1, COLOR_RGB2YUV);
	cvtColor(image_2, imag2, COLOR_RGB2YUV);
	imwrite("YUVImage1.png", imag1);
	imwrite("YUVImage2.png", imag2);

	vector<Mat>  Imag1channels;
	split(imag1, Imag1channels);
	vector<Mat>  Imag2channels;
	split(imag2, Imag2channels);

	YUVgetHistogram(imag1, imag2, Imag1channels, Imag2channels); //計算與繪製直方圖
	YUVequal(imag1, Imag1channels, Imag2channels);//直方圖等化
	YUVSpec(imag1, imag2, Imag1channels, Imag2channels); // 直方圖匹配
}

void cv2ImageProcessing::YUVgetHistogram(const Mat& imag1, const Mat& imag2, vector<Mat>  Imag1channels, vector<Mat>  Imag2channels)
{
	/***********計算與繪製SourceImage和ReferenceImage的直方圖************/
	Mat histImg1_Y = calculateOneChannelHistogram(Imag1channels[0]);
	Mat histImg1_U = calculateOneChannelHistogram(Imag1channels[1]);
	Mat histImg1_V = calculateOneChannelHistogram(Imag1channels[2]);
	vector<Mat> histImg1_YUV;
	histImg1_YUV.push_back(histImg1_Y);
	histImg1_YUV.push_back(histImg1_U);
	histImg1_YUV.push_back(histImg1_V);
	Mat YUVHist = Mat::zeros(imag1.size(), CV_8UC3);
	YUVHist = grawColorHistogram(histImg1_YUV);
	imwrite("YUVHist1.png", YUVHist);
}

void cv2ImageProcessing::YUVequal(const Mat& imag1, vector<Mat>  Imag1channels, vector<Mat>  Imag2channels)
{
	/*****************直方圖等化(只改Y)*******************/
	Mat equImg_Y, equImg_U, equImg_V = Mat::zeros(imag1.rows, imag1.cols, imag1.type());
	equalizeHist(Imag1channels[0], equImg_Y);

	vector <Mat> equImg1;
	equImg1.push_back(equImg_Y);
	equImg1.push_back(Imag1channels[1]);
	equImg1.push_back(Imag1channels[2]);
	Mat YUVequImg1 = Mat::zeros(imag1.size(), CV_8UC3);
	merge(&equImg1[0], equImg1.size(), YUVequImg1);
	imwrite("YUVequImg1.png", YUVequImg1);


	Mat HistequImg1_Y = calculateOneChannelHistogram(equImg_Y);
	Mat HistequImg1_U = calculateOneChannelHistogram(Imag1channels[1]);
	Mat HistequImg1_V = calculateOneChannelHistogram(Imag1channels[2]);
	vector <Mat> histEquImg1_YUV;
	histEquImg1_YUV.push_back(HistequImg1_Y);
	histEquImg1_YUV.push_back(HistequImg1_U);
	histEquImg1_YUV.push_back(HistequImg1_V);
	Mat YUVEquHist1 = Mat::zeros(imag1.size(), CV_8UC3);

	YUVEquHist1 = grawColorHistogram(histEquImg1_YUV);
	imwrite("YUVequImg1_hist.png", YUVEquHist1);
}

void cv2ImageProcessing::YUVSpec(const Mat& imag1, const Mat& imag2, vector<Mat>  Imag1channels, vector<Mat>  Imag2channels)
{
	/*****************直方圖匹配(只改Y)*******************/
	Mat specifyImg_Y, specifyImg_U, specifyImg_V = Mat::zeros(imag2.rows, imag2.cols, imag2.type());
	HistSpecify(Imag1channels[0], Imag2channels[0], specifyImg_Y);

	vector <Mat> SpecifyImag1;
	SpecifyImag1.push_back(specifyImg_Y);
	SpecifyImag1.push_back(Imag1channels[1]);
	SpecifyImag1.push_back(Imag1channels[2]);
	Mat YUVSpecifyImag1 = Mat::zeros(imag1.size(), CV_8UC3);
	merge(&SpecifyImag1[0], SpecifyImag1.size(), YUVSpecifyImag1);
	imwrite("YUVSpecifyImag.png", YUVSpecifyImag1);

	Mat HistSpecifyImg_Y = calculateOneChannelHistogram(specifyImg_Y);
	Mat HistSpecifyImg_U = calculateOneChannelHistogram(Imag1channels[1]);
	Mat HistSpecifyImg_V = calculateOneChannelHistogram(Imag1channels[2]);

	vector <Mat> SpecHist;
	SpecHist.push_back(HistSpecifyImg_Y);
	SpecHist.push_back(HistSpecifyImg_U);
	SpecHist.push_back(HistSpecifyImg_V);
	Mat YUVSpecHist = Mat::zeros(imag1.size(), CV_8UC3);
	YUVSpecHist = grawColorHistogram(SpecHist);
	imwrite("HSVspecifyImg_hist.png", YUVSpecHist);
}
void cv2ImageProcessing::HSVSpec(const Mat& imag1, const Mat& imag2, vector<Mat>  Imag1channels, vector<Mat>  Imag2channels)
{
	/*****************直方圖匹配(只改V)*******************/
	Mat specifyImg_H, specifyImg_S, specifyImg_V = Mat::zeros(imag2.rows, imag2.cols, imag2.type());
	HistSpecify(Imag1channels[2], Imag2channels[2], specifyImg_V);

	vector <Mat> SpecifyImag1;
	SpecifyImag1.push_back(Imag1channels[0]);
	SpecifyImag1.push_back(Imag1channels[1]);
	SpecifyImag1.push_back(specifyImg_V);
	Mat HSVSpecifyImag1 = Mat::zeros(imag1.size(), CV_8UC3);
	merge(&SpecifyImag1[0], SpecifyImag1.size(), HSVSpecifyImag1);
	imwrite("HSVSpecifyImag.png", HSVSpecifyImag1);

	Mat HistSpecifyImg_H = calculateOneChannelHistogram(Imag1channels[0]);
	Mat HistSpecifyImg_S = calculateOneChannelHistogram(Imag1channels[1]);
	Mat HistSpecifyImg_V = calculateOneChannelHistogram(specifyImg_V);

	vector <Mat> SpecHist;
	SpecHist.push_back(HistSpecifyImg_H);
	SpecHist.push_back(HistSpecifyImg_S);
	SpecHist.push_back(HistSpecifyImg_V);
	Mat HSVSpecHist = Mat::zeros(imag1.size(), CV_8UC3);
	HSVSpecHist = grawColorHistogram(SpecHist);
	imwrite("HSVspecifyImg_hist.png", HSVSpecHist);
}

void cv2ImageProcessing::HSVequal(const Mat& imag1, vector<Mat>  Imag1channels, vector<Mat>  Imag2channels)
{
	/*****************直方圖等化(只改V)*******************/
	Mat equImg_H, equImg_S, equImg_V = Mat::zeros(imag1.rows, imag1.cols, imag1.type());
	equalizeHist(Imag1channels[2], equImg_V);

	vector <Mat> equImg1;
	equImg1.push_back(Imag1channels[0]);
	equImg1.push_back(Imag1channels[1]);
	equImg1.push_back(equImg_V);
	Mat HSVequImg1 = Mat::zeros(imag1.size(), CV_8UC3);
	merge(&equImg1[0], equImg1.size(), HSVequImg1);
	imwrite("HSVequImg1.png", HSVequImg1);


	Mat HistequImg1_H = calculateOneChannelHistogram(Imag1channels[0]);
	Mat HistequImg1_S = calculateOneChannelHistogram(Imag1channels[1]);
	Mat HistequImg1_V = calculateOneChannelHistogram(equImg_V);
	vector <Mat> histEquImg1_HSV;
	histEquImg1_HSV.push_back(HistequImg1_H);
	histEquImg1_HSV.push_back(HistequImg1_S);
	histEquImg1_HSV.push_back(HistequImg1_V);
	Mat HSVEquHist1 = Mat::zeros(imag1.size(), CV_8UC3);

	HSVEquHist1 = grawColorHistogram(histEquImg1_HSV);
	imwrite("HSVequImg1_hist.png", HSVEquHist1);
}

void cv2ImageProcessing::HSVgetHistogram(const Mat& imag1, const Mat& imag2, vector<Mat>  Imag1channels, vector<Mat>  Imag2channels)
{
	/***********計算與繪製SourceImage和ReferenceImage的直方圖************/
	cv2ImageProcessing hist1D;

	Mat histImg1_H = hist1D.calculateOneChannelHistogram(Imag1channels[0]);
	Mat histImg1_S = hist1D.calculateOneChannelHistogram(Imag1channels[1]);
	Mat histImg1_V = hist1D.calculateOneChannelHistogram(Imag1channels[2]);
	vector<Mat> histImg1_HSV;
	histImg1_HSV.push_back(histImg1_H);
	histImg1_HSV.push_back(histImg1_S);
	histImg1_HSV.push_back(histImg1_V);
	Mat HSVHist = Mat::zeros(imag1.size(), CV_8UC3);
	HSVHist = hist1D.grawColorHistogram(histImg1_HSV);
	imwrite("HSVHist1.png", HSVHist);
	//imshow("HSVHist1", HSVHist);
}

Mat cv2ImageProcessing::calculateOneChannelHistogram(const Mat& image)
{
	Mat hist;
	GrayHistogram();
	// 計算直方圖
	calcHist(&image, 1, &channels, Mat(), hist, 1, histSize, ranges);
	return hist;
}

Mat cv2ImageProcessing::grawGrayHistogram(const Mat& hist)
{
	//查找最大值用于归一化
	double maxVal = 0;

	minMaxLoc(hist, NULL, &maxVal);

	//绘制直方图的图像
	Mat histImg(histSize[0], histSize[0], CV_8U, Scalar(255));

	// 设置最高点为最大值的90%
	double hpt = 0.9 * histSize[0];
	//每个条目绘制一条垂直线
	for (int h = 0; h < histSize[0]; h++)
	{
		//直方图的元素类型为32位浮点数
		float binVal = hist.at<float>(h);
		int intensity = static_cast<int>(binVal * hpt / maxVal);
		line(histImg, Point(h, histSize[0]), Point(h, histSize[0] - intensity), Scalar::all(0));
	}
	return histImg;
}

Mat cv2ImageProcessing::grawColorHistogram(const vector<Mat>& hist)
{
	//channel_1
	double maxVal = 0;
	minMaxLoc(hist[0], NULL, &maxVal);
	Mat histImg(histSize[0], histSize[0], CV_8U, Scalar(255));

	double hpt = 0.9 * histSize[0];
	for (int h = 0; h < histSize[0]; h++)
	{
		//直方图的元素类型为32位浮点数
		float binVal = hist[0].at<float>(h);
		int intensity = static_cast<int>(binVal * hpt / maxVal);
		line(histImg, Point(h, histSize[0]), Point(h, histSize[0] - intensity), Scalar(255, 0, 0),1);
	}

	//channel_2
	maxVal = 0;
	minMaxLoc(hist[1], NULL, &maxVal);
	for (int h = 0; h < histSize[0]; h++)
	{
		//直方图的元素类型为32位浮点数
		float binVal = hist[1].at<float>(h);
		int intensity = static_cast<int>(binVal * hpt / maxVal);
		line(histImg, Point(h, histSize[0]), Point(h, histSize[0] - intensity), Scalar(0, 255, 0), 1);
	}

	//channel_3
	maxVal = 0;
	minMaxLoc(hist[2], NULL, &maxVal);
	for (int h = 0; h < histSize[0]; h++)
	{
		//直方图的元素类型为32位浮点数
		float binVal = hist[2].at<float>(h);
		int intensity = static_cast<int>(binVal * hpt / maxVal);
		line(histImg, Point(h, histSize[0]), Point(h, histSize[0] - intensity), Scalar(0, 0, 255), 1);
	}
	return histImg;
}

void  cv2ImageProcessing::HistSpecify(const Mat& src, const Mat& ref, Mat& result)
{
	cv2ImageProcessing hist1D;
	Mat src_hist = hist1D.calculateOneChannelHistogram(src);
	Mat dst_hist = hist1D.calculateOneChannelHistogram(ref);

	float src_cdf[256] = { 0 };
	float dst_cdf[256] = { 0 };

	// 直方图进行归一化处理
	src_hist /= (src.rows * src.cols);
	dst_hist /= (ref.rows * ref.cols);

	// 计算原始直方图和规定直方图的累积概率
	for (int i = 0; i < 256; i++)
	{
		if (i == 0)
		{
			src_cdf[i] = src_hist.at<float>(i);
			dst_cdf[i] = dst_hist.at<float>(i);
		}
		else
		{
			src_cdf[i] = src_cdf[i - 1] + src_hist.at<float>(i);
			dst_cdf[i] = dst_cdf[i - 1] + dst_hist.at<float>(i);
		}
	}

	// 累积概率的差值
	float diff_cdf[256][256];
	for (int i = 0; i < 256; i++)
		for (int j = 0; j < 256; j++)
			diff_cdf[i][j] = fabs(src_cdf[i] - dst_cdf[j]);

	// 构建灰度级映射表
	Mat lut(1, 256, CV_8U);
	for (int i = 0; i < 256; i++)
	{
		// 查找源灰度级为ｉ的映射灰度
		//　和ｉ的累积概率差值最小的规定化灰度
		float min = diff_cdf[i][0];
		int index = 0;
		for (int j = 1; j < 256; j++)
		{
			if (min > diff_cdf[i][j])
			{
				min = diff_cdf[i][j];
				index = j;
			}
		}
		lut.at<uchar>(i) = static_cast<uchar>(index);
	}

	// 应用查找表，做直方图规定化
	LUT(src, lut, result);
}
