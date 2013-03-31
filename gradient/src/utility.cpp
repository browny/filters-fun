#include <math.h>
#include <vector>
#include "../include/utility.h"
using namespace std;

double dist(CvPoint a, CvPoint b) {
    return sqrt(pow((double) (a.x - b.x), 2) + pow((double) (a.y - b.y), 2));
}

void getLineFunc(CvPoint strtPt, CvPoint endPt, CvScalar &lineFunc) {

    // Line function: ax -y + b = 0

    float slope = (float) (endPt.y - strtPt.y) / (float) (endPt.x - strtPt.x);
    if ((endPt.x - strtPt.x) == 0)
        slope = 999;

    lineFunc.val[0] = slope;
    lineFunc.val[1] = -1;
    lineFunc.val[2] = (float) strtPt.y - ((float) strtPt.x * slope);

}

float getPt2LineDis(const CvPoint &p, const CvScalar &line) {

    float a = (float) line.val[0];
    float b = (float) line.val[1];
    float c = (float) line.val[2];
    float px = (float) p.x;
    float py = (float) p.y;

    float nom = abs(a * px + b * py + c);
    float denom = sqrt(pow(a, 2) + pow(b, 2));

    return nom / denom;

}

double getMaxDisFromCorners(const CvSize &imgSize, const CvPoint &center) {

    // given a rect and a line
    // get which corner of rect is farest from the line

    vector<CvPoint> corners(4);
    corners[0] = cvPoint(0, 0);
    corners[1] = cvPoint(imgSize.width, 0);
    corners[2] = cvPoint(0, imgSize.height);
    corners[3] = cvPoint(imgSize.width, imgSize.height);

    double maxDis = 0;
    for (int i = 0; i < 4; ++i) {

        double dis = dist(corners[i], center);
        if (maxDis < dis)
            maxDis = dis;

    }

    return maxDis;

}

float getMaxDisFromCorners(const CvSize &imgSize, const CvScalar &line) {

    // given a rect and a line
    // get which corner of rect is farest from the line

    vector<CvPoint> corners(4);
    corners[0] = cvPoint(0, 0);
    corners[1] = cvPoint(imgSize.width, 0);
    corners[2] = cvPoint(0, imgSize.height);
    corners[3] = cvPoint(imgSize.width, imgSize.height);

    float maxDis = 0;
    for (int i = 0; i < 4; ++i) {

        float dis = getPt2LineDis(corners[i], line);
        if (maxDis < dis)
            maxDis = dis;

    }

    return maxDis;

}

double getRotateAngle(Coord vec1, Coord vec2) {

    // given 2 vectors: vec1 and vec2
    // get the included angle between them (directional)

    const double epsilon = 1.0e-6;
    const double PI = acos(-1.0); // 180 degree
    double angle = 0;

    // normalize
    Coord norVec1, norVec2;
    norVec1.x = vec1.x / sqrt(pow(vec1.x, 2) + pow(vec1.y, 2));
    norVec1.y = vec1.y / sqrt(pow(vec1.x, 2) + pow(vec1.y, 2));
    norVec2.x = vec2.x / sqrt(pow(vec2.x, 2) + pow(vec2.y, 2));
    norVec2.y = vec2.y / sqrt(pow(vec2.x, 2) + pow(vec2.y, 2));

    // dot product
    double dotProd = (norVec1.x * norVec2.x) + (norVec1.y * norVec2.y);
    if (abs(dotProd - 1.0) <= epsilon)
        angle = 0;
    else if (abs(dotProd + 1.0) <= epsilon)
        angle = PI;
    else {
        double cross = 0;
        angle = acos(dotProd);

        //cross product (for judging clockwise or counter-clockwise)
        cross = (norVec1.x * norVec2.y) - (norVec2.x * norVec1.y);

        if (cross > 0) // vec1 rotate clockwise to vec2
            angle = 2 * PI - angle;
    }

    return angle * (180 / PI);

}

Coord transRotate(Coord &point, Coord &trans, double rotDeg) {

    // translation then rotation

    const double PI = acos(-1.0); // 180 degree
    Coord res = point;

    // translation
    res.x -= trans.x;
    res.y -= trans.y;

    // rotation
    double theta = -1 * rotDeg * (PI / 180);
    double cosTheta = cos(theta);
    double sinTheta = sin(theta);
    Coord temp = res;

    res.x = temp.x * cosTheta - temp.y * sinTheta;
    res.y = temp.x * sinTheta + temp.y * cosTheta;

    return res;

}

CvPoint getMappingPoint(CvPoint pt, CvPoint strtPt, CvPoint endPt) {

    // use the line from strtPt to endPt as x axis to define new coordinate system
    // how 'pt' to change its coordinate

    double longAxisLength = dist(strtPt, endPt);
    Coord longAxisUnitVector;
    longAxisUnitVector.x = (endPt.x - strtPt.x) / longAxisLength;
    longAxisUnitVector.y = (endPt.y - strtPt.y) / longAxisLength;

    // get rotation angle
    Coord horUnitVector = { 1, 0 };
    double rotateDegree = getRotateAngle(longAxisUnitVector, horUnitVector);

    // translation & rotation
    Coord ellipseCenter = { (strtPt.x + endPt.x) / 2, (strtPt.y + endPt.y) / 2 };
    Coord pointBefore = { pt.x, pt.y };
    Coord pointAfter = transRotate(pointBefore, ellipseCenter, rotateDegree);

    return cvPoint((int) pointAfter.x, (int) pointAfter.y);

}

