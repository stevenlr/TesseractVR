#include "cube.h"

#include "tinyxml2.h"

using namespace tinyxml2;

namespace vr {

    vector<virtual_screen> virtual_screens;
    stereoscopy_adapter *stereo_adapter = nullptr;
    int screenw = 0;
    int screenh = 0;
    int gbufferw = 0;
    int gbufferh = 0;
    float eyesdistance = 0;
    int main_screen = -1;

    namespace {

        char *screens_config_name;

        void load_screen_config()
        {
            size_t length;
            string config_file;
            char *data;

            formatstring(config_file, "config/vr/%s.xml", screens_config_name);
            data = loadfile(config_file, &length);

            if (!data) {
                fatal("Couldn't open virtual screens configuration file");
            }

            XMLDocument doc;

            if (doc.Parse(data, length) != XML_NO_ERROR) {
                fatal("Error when parsing virtual screens configuration file");
            }

            XMLElement *root = doc.RootElement();
            XMLElement *elt = root->FirstChildElement("virtualscreen");
            int i = 0;

            while (elt) {
                virtual_screen screen;
                XMLElement *p_elt = elt->FirstChildElement("pos");
                XMLElement *r_elt = elt->FirstChildElement("right");
                XMLElement *u_elt = elt->FirstChildElement("up");
                XMLElement *v_elt = elt->FirstChildElement("viewport");
                vec right, up, front;

                if (!p_elt || !r_elt || !u_elt || !v_elt) {
                    fatal("Invalid virtual screens configuration file");
                }

                screen.width = elt->FloatAttribute("width");
                screen.height = elt->FloatAttribute("height");
                screen.is_main = elt->BoolAttribute("ismain");

                screen.o_screen_cave.x = p_elt->FloatAttribute("x");
                screen.o_screen_cave.y = p_elt->FloatAttribute("y");
                screen.o_screen_cave.z = p_elt->FloatAttribute("z");

                right.x = r_elt->FloatAttribute("x");
                right.y = r_elt->FloatAttribute("y");
                right.z = r_elt->FloatAttribute("z");

                up.x = u_elt->FloatAttribute("x");
                up.y = u_elt->FloatAttribute("y");
                up.z = u_elt->FloatAttribute("z");

                right.normalize();
                up.normalize();
                front.cross(right, up);

                screen.p_screen_cave.a = vec4(right, 0);
                screen.p_screen_cave.b = vec4(up, 0);
                screen.p_screen_cave.c = vec4(front, 0);
                screen.p_screen_cave.d = vec4(0, 0, 0, 1);

                screen.viewport.width = v_elt->IntAttribute("width");
                screen.viewport.height = v_elt->IntAttribute("height");
                screen.viewport.x = v_elt->IntAttribute("x");
                screen.viewport.y = v_elt->IntAttribute("y");

                virtual_screens.put(screen);

                screenw = max(screenw, screen.viewport.x + screen.viewport.width);
                screenh = max(screenh, screen.viewport.y + screen.viewport.height);
                gbufferw = max(gbufferw, screen.viewport.width);
                gbufferh = max(gbufferh, screen.viewport.height);

                if (screen.is_main) {
                    main_screen = i;
                }

                elt = elt->NextSiblingElement("virtualscreen");
                i++;
            }

            if (main_screen < 0) {
                fatal("No main screen found");
            }

            delete[] data;
        }

        void load_config()
        {
            size_t length;
            char *data;

            data = loadfile("config/vr/config.xml", &length);

            if (!data) {
                fatal("Couldn't open vr configuration file");
            }

            XMLDocument doc;

            if (doc.Parse(data, length) != XML_NO_ERROR) {
                fatal("Error when parsing vr configuration file");
            }

            XMLElement *root = doc.RootElement();
            XMLElement *elt;

            if (!(elt = root->FirstChildElement("screensconfig"))) {
                fatal("No screens config specified");
            }

            screens_config_name = newstring(elt->FirstChild()->Value());
            
            if (!(elt = root->FirstChildElement("stereoscopytype"))) {
                fatal("No stereoscopy type specified");
            }

            if (strncasecmp("anaglyph", elt->FirstChild()->Value(), 5) == 0) {
                stereo_adapter = new anaglyph_stereo_adapter;
            } else if (strncasecmp("quadbuffer", elt->FirstChild()->Value(), 5) == 0) {
                stereo_adapter = new quadbuffer_stereo_adapter;
            } else {
                fatal("Invalid stereo adapter");
            }

            if (!(elt = root->FirstChildElement("eyesdistance"))) {
                fatal("No interpupillary distance specified");
            }

            elt->QueryFloatText(&eyesdistance);

            delete[] data;
        }
    }

    void init()
    {
        load_config();
        load_screen_config();
    }

}
