
#ifndef __GAMMA_H__
#define __GAMMA_H__

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <vector>
#include "filter.h"
using namespace std;

class Gamma : public Filter {
public:

	Gamma(const IplImage* src);

	vector< vector<CvPoint2D32f> > ctrlPointsList;

	// Virtual function implementation
	void filtering(const IplImage* src, IplImage* rst);
	void reset();
	void importSettings(string fileName, int suffix);
	void exportSettings(string fileName, int suffix);

	// Member function
	void setCtrlPoints(int ch, vector<CvPoint2D32f> ctrlPoints);
	void updateGammaTables(int ch);
	void setCtrlPointsList(vector< vector<CvPoint2D32f> > ctrlPointsList);

	~Gamma();

private:

	const int ACCURACY;

	vector<int> gammaTableB;
	vector<int> gammaTableG;
	vector<int> gammaTableR;

	CvPoint2D32f Bernstein(float u, CvPoint2D32f* p);
	CvPoint2D32f pointAdd(CvPoint2D32f p, CvPoint2D32f q);
	CvPoint2D32f pointTimes(float c, CvPoint2D32f p);

};



#endif

