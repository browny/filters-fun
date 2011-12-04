
#include "../include/bokeh.h"

Bokeh::Bokeh(const IplImage &img) : Filter(img, "Bokeh") {

	m_gradientMode = ELLIPSE;

	m_linearGrad  = new LinearGradient(cvPoint(0, 0), cvPoint(0, 0), 0.5, cvScalar(0));
	m_pointGrad   = new PointGradient(cvPoint(img.width/2, img.height/2), 0.7, 1.0);
	m_ellipseGrad = new EllipseGradient(cvPoint(0, 0), cvPoint(0, 0), 3, 0.3);

	m_blurMaker = new Blur(img);
	m_gradImg = cvCreateImage(cvGetSize(&img), IPL_DEPTH_64F, 1);

	genBlurredImg(img);

}

void Bokeh::incrementPower() {

	if (m_gradientMode == LINEAR) {
		m_linearGrad->incrementPower();

	} else if (m_gradientMode == CIRCULAR) {
		m_pointGrad->incrementPower();

	} else if (m_gradientMode == ELLIPSE) {
		m_ellipseGrad->decrementPower(); // ellipse power 越小, 模糊效果越強

	}

}

void Bokeh::decrementPower() {

	if (m_gradientMode == LINEAR) {
		m_linearGrad->decrementPower();

	} else if (m_gradientMode == CIRCULAR) {
		m_pointGrad->decrementPower();

	} else if (m_gradientMode == ELLIPSE) {
		m_ellipseGrad->incrementPower(); // ellipse power 越大, 模糊效果越弱

	}

}

void Bokeh::genGradient(Gradient* grad) {

	grad->generateGradient(m_gradImg);

}

void Bokeh::genBlurredImg(const IplImage &src) {

	m_blurMaker->genBlurredImgs(src, m_blurMaker->blurredImgs);

}

Bokeh::~Bokeh() {

	delete m_blurMaker;
	delete m_linearGrad;
	delete m_pointGrad;
	delete m_ellipseGrad;
	cvReleaseImage(&m_gradImg);

}

CvPoint Bokeh::getFirstPt() {

	if (m_gradientMode == LINEAR) {
		return m_linearGrad->getFirstPt();

	} else if (m_gradientMode == CIRCULAR) {
		return m_pointGrad->getFirstPt();

	} else if (m_gradientMode == ELLIPSE) {
		return m_ellipseGrad->getFirstPt();

	} else {
		return cvPoint(0,0);
	}

}

CvPoint Bokeh::getSecondPt() {

	if (m_gradientMode == LINEAR) {
		return m_linearGrad->getSecondPt();

	} else if (m_gradientMode == CIRCULAR) {
		return m_pointGrad->getSecondPt();

	} else if (m_gradientMode == ELLIPSE) {
		return m_ellipseGrad->getSecondPt();

	} else {
		return cvPoint(0,0);
	}

}

void Bokeh::setFirstCenter(CvPoint pt) {

	if (m_gradientMode == LINEAR) {
		m_linearGrad->setFirstPt(pt);

	} else if (m_gradientMode == CIRCULAR) {
		m_pointGrad->setFirstPt(pt);

	} else if (m_gradientMode == ELLIPSE) {
		m_ellipseGrad->setFirstPt(pt);

	}

}

void Bokeh::setSecondCenter(CvPoint pt) {

	if (m_gradientMode == LINEAR) {
		m_linearGrad->setSecondPt(pt);

	} else if (m_gradientMode == CIRCULAR) {
		m_pointGrad->setSecondPt(pt);

	} else if (m_gradientMode == ELLIPSE) {
		m_ellipseGrad->setSecondPt(pt);

	}

}

// Virtual function implementation
void Bokeh::filtering(const IplImage &src, IplImage* rst) {

	cvCopy(&src, rst);
	genBlurredImg(*rst);

	if (m_gradientMode == LINEAR) {
		genGradient(m_linearGrad);
	} else if (m_gradientMode == CIRCULAR) {
		genGradient(m_pointGrad);
	} else if (m_gradientMode == ELLIPSE) {
		genGradient(m_ellipseGrad);
	}

	for (int row = 0; row < m_gradImg->height; ++row) {

		double* pGradImg  = (double*) (m_gradImg->imageData + row * m_gradImg->widthStep);
		uchar*  pRstImg = (uchar*) (rst->imageData + row * rst->widthStep);

		double blurStepSize = 1.0 / m_blurMaker->levelCnt;
		for (int col = 0; col < m_gradImg->width; ++col) {

			// blurPower ranges 0~1
			// 1 is white (weakest blur), 0 is black (strongest blur)
			double blurPower = pGradImg[col];

			int blurDegree = 0;
			if ( (int)(blurPower / blurStepSize) > 0 )
				blurDegree = m_blurMaker->levelCnt - (int)(blurPower / blurStepSize);
			else
				blurDegree = m_blurMaker->levelCnt - 1;

			IplImage* blurImg = m_blurMaker->blurredImgs[blurDegree];
			uchar* pBlurImg = (uchar*) (blurImg->imageData + row * blurImg->widthStep);

			for (int ch = 0; ch < 3; ++ch) {
				pRstImg[col * 3 + ch] = pBlurImg[col * 3 + ch];
			}

		}
	}

	cvCopy(rst, backupResultImg);

}

void Bokeh::reset() {

}

void Bokeh::importSettings(string fileName, int suffix) {

}

void Bokeh::exportSettings(string fileName, int suffix) {

}





