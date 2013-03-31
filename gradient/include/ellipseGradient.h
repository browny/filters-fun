#ifndef __ELLIPSEGRADIENT_H__
#define __ELLIPSEGRADIENT_H__

#include "gradient.h"
#include "../../include/utility.h"

class EllipseGradient: public Gradient
{
public:

    EllipseGradient(CvPoint p1, CvPoint p2, double pw, double ratio);

    // Virtual function implementation
    void incrementPower();
    void decrementPower();
    void generateGradient(IplImage* img);

private:

    const double POWER_MAX;
    const double POWER_MIN;
    const double POWER_STEP;

    double m_ratio;
    double m_longAxisLength;
    double m_shortAxisLength;

    void updateAxis();
    double getEllipseGaussianValue(CvPoint pt, double a, double b);

};

#endif
