
#include <iostream>
#include "../include/noise.h"
using namespace std;

Noise::Noise(const IplImage &src) : Filter(src, "Noise") {

    noisePower = 0;
    noiseType = NOISE_GAUSSIAN;

    tempNoisePower = 0;
    tempNoiseType = NOISE_GAUSSIAN;

}

// Returns a uniformly distributed random number
double Noise::uniform()
{
    return (rand()/(float)0x7fff);
}

// Returns a gaussian random number (using uniform random numbers)
double Noise::gaussian(void)
{
    static double v, fac;
    static int phase = 0;
    double S, Z, U1, U2, u;

    if (phase)
        Z = v * fac;
    else
    {
        do
        {
            U1 = uniform();
            U2 = uniform();

            u = 2. * U1 - 1.;
            v = 2. * U2 - 1.;
            S = u * u + v * v;
        } while(S >= 1);

        fac = sqrt (-2. * log(S) / S);
        Z = u * fac;
    }

    phase = 1 - phase;

    return Z;
}

// Generates an exponential random number using a uniform random number
double Noise::exponential(float lambda)
{
    return -lambda*log(uniform());
}

// Generates a rayleigh random number using a uniform random number
double Noise::rayleigh(float sigma)
{
    return sigma*sqrt(-1*log(uniform()));
}

// Generates a gamma random number using a uniform random number
// NOTE: THIS IS NOT ACCURATE
double Noise::gamma(int k)
{
    double ret=0;
    while(k>0)
    {
        ret+= (-(log(uniform())));
        k--;
    }
    return ret;
}

// Generates an impulse using a uniform random number.. This is just one of the
// thousands of other possibilities.
double Noise::impulse(float amount)
{
    if(uniform()>1-amount)
        return 100;
    if(uniform()<amount)
        return -100;

    return 0;
}

void Noise::genNoise(const IplImage &src, IplImage* result, int ch, float amount) {

    cvCopy(&src, result);
    CvSize imgSize = cvGetSize(result);

    // Go through each pixel
    for (int y = 0; y < imgSize.height; y++) {
        uchar* pImg = (uchar*) (result->imageData + y * result->widthStep);

        for (int x = 0; x < imgSize.width; x++) {
            int randomValue = 0; // Our noise is additive.. this holds
            switch (noiseType) // the amount to add/subtract
            {
                case NOISE_UNIFORM: // I chose UNIFORM, so give me a uniform random number
                    randomValue = (char) (uniform() * amount);
                    break;

                case NOISE_EXPONENTIAL: // I chose EXPONENTIAL... so exp random number please
                    randomValue = (int) (exponential() * amount);
                    break;

                case NOISE_GAUSSIAN: // same here
                    randomValue = (int) (gaussian() * amount);
                    break;

                case NOISE_RAYLEIGH: // ... guess!!
                    randomValue = (int) (rayleigh() * amount);
                    break;

                case NOISE_GAMMA: // I chose gamma... give me a gamma random number
                    randomValue = (int) (gamma() * amount);
                    break;

                case NOISE_IMPULSE: // I need salt and pepper.. pass the shakers please
                    randomValue = (int) (impulse((float) amount / 256) * amount);
            }

            if (ch == 0) {
                if (((pImg[3 * x + 0] + randomValue) < 256) && ((pImg[3 * x + 0] + randomValue)
                            >= 0))
                    pImg[3 * x + 0] = pImg[3 * x + 0] + randomValue;
            }
            if (ch == 1)
                if (((pImg[3 * x + 1] + randomValue) < 256) && ((pImg[3 * x + 1] + randomValue)
                            >= 0))
                    pImg[3 * x + 1] = pImg[3 * x + 1] + randomValue;

            if (ch == 2)
                if (((pImg[3 * x + 2] + randomValue) < 256) && ((pImg[3 * x + 2] + randomValue)
                            >= 0))
                    pImg[3 * x + 2] = pImg[3 * x + 2] + randomValue;
            if (ch == 3) {
                if (((pImg[3 * x + 0] + randomValue) < 256) && ((pImg[3 * x + 0] + randomValue)
                            >= 0))
                    pImg[3 * x + 0] = pImg[3 * x + 0] + randomValue;
                if (((pImg[3 * x + 1] + randomValue) < 256) && ((pImg[3 * x + 1] + randomValue)
                            >= 0))
                    pImg[3 * x + 1] = pImg[3 * x + 1] + randomValue;
                if (((pImg[3 * x + 2] + randomValue) < 256) && ((pImg[3 * x + 2] + randomValue)
                            >= 0))
                    pImg[3 * x + 2] = pImg[3 * x + 2] + randomValue;

            }

        }
    }

}

// --- virtual function implementation --- //
void Noise::filtering(const IplImage &src, IplImage* rst) {

    genNoise(src, rst, 3, noisePower);
    cvCopy(rst, backupResultImg);

}

void Noise::reset() {

    noisePower = 0;
    noiseType = NOISE_GAUSSIAN;

    tempNoisePower = 0;
    tempNoiseType = NOISE_GAUSSIAN;
}

void Noise::importSettings(string fileName, int suffix) {

}

void Noise::exportSettings(string fileName, int suffix) {

}
