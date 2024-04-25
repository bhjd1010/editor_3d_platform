#include "mesh_element.h"
#include "viewer/geom_to_drawable.h"
#include "easy3d/renderer/drawable_lines.h"
#include "data_converter.h"
#include "easy3d/renderer/drawable_triangles.h"

namespace gmv {

    bool MeshElement::Init(std::unique_ptr<E3dMath::Mesh> mesh, std::string name /*= ""*/) {
        _mesh = std::move(mesh);
        return true;
    }

    const E3dMath::Mesh *MeshElement::GetGeometry() const {
        return _mesh.get();
    }

    std::string MeshElement::GetName() const {
        return "Geo_Mesh";
    }

    std::vector<easy3d::Drawable *> MeshElement::GetRenderNode() const {
        std::vector<easy3d::Drawable *> results;
        std::vector<easy3d::vec3> meshPoints;
        std::vector<unsigned int> meshIndices;
        DataConverter::MeshToPointsIndices(_mesh.get(), meshPoints, meshIndices);
        auto surface = new easy3d::TrianglesDrawable(this->GetElementId().ToString());
        surface->update_vertex_buffer(meshPoints);
        surface->update_element_buffer(meshIndices);
        results.push_back(surface);
        return results;
    }

    ElementType MeshElement::GetType() const {
        return ElementType::MESH_ELE;
    }
}