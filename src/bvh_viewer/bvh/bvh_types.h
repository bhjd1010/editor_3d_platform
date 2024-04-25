#pragma once

#include <bvh/bvh.hpp>
#include <bvh/ray.hpp>
#include <bvh/triangle.hpp>
#include <bvh/vector.hpp>
#include "bvh/bounding_box.hpp"

namespace gmv {
    using BvhVec3 = bvh::Vector3<double>;

    using BvhTriangle = bvh::Triangle<double>;

    using BvhRay = bvh::Ray<double>;

    using Bvh = bvh::Bvh<double>;

    using BvhNode = bvh::Bvh<double>::Node;

    using BvhBoundingBox = bvh::BoundingBox<double>;

} // namespace gmv
