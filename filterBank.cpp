
#include "filterBank.h"

FilterBank::FilterBank() {

	m_filters.resize(0);

}

void FilterBank::addFilter(Filter* filter) {

	if (getFilterIndex(filter->filterName) == -1) // the filter doesn't exist in filter bank
		m_filters.push_back(filter);

}

void FilterBank::runFilterBank(const IplImage &src, IplImage* rst) {

	vector<Filter*>::iterator filterIndex = m_filters.begin();

	bool first = true;

	while (filterIndex != m_filters.end()) {

		if (first) {

			(*filterIndex)->filtering(src, rst);
			first = false;

		} else {

			vector<Filter*>::iterator preFilterIndex = filterIndex - 1;
			IplImage* backImg = (*preFilterIndex)->backupResultImg;

			(*filterIndex)->filtering(*backImg, rst);

		}

		filterIndex++;

	}

}

void FilterBank::runFilterBank(const IplImage &src, string filterName, IplImage* rst) {

	int index = getFilterIndex(filterName);

	bool filterIsFirst = false;
	if (index == 0)
		filterIsFirst = true;

	vector<Filter*>::iterator filterIndex = m_filters.begin() + index;

	while (filterIndex != m_filters.end()) {

		if (filterIsFirst) {

			(*filterIndex)->filtering(src, rst);
			filterIsFirst = false;

		} else {

			vector<Filter*>::iterator preFilterIndex = filterIndex - 1;
			IplImage* backImg = (*preFilterIndex)->backupResultImg;

			(*filterIndex)->filtering(*backImg, rst);

		}

		filterIndex++;

	}

}

void FilterBank::randomOrderFilters() {

	int filterCnt = m_filters.size();

	if (filterCnt >= 2) {

		FilterBank newFilterBank;
		int randIndex = 0;

		randIndex = rand() % filterCnt;
		newFilterBank.m_filters.resize(0);

		for (int i = randIndex; i < filterCnt; ++i) {

			newFilterBank.addFilter(m_filters[i]);

		}

		for (int i = 0; i < randIndex; ++i) {

			newFilterBank.addFilter(m_filters[i]);

		}

		m_filters = newFilterBank.m_filters;

	}

}

int FilterBank::getFilterIndex(string filterName) {

	vector<Filter*>::iterator it = m_filters.begin();
	int index = 0;
	bool existence = false;

	while (it != m_filters.end()) {

		if (filterName == (*it)->filterName) {
			existence = true;
			break;
		}

		index++;
		it++;
	}

	return existence ? index : -1; // -1 menas the filter doesn't exist in filter bank

}

