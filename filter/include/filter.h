
/*
 * An abstract class for gamma, vignet, noise, and bokeh filters
 */

#ifndef __FILTER_H__
#define __FILTER_H__

#include <string>
#include "../../include/opencv/core/core_c.h"
#include "../../include/opencv/imgproc/imgproc_c.h"
using namespace std;

class Filter {

public:

	string filterName;
	IplImage* backupResultImg;

	virtual void filtering(const IplImage &src, IplImage* rst) = 0;
	virtual void reset() = 0;
	virtual void importSettings(string fileName, int suffix) = 0;
	virtual void exportSettings(string fileName, int suffix) = 0;

	virtual ~Filter() {

		if (backupResultImg != NULL)
			cvReleaseImage(&backupResultImg);

	}

protected:

	Filter(const IplImage &src, string name) {

		filterName = name;
		backupResultImg = cvCreateImage(cvGetSize(&src), src.depth, src.nChannels);

	}

};


#endif
