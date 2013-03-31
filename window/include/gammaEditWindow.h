
#ifndef __GAMMAEDITWINDOW_H__
#define __GAMMAEDITWINDOW_H__

#include <string>
#include <vector>
#include "uiWindow.h"
using namespace std;

enum GAMMA_CHANNEL { R_CHANNEL = 2, G_CHANNEL = 1, B_CHANNEL = 0 };

class GammaEditWindow : public UIWindow
{
public:

    GammaEditWindow(string winName, CvSize winSize);

    bool needUpdateGamma;

    // Virtual function implementation
    void setupCallbacks();
    void onMouseCallback(int event, int x, int y);
    void onKeyCallback(int keyCode);

    // Access function
    GAMMA_CHANNEL getCurrentChannel();
    void setCurrentChannel(GAMMA_CHANNEL ch);

    // Member function
    void reset();

    void gammaInvokeController(void* pt2Obj,
            void( pt2Func)(void* pt2Obj, const vector< vector<CvPoint2D32f> > &ctrlPointsList));

    ~GammaEditWindow();

private:

    const int ACCURACY;

    GAMMA_CHANNEL m_currentChannel;
    int m_selectedCtrlPtIndex;
    vector<int> m_inverseTable;
    vector< vector<CvPoint2D32f> > ctrlPointsList;

    void updateGammaCurve(IplImage* ctrlPannel);
    int getNearPointIndex(CvPoint mouse_pt, int ch);
    CvPoint2D32f Bernstein(float u, CvPoint2D32f* p);
    CvPoint2D32f pointAdd(CvPoint2D32f p, CvPoint2D32f q);
    CvPoint2D32f pointTimes(float c, CvPoint2D32f p);

    static void wrapperToOnMouseCallback(int event, int x, int y, int flags, void *param);

};

#endif
