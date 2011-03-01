
#include "imgEditWindow.h"

class Controller;

ImgEditWindow::ImgEditWindow(string winName, CvSize winSize) : UIWindow(winName, winSize) {

	m_vignetPt     = cvPoint(0, 0);
	m_bokehFirstPt = cvPoint(0, 0);
	m_bokehSecPt   = cvPoint(0, 0);

	needUpdateVignet = false;
	needUpdateBokeh  = false;


	setEditMode(VIGNET_EDIT);
	setEditModeText("Vignet Mode");

	m_rightClickCnt = 0;

}

void ImgEditWindow::setupCallbacks() {

	cvSetMouseCallback(cvGetWindowName(m_window),
			             &ImgEditWindow::wrapperToOnMouseCallback,
			             this);

}

void ImgEditWindow::onMouseCallback(int event, int x, int y) {

	if (m_editMode == VIGNET_EDIT) {

		if (event == CV_EVENT_LBUTTONDOWN) {

			m_vignetPt = cvPoint(x, y);
			needUpdateVignet = true;

		}

	}

	if (m_editMode == BOKEH_EDIT) {

		if (event == CV_EVENT_LBUTTONDOWN) {

			m_bokehFirstPt = cvPoint(x, y);
			needUpdateBokeh = true;

		}

		if (event == CV_EVENT_RBUTTONDOWN) {

			if (m_rightClickCnt == 0) {

				m_bokehFirstPt = cvPoint(x, y);
				m_rightClickCnt = 1;

			} else if (m_rightClickCnt == 1) {

				m_bokehSecPt = cvPoint(x, y);
				m_rightClickCnt = 0;
				needUpdateBokeh = true;

			}

		}

	}

}

void ImgEditWindow::onKeyCallback(int keyCode) {


}

void ImgEditWindow::wrapperToOnMouseCallback(int event, int x, int y, int flags, void *param) {

	ImgEditWindow* imgEditWindowObj = (ImgEditWindow*) param;
	imgEditWindowObj->onMouseCallback(event, x, y);

}

void ImgEditWindow::vignetInvokeController(void* pt2Obj,
		void( pt2Func)(void* pt2Obj, CvPoint mousePt)) {

	pt2Func(pt2Obj, m_vignetPt);
	needUpdateVignet = false;

}

void ImgEditWindow::bokehInvokeController(void* pt2Obj,
		void( pt2Func)(void* pt2Obj, CvPoint firstPt, CvPoint secondPt)) {

	pt2Func(pt2Obj, m_bokehFirstPt, m_bokehSecPt);
	needUpdateBokeh = false;

}


ImgEditWindow::~ImgEditWindow() {

}

