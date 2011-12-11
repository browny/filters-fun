
#include <iostream>
#include "../include/linearGradient.h"
#include "utility.h"
using namespace std;

LinearGradient::LinearGradient(CvPoint p1, CvPoint p2, double pw, CvScalar s) :
	Gradient(p1, p2, pw), POWER_MAX(2.0), POWER_MIN(0.1) {

	m_lineFunc = s;

}

void LinearGradient::updateLineFunc() {

	float slope = (float) (secondPt.y - firstPt.y) / (float) (secondPt.x
			- firstPt.x);
	slope = ((secondPt.x - firstPt.x) == 0) ? 999 : slope; // ¤À¥À¬°¹sªºª¬ªp

	m_lineFunc.val[0] = slope;
	m_lineFunc.val[1] = -1;
	m_lineFunc.val[2] = (float) firstPt.y - ((float) firstPt.x * slope);

}

// Virtual function implementation

void LinearGradient::incrementPower() {

	if (power < POWER_MAX) {
		power += 0.1;
		cout << "linear: increment power to " << power << endl;
	}

}

void LinearGradient::decrementPower() {

	if (power > POWER_MIN) {
		power -= 0.1;
		cout << "linear: decrement power to " << power << endl;
	}

}

void LinearGradient::generateGradient(IplImage* img) {

	updateLineFunc();

	cvSet(img, cvScalar(1));
	float maxDis = getMaxDisFromCorners(cvGetSize(img), this->m_lineFunc);

	for (int i = 0; i < img->height; i++) {
		for (int j = 0; j < img->width; j++) {

			float dis = getPt2LineDis(cvPoint(j, i), this->m_lineFunc);
			float temp = dis / maxDis;
			temp = temp * this->power;
			CvScalar tmepS = cvScalar(pow(cos(temp), 4));
			cvSet2D(img, i, j, tmepS);

		}
	}
}
