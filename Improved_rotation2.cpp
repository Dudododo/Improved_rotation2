#include <iostream>
#include <opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	cv::Mat srcMat = imread("lena.jpg", 1);
	cv::Mat dstMat, dstMat1;

	int height = srcMat.rows;
	int width = srcMat.cols;

	//顺时针旋转10°
	float angle = -10.0, scale = 1;
	//旋转中心为图像中心
	cv::Point2f center(srcMat.cols * 0.5, srcMat.rows * 0.5);
	//获得变换矩阵
	const cv::Mat affine_matrix = cv::getRotationMatrix2D(center, angle, scale);
	cv::warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());

	//改进后
	cv::Mat rot = cv::getRotationMatrix2D(center, angle, scale);
	//获取外界四边形
	cv::Rect bbox = cv::RotatedRect(center, srcMat.size(), angle).boundingRect();
	//调整仿射矩阵参数
	rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
	rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;
	//仿射变换
	cv::warpAffine(srcMat, dstMat1, rot, bbox.size());

	cv::imshow("srcMat", srcMat);
	cv::imshow("dstMat", dstMat);
	cv::imshow("dstMat1", dstMat1);
	waitKey(0);
}