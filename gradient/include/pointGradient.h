#ifndef __POINTGRADIENT_H__
#define __POINTGRADIENT_H__

#include "gradient.h"

class PointGradient: public Gradient {
public:

	PointGradient(CvPoint p, double pw, double rad);

	// Virtual function implementation
	void incrementPower();
	void decrementPower();
	void generateGradient(IplImage* img);

private:

	const double POWER_MAX;
	const double POWER_MIN;

	double m_radius;

};

#endif
