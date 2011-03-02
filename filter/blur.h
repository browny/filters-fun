
#ifndef __BLUR_H__
#define __BLUR_H__

#include <cv.h>
#include <cxcore.h>
#include <vector>
using namespace std;

class Blur {
public:

	Blur(const IplImage &src);

	int levelCnt;
	vector<IplImage*> blurredImgs;

	void genBlurredImgs(const IplImage &src, vector<IplImage*> &imgs);

	~Blur();

private:

	const double STEP;
	const double MAX_SIGMA;

};

#endif
