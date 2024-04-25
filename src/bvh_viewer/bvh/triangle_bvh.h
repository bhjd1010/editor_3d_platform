#pragma once

#include <iostream>
#include <type_traits>
#include <vector>

#include <bvh/primitive_intersectors.hpp>
#include <bvh/single_ray_traverser.hpp>
#include <bvh/sweep_sah_builder.hpp>

#include "math/Math//Vector3d.h"
#include "bvh_types.h"

namespace E3dMath {
    class Box3d;
}

namespace gmv {
    class TriangleBVH final {
    public:
        TriangleBVH(const std::vector<BvhTriangle> &&triangles);

        void Build(unsigned int maxDepth = 16, unsigned int maxLeafSize = 16);

        void Build1(unsigned int maxDepth = 16, unsigned int maxLeafSize = 16);


        bool
        Intersect(const E3dMath::Vector3d &rayOrigin, const E3dMath::Vector3d &rayDir, E3dMath::Vector3d &intersectPt,
                  std::size_t &hitTriIndex);

        std::vector<std::vector<const BvhTriangle *>> GetLeafTriangles() const;

        std::vector<std::unique_ptr<E3dMath::Box3d>> GetTreeNodeBoxes() const;

        std::vector<std::vector<std::unique_ptr<E3dMath::Box3d>>> GetTreeNodeBoxesByLevel() const;

        std::size_t GetTriangleCount() const;

        std::size_t GetBoxCount() const;

        std::vector<unsigned int> GetTriangleCountInLeaf() const;

    private:
        std::vector<std::vector<std::size_t>> _GetPrimitivesByLevel(std::size_t level) const;

        std::vector<BvhTriangle> _triangles;
        std::unique_ptr<Bvh> _bvh;
    };

} // namespace gmv
