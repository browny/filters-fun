
#ifndef __BOKEH_H__
#define __BOKEH_H__

#include <vector>
#include <cv.h>
#include <highgui.h>
#include "../../gradient/include/linearGradient.h"
#include "../../gradient/include/pointGradient.h"
#include "../../gradient/include/ellipseGradient.h"
#include "filter.h"
#include "blur.h"
using namespace std;

enum GRADIENT_MODE {
	LINEAR = 0,
	CIRCULAR,
	ELLIPSE
};

class Bokeh : public Filter {
public:

	Bokeh(const IplImage &img);

	// Virtual function implementation
	void filtering(const IplImage &src, IplImage* rst);
	void reset();
	void importSettings(string fileName, int suffix);
	void exportSettings(string fileName, int suffix);

	// Access function
	GRADIENT_MODE getGradientMode()          { return m_gradientMode; }
	void setGradientMode(GRADIENT_MODE mode) { m_gradientMode = mode;  }

	CvPoint getFirstPt();
	CvPoint getSecondPt();

	void setFirstCenter(CvPoint pt);
	void setSecondCenter(CvPoint pt);

	// Member function
	void incrementPower();
	void decrementPower();

	void genGradient(Gradient* grad);
	void genBlurredImg(const IplImage &src);


	~Bokeh();

private:

	GRADIENT_MODE m_gradientMode;

	LinearGradient* m_linearGrad;
	PointGradient* m_pointGrad;
	EllipseGradient* m_ellipseGrad;

	Blur* m_blurMaker;
	IplImage* m_gradImg;
	
};

#endif
