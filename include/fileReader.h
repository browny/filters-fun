
#ifndef __FILEREADER_H__
#define __FILEREADER_H__

#include <string>
#include "./opencv/core/core_c.h"
#include "./opencv/highgui/highgui_c.h"
using namespace std;

class FileReader {
public:

	FileReader(int argc, const char** argv);

	IplImage* scaledImg;

	bool readFile(string filePath);

	~FileReader();

private:

	const double LONGSIDE_MAX;

	IplImage* m_srcImg;

	void scaleImg(const IplImage &srcImg);

};


#endif
