#ifndef VR_H_
#define VR_H_

//#include "vrpn/vrpn_Tracker.h"
//#include "vrpn/vrpn_XInputGamepad.h"
//#include "vrpn/vrpn_Analog.h"
//#include "vrpn/vrpn_Button.h"

//class vrpn_TRACKERCB;
struct _vrpn_ANALOGCB;
typedef struct _vrpn_ANALOGCB vrpn_ANALOGCB;
struct _vrpn_BUTTONCB;
typedef struct _vrpn_BUTTONCB vrpn_BUTTONCB;
struct _vrpn_BUTTONSTATECB;
typedef struct _vrpn_BUTTONSTATECB vrpn_BUTTONSTATESCB;
class vrpn_Analog_Remote;
class vrpn_Button_Remote;

namespace vr {

    struct virtual_screen {
        float width;
        float height;
        vec up;
        vec right;
        bool is_main;

        struct {
            int width;
            int height;
            int x;
            int y;
        } viewport;
    };

    extern vector<virtual_screen> virtual_screens;

    void init();

    namespace input {

    //    class Tracker {
    //    public:
    //        Tracker(const char* device);
    //        ~Tracker();

    //        void getPos(double &x, double &y, double &z) const;
    //        void getQuat(double &x, double &y, double &z, double &w) const;
    //        void update();

    //        void handle_tracker(void *userdata, const vrpn_TRACKERCB t);

    //    private:
    //        double _pos[3];
    //        double _quat[4];

    //        vrpn_Tracker_Remote *_tracker;
    //    };

        class Gamepad {
        public:
            Gamepad(char *name);
            ~Gamepad();
            void handle_analog(void *userdata, const vrpn_ANALOGCB a);
            void handle_button(void *userdata, const vrpn_BUTTONCB b);
            void handle_button_states(void *userdata, const vrpn_BUTTONSTATESCB b);
            void update();
            void getAnalogL(float &x, float &y);
            void getAnalogR(float &x, float &y);
			void getAnalogBack(float &x, float &y);
			bool isPressed(int idButton);
			bool isReleased(int idButton);
			bool isDown(int idButton);

        private:
            char *_name;

            vrpn_Button_Remote *buttons;
            vrpn_Analog_Remote *analogs;

            float analogL[2];
            float analogR[2];
			float analogBack[2];
			int *button;
			bool *buttonPressed;
			bool *buttonReleased;
			int nb_buttons;
			
			bool isInitialized = false;
        };

        extern Gamepad *gamepad;
        extern bool leftDown;
        extern bool rightDown;
        extern bool upDown;
        extern bool downDown;

		extern void check_input();
    }

}

#endif
