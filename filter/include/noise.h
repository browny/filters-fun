
#ifndef __NOISE_H__
#define __NOISE_H__

#include <math.h>
#include <float.h>
#include "filter.h"
#include "../../include/opencv/core/core_c.h"
#include "../../include/opencv/imgproc/imgproc_c.h"
#include "../../include/opencv/highgui/highgui_c.h"

enum NoiseType {

	NOISE_UNIFORM = 0,
	NOISE_GAUSSIAN,
	NOISE_EXPONENTIAL,
	NOISE_RAYLEIGH,
	NOISE_GAMMA,
	NOISE_IMPULSE

};

class Noise : public Filter {
public:

	int noisePower;
	NoiseType noiseType;

	int tempNoisePower;
	NoiseType tempNoiseType;

	Noise(const IplImage &src);

	// Virtual function implementation
	void filtering(const IplImage &src, IplImage* rst);
	void reset();
	void importSettings(string fileName, int suffix);
	void exportSettings(string fileName, int suffix);

	void genNoise(const IplImage &src, IplImage* result, int ch, float amount);

private:

	// Returns a uniformly distributed random number
	double uniform();

	// Returns a gaussian random number (using uniform random numbers)
	double gaussian(void);

	// Generates an exponential random number using a uniform random number
	double exponential(float lambda = 1);

	// Generates a rayleigh random number using a uniform random number
	double rayleigh(float sigma = 1);

	// Generates a gamma random number using a uniform random number
	// NOTE: THIS IS NOT ACCURATE
	double gamma(int k = 2);

	// Generates an impulse using a uniform random number.. This is just one of the
	// thousands of other possibilities.
	double impulse(float amount);

};

#endif
