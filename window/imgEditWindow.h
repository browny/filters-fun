
#ifndef __IMGEDITWINDOW_H__
#define __IMGEDITWINDOW_H__

#include <cv.h>
#include <cxcore.h>
#include <string>
#include "uiWindow.h"
using namespace std;

enum EDIT_MODE { VIGNET_EDIT = 0, BOKEH_EDIT };

class ImgEditWindow : public UIWindow {

public:

	ImgEditWindow(string winName, CvSize winSize);

	CvPoint m_vignetPt;
	CvPoint m_bokehFirstPt, m_bokehSecPt;

	bool m_needUpdateVignet;
	bool m_needUpdateBokeh;

	// Virtual function implementation
	void setupCallbacks();
	void onMouseCallback(int event, int x, int y);
	void onKeyCallback(int keyCode);

	// Access method
	EDIT_MODE getEditMode() { return m_editMode; }
	void setEditMode(EDIT_MODE mode) { m_editMode = mode; }

	string getEditModeText() { return m_editModeText; }
	void setEditModeText(string text) { m_editModeText = text; }

	// Member function
	void vignetInvokeController(void* pt2Obj,
                                void (pt2Func)(void* pt2Obj, CvPoint mousePt));

	void bokehInvokeController(void* pt2Obj,
			                   void (pt2Func)(void* pt2Obj, CvPoint firstPt, CvPoint secondPt));


	~ImgEditWindow();

private:

	int m_rightClickCnt;

	EDIT_MODE m_editMode;
	string m_editModeText;

	static void wrapperToOnMouseCallback(int event, int x, int y, int flags, void *param);


};


#endif
