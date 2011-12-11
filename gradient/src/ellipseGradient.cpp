
#include <math.h>
#include <iostream>
#include "utility.h"
#include "../include/ellipseGradient.h"
using namespace std;

EllipseGradient::EllipseGradient(CvPoint p1, CvPoint p2, double pw, double ratio) :
	Gradient(p1, p2, pw), POWER_MAX(10.0), POWER_MIN(0.1), POWER_STEP(0.5) {

	m_ratio = ratio;
	m_longAxisLength = dist(p1, p2);
	m_shortAxisLength = ratio * m_longAxisLength;

}


void EllipseGradient::updateAxis() {
	m_longAxisLength = dist(firstPt, secondPt);
	m_shortAxisLength = m_ratio * m_longAxisLength;
}

double EllipseGradient::getEllipseGaussianValue(CvPoint pt, double a, double b) {

	double sigma_x = a * a * power;
	double sigma_y = b * b * power;

	const double PI = acos(-1.0); // 180 degree
	double sqrt_det_val = sqrt(sigma_x * sigma_y);

	double tmp = exp(-0.5 * (pt.x * pt.x / sigma_x + pt.y * pt.y / sigma_y));

	tmp = tmp / (2 * PI * sqrt_det_val);

	return tmp;

}

// Virtual function implementation
void EllipseGradient::incrementPower() {

	if (power < POWER_MAX) {
		power += POWER_STEP;
		cout << "ellipse: increment power to " << power << endl;

	}

}

void EllipseGradient::decrementPower() {

	if (power > POWER_MIN) {
		power -= POWER_STEP;
		cout << "ellipse: decrement power to " << power << endl;

	}

}

void EllipseGradient::generateGradient(IplImage* img) {

	updateAxis();

	cvSet(img, cvScalar(1));

	double maxVal = getEllipseGaussianValue(cvPoint(0, 0), m_longAxisLength,
			m_shortAxisLength);

	for (int i = 0; i < img->height; i++) {
		for (int j = 0; j < img->width; j++) {

			CvPoint mappedPoint = getMappingPoint(cvPoint(j, i), firstPt,
					secondPt);

			double temp = getEllipseGaussianValue(mappedPoint, m_longAxisLength,
					m_shortAxisLength);
			temp = (temp / maxVal);

			CvScalar tempS = cvScalar(1.0 - pow(cos(temp), 4));
			cvSet2D(img, i, j, tempS);

		}
	}

}
