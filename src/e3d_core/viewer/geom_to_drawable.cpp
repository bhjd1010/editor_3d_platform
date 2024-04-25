#include "geom_to_drawable.h"
#include "geometry/Loop.h"
#include "easy3d/renderer/drawable_lines.h"
#include "easy3d/renderer/drawable_points.h"
#include "random_color.h"
#include "data_converter.h"
#include "easy3d/renderer/drawable_triangles.h"
#include "Line3d.h"
#include "Box3d.h"

using namespace easy3d;
namespace gmv {
    gmv::ElementStyle GeomToDrawable::defaultStyle = ElementStyle();

    easy3d::LinesDrawable *GeomToDrawable::LoopToLinesDrawable(const E3dMath::ILoop *loop, std::string name) {
        std::vector<vec3> loopPts;
        std::vector<E3dMath::Vector2d> path = loop->ToPath();
        for (std::size_t i = 0; i < path.size() - 1; ++i) {
            loopPts.push_back(DataConverter::AesVector2dToVec3(path[i]));
        }

        auto loop_drawable = new LinesDrawable();
        std::vector<unsigned int> loop_indices;
        for (std::size_t i = 0; i < loopPts.size(); ++i) {
            loop_indices.push_back((unsigned int) (i));
            loop_indices.push_back((unsigned int) (((i + 1) % loopPts.size())));
        }
        loop_drawable->update_vertex_buffer(loopPts);
        loop_drawable->update_element_buffer(loop_indices);

        if (defaultStyle.lineColor == vec4(0, 0, 0, 1)) {
            vec4 randomColor;
            RandomColor::Genete(randomColor);
            loop_drawable->set_uniform_coloring(randomColor);    // r, g, b, a
        } else {
            loop_drawable->set_uniform_coloring(vec4(defaultStyle.lineColor));    // r, g, b, a
        }

        loop_drawable->set_line_width(defaultStyle.lineWidth);
        loop_drawable->set_name(name);
        return loop_drawable;
    }

    easy3d::LinesDrawable *GeomToDrawable::Line3dToLinesDrawable(const E3dMath::Line3d *line, std::string name) {
        auto startPt = line->GetStartPoint();
        auto endPt = line->GetEndPoint();
        std::vector<vec3> linePts{DataConverter::AesVector3dToVec3(startPt), DataConverter::AesVector3dToVec3(endPt)};

        auto loop_drawable = new LinesDrawable();

        std::vector<unsigned int> loop_indices;
        for (std::size_t i = 0; i < linePts.size() - 1; ++i) {
            loop_indices.push_back((unsigned int) (i));
            loop_indices.push_back((unsigned int) ((i + 1) % linePts.size()));
        }
        loop_drawable->update_vertex_buffer(linePts);
        loop_drawable->update_element_buffer(loop_indices);
        loop_drawable->set_uniform_coloring(vec4(defaultStyle.lineColor));    // r, g, b, a
        loop_drawable->set_line_width(defaultStyle.lineWidth);
        loop_drawable->set_name(name);

        return loop_drawable;
    }

    easy3d::PointsDrawable *GeomToDrawable::Vector3dToPointsDrawable(const E3dMath::Vector3d *point, std::string name) {
        auto vertices = new PointsDrawable();
        std::vector<easy3d::vec3> pts;
        pts.push_back(DataConverter::AesVector3dToVec3(*point));
        vertices->update_vertex_buffer(pts);
        vertices->set_uniform_coloring(vec4(defaultStyle.pointColor[0], defaultStyle.pointColor[1],
                                            defaultStyle.pointColor[2], defaultStyle.pointColor[3]));    // r, g, b, a
        vertices->set_impostor_type(PointsDrawable::SPHERE);
        vertices->set_point_size(defaultStyle.pointSize);
        vertices->set_name(name);
        return vertices;
    }

