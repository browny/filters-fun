
#include <iostream>
#include <vector>
#include "../include/pointGradient.h"
#include "utility.h"

using namespace std;

PointGradient::PointGradient(CvPoint p, double pw, double rad) :
    Gradient(p, cvPoint(0, 0), pw), POWER_MAX(2.0), POWER_MIN(0.1) {

        m_radius = rad;

    }

// Virtual function implementation
void PointGradient::incrementPower() {

    if (power < POWER_MAX) {
        power += 0.1;
        cout << "point: increment power to " << power << endl;
    }

}

void PointGradient::decrementPower() {

    if (power > POWER_MIN) {
        power -= 0.1;
        cout << "point: decrement power to " << power << endl;

    }

}

void PointGradient::generateGradient(IplImage* img)  {

    double maxImageRad = this->m_radius * getMaxDisFromCorners(cvGetSize(img), firstPt);

    cvSet(img, cvScalar(1));

    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            double temp = dist(firstPt, cvPoint(j, i)) / maxImageRad;
            temp = temp * this->power;
            CvScalar tmepS = cvScalar(pow(cos(temp), 4));
            cvSet2D(img, i, j, tmepS);
        }
    }
}


