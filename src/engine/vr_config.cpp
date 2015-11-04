#include "cube.h"

#include "tinyxml2.h"

using namespace tinyxml2;

namespace vr {

    vector<virtual_screen> virtual_screens;

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

            elt = root->FirstChildElement("screensconfig");

            if (!elt) {
                fatal("No screens config specified");
            }

            screens_config_name = newstring(elt->FirstChild()->Value());

            delete[] data;
        }
    }

    void init()
    {
        load_config();
        load_screen_config();
    }

}
