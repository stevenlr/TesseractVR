#include "cube.h"

namespace vr {

    bool projection_initialized = false;
    quat q_player_cave(0, 0, 0, 1);
    vec o_player_cave(0, 0.11f, 0.1f); // TODO: test value, to hook up to vrpn
    vec o_camera_world;
    matrix4 p_camera_world;
    matrix4 p_cave_camera;
    matrix4 p_camera_cave;
    const float world_scale = 10;
    Eye current_eye = Center;

    float time = 0;

    void update_camera()
    {
        if (!projection_initialized) {
            projection_initialized = true;

            p_camera_cave = matrix4(
                vec4(-world_scale, 0, 0, 0),
                vec4(0, 0, world_scale, 0),
                vec4(0, -world_scale, 0, 0),
                vec4(0, 0, 0, 1)
            );

            p_cave_camera.invert(p_camera_cave);
        }

        o_camera_world = camera1->headpos();
        p_camera_world.identity();
        p_camera_world.rotate_around_z(-camera1->yaw * RAD);

        /*time += 0.01f;
        virtual_screen &screen = vr::virtual_screens[1];
        screen.p_screen_cave.identity();
        screen.p_screen_cave.rotate_around_y(sin(time) * 0.5f);*/
    }

    void compute_projection(int screenid, Eye eye, float nearp, float farp, matrix4 &m)
    {
        const virtual_screen &screen = vr::virtual_screens[screenid];
        vec o_eye_cave;
        vec4 o_eye_screen;
        float side = (eye == Left) ? -1 : 1;

        nearp /= world_scale;
        farp /= world_scale;

        o_eye_cave = q_player_cave.rotate(vec(side * eyesdistance, 0, 0)).add(o_player_cave);
        o_eye_cave.sub(screen.o_screen_cave);
        screen.p_screen_cave.transform(vec4(o_eye_cave, 1), o_eye_screen);

        float left = (-screen.width / 2 - o_eye_screen.x) * nearp / o_eye_screen.z;
        float right = (screen.width / 2 - o_eye_screen.x) * nearp / o_eye_screen.z;
        float top = (screen.height / 2 - o_eye_screen.y) * nearp / o_eye_screen.z;
        float bottom = (-screen.height / 2 - o_eye_screen.y) * nearp / o_eye_screen.z;

        m.identity();
        m.frustum(left, right, bottom, top, nearp, farp);
        m.translate(vec(o_eye_screen).neg());
        m.mult<vec4>(m, screen.p_screen_cave);
        m.translate(vec(screen.o_screen_cave).neg());
        m.translate(o_player_cave);
        m.scale(1 / world_scale);
    }

    void compute_camera(Eye eye, matrix4 &c)
    {
        c.identity();
        c.scale(world_scale);
        c.mult<vec4>(p_cave_camera, p_camera_world);
        c.translate(vec(o_camera_world).neg());
    }

}
