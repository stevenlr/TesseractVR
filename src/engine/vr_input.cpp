#include "cube.h"
#include "vr.h"

namespace vr {

    namespace input {

        Gamepad *gamepad = new Gamepad("XInput0@localhost");

        void check_input()
        {
            float x, y;
            float min_analog = 0.2;
            gamepad->getAnalogL(x, y);

            if (x > min_analog) {
                processkey(SDLK_RIGHT, true);
                rightDown = true;
            }
            else if (x < -min_analog) {
                processkey(SDLK_LEFT, true);
                leftDown = true;
            }
            else {
                if (rightDown) {
                    rightDown = false;
                    processkey(SDLK_RIGHT, false);
                }
                else if (leftDown) {
                    leftDown = false;
                    processkey(SDLK_LEFT, false);
                }
            }

            if (y > min_analog) {
                processkey(SDLK_UP, true);
                upDown = true;
            }
            else if (y < -min_analog) {
                processkey(SDLK_DOWN, true);
                downDown = true;
            }
            else {
                if (upDown) {
                    upDown = false;
                    processkey(SDLK_UP, false);
                }
                else if (downDown) {
                    downDown = false;
                    processkey(SDLK_DOWN, false);
                }
            }
        }
    }
}