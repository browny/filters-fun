
#include <iostream>
#include <highgui.h>
#include "../include/fileReader.h"
#include "../include/controller.h"
#include "../window/include/imgEditWindow.h"
#include "../window/include/gammaEditWindow.h"
using namespace std;

int main (int argc, const char **argv) {

    FileReader fileReader(argc, argv);
    fileReader.readFile("test.jpg");

    Controller controller(*fileReader.scaledImg);

    ImgEditWindow imgEditWindow("ImgEdit", cvGetSize(fileReader.scaledImg));
    imgEditWindow.setupCallbacks();

    GammaEditWindow gammaEditWindow("gamma", cvSize(255, 255));
    gammaEditWindow.setupCallbacks();

    bool eventLoop = true;
    while (eventLoop) {

        // EditWindows notify Controller to respond user event
        if (imgEditWindow.needUpdateVignet)
            imgEditWindow.vignetInvokeController(&controller, Controller::setVignetCenterWarpper);

        if (imgEditWindow.needUpdateBokeh)
            imgEditWindow.bokehInvokeController(&controller, Controller::setBokehCentersWarpper);

        if (gammaEditWindow.needUpdateGamma)
            gammaEditWindow.gammaInvokeController(&controller, Controller::setGammaCtrlPointsListWrapper);


        // Display
        cvShowImage(cvGetWindowName(gammaEditWindow.m_window), gammaEditWindow.m_windowImg);
        cvShowImage(cvGetWindowName(imgEditWindow.m_window), controller.outImg);


        // Global keyboard events
        int c = cvWaitKey(10);

        if ((char) c == 27) { // 'Esc' to terminate

            eventLoop = false;

        }

        if (c == '=' || c == '+') { // increase power

            if (imgEditWindow.getEditMode() == VIGNET_EDIT) {

                controller.increVignetPower();

            }

            if (imgEditWindow.getEditMode() == BOKEH_EDIT) {

                controller.increBokehPower();

            }

        }

        if (c == '-' || c == '_') { // decrease power

            if (imgEditWindow.getEditMode() == VIGNET_EDIT) {

                controller.decreVignetPower();

            }

            if (imgEditWindow.getEditMode() == BOKEH_EDIT) {

                controller.decreBokehPower();

            }

        }

        if (c == 'm' || c == 'M') { // change edit mode (Vignet, Bokeh)

            if (imgEditWindow.getEditMode() == VIGNET_EDIT) {

                imgEditWindow.setEditMode(BOKEH_EDIT);
                cout << "currnet mode: 'Bokeh'" << endl;
            }
            else {

                imgEditWindow.setEditMode(VIGNET_EDIT);
                cout << "currnet mode: 'Vignet'" << endl;

            }

        }

        if (c == '1' || c == '!') { // change bokeh gradient mode

            if (imgEditWindow.getEditMode() == BOKEH_EDIT) {

                if (controller.getBokehGradientMode() == LINEAR) {
                    controller.setBokehGradientMode(CIRCULAR);
                    cout << "currnet mode: 'Bokeh' in 'CIRCULAR'" << endl;
                }
                else if (controller.getBokehGradientMode() == CIRCULAR) {
                    controller.setBokehGradientMode(ELLIPSE);
                    cout << "currnet mode: 'Bokeh' in 'ELLIPSE'" << endl;
                }
                else if (controller.getBokehGradientMode() == ELLIPSE) {
                    controller.setBokehGradientMode(LINEAR);
                    cout << "currnet mode: 'Bokeh' in 'LINEAR'" << endl;
                }

            }

        }

        if (c == 'g' || c == 'G') { // change gamma channel

            if (gammaEditWindow.getCurrentChannel() == R_CHANNEL) {
                gammaEditWindow.setCurrentChannel(G_CHANNEL);
            } else if (gammaEditWindow.getCurrentChannel() == G_CHANNEL) {
                gammaEditWindow.setCurrentChannel(B_CHANNEL);
            } else if (gammaEditWindow.getCurrentChannel() == B_CHANNEL) {
                gammaEditWindow.setCurrentChannel(R_CHANNEL);
            }

        }

        if (c == 'c' || c == 'C') { // recover to original photo

            gammaEditWindow.reset();
            controller.resetAll();

        }

        if (c == 's' || c == 'S') { // output result to 'lomo.jpg' file

            int p[3] = { CV_IMWRITE_JPEG_QUALITY, 100, 0 };
            cvSaveImage("lomo.jpg", controller.outImg, p);
            cout << ">> your lomo Image was saved!" << endl;

        }

        if (c == 'r' || c == 'r') { // random order filters

            controller.randomSurprise();

        }

    }

    return 0;

}
