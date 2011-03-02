
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "gamma.h"
using namespace std;

// Helper functions
template<class T> string to_string(T t);
template<class T> bool from_string(T& t, const string& s, ios_base& (*f)(ios_base&));
void tokenize(const string &str, vector<float> &tokens, const string &delimiters);

Gamma::Gamma(const IplImage &src) :
	Filter(src, "Gamma"), ACCURACY(255) {

	gammaTableB.resize(256);
	gammaTableG.resize(256);
	gammaTableR.resize(256);

}

void Gamma::setCtrlPoints(int ch, const vector<CvPoint2D32f> &ctrlPoints) {

	ctrlPointsList[ch] = ctrlPoints;

}

void Gamma::updateGammaTables(int ch) {

	vector<CvPoint2D32f> ctrlPts = ctrlPointsList[ch];

	CvPoint2D32f *pControls = new CvPoint2D32f[4];
	for (int i = 0; i < 4; ++i) {
		pControls[i] = ctrlPts[i];
	}

	int orderIdx = 255;
	for (int i = 0; i <= ACCURACY; i++) {

		float u = (float) i / ACCURACY;
		CvPoint2D32f newPt = Bernstein(u, pControls);

		if (ch == 0) {
			for (int j = (int) newPt.x; j <= orderIdx; j++) {
				gammaTableB[j] = (int) newPt.y;
			}
		}
		if (ch == 1) {
			for (int j = (int) newPt.x; j <= orderIdx; j++) {
				gammaTableG[j] = (int) newPt.y;
			}
		}
		if (ch == 2) {
			for (int j = (int) newPt.x; j <= orderIdx; j++) {
				gammaTableR[j] = (int) newPt.y;
			}
		}

		orderIdx--;

	}

	delete[] pControls;

}

void Gamma::setCtrlPointsList(const vector< vector<CvPoint2D32f> > &ctrlPointsList) {

	this->ctrlPointsList = ctrlPointsList;

	updateGammaTables(0);
	updateGammaTables(1);
	updateGammaTables(2);

}

CvPoint2D32f Gamma::Bernstein(float u, const CvPoint2D32f* p) {

	CvPoint2D32f a, b, c, d, r;

	a = pointTimes(pow(u, 3), p[0]);
	b = pointTimes(3 * pow(u, 2) * (1 - u), p[1]);
	c = pointTimes(3 * u * pow((1 - u), 2), p[2]);
	d = pointTimes(pow((1 - u), 3), p[3]);

	r = pointAdd(pointAdd(a, b), pointAdd(c, d));

	return r;
}

CvPoint2D32f Gamma::pointAdd(CvPoint2D32f p, CvPoint2D32f q) {
	// 2 vector addition (p=p+q)
	p.x += q.x;
	p.y += q.y;

	return p;
}

CvPoint2D32f Gamma::pointTimes(float c, CvPoint2D32f p) {
	// vector * scale (p=c*p)
	p.x *= c;
	p.y *= c;

	return p;
}

// Virtual function implementation
void Gamma::filtering(const IplImage &src, IplImage* rst) {

	for (int row = 0; row < src.height; row++) {

		uchar* pImg = (uchar*) (src.imageData + row * src.widthStep);
		uchar* pResult = (uchar*) (rst->imageData + row * rst->widthStep);

		for (int col = 0; col < src.width; col++) {
			for (int ch = 0; ch < 3; ++ch) {

				if (ch == 0)
					pResult[3 * col + ch] = gammaTableB[pImg[3 * col + ch]];
				if (ch == 1)
					pResult[3 * col + ch] = gammaTableG[pImg[3 * col + ch]];
				if (ch == 2)
					pResult[3 * col + ch] = gammaTableR[pImg[3 * col + ch]];

			}
		}
	}

	cvCopy(rst, backupResultImg);

}

void Gamma::reset() {

	gammaTableB.resize(256, 0);
	gammaTableG.resize(256, 0);
	gammaTableR.resize(256, 0);

}

void Gamma::importSettings(string fileName, int suffix) {

	fileName = fileName + to_string<int> (suffix);

	string line;
	ifstream myfile(fileName.c_str());
	int lineCnt = 0;
	vector<float> temp;

	if (myfile.is_open()) {

		cout << "> gamma file was loaded from: " << fileName << endl;

		while (myfile.good()) {

			getline(myfile, line);
			tokenize(line, temp, " ");

			vector<CvPoint2D32f> loadedCtrlPts;
			for (unsigned int i = 0; i < temp.size(); i += 2) {
				CvPoint2D32f loadedPt = cvPoint2D32f(temp[i], temp[i + 1]);
				loadedCtrlPts.push_back(loadedPt);
			}

			if (loadedCtrlPts.size() != 0) {
				setCtrlPoints(lineCnt, loadedCtrlPts);
				this->updateGammaTables(lineCnt);
			}

			lineCnt++;

		}

		myfile.close();

	} else {

		cout << "> Fail to load gamma file: " << fileName << endl;

	}

}

void Gamma::exportSettings(string fileName, int suffix) {

	fileName = fileName + to_string<int> (suffix);
	ofstream outfile;
	outfile.open(fileName.c_str());

	cout << "> gamma setting was saved to: " << fileName << endl;

	for (unsigned int i = 0; i < ctrlPointsList.size(); ++i) {

		vector<CvPoint2D32f> ctrlPts = ctrlPointsList[i];
		for (unsigned int j = 0; j < ctrlPts.size(); ++j) {
			outfile << " " << ctrlPts[j].x << " " << ctrlPts[j].y;
		}
		outfile << "\n";
	}

	outfile.close();

}


Gamma::~Gamma() {

}

template<class T>
string to_string(T t) {
	ostringstream oss;
	oss << std::dec << t;
	return oss.str();
}

template<class T>
bool from_string(T& t, const string& s, ios_base& (*f)(ios_base&)) {
	std::istringstream iss(s);
	return !(iss >> f >> t).fail();
}

void tokenize(const string &str, vector<float> &tokens, const string &delimiters) {

	// Skip delimiters at beginning.
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// Find first "non-delimiter".
	string::size_type pos = str.find_first_of(delimiters, lastPos);

	tokens.clear();
	float f;
	while (string::npos != pos || string::npos != lastPos) {
		// Found a token, add it to the vector.
		string temp = str.substr(lastPos, pos - lastPos);
		from_string<float> (f, temp, std::dec);
		tokens.push_back(f);
		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}

}
