#include "cube.h"

namespace vr {

    bool projection_initialized = false;
    vec o_player_cave(0, 0.11f, 0.7f); // TODO: test value, to hook up to vrpn
    vec o_cave_camera;
    vec o_camera_world;
    matrix4 p_camera_world;
    matrix4 p_cave_camera;
    const float world_scale = 10;

    void update_camera()
    {
        if (!projection_initialized) {
            projection_initialized = true;

            matrix4 p_camera_cave(
                vec4(-world_scale, 0, 0, 0),
                vec4(0, 0, -world_scale, 0),
                vec4(0, world_scale, 0, 0),
                vec4(0, 0, 0, 1)
            );

            p_cave_camera.invert(p_camera_cave);

            p_camera_cave.transform(vec4(o_player_cave, 1), o_cave_camera);
            o_cave_camera.neg();
        }

        o_camera_world = camera1->headpos();
        p_camera_world.identity();
        p_camera_world.rotate_around_z(-camera1->yaw);
    }

}
