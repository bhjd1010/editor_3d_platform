#pragma once

#include "ui_triangle_bvh.h"
#include "action_frame/action_manager.h"
#include "action/intersect_bvh_action.h"
#include "data_converter.h"
#include "document.h"
#include "easy3d/core/types.h"
#include "easy3d/core/model.h"
#include "easy3d/renderer/renderer.h"
#include "easy3d/renderer/drawable_lines.h"
#include "easy3d/renderer/drawable_triangles.h"
#include "geom_to_drawable.h"
#include "imgui.h"
#include "bvh/mesh_bvh.h"
#include "utils/random_color.h"
#include "bvh/triangle_bvh.h"
#include "ui_utils.h"
#include "viewer/ui_viewer.h"
#include <memory>
#include "easy3d/core/surface_mesh.h"
#include "debug_warn.h"

using namespace easy3d;
using namespace gmv;

void UITriangleBVhMenu::CreateMenu() {
    if (ImGui::CollapsingHeader("Triangle_BVH")) {
        Build();
        ImGui::SameLine();
        if (ImGui::Button("Intersect")) {
            auto intersectBVhAction = std::make_unique<IntersectBVhAction>();
            ActionManager::Get()->RunAction(std::move(intersectBVhAction));
        }
        ShowHideBox();
    }
}

void UITriangleBVhMenu::BvhTriangleToPointsIndices(const std::vector<const BvhTriangle *>& bvhTriangles,
                                       std::vector<easy3d::vec3> &points, std::vector<unsigned int> &indices) {
    for (unsigned int i = 0; i < bvhTriangles.size(); ++i) {
        auto &triangle = bvhTriangles[i];
        points.emplace_back(static_cast<float>(triangle->p0[0]), static_cast<float>(triangle->p0[1]),
                                      static_cast<float>(triangle->p0[2]));
        auto p1 = triangle->p0 - triangle->e1;
        auto p2 = triangle->p0 + triangle->e2;
        points.emplace_back(static_cast<float>(p1[0]), static_cast<float>(p1[1]), static_cast<float>(p1[2]));
        points.emplace_back(static_cast<float>(p2[0]), static_cast<float>(p2[1]), static_cast<float>(p2[2]));

        indices.push_back(i * 3);
        indices.push_back(i * 3 + 1);
        indices.push_back(i * 3 + 2);
    }
}

void UITriangleBVhMenu::Build() {
    if (ImGui::Button("Build")) {
        const auto &models = Document::Get()->GetViewer()->models();
        std::vector<BvhTriangle> _triangles;
        for (auto model: models) {
            auto surfaceMesh = dynamic_cast<easy3d::SurfaceMesh *>(model);
            if (!surfaceMesh)
                continue;
            SurfaceMesh::VertexProperty<vec3> vertices = surfaceMesh->get_vertex_property<vec3>("v:point");

            // collect triangles
            for (SurfaceMesh::FaceIterator fit = surfaceMesh->faces_begin();
                 fit != surfaceMesh->faces_end(); ++fit) {
                SurfaceMesh::VertexAroundFaceCirculator vfit = surfaceMesh->vertices(*fit);
                easy3d::vec3 position_0 = vertices[*vfit];
                ++vfit;
                easy3d::vec3 position_1 = vertices[*vfit];
                ++vfit;
                easy3d::vec3 position_2 = vertices[*vfit];
                _triangles.emplace_back(BvhVec3(position_0[0], position_0[1], position_0[2]),
                                        BvhVec3(position_1[0], position_1[1], position_1[2]),
                                        BvhVec3(position_2[0], position_2[1], position_2[2]));
            }
            model->renderer()->set_visible(false);
        }
        if (_triangles.empty())
            return;
        std::unique_ptr<TriangleBVH> bvh = std::make_unique<TriangleBVH>(std::move(_triangles));
        auto start = std::chrono::steady_clock::now();
        bvh->Build(7);
        auto end = std::chrono::steady_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::string timeLog =
                "Build BVH Time = " + std::to_string(time) + "us;  " + std::to_string(time / 1000) + "ms";
        DBG_LOG(timeLog)

        std::vector<std::vector<const BvhTriangle *>> trianglesOfLeaf = bvh->GetLeafTriangles();
        for (auto drawable: Document::Get()->GetViewer()->drawables()) {
            Document::Get()->GetViewer()->delete_drawable(drawable);
        }
        for (auto &triangles: trianglesOfLeaf) {
            std::vector<easy3d::vec3> meshPoints;
            std::vector<unsigned int> meshIndices;
            BvhTriangleToPointsIndices(triangles, meshPoints, meshIndices);
            auto surface = new easy3d::TrianglesDrawable("faces");
            surface->update_vertex_buffer(meshPoints);
            surface->update_element_buffer(meshIndices);
            easy3d::vec4 color;
            RandomColor::Genete(color);
            surface->set_uniform_coloring(color);
            Document::Get()->GetViewer()->add_drawable(surface);
        }
        _triangleBVH = std::move(bvh);
    }
}

void UITriangleBVhMenu::ShowHideBox() {
    if (ImGui::Button("Shou/Hide_Box")) {
        if (!_triangleBVH) {
            return;
        }
        static bool tag = false;
        if (!tag) {
            tag = true;
            auto boxes = _triangleBVH->GetTreeNodeBoxesByLevel();
            for (auto &boxesLevel: boxes) {
                std::vector<const E3dMath::Box3d *> box3ds;
                box3ds.reserve(boxesLevel.size());
                for (auto &box: boxesLevel) {
                    box3ds.push_back(box.get());
                }
                auto drawable = GeomToDrawable::Box3dsToLinesDrawable(box3ds, "mesh_box");
                easy3d::vec4 color;
                RandomColor::Genete(color);
                drawable->set_uniform_coloring(color);
                Document::Get()->GetViewer()->add_drawable(drawable);
            }
        } else {
            tag = false;
            while (true) {
                if (!Document::Get()->GetViewer()->DeleteDrawableByName("mesh_box")) {
                    break;
                }
            }
        }
    }
}
