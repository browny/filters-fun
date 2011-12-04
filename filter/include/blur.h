
#ifndef __BLUR_H__
#define __BLUR_H__

#include <vector>
#include "../../include/opencv/core/core_c.h"
#include "../../include/opencv/imgproc/imgproc_c.h"

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
