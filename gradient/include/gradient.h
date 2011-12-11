
/*
 * An abstract class for linear, point and ellipse gradients
 */

#ifndef __GRADIENT_H__
#define __GRADIENT_H__

#include <cv.h>

class Gradient {
public:

	// Abstract function
	virtual void incrementPower() = 0;
	virtual void decrementPower() = 0;
	virtual void generateGradient(IplImage* img) = 0;

	// Access method
	CvPoint getFirstPt() { return firstPt; }
	CvPoint getSecondPt() { return secondPt; }
	double  getPower() { return power; }

	void setFirstPt(CvPoint pt) { firstPt = pt; }
	void setSecondPt(CvPoint pt) { secondPt = pt; }

	virtual ~Gradient() {}

protected:

	CvPoint firstPt;
	CvPoint secondPt;
	double power;

	Gradient(CvPoint p1, CvPoint p2, double pw) :
		firstPt(p1), secondPt(p2), power(pw) {
	}

};

#endif
