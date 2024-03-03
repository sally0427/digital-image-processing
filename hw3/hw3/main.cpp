#include "cv2ImageProcessing.h"

int main()
{
	/****************顯示SourceImage和ReferenceImage的直方圖******************/
	cv2ImageProcessing hist1, hist2, hist3, hist4;
	Mat img1 = imread(IMAGE1_PATH, 1);
	Mat img2 = imread(IMAGE2_PATH, 1);
	resize(img1, img1, Size(970, 650), (0, 0), (0, 0), INTER_LINEAR);
	resize(img2, img2, Size(970, 650), (0, 0), (0, 0), INTER_LINEAR);
	hist1.Gray(img1, img2);
	hist2.HSV(img1, img2);
	hist3.YUV(img1, img2);
	waitKey();
	return 0;
}