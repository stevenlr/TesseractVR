#ifndef VR_H_
#define VR_H_

//#include "vrpn/vrpn_Tracker.h"
//#include "vrpn/vrpn_XInputGamepad.h"
//#include "vrpn/vrpn_Analog.h"
//#include "vrpn/vrpn_Button.h"

struct _vrpn_TRACKERCB;
typedef struct _vrpn_TRACKERCB vrpn_TRACKERCB;
struct _vrpn_ANALOGCB;
typedef struct _vrpn_ANALOGCB vrpn_ANALOGCB;
struct _vrpn_BUTTONCB;
typedef struct _vrpn_BUTTONCB vrpn_BUTTONCB;
struct _vrpn_BUTTONSTATECB;
typedef struct _vrpn_BUTTONSTATECB vrpn_BUTTONSTATESCB;

class vrpn_Analog_Remote;
class vrpn_Button_Remote;
class vrpn_Tracker_Remote;

namespace vr {

    enum Eye {
        Left, Right, Center
    };

    class stereoscopy_adapter {
    public:
        virtual ~stereoscopy_adapter() {}

        virtual void start_config() = 0;
        virtual void begin_frame() = 0;
        virtual void begin_left() = 0;
        virtual void begin_right() = 0;
        virtual void end_frame() = 0;

        void begin_eye(Eye eye)
        {
            if (eye == Left) {
                this->begin_left();
            } else {
                this->begin_right();
            }
        }
    };

    class anaglyph_stereo_adapter : public stereoscopy_adapter {
    public:
        void start_config() override {}
        void begin_frame() override {}

        void begin_left() override
        {
            glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_TRUE);
        }

        void begin_right() override
        {
            glColorMask(GL_FALSE, GL_TRUE, GL_TRUE, GL_TRUE);
        }

        void end_frame() override
        {
            glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        }
    };

    class quadbuffer_stereo_adapter : public stereoscopy_adapter {
    public:
        void start_config() override
        {
            SDL_GL_SetAttribute(SDL_GL_STEREO, 1);
        }

        void begin_frame() override {}

        void begin_left() override
        {
            glDrawBuffer(GL_BACK_LEFT);
        }

        void begin_right() override
        {
            glDrawBuffer(GL_BACK_RIGHT);
        }

        void end_frame() override {}
    };

    struct virtual_screen {
        float width;
        float height;
        matrix4 p_screen_cave;
        vec o_screen_cave;
        bool is_main;

        struct {
            int width;
            int height;
            int x;
            int y;
        } viewport;
    };

    // CONFIG =================================================================

    extern vector<virtual_screen> virtual_screens;
    extern stereoscopy_adapter *stereo_adapter;
    extern int screenw;
    extern int screenh;
    extern int gbufferw;
    extern int gbufferh;
    extern int main_screen;
    extern float eyesdistance;

    extern void init();

    // PROJECTION =============================================================

    extern bool projection_initialized;
    extern quat q_player_cave;
    extern vec o_player_cave;
    extern vec o_camera_world;
    extern matrix4 p_camera_world;
    extern matrix4 p_cave_camera;
    extern const float world_scale;
    extern Eye current_eye;

    extern void update_camera();
    extern void compute_projection(int screenid, Eye eye, float near, float far, matrix4 &m);
    extern void compute_camera(Eye eye, matrix4 &cammatrix);

    namespace input {

        class Tracker {
        public:
            Tracker(char* device);
            ~Tracker();
			void handle_tracker(void *userdata, const vrpn_TRACKERCB t);
            void getPos(double &x, double &y, double &z) const;
            void getQuat(double &x, double &y, double &z, double &w) const;
            void update();

        private:
			char *_name;
            double _pos[3];
            double _quat[4];

            vrpn_Tracker_Remote *tracker;
        };

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

		extern Tracker *tracker;

        extern Gamepad *gamepad;
        extern bool leftDown;
        extern bool rightDown;
        extern bool upDown;
        extern bool downDown;
		extern bool backLeftDown;
		extern bool backRightDown;
		extern int mode;

		extern void check_input();
		extern void check_input_edit();
		extern void check_input_play();
    }

}

#endif
