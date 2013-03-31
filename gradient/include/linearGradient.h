#ifndef __LINEARGRADIENT_H__
#define __LINEARGRADIENT_H__

#include "gradient.h"

class LinearGradient: public Gradient
{
public:

    LinearGradient(CvPoint p1, CvPoint p2, double pw, CvScalar s);

    // Virtual function implementation
    void incrementPower();
    void decrementPower();
    void generateGradient(IplImage* img);

private:

    const double POWER_MAX;
    const double POWER_MIN;

    CvScalar m_lineFunc;

    void updateLineFunc();

};

#endif
