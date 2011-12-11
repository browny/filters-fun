
#ifndef __FILTERBANK_H__
#define __FILTERBANK_H__

#include <string>
#include <vector>
#include <cv.h>
#include "../filter/include/filter.h"

using namespace std;

class FilterBank {
public:

	FilterBank();

	vector<Filter*> m_filters;

	void addFilter(Filter* filter);
	void runFilterBank(const IplImage &src, IplImage* rst);
	void runFilterBank(const IplImage &src, string filterName, IplImage* rst);
	void randomOrderFilters();

private:

	int getFilterIndex(string filterName);

};

#endif
