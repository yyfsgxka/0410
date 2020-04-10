#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
	
	//��ϰһ
	Mat text = imread("lena.jpg");
	imshow("lena", text);
	Mat dst;
	cv::Point2f center(text.cols / 2.0, text.rows / 2.0);
	double angle = -30;
	int scale = 1;
	cv::Mat rot = cv::getRotationMatrix2D(center, angle, scale);
	//��ȡ����ı���
    Rect bbox=cv::RotatedRect(center,text.size(), angle).boundingRect();
	//��������������
	rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
	rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;
	//����任
	cv::warpAffine(text, dst, rot, bbox.size());
	cv::imshow("dst", dst);
	

//��ϰ��
	Mat scrM = imread("metal-part-distorted-03.png",1);
	imshow("ԭͼ", scrM);
	Mat gryMat, image,Canny_img;
	
	//Canny����
	Canny(scrM, Canny_img, 50, 200, 3);
	imshow("Canny",Canny_img);
	//�Ҷ�ͼ
	cvtColor(scrM, gryMat, CV_RGB2GRAY);
	
    std::vector<cv::Vec2f>lines;
	//Mat lines;
	
	//ͨ�������������ֱ��
	cv::HoughLines(Canny_img, lines, 1, CV_PI / 180, 100);
	std::vector<cv::Vec2f>::iterator it = lines.begin();
	for (; it != lines.end(); ++it) {
		float rho = (*it)[0], theta = (*it)[1];
		cv::Point pt1, pt2;
		double a = cos(theta);
		double b = sin(theta);
		double x0 = a * rho;
		double y0 = b * rho;
		pt1.x = cv::saturate_cast<int>(x0 + 1000 * (-b));
		pt1.y = cv::saturate_cast<int>(y0 + 1000 * (a));
		pt2.x = cv::saturate_cast<int>(x0 - 1000 * (-b));
		pt2.y = cv::saturate_cast<int>(y0 - 1000 * (a));
		cv::line(scrM, pt1, pt2, cv::Scalar(0, 0, 255),1, CV_AA);

	}


	imshow("ֱ��",scrM);
	
	

	//��ϰ��
	/*ͨ�������������ֱ��*/
	Mat Canny2,  gry;
	Mat frame = imread("metal-part-distorted-03.png", 1);
	//Canny����
	Canny(frame,Canny2, 50, 200, 3);
	imshow("Canny2", Canny2);
	/*�Ҷ�ͼ*/
	cvtColor(frame, gry, CV_RGB2GRAY);

	std::vector<cv::Vec4i>lineMat;
	cv::HoughLinesP(Canny2, lineMat, 1, CV_PI / 180, 30, 10, 20);
	std::vector<cv::Vec4i>::iterator itt = lineMat.begin();
	for (int i = 0; i < lineMat.size(); i++) {
		Point pt1, pt2;
		pt1.x = lineMat[i][0];
		pt1.y = lineMat[i][1];
		pt2.x = lineMat[i][2];
		pt2.y = lineMat[i][3];
		line(frame, pt1, pt2, cv::Scalar(0, 0, 255), 2, CV_AA);

	}

	
	imshow("���ͼ",frame);
	waitKey(0);
	return 0;
}