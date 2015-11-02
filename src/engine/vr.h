#ifndef VR_H_
#define VR_H_

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

}

#endif
