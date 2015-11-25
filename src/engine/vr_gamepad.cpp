#include "cube.h"
#include "vr.h"
#include "vrpn/vrpn_XInputGamepad.h"
#include "vrpn/vrpn_Analog.h"
#include "vrpn/vrpn_Button.h"

using namespace vr::input;

using namespace std;

namespace {
    void VRPN_CALLBACK handle_analog_stub(void* userData, const vrpn_ANALOGCB a)
    {
        Gamepad *gamepad = static_cast<Gamepad*>(userData);
        gamepad->handle_analog(NULL, a);
    }

    void VRPN_CALLBACK handle_button_stub(void* userData, const vrpn_BUTTONCB b)
    {
        Gamepad *gamepad = static_cast<Gamepad*>(userData);
        gamepad->handle_button(NULL, b);
    }

    void VRPN_CALLBACK handle_button_states_stub(void* userData, const vrpn_BUTTONSTATESCB b)
    {
        Gamepad *gamepad = static_cast<Gamepad*>(userData);
        gamepad->handle_button_states(NULL, b);
    }
}

Gamepad::Gamepad(char *name) : _name(name)
{
	analogs = new vrpn_Analog_Remote(_name);
	analogs->register_change_handler(this, handle_analog_stub);

	buttons = new vrpn_Button_Remote(_name);
	buttons->register_change_handler(this, handle_button_stub);
	buttons->register_states_handler(this, handle_button_states_stub);
}

Gamepad::~Gamepad()
{

}

void Gamepad::update()
{
	if (isInitialized) {
		for (int i = 0; i < nb_buttons; ++i) {
			buttonPressed[i] = false;
			buttonReleased[i] = false;
		}
	}
	analogs->mainloop();
	buttons->mainloop();
}

void Gamepad::handle_analog(void *userdata, const vrpn_ANALOGCB a)
{
	for (int i = 0; i < 2; ++i) {
		analogL[i] = a.channel[i];
		analogR[i] = a.channel[i + 2];
		analogBack[i] = a.channel[i + 5];
	}
}

void Gamepad::handle_button(void *userdata, const vrpn_BUTTONCB b)
{
	if (button[b.button] == 0) //event = pressed
		buttonPressed[b.button] = true;
	else //even = released
		buttonReleased[b.button] = true;
	button[b.button] = b.state;
}

void Gamepad::handle_button_states(void *userdata, const vrpn_BUTTONSTATESCB b)
{
	nb_buttons = b.num_buttons;
	button = new int[b.num_buttons];
	buttonPressed = new bool[b.num_buttons];
	buttonReleased = new bool[b.num_buttons];
	for (int i = 0; i < b.num_buttons; ++i) {
		button[i] = b.states[i];
	}
	isInitialized = true;
}

void Gamepad::getAnalogL(float &x, float &y)
{
	x = analogL[0];
	y = analogL[1];
}

void Gamepad::getAnalogR(float &x, float &y)
{
	x = analogR[0];
	y = analogR[1];
}

void Gamepad::getAnalogBack(float &x, float &y)
{
	x = analogBack[0];
	y = analogBack[1];
}

bool Gamepad::isPressed(int idButton)
{
	return buttonPressed[idButton];
}

bool Gamepad::isReleased(int idButton)
{
	return buttonReleased[idButton];
}

bool Gamepad::isDown(int idButton)
{
	return button[idButton] == 1;
}