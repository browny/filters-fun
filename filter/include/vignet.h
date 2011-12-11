
#ifndef __VIGNET_H__
#define __VIGNET_H__

#include <cv.h>
#include <highgui.h>
#include "filter.h"
#include "../../gradient/include/pointGradient.h"

class Vignet : public Filter {
	
public:
	
	Vignet(const IplImage &img);

	// Virtual function implementation
	void filtering(const IplImage &src, IplImage* rst);
	void reset();
	void importSettings(string fileName, int suffix);
	void exportSettings(string fileName, int suffix);

	// Member function
	CvPoint getCenter()            { return m_pointGrad->getFirstPt(); }
	void    setCenter(CvPoint pt)  { m_pointGrad->setFirstPt(pt); }

	void incrementPower() { m_pointGrad->incrementPower(); }
	void decrementPower() { m_pointGrad->decrementPower(); }

	~Vignet();

private:
			
	PointGradient* m_pointGrad;

	IplImage* m_maskImg;
	IplImage* m_labImg;
		
};


#endif

