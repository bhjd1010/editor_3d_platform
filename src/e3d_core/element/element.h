#pragma once

#include "element_id.h"
#include <vector>

namespace easy3d {
    class Drawable;
}

namespace gmv {
    enum class ElementType {
        INVALID = -1,
        TEMP_ELE = 0,
        POINT_ELE = 1,
        LINE_ELE = 2,
        LOOP_ELE = 3,
        POLYGON_ELE = 4,
        PLANE_ELE = 5,
        MESH_ELE = 6
    };

    class Element {
    public:
        virtual ~Element() {}

        ElementId GetElementId() const;

        bool DrawElement() const;

        virtual std::string GetName() const;

        virtual std::vector<easy3d::Drawable *> GetRenderNode() const;

    public:
        virtual ElementType GetType() const = 0;


    protected:
        Element(const ElementId &id);

        ElementId _id;

        friend class Document;

    };
}
