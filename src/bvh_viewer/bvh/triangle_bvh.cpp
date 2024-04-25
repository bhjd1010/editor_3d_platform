#include "triangle_bvh.h"
#include "math/math/Box3d.h"
#include "bvh/binned_sah_builder.hpp"
#include "debug_warn.h"
#include <chrono>

namespace gmv {
    TriangleBVH::TriangleBVH(const std::vector<BvhTriangle> &&triangles) : _triangles(triangles) {}

    void TriangleBVH::Build(unsigned int maxDepth /*= 16*/, unsigned int maxLeafSize /*= 16*/) {
        if (_bvh) {
            return;
        }
        _bvh = std::make_unique<Bvh>();
        // Compute the global bounding box and the centers of the primitives.
        // This is the input of the BVH construction algorithm.
        // Note: Using the bounding box centers instead of the primitive centers is possible,
        // but usually leads to lower-quality BVHs.
        auto [bboxes, centers] = bvh::compute_bounding_boxes_and_centers(_triangles.data(), _triangles.size());
        auto global_bbox = bvh::compute_bounding_boxes_union(bboxes.get(), _triangles.size());

        // Create an acceleration data structure on the primitives
        bvh::SweepSahBuilder<Bvh> builder(*_bvh);
        builder.max_depth = maxDepth;
        builder.max_leaf_size = maxLeafSize;
        builder.build(global_bbox, bboxes.get(), centers.get(), _triangles.size());
    }

    void TriangleBVH::Build1(unsigned int maxDepth /*= 16*/, unsigned int maxLeafSize /*= 16*/) {
        _bvh = std::make_unique<Bvh>();
        // Compute the global bounding box and the centers of the primitives.
        // This is the input of the BVH construction algorithm.
        // Note: Using the bounding box centers instead of the primitive centers is possible,
        // but usually leads to lower-quality BVHs.
        auto [bboxes, centers] = bvh::compute_bounding_boxes_and_centers(_triangles.data(), _triangles.size());
        auto global_bbox = bvh::compute_bounding_boxes_union(bboxes.get(), _triangles.size());

        // Create an acceleration data structure on the primitives
        bvh::BinnedSahBuilder<Bvh, 4> builder(*_bvh);
        builder.build(global_bbox, bboxes.get(), centers.get(), _triangles.size());
    }

    bool TriangleBVH::Intersect(const E3dMath::Vector3d &rayOrigin, const E3dMath::Vector3d &rayDir,
                                E3dMath::Vector3d &intersectPt, std::size_t &hitTriIndex) {
        if (!_bvh || !_triangles.size()) {
            return false;
        }
        auto start = std::chrono::steady_clock::now();


        // Intersect a ray with the data structure
        BvhRay ray(BvhVec3(rayOrigin.X(), rayOrigin.Y(), rayOrigin.Z()), // origin
                   BvhVec3(rayDir.X(), rayDir.Y(), rayDir.Z())             // direction
        );
        bvh::AnyPrimitiveIntersector<Bvh, BvhTriangle> primitive_intersector(*_bvh, _triangles.data(), 100);
        bvh::SingleRayTraverser<Bvh> traverser(*_bvh);

        if (auto hit = traverser.traverse(ray, primitive_intersector)) {
            //auto triangle_index = hit->primitive_index;
            //auto intersection = hit->intersection;
            //intersectPt = rayOrigin.Clone() + intersection.t * rayDir;
            intersectPt = rayOrigin.Clone() + hit->t * rayDir;
            auto end = std::chrono::steady_clock::now();
            auto tt = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            std::string timeStr = "Intersect Time = " + std::to_string(tt) + "us;  " + std::to_string(tt / 1000) + "ms";
            DBG_LOG(timeStr);
            return true;
        }
        return false;
    }

