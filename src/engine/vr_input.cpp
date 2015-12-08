#include "cube.h"
#include "vr.h"

namespace vr {

    namespace input {

        Gamepad *gamepad = new Gamepad("XInput0@localhost");
		bool leftDown = false;
		bool rightDown = false;
		bool upDown = false;
		bool downDown = false;

        void check_input()
        {
			gamepad->update();

			/*Motion emulation*/
            float x, y, backLeft, backRight;
            float min_analog = 0.2;
            gamepad->getAnalogL(x, y);
			gamepad->getAnalogBack(backLeft, backRight);

			player->movemag = max(fabs(x), fabs(y));
			logoutf("Movemag : %f\n", player->movemag);

            if (x > min_analog) {
                processkey(SDLK_d, true);
                rightDown = true;
            }
            else if (x < -min_analog) {
                processkey(SDLK_a, true);
                leftDown = true;
            }
            else {
                if (rightDown) {
                    rightDown = false;
                    processkey(SDLK_d, false);
                }
                else if (leftDown) {
                    leftDown = false;
                    processkey(SDLK_a, false);
                }
            }

            if (y > min_analog) {
                processkey(SDLK_w, true);
                upDown = true;
            }
            else if (y < -min_analog) {
                processkey(SDLK_s, true);
                downDown = true;
            }
            else {
                if (upDown) {
                    upDown = false;
                    processkey(SDLK_w, false);
                }
                else if (downDown) {
                    downDown = false;
                    processkey(SDLK_s, false);
                }
            }

			/*Target emulation*/
			float movingPower = 7.0f * (backRight + 1)/(backLeft + 1);
			gamepad->getAnalogR(x, y);
			if (x != y || y != 0)
				mousemove(x * movingPower, -y * movingPower);

			/*Action emulation*/
			/*Mapping device
				4		5
				   6 7  3
					   2 1
				   8 9	0
			*/
			if (gamepad->isPressed(0)) {
				processkey(SDLK_SPACE, true);
			}
			else if (gamepad->isReleased(0)) {
				processkey(SDLK_SPACE, false);
			}

			if (gamepad->isPressed(5)) { //left click
				processkey(-1, true);
			}
			else if (gamepad->isReleased(5)) {
				processkey(-1, false);
			}

			if (gamepad->isPressed(4)) { //right click
				processkey(-3, true);
			}
			else if (gamepad->isReleased(4)) {
				processkey(-3, false);
			}

			if (gamepad->isPressed(3)) { //wheel up
				processkey(-4, true);
			}
			else if (gamepad->isReleased(3)) {
				processkey(-4, false);
			}
        }
    }
}