#pragma once

#include "easy3d/core/types.h"

namespace easy3d {
    class LinesDrawable;

    class PointsDrawable;

    class TrianglesDrawable;
} // namespace easy3d

namespace E3dMath {
    class ILoop;

    class Vector2d;

    class Vector3d;

    class Line2d;

    class Line3d;

    class Plane;

    class Box3d;

    class Mesh;
} // namespace E3dMath

namespace gmv {
    struct ElementStyle {
        ElementStyle() {}

        ElementStyle(easy3d::vec4 inPColor, easy3d::vec4 inLColor, float inLineWidth, float inPointSize)
                : pointColor(inPColor), lineColor(inLColor), lineWidth(inLineWidth), pointSize(inPointSize) {
        }

        void Reset() {
            pointColor = easy3d::vec4(0.0f, 0.0f, 0.0f, 1.0f);
            lineColor = easy3d::vec4(0.0f, 0.0f, 0.0f, 1.0f);
            lineWidth = 5.0f;
            pointSize = 20.0f;
        }

        easy3d::vec4 pointColor = easy3d::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        easy3d::vec4 lineColor = easy3d::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        float lineWidth = 5.0f;
        float pointSize = 8.0f;
    };

    class GeomToDrawable {
    public:
        static easy3d::LinesDrawable *LoopToLinesDrawable(const E3dMath::ILoop *loop, std::string name);

        static easy3d::LinesDrawable *Line3dToLinesDrawable(const E3dMath::Line3d *line, std::string name);

        static easy3d::PointsDrawable *Vector3dToPointsDrawable(const E3dMath::Vector3d *vec3, std::string name);

        static easy3d::LinesDrawable *Box3dToLinesDrawable(const E3dMath::Box3d *box3d, std::string name);

        static easy3d::LinesDrawable *
        Box3dsToLinesDrawable(const std::vector<const E3dMath::Box3d *> &box3ds, std::string name);

        static easy3d::TrianglesDrawable *MeshToTrianglesDrawable(const E3dMath::Mesh *mesh, std::string name);

    public:
        static ElementStyle defaultStyle;
    };

} // namespace gmv
