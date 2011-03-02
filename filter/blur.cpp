
#include "blur.h"

Blur::Blur(const IplImage &src) :
	STEP(0.3), MAX_SIGMA(4.0) {

	levelCnt = (int) (MAX_SIGMA / STEP);
	blurredImgs.resize(levelCnt);

	for (int levelIdx = 0; levelIdx < levelCnt; ++levelIdx)
		blurredImgs[levelIdx] = cvCreateImage(cvGetSize(&src), src.depth, src.nChannels);

}

void Blur::genBlurredImgs(const IplImage &src, vector<IplImage*> &imgs) {

	double smoothDegree = 0.1;

	vector<IplImage*>::iterator it = imgs.begin();
	while (it != imgs.end()) {

		cvSmooth(&src, *it, CV_GAUSSIAN, 0, 0, smoothDegree, smoothDegree);

		smoothDegree += STEP;
		++it;
	}

}

Blur::~Blur() {

	vector<IplImage*>::iterator it = blurredImgs.begin();
	while (it != blurredImgs.end()) {

		cvReleaseImage(&(*it));
		++it;
	}

}
