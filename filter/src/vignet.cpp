
#include "../include/vignet.h"
#include "../../include/opencv/highgui/highgui_c.h"

Vignet::Vignet(const IplImage &img) : Filter(img, "Vignet") {

	m_pointGrad = new PointGradient(cvPoint(img.width/2, img.height/2), 0.5, 1.0);

	m_maskImg = cvCreateImage(cvGetSize(&img), IPL_DEPTH_64F, 1);
	m_labImg = cvCreateImage(cvGetSize(&img), IPL_DEPTH_8U, 3);

}

Vignet::~Vignet() {

	delete m_pointGrad;
	cvReleaseImage(&m_labImg);
	cvReleaseImage(&m_maskImg);

}

// Virtual function implementation
void Vignet::filtering(const IplImage &src, IplImage* rst) {

	CvScalar value;

	m_pointGrad->generateGradient(m_maskImg);
	cvCvtColor(&src, m_labImg, CV_BGR2Lab);

	for (int row = 0; row < m_labImg->height; row++) {
		for (int col = 0; col < m_labImg->width; col++) {

			value = cvGet2D(m_labImg, row, col);
			value.val[0] *= cvGet2D(m_maskImg, row, col).val[0];
			cvSet2D(m_labImg, row, col, value);

		}
	}

	cvCvtColor(m_labImg, rst, CV_Lab2BGR);

	cvCopy(rst, backupResultImg);

}

void Vignet::reset() {


}

void Vignet::importSettings(string fileName, int suffix) {

}

void Vignet::exportSettings(string fileName, int suffix) {

}


