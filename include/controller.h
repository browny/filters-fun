
#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "./opencv/core/core_c.h"
#include "./opencv/highgui/highgui_c.h"
#include "filterBank.h"
#include "../filter/include/filter.h"
#include "../filter/include/gamma.h"
#include "../filter/include/vignet.h"
#include "../filter/include/bokeh.h"

class Controller {
public:

	Controller(const IplImage &src);

	IplImage* outImg;

	// Access function
	GRADIENT_MODE getBokehGradientMode();
	void setBokehGradientMode(GRADIENT_MODE mode);

	// Member function
	void setVignetCenter(CvPoint mousePt);
	static void setVignetCenterWarpper(void* pt2Obj, CvPoint mousePt);

	void setBokehCenters(CvPoint firstPt, CvPoint secondPt);
	static void setBokehCentersWarpper(void* pt2Obj, CvPoint firstPt, CvPoint secondPt);

	void setGammaCtrlPointsList(const vector< vector<CvPoint2D32f> > &ctrlPointsList);
	static void setGammaCtrlPointsListWrapper(void* pt2Obj,
			const vector<vector<CvPoint2D32f> > &ctrlPointsList);


	void resetAll();
	void randomSurprise();

	void increVignetPower();
	void decreVignetPower();
	void increBokehPower();
	void decreBokehPower();


	~Controller();

private:

	Gamma* m_gamma;
	Vignet* m_vignet;
	Bokeh* m_bokeh;
	FilterBank m_filterBank;

	IplImage* m_srcImg;

	void updateAndRunFilterBank(Filter* filter);

};



#endif
