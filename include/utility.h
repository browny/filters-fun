#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <cv.h>

struct Coord {
	double x;
	double y;
};

double dist(CvPoint a, CvPoint b);

void getLineFunc(CvPoint strtPt, CvPoint endPt, CvScalar &lineFunc);

float getPt2LineDis(const CvPoint &p, const CvScalar &line);

float getMaxDisFromCorners(const CvSize &imgSize, const CvScalar &line);

double getMaxDisFromCorners(const CvSize &imgSize, const CvPoint &center);

double getRotateAngle(Coord vec1, Coord vec2);

Coord transRotate(Coord &point, Coord &trans, double rotDeg);

CvPoint getMappingPoint(CvPoint pt, CvPoint strtPt, CvPoint endPt);

#endif
