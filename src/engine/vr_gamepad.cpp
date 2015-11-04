#include "cube.h"
//#include "vr.h"
//
//using namespace vr::input;
//
//using namespace std;
//#include "vrpn/vrpn_XInputGamepad.h"
//#include "vrpn/vrpn_Analog.h"
//#include "vrpn/vrpn_Button.h"
//
//void VRPN_CALLBACK Gamepad::handle_analog_stub(void* userData, const vrpn_ANALOGCB a)
//{
//	Gamepad *gamepad = static_cast<Gamepad*>(userData);
//	gamepad->handle_analog(NULL, a);
//}
//
//void VRPN_CALLBACK Gamepad::handle_button_stub(void* userData, const vrpn_BUTTONCB b)
//{
//	Gamepad *gamepad = static_cast<Gamepad*>(userData);
//	gamepad->handle_button(NULL, b);
//}
//
//void VRPN_CALLBACK Gamepad::handle_button_states_stub(void* userData, const vrpn_BUTTONSTATESCB b)
//{
//	Gamepad *gamepad = static_cast<Gamepad*>(userData);
//	gamepad->handle_button_states(NULL, b);
//}
//
//Gamepad::Gamepad(char *name) : _name(name)
//{
//	analogs = new vrpn_Analog_Remote(_name);
//	analogs->register_change_handler(this, handle_analog_stub);
//
//	buttons = new vrpn_Button_Remote(_name);
//	buttons->register_change_handler(this, handle_button_stub);
//	buttons->register_states_handler(this, handle_button_states_stub);
//}
//
//Gamepad::~Gamepad()
//{
//
//}
//
//void Gamepad::update()
//{
//	analogs->mainloop();
//	buttons->mainloop();
//}
//
//void Gamepad::handle_analog(void *userdata, const vrpn_ANALOGCB a)
//{
//	for (int i = 0; i < 2; ++i) {
//		analogL[i] = a.channel[i];
//	}
//	for (int i = 0; i < 2; ++i) {
//		analogR[i] = a.channel[i + 2];
//	}
//}
//
//void Gamepad::handle_button(void *userdata, const vrpn_BUTTONCB b)
//{
//
//}
//
//void Gamepad::handle_button_states(void *userdata, const vrpn_BUTTONSTATESCB b)
//{
//
//}
//
//void Gamepad::getAnalogL(float &x, float &y)
//{
//	x = analogL[0];
//	y = analogL[1];
//}
//
//void Gamepad::getAnalogR(float &x, float &y)
//{
//	x = analogR[0];
//	y = analogR[1];
//}