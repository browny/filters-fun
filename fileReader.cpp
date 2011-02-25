
#include "fileReader.h"
#include <highgui.h>
#include <assert.h>

FileReader::FileReader(int argc, const char** argv) : LONGSIDE_MAX(640) {

	m_srcImg = 0;
	m_scaledImg = 0;

}

bool FileReader::readFile(string filePath) {

	bool readOK = false;

	m_srcImg = cvLoadImage(filePath.c_str());

	if (!m_srcImg) { // fail to load image

		readOK = false;
		return readOK;

	} else {

		scaleImg(m_srcImg);

		readOK = true;
		return readOK;

	}


}

void FileReader::scaleImg(const IplImage* srcImg) {

	int longSide = (srcImg->width > srcImg->height) ? srcImg->width : srcImg->height;

	if (longSide > LONGSIDE_MAX) {

		double scaleRatio = (double) longSide / LONGSIDE_MAX;

		int newWidth  = (double)(srcImg->width)  / scaleRatio;
		int newHeight = (double)(srcImg->height) / scaleRatio;
		CvSize newSize = cvSize(newWidth, newHeight);
		m_scaledImg = cvCreateImage(newSize, srcImg->depth, srcImg->nChannels);

		cvResize(srcImg, m_scaledImg);

	} else {

		m_scaledImg = cvCreateImage(cvGetSize(srcImg), srcImg->depth, srcImg->nChannels);
		cvCopy(srcImg, m_scaledImg);

	}

}

FileReader::~FileReader() {

	cvReleaseImage(&m_scaledImg);

}
