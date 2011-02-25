
#ifndef __FILEREADER_H__
#define __FILEREADER_H__

#include <string>
#include <cv.h>
#include <cxcore.h>
using namespace std;

class FileReader {
public:

	FileReader(int argc, const char** argv);

	IplImage* m_scaledImg;

	bool readFile(string filePath);

	~FileReader();

private:

	const double LONGSIDE_MAX;

	IplImage* m_srcImg;

	void scaleImg(const IplImage* srcImg);

};


#endif
