#ifndef BOX_
#define BOX_

#include "../PrimitiveProperties.h"
#include "../../json/json.h"
#include "../../geometry/geometry.h"
#include <string>

class EasyPrimitive::Box{
    public:
        nlohmann::json mouse_event;
        PrimitiveProperties *properties;
        
        double_point_t bottom_left;
        float width;
        float height;
        float corner_radius;

        Box(double_point_t bl, float w, float h, float cr)
        {
            this->properties = new PrimitiveProperties();
            this->bottom_left = bl;
            this->width = w;
            this->height = h;
            this->corner_radius = cr;
            this->mouse_event = NULL;
        }
        std::string get_type_name();
        void process_mouse(float mpos_x, float mpos_y);
        void render_rectangle_with_radius(float x, float y, float width, float height, float radius);
        void render();
        void destroy();
        nlohmann::json serialize();
};

#endif //BOX_