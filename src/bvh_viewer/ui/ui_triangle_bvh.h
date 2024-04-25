#pragma once

#include "easy3d/core/types.h"
#include "bvh/triangle_bvh.h"

namespace gmv {
    class UITriangleBVhMenu {
    public:
        static void CreateMenu();

        static TriangleBVH *GetBVH() { return _triangleBVH.get(); }

    private:
        static void BvhTriangleToPointsIndices(const std::vector<const BvhTriangle *>& bvhTriangles,
                                               std::vector<easy3d::vec3> &points, std::vector<unsigned int> &indices);

        static void Build();

        static void ShowHideBox();

        inline static std::unique_ptr<TriangleBVH> _triangleBVH;
    };
} // namespace gmv
