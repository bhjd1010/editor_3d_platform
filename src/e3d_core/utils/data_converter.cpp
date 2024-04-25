#include "data_converter.h"
#include "geometry/Mesh.h"

namespace gmv {
    easy3d::vec3 DataConverter::AesVector2dToVec3(const E3dMath::Vector2d &vec) {
        return easy3d::vec3(static_cast<float>(vec.X()), static_cast<float>(vec.Y()), 0.0f);
    }

    easy3d::vec3 DataConverter::AesVector3dToVec3(const E3dMath::Vector3d &vec) {
        return easy3d::vec3(static_cast<float>(vec.X()), static_cast<float>(vec.Y()), static_cast<float>(vec.Z()));
    }

    E3dMath::Vector2d DataConverter::Vec3ToAesVector2d(const easy3d::vec3 &vec) {
        return E3dMath::Vector2d(vec[0], vec[1]);
    }

    void DataConverter::MeshToPointsIndices(const E3dMath::Mesh *mesh, std::vector<easy3d::vec3> &points,
                                            std::vector<unsigned int> &indices) {
        const std::vector<E3dMath::Vector3d> &meshPoints = mesh->GetPoints();
        const std::vector<unsigned int> &meshIndices = mesh->GetPointIndices();
        points.clear();
        indices.clear();
        points.reserve(meshPoints.size());
        indices.reserve(meshIndices.size());
        for (auto &p: meshPoints) {
            points.push_back(DataConverter::AesVector3dToVec3(p));
        }
        indices.insert(indices.begin(), meshIndices.begin(), meshIndices.end());
    }

    E3dMath::Vector3d DataConverter::Vec3ToAesVector3d(const easy3d::vec3 &vec) {
        return E3dMath::Vector3d(vec[0], vec[1], vec[2]);
    }

} // namespace gmv