    std::vector<std::vector<const BvhTriangle *>> TriangleBVH::GetLeafTriangles() const {
        std::vector<std::vector<const BvhTriangle *>> result;
        if (!_bvh) {
            return result;
        }
        for (std::size_t i = 0; i < _bvh->node_count; ++i) {
            auto bounds = _bvh->nodes[i].bounds;
            if (_bvh->nodes[i].primitive_count == 0) {
                continue;
            }
            std::vector<const BvhTriangle *> triangles;
            for (std::size_t j = 0; j < _bvh->nodes[i].primitive_count; ++j) {
                triangles.push_back(&(_triangles[_bvh->nodes[i].first_child_or_primitive + j]));
            }
            result.push_back(triangles);
        }
        return result;
    }

    std::vector<std::unique_ptr<E3dMath::Box3d>> TriangleBVH::GetTreeNodeBoxes() const {
        std::vector<std::unique_ptr<E3dMath::Box3d>> result;
        if (!_bvh) {
            return result;
        }
        for (std::size_t i = 0; i < _bvh->node_count; ++i) {
            auto bounds = _bvh->nodes[i].bounds;
            if (_bvh->nodes[i].primitive_count != 0) {
                continue;
            }
            result.push_back(std::make_unique<E3dMath::Box3d>(E3dMath::Vector3d(bounds[0], bounds[2], bounds[4]),
                                                              E3dMath::Vector3d(bounds[1], bounds[3], bounds[5])));
        }
        return result;
    }

    std::vector<std::vector<std::unique_ptr<E3dMath::Box3d>>> TriangleBVH::GetTreeNodeBoxesByLevel() const {
        if (!_bvh || !_bvh->node_count) {
            return std::vector<std::vector<std::unique_ptr<E3dMath::Box3d>>>();
        }

        std::vector<std::vector<std::size_t>> result;
        std::queue<size_t> queue;
        queue.push(0);
        while (!queue.empty()) {
            std::size_t currentLevelSize = queue.size();
            result.push_back(std::vector<std::size_t>());
            for (std::size_t i = 1; i <= currentLevelSize; ++i) {
                std::size_t node = queue.front();
                queue.pop();
                result.back().push_back(node);
                if ((_bvh->nodes.get())[node].primitive_count == 0) {
                    queue.push((_bvh->nodes.get())[node].first_child_or_primitive);
                    queue.push(_bvh->sibling((_bvh->nodes.get())[node].first_child_or_primitive));
                }
            }
        }

        std::vector<std::vector<std::unique_ptr<E3dMath::Box3d>>> BoxResult;
        for (auto &boxes: result) {
            std::vector<std::unique_ptr<E3dMath::Box3d>> boxLevel;
            for (auto &idx: boxes) {
                auto bounds = _bvh->nodes[idx].bounds;
                boxLevel.push_back(std::make_unique<E3dMath::Box3d>(E3dMath::Vector3d(bounds[0], bounds[2], bounds[4]),
                                                                    E3dMath::Vector3d(bounds[1], bounds[3],
                                                                                      bounds[5])));
            }
            BoxResult.push_back(std::move(boxLevel));
        }
        return BoxResult;
    }

    std::size_t TriangleBVH::GetTriangleCount() const {
        return _triangles.size();
    }

    std::size_t TriangleBVH::GetBoxCount() const {
        std::size_t count = 0;
        if (!_bvh) {
            return count;
        }
        return _bvh->node_count;
    }

    std::vector<unsigned int> TriangleBVH::GetTriangleCountInLeaf() const {
        std::vector<unsigned int> counts;
        auto nodes = _bvh->nodes.get();
        for (unsigned int i = 0; i < _bvh->node_count; ++i) {
            counts.push_back(nodes[i].primitive_count);
        }
        return counts;
    }

    std::vector<std::vector<std::size_t>> TriangleBVH::_GetPrimitivesByLevel(std::size_t level) const {
        return std::vector<std::vector<std::size_t>>();
    }
} // namespace gmv
