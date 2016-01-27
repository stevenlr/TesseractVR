#include "cube.h"
#include "game.h"
#include "vr.h"

#define PRESS_ACTION(b, key, elseFct) (gamepad->isPressed(b) ? processkey(key, true) : elseFct) 
#define RELEASE_ACTION(b, key, elseFct) (gamepad->isReleased(b) ? processkey(key, false) : elseFct)
#define CHECKBUTTON(b, key)	(PRESS_ACTION(b, key, RELEASE_ACTION(b, key, NULL)))
#define MODE_COPYPASTE 1

namespace vr {

    namespace input {

        Gamepad *gamepad = new Gamepad("XInput0@localhost");
		//Tracker *tracker = new Tracker("Tracker0@localhost");
		bool leftDown = false;
		bool rightDown = false;
		bool upDown = false;
		bool downDown = false;
		bool backLeftDown = false;
		bool backRightDown = false;
		int mode = 0;

		void check_input_edit()
		{
			/*Mapping device
				4		5
				   6 7  3
					   2 1
				   8 9	0
			*/
			if (gamepad->isPressed(9)) {
				mode = (mode + 1) % 2;
			}

			if (mode != MODE_COPYPASTE) {
				CHECKBUTTON(1, SDLK_g);	//grid power with Wheel
				CHECKBUTTON(2, SDLK_y);	//texture with Wheel
				CHECKBUTTON(3, SDLK_r);	//Rotate with Wheel
				CHECKBUTTON(0, SDLK_f);	//Push or pull faces of cubes with Wheel
				RELEASE_ACTION(1, SDLK_v, NULL);
				RELEASE_ACTION(2, SDLK_k, NULL);
				RELEASE_ACTION(3, SDLK_x, NULL);
				RELEASE_ACTION(0, SDLK_c, NULL);
			}
			else {
				RELEASE_ACTION(1, SDLK_g, NULL);
				RELEASE_ACTION(2, SDLK_y, NULL);
				RELEASE_ACTION(3, SDLK_r, NULL);
				RELEASE_ACTION(0, SDLK_f, NULL);
				CHECKBUTTON(1, SDLK_v);	//paste
				CHECKBUTTON(2, SDLK_k);	//optimize map (perf + looks)
				CHECKBUTTON(3, SDLK_x);	//flip
				CHECKBUTTON(0, SDLK_c);	//copy
			}
			CHECKBUTTON(8, SDLK_SPACE);
			CHECKBUTTON(5, -4); //wheel up  	->	extend forward
			CHECKBUTTON(4, -5); //wheel down	->	extrude
			CHECKBUTTON(9, SDLK_LSHIFT); //analog right click -> Move faster

			float backLeft, backRight, min_analog = 0.2;
			gamepad->getAnalogBack(backLeft, backRight);

			if (backLeft > min_analog && !backLeftDown) { //left click	->	select
				backLeftDown = true;
				processkey(-1, true);
			}
			else if (backLeftDown) {
				backLeftDown = false;
				processkey(-1, false);
			}
			if (backRight > min_analog && !backRightDown) { //right click	->	hold to move selection, click to extend selection or reorient selection face
				backRightDown = true;
				processkey(-3, true);
			}
			else if (backRightDown) {
				backRightDown = false;
				processkey(-1, false);
			}
		}

		void check_input_play()
		{
			/*Mapping device
				4		5
				   6 7  3
					   2 1
				   8 9	0
			*/

			CHECKBUTTON(0, SDLK_SPACE);
			CHECKBUTTON(5, -1);	//left click
			CHECKBUTTON(4, -3); //right click
			CHECKBUTTON(3, -4); //wheel up
		}

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
			float movingPower = 7.0f * (player->state == CS_EDITING ? 1 : (backRight + 1)/(backLeft + 1));
			gamepad->getAnalogR(x, y);
			if (x != y || y != 0)
				mousemove(x * movingPower, 0); //-y * movingPower);

			/*Action emulation*/
			CHECKBUTTON(6, SDLK_e); // edit mode
			if (player->state == CS_EDITING) {
				check_input_edit();
			}
			else {
				check_input_play();
			}
        }
    }
}