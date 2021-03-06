
#include <assert.h>
#include "../include/fileReader.h"

FileReader::FileReader(int argc, const char** argv) : LONGSIDE_MAX(640) {

    m_srcImg = 0;
    scaledImg = 0;

}

bool FileReader::readFile(string filePath) {

    bool readOK = false;

    m_srcImg = cvLoadImage(filePath.c_str());

    if (!m_srcImg) { // fail to load image

        readOK = false;
        return readOK;

    } else {

        scaleImg(*m_srcImg);

        readOK = true;
        return readOK;

    }


}

void FileReader::scaleImg(const IplImage &srcImg) {

    int longSide = (srcImg.width > srcImg.height) ? srcImg.width : srcImg.height;

    if (longSide > LONGSIDE_MAX) {

        double scaleRatio = (double) longSide / LONGSIDE_MAX;

        int newWidth  = (double)(srcImg.width)  / scaleRatio;
        int newHeight = (double)(srcImg.height) / scaleRatio;
        CvSize newSize = cvSize(newWidth, newHeight);
        scaledImg = cvCreateImage(newSize, srcImg.depth, srcImg.nChannels);

        cvResize(&srcImg, scaledImg);

    } else {

        scaledImg = cvCreateImage(cvGetSize(&srcImg), srcImg.depth, srcImg.nChannels);
        cvCopy(&srcImg, scaledImg);

    }

}

FileReader::~FileReader() {

    cvReleaseImage(&scaledImg);

}
