
#include "gammaEditWindow.h"

GammaEditWindow::GammaEditWindow(string winName, CvSize winSize) :
    UIWindow(winName, winSize), ACCURACY(255) {

        m_windowImg->origin = IPL_ORIGIN_BL;
        m_inverseTable.resize(256);
        for (int i = 0; i < 256; ++i)
            m_inverseTable[i] = 256 - (i + 1);

        reset();

    }

void GammaEditWindow::reset() {

    needUpdateGamma = false;
    m_currentChannel = R_CHANNEL;
    m_selectedCtrlPtIndex = -1;

    ctrlPointsList.resize(3, vector<CvPoint2D32f>(4));

    vector< vector<CvPoint2D32f> >::iterator it = ctrlPointsList.begin();
    while (it != ctrlPointsList.end()) {

        vector<CvPoint2D32f>::iterator it2 = it->begin();

        it2->x = 0;
        it2->y = 0;
        it2++;

        it2->x = 85.333f;
        it2->y = 85.333f;
        it2++;

        it2->x = 170.666f;
        it2->y = 170.666f;
        it2++;

        it2->x = 255;
        it2->y = 255;
        it2++;

        it++;
    }

    updateGammaCurve(m_windowImg);

}

void GammaEditWindow::gammaInvokeController(void* pt2Obj,
        void( pt2Func)(void* pt2Obj, const vector< vector<CvPoint2D32f> > &ctrlPointsList)) {

    pt2Func(pt2Obj, ctrlPointsList);
    needUpdateGamma = false;

}

void GammaEditWindow::updateGammaCurve(IplImage* ctrlPannel) {

    cvZero(ctrlPannel);

    vector<CvPoint2D32f> ctrlPts = ctrlPointsList[ (int)m_currentChannel ];

    // draw control points
    for (int i = 0; i < 4; i++) {
        CvPoint ptc;
        ptc.x = (int) ctrlPts[i].x;
        ptc.y = (int) ctrlPts[i].y;
        cvCircle(ctrlPannel, ptc, 5, CV_RGB(0,255,0), -2, CV_AA, 0);
    }


    //draw Bezier curve
    CvPoint2D32f *pControls = new CvPoint2D32f[4];
    for (int i = 0; i < 4; ++i) {
        pControls[i] = ctrlPts[i];
    }

    CvPoint pt_now = cvPoint(0, 0);
    CvPoint pt_pre = cvPoint(0, 0);
    for (int i = 0; i <= ACCURACY; i++) {

        float u = (float) i / (float)ACCURACY;
        CvPoint2D32f newPt = Bernstein(u, pControls);

        pt_now.x = (int) newPt.x;
        pt_now.y = (int) newPt.y;

        if (i > 0)
            cvLine(ctrlPannel, pt_now, pt_pre, CV_RGB(230,255,0));

        pt_pre = pt_now;
    }

    CvFont font;
    cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.5, 0.5);
    if ((int)m_currentChannel == 0)
        cvPutText(ctrlPannel, "B", cvPoint(20, 240), &font, cvScalar(0, 0, 255, 0));
    if ((int)m_currentChannel == 1)
        cvPutText(ctrlPannel, "G", cvPoint(20, 240), &font, cvScalar(0, 0, 255, 0));
    if ((int)m_currentChannel == 2)
        cvPutText(ctrlPannel, "R", cvPoint(20, 240), &font, cvScalar(0, 0, 255, 0));

    delete[] pControls;

}

int GammaEditWindow::getNearPointIndex(CvPoint mouse_pt, int ch) {

    CvPoint pt = cvPoint(0, 0);
    for (int i = 0; i < 4; i++) {

        vector<CvPoint2D32f> ctrlPts = ctrlPointsList[ch];

        pt.x = mouse_pt.x - (int) ctrlPts[i].x;
        pt.y = mouse_pt.y - (int) ctrlPts[i].y;
        float distance = sqrt((float) (pt.x * pt.x + pt.y * pt.y));

        if (distance < 20)
            return i;
    }

    return -1;
}

CvPoint2D32f GammaEditWindow::Bernstein(float u, CvPoint2D32f* p) {
    CvPoint2D32f a, b, c, d, r;

    a = pointTimes(pow(u, 3), p[0]);
    b = pointTimes(3 * pow(u, 2) * (1 - u), p[1]);
    c = pointTimes(3 * u * pow((1 - u), 2), p[2]);
    d = pointTimes(pow((1 - u), 3), p[3]);

    r = pointAdd(pointAdd(a, b), pointAdd(c, d));

    return r;
}

CvPoint2D32f GammaEditWindow::pointAdd(CvPoint2D32f p, CvPoint2D32f q) {
    // 2 vector addition (p=p+q)
    p.x += q.x;
    p.y += q.y;

    return p;
}

CvPoint2D32f GammaEditWindow::pointTimes(float c, CvPoint2D32f p) {
    // vector * scale (p=c*p)
    p.x *= c;
    p.y *= c;

    return p;
}

// Virtual function implementation
void GammaEditWindow::onMouseCallback(int event, int x, int y) {

    if ( (x >= 0) && (x < 256) && (y >= 0) && (y < 256) ) {

        y = m_inverseTable[y];

        vector<CvPoint2D32f> ctrlPts = ctrlPointsList[ (int)m_currentChannel ];

        if (event == CV_EVENT_LBUTTONDOWN) {

            CvPoint pt = cvPoint(x, y);

            if (m_selectedCtrlPtIndex > -1) {  // 第一次選到點, 移動後的第二次點

                m_selectedCtrlPtIndex = -1;

            } else {

                m_selectedCtrlPtIndex = getNearPointIndex(pt, (int)m_currentChannel);

            }

        } else if (event == CV_EVENT_MOUSEMOVE) { // change control point location

            if (m_selectedCtrlPtIndex > -1) {

                ctrlPts[m_selectedCtrlPtIndex].x = (float) x;
                ctrlPts[m_selectedCtrlPtIndex].y = (float) y;

                ctrlPointsList[ (int)m_currentChannel ] = ctrlPts;

                updateGammaCurve(m_windowImg);
                needUpdateGamma = true;

            }
        }

    }
}

void GammaEditWindow::setupCallbacks() {

    cvSetMouseCallback(cvGetWindowName(m_window),
            &GammaEditWindow::wrapperToOnMouseCallback,
            this);

}

void GammaEditWindow::onKeyCallback(int keyCode) {


}

GAMMA_CHANNEL GammaEditWindow::getCurrentChannel() {

    return m_currentChannel;

}

void GammaEditWindow::setCurrentChannel(GAMMA_CHANNEL ch) {

    m_currentChannel = ch;
    updateGammaCurve(m_windowImg);
    needUpdateGamma = true;

}

void GammaEditWindow::wrapperToOnMouseCallback(int event, int x, int y, int flags, void *param) {

    GammaEditWindow* GammaEditWindowObj = (GammaEditWindow*) param;
    GammaEditWindowObj->onMouseCallback(event, x, y);

}

GammaEditWindow::~GammaEditWindow() {

}
