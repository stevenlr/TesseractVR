#ifndef VR_H_
#define VR_H_

//#include "vrpn/vrpn_Tracker.h"
//#include "vrpn/vrpn_XInputGamepad.h"
//#include "vrpn/vrpn_Analog.h"
//#include "vrpn/vrpn_Button.h"

//class vrpn_TRACKERCB;
//class vrpn_Tracker_Remote;

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

    //namespace input {

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

    //    class Gamepad {
    //    public:
    //        /*static void VRPN_CALLBACK handle_analog_stub(void* userData, const vrpn_ANALOGCB a);
    //        static void VRPN_CALLBACK handle_button_stub(void* userData, const vrpn_BUTTONCB a);
    //        static void VRPN_CALLBACK handle_button_states_stub(void* userData, const vrpn_BUTTONSTATESCB a);*/
    //        Gamepad(char *name);
    //        ~Gamepad();
    //        /*void VRPN_CALLBACK handle_analog(void *userdata, const vrpn_ANALOGCB a);
    //        void VRPN_CALLBACK handle_button(void *userdata, const vrpn_BUTTONCB b);
    //        void VRPN_CALLBACK handle_button_states(void *userdata, const vrpn_BUTTONSTATESCB b);*/
    //        void update();
    //        void getAnalogL(float &x, float &y);
    //        void getAnalogR(float &x, float &y);

    //    private:
    //        char *_name;

    //        /*vrpn_Button_Remote *buttons;
    //        vrpn_Analog_Remote *analogs;*/

    //        float analogL[2];
    //        float analogR[2];
    //    };

    //    extern Gamepad *gamepad;

    //}

}

#endif
