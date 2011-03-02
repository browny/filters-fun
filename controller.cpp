
#include "controller.h"
#include <highgui.h>

Controller::Controller(const IplImage &src) {

	m_srcImg = cvCreateImage(cvGetSize(&src), src.depth, src.nChannels);
	outImg = cvCreateImage(cvGetSize(&src), src.depth, src.nChannels);
	cvCopy(&src, m_srcImg);
	cvCopy(&src, outImg);

	m_gamma  = new Gamma(src);
	m_vignet = new Vignet(src);
	m_bokeh  = new Bokeh(src);

	m_filterBank = FilterBank();

}


void Controller::setVignetCenter(CvPoint mousePt) {

	m_vignet->setCenter(mousePt);

	updateAndRunFilterBank(m_vignet);


}

void Controller::setVignetCenterWarpper(void* pt2Obj, CvPoint mousePt) {

	Controller* controllerObj = (Controller*)pt2Obj;
	controllerObj->setVignetCenter(mousePt);

}

GRADIENT_MODE Controller::getBokehGradientMode() {

	return m_bokeh->getGradientMode();

}

void Controller::setBokehCenters(CvPoint firstPt, CvPoint secondPt) {

	m_bokeh->setFirstCenter(firstPt);
	m_bokeh->setSecondCenter(secondPt);

	updateAndRunFilterBank(m_bokeh);

}

void Controller::setBokehGradientMode(GRADIENT_MODE mode) {

	m_bokeh->setGradientMode(mode);

}

void Controller::setBokehCentersWarpper(void* pt2Obj, CvPoint firstPt, CvPoint secondPt) {

	Controller* controllerObj = (Controller*)pt2Obj;
	controllerObj->setBokehCenters(firstPt, secondPt);

}

void Controller::setGammaCtrlPointsList(const vector< vector<CvPoint2D32f> > &ctrlPointsList) {

	m_gamma->setCtrlPointsList(ctrlPointsList);

	updateAndRunFilterBank(m_gamma);

}

void Controller::setGammaCtrlPointsListWrapper(void* pt2Obj,
		const vector<vector<CvPoint2D32f> > &ctrlPointsList) {

	Controller* controllerObj = (Controller*) pt2Obj;
	controllerObj->setGammaCtrlPointsList(ctrlPointsList);

}

void Controller::resetAll() {

	m_gamma->reset();
	m_filterBank.m_filters.clear();
	cvCopy(m_srcImg, outImg);

}

void Controller::randomSurprise() {

	m_filterBank.randomOrderFilters();
	m_filterBank.runFilterBank(*m_srcImg, outImg);

}

void Controller::increVignetPower() {

	m_vignet->incrementPower();

	updateAndRunFilterBank(m_vignet);

}

void Controller::decreVignetPower() {

	m_vignet->decrementPower();

	updateAndRunFilterBank(m_vignet);
}

void Controller::increBokehPower() {

	m_bokeh->incrementPower();

	updateAndRunFilterBank(m_bokeh);
}

void Controller::decreBokehPower() {

	m_bokeh->decrementPower();

	updateAndRunFilterBank(m_bokeh);

}

void Controller::updateAndRunFilterBank(Filter* filter) {

	m_filterBank.addFilter(filter);
	m_filterBank.runFilterBank(*m_srcImg, filter->filterName, outImg);

}

Controller::~Controller() {

	delete m_gamma;
	delete m_vignet;
	delete m_bokeh;
	cvReleaseImage(&m_srcImg);
	cvReleaseImage(&outImg);

}
