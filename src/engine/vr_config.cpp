#include "cube.h"

#include "tinyxml2.h"

using namespace tinyxml2;

namespace vr {

    vector<virtual_screen> virtual_screens;

    namespace {
        void load_screen_config()
        {
            size_t length;
            char *data;

            data = loadfile("config/vr/virtual_screens.xml", &length);

            if (!data) {
                fatal("Couldn't open virtual screens configuration file");
            }

            XMLDocument doc;

            if (doc.Parse(data, length) != XML_NO_ERROR) {
                fatal("Error when parsing virtual screens configuration file");
            }

            XMLElement *root = doc.RootElement();
            XMLElement *elt = root->FirstChildElement("virtualscreen");

            while (elt) {
                virtual_screen screen;
                XMLElement *r_elt = elt->FirstChildElement("right");
                XMLElement *u_elt = elt->FirstChildElement("up");
                XMLElement *v_elt = elt->FirstChildElement("viewport");

                if (!r_elt || !u_elt || !v_elt) {
                    fatal("Invalid virtual screens configuration file");
                }

                screen.width = elt->FloatAttribute("width");
                screen.height = elt->FloatAttribute("height");
                screen.is_main = elt->BoolAttribute("ismain");

                screen.right.x = r_elt->FloatAttribute("x");
                screen.right.y = r_elt->FloatAttribute("y");
                screen.right.z = r_elt->FloatAttribute("z");

                screen.up.x = u_elt->FloatAttribute("x");
                screen.up.y = u_elt->FloatAttribute("y");
                screen.up.z = u_elt->FloatAttribute("z");

                screen.viewport.width = v_elt->IntAttribute("width");
                screen.viewport.height = v_elt->IntAttribute("height");
                screen.viewport.x = v_elt->IntAttribute("x");
                screen.viewport.y = v_elt->IntAttribute("y");

                virtual_screens.put(screen);

                elt = elt->NextSiblingElement("virtualscreen");
            }

            delete[] data;
        }
    }

    void init()
    {
        load_screen_config();
    }

}
