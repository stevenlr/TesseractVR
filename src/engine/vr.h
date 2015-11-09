#ifndef VR_H_
#define VR_H_

namespace vr {

    class stereoscopy_adapter {
    public:
        virtual ~stereoscopy_adapter() {}

        virtual void start_config() = 0;
        virtual void begin_frame() = 0;
        virtual void begin_left() = 0;
        virtual void begin_right() = 0;
        virtual void end_frame() = 0;
    };

    class anaglyph_stereo_adapter : public stereoscopy_adapter {
    public:
        void start_config() override {}
        void begin_frame() override {}

        void begin_left() override
        {
            glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_TRUE);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void begin_right() override
        {
            glColorMask(GL_FALSE, GL_TRUE, GL_TRUE, GL_TRUE);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void begin_right() override
        {
            glDrawBuffer(GL_BACK_RIGHT);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void end_frame() override {}
    };

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
    extern stereoscopy_adapter *stereo_adapter;
    extern int screenw;
    extern int screenh;
    extern int gbufferw;
    extern int gbufferh;
    extern int main_screen;

    void init();

}

#endif