    easy3d::LinesDrawable *GeomToDrawable::Box3dToLinesDrawable(const E3dMath::Box3d *box, std::string name) {
        auto bbox_drawable = new LinesDrawable("bbox");
        E3dMath::Vector3d corners[8];
        box->GetCorners(corners);
        // The vertex indices of the twelve edges of the bounding box (each consecutive two numbers represent an edge).
        const std::vector<unsigned int> bbox_indices = {0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6,
                                                        6, 7, 7, 4, 0, 4, 1, 5, 2, 6, 3, 7};
        std::vector<vec3> bbox_points;
        for (int i = 0; i < 8; ++i) {
            bbox_points.push_back(DataConverter::AesVector3dToVec3(corners[i]));
        }
        // Upload the vertex positions of the bounding box to the GPU.
        bbox_drawable->update_vertex_buffer(bbox_points);
        // Upload the vertex indices of the bounding box to the GPU.
        bbox_drawable->update_element_buffer(bbox_indices);
        //// Set a color for the edges of the bounding box (here we want a blue color).
        //bbox_drawable->set_uniform_coloring(vec4(0.0f, 0.0f, 1.0f, 1.0f)); // r, g, b, a
        // Set the width of the edges (here 5 pixels).
        bbox_drawable->set_line_width(2.0f);
        bbox_drawable->set_name(name);
        return bbox_drawable;
    }

    easy3d::LinesDrawable *GeomToDrawable::Box3dsToLinesDrawable(const std::vector<const E3dMath::Box3d *> &box3ds,
                                                                 std::string name) {
        auto bbox_drawable = new LinesDrawable("bbox");

        std::vector<unsigned int> bbox_indices;
        bbox_indices.reserve(box3ds.size() * 24);
        std::vector<vec3> bbox_points;
        bbox_points.reserve(box3ds.size() * 8);

        for (unsigned int i = 0; i < box3ds.size(); ++i) {
            E3dMath::Vector3d corners[8];
            box3ds[i]->GetCorners(corners);
            for (int j = 0; j < 8; ++j) {
                bbox_points.push_back(DataConverter::AesVector3dToVec3(corners[j]));
            }
            const std::vector<unsigned int> _bbox_indices = {
                    0 + i * 24, 1 + i * 24, 1 + i * 24, 2 + i * 24, 2 + i * 24, 3 + i * 24, 3 + i * 24, 0 + i * 24,
                    4 + i * 24, 5 + i * 24, 5 + i * 24, 6 + i * 24, 6 + i * 24, 7 + i * 24, 7 + i * 24, 4 + i * 24,
                    0 + i * 24, 4 + i * 24, 1 + i * 24, 5 + i * 24, 2 + i * 24, 6 + i * 24, 3 + i * 24, 7 + i * 24};
            bbox_indices.insert(bbox_indices.end(), _bbox_indices.begin(), _bbox_indices.end());
        }


        // Upload the vertex positions of the bounding box to the GPU.
        bbox_drawable->update_vertex_buffer(bbox_points);
        // Upload the vertex indices of the bounding box to the GPU.
        bbox_drawable->update_element_buffer(bbox_indices);
        //// Set a color for the edges of the bounding box (here we want a blue color).
        // bbox_drawable->set_uniform_coloring(vec4(0.0f, 0.0f, 1.0f, 1.0f)); // r, g, b, a
        // Set the width of the edges (here 5 pixels).
        bbox_drawable->set_line_width(2.0f);
        bbox_drawable->set_name(name);
        return bbox_drawable;
    }

    easy3d::TrianglesDrawable *GeomToDrawable::MeshToTrianglesDrawable(const E3dMath::Mesh *mesh, std::string name) {
        std::vector<easy3d::vec3> meshPoints;
        std::vector<unsigned int> meshIndices;
        DataConverter::MeshToPointsIndices(mesh, meshPoints, meshIndices);
        auto surface = new easy3d::TrianglesDrawable(name);
        surface->update_vertex_buffer(meshPoints);
        surface->update_element_buffer(meshIndices);
        return surface;
    }

}
