#include "ui_creater.h"
#include "element/document.h"
#include "imgui.h"
#include "ui_triangle_bvh.h"
#include <easy3d/algo/surface_mesh_subdivision.h>
#include "ui_viewer.h"
#include "easy3d/core/surface_mesh.h"
#include "easy3d/renderer/renderer.h"
#include "debug_warn.h"

using namespace easy3d;
namespace gmv {
    void UICreater::CreateMenu() {
        // viewer???
        if (ImGui::BeginMenu("View")) {
            if (ImGui::MenuItem("Clear", nullptr, false)) {
                Document::Get()->DeleteAll();
            }
            if (ImGui::MenuItem("Fit_Screen", nullptr, false)) {
                Document::Get()->GetViewer()->fit_screen();
            }
            ImGui::Separator();
            ImGui::EndMenu();
        }

        if (ImGui::CollapsingHeader("Model")) {
            if(ImGui::Button("Subdivision"))
            {
                const auto models = Document::Get()->GetViewer()->models();
                for (auto model: models) {
                    auto surfaceMesh = dynamic_cast<easy3d::SurfaceMesh *>(model);
                    if (!surfaceMesh)
                        continue;
                    std::cout << "vertex count: " << surfaceMesh->vertices_size() << std::endl;
                    std::string logBeforeSubdivision =
                            "before subdivision vertex count: " + std::to_string(surfaceMesh->vertices_size()) +
                            "; face count: " + std::to_string(surfaceMesh->faces_size());
                    DBG_LOG(logBeforeSubdivision);
                    SurfaceMeshSubdivision::sqrt3(surfaceMesh);
                    std::string logAfterSubdivision =
                            "after subdivision vertex count: " + std::to_string(surfaceMesh->vertices_size()) +
                            "; face count: " + std::to_string(surfaceMesh->faces_size());
                    DBG_LOG(logAfterSubdivision);
                    surfaceMesh->set_renderer(new Renderer(model));
                }
            }
        }
        // mesh Bvh
        UITriangleBVhMenu::CreateMenu();

        // log
        if (ImGui::CollapsingHeader("Log")) {
            ImGui::TextWrapped("%s", DebugWarn::LogStr.c_str());
        }
    }


} // namespace gmv