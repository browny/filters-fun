
#ifndef __FILTERBANK_H__
#define __FILTERBANK_H__

#include <cv.h>
#include <cxcore.h>
#include <string>
#include <vector>
#include "./filter/filter.h"

using namespace std;

class FilterBank {
public:

	FilterBank();

	vector<Filter*> m_filters;

	void addFilter(Filter* filter);
	void runFilterBank(const IplImage* src, IplImage* rst);
	void runFilterBank(const IplImage* src, IplImage* rst, string filterName);
	void randomOrderFilters();

private:

	int getFilterIndex(string filterName);

};

#endif
