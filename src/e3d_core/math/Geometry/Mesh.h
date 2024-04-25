#pragma once

#include "math/math/Vector3d.h"
#include "IGeometry.h"
#include <memory>
#include <vector>


namespace E3dMath {

/**
 * 环，封闭且无自交的曲线序列
 */
    class Mesh : public IGeometry {
    public:

        const std::vector<Vector3d> &GetPoints() const;

        void SetPoints(const std::vector<Vector3d> &&points);

        const std::vector<unsigned int> &GetPointIndices() const;

        void SetPointIndices(const std::vector<unsigned int> &&pointIndices);

        const std::vector<Vector3d> &GetNormals() const;

        void SetNormals(const std::vector<Vector3d> &&normals);

        const std::vector<Vector2d> &GetUVs() const;

        void SetUVs(const std::vector<Vector2d> &&uvs);


        ///////////////////////////////////////////////////////////////////
        // IAesGeometry接口实现
        MathObjectType GetType() const override;

        void Release() override;


    private:
        std::vector<Vector3d> _points;
        std::vector<unsigned int> _indices;
        std::vector<Vector3d> _vertexNormals;
        std::vector<unsigned int> m_triangleVertexNormalIndices;
        std::vector<Vector2d> _vertexUVs;
        std::vector<unsigned int> _vertexUVIndices;
    };


}

