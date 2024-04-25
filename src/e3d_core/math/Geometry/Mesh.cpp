
#include "Mesh.h"
#include <memory>
#include <vector>

namespace E3dMath {

    const std::vector<Vector3d> &Mesh::GetPoints() const {
        return _points;
    }

    void Mesh::SetPoints(const std::vector<Vector3d> &&points) {
        _points = points;
    }

    const std::vector<unsigned int> &Mesh::GetPointIndices() const {
        return _indices;
    }

    void Mesh::SetPointIndices(const std::vector<unsigned int> &&pointIndices) {
        _indices = pointIndices;
    }

    const std::vector<Vector3d> &Mesh::GetNormals() const {
        return _vertexNormals;
    }

    void Mesh::SetNormals(const std::vector<Vector3d> &&normals) {
        _vertexNormals = normals;
    }

    const std::vector<Vector2d> &Mesh::GetUVs() const {
        return _vertexUVs;
    }

    void Mesh::SetUVs(const std::vector<Vector2d> &&uvs) {
        _vertexUVs = uvs;
    }

///////////////////////////////////////////////////////////////////
// IAesGeometry接口实现
    MathObjectType Mesh::GetType() const {
        return MathObjectType::Mesh;
    }

    void Mesh::Release() {
        delete this;
    }

}
