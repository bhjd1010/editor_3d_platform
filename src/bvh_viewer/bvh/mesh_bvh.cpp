#include "mesh_bvh.h"
#include "math/geometry/Mesh.h"
#include "math/math/Box3d.h"
#include "bvh/binned_sah_builder.hpp"
#include <chrono>
#include <time.h>

using std::size_t;
using std::vector;

namespace gmv {
    MeshBVH::MeshBVH(const vector<const E3dMath::Mesh *> &&meshes) {
        _meshes.reserve(meshes.size());
        for (auto &mesh: meshes) {
            _meshes.push_back(BvhMesh(mesh));
        }
    }

    void MeshBVH::Build(unsigned int maxDepth /*= 16*/, unsigned int maxLeafSize /*= 16*/) {
        if (_bvh) {
            return;
        }
        auto start = std::chrono::steady_clock::now();

        _bvh = std::make_unique<Bvh>();
        // Compute the global bounding box and the centers of the primitives.
        // This is the input of the BVH construction algorithm.
        // Note: Using the bounding box centers instead of the primitive centers is possible,
        // but usually leads to lower-quality BVHs.
        auto [bboxes, centers] = bvh::compute_bounding_boxes_and_centers<BvhMesh, double>(_meshes.data(),
                                                                                          _meshes.size());
        auto global_bbox = bvh::compute_bounding_boxes_union(bboxes.get(), _meshes.size());

        // Create an acceleration data structure on the primitives
        bvh::SweepSahBuilder<Bvh> builder(*_bvh);
        builder.max_depth = maxDepth;
        builder.max_leaf_size = maxLeafSize;
        builder.build(global_bbox, bboxes.get(), centers.get(), _meshes.size());

        auto end = std::chrono::steady_clock::now();
        auto tt = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Build BVH Time = " << tt.count() << "΢��;  " << tt.count() / 1000 << "����" << std::endl;
    }

    void MeshBVH::Build1(unsigned int maxDepth /*= 16*/, unsigned int maxLeafSize /*= 16*/) {
        _bvh = std::make_unique<Bvh>();
        // Compute the global bounding box and the centers of the primitives.
        // This is the input of the BVH construction algorithm.
        // Note: Using the bounding box centers instead of the primitive centers is possible,
        // but usually leads to lower-quality BVHs.
        auto [bboxes, centers] = bvh::compute_bounding_boxes_and_centers<BvhMesh, double>(_meshes.data(),
                                                                                          _meshes.size());
        auto global_bbox = bvh::compute_bounding_boxes_union(bboxes.get(), _meshes.size());

        // Create an acceleration data structure on the primitives
        bvh::BinnedSahBuilder<Bvh, 4> builder(*_bvh);
        builder.build(global_bbox, bboxes.get(), centers.get(), _meshes.size());
    }

    bool MeshBVH::Intersect(const E3dMath::Vector3d &rayOrigin, const E3dMath::Vector3d &rayDir,
                            E3dMath::Vector3d &intersectPt, size_t &hitTriIndex) {
        if (!_bvh || !_meshes.size()) {
            return false;
        }
        auto start = std::chrono::steady_clock::now();


        // Intersect a ray with the data structure
        BvhRay ray(BvhVec3(rayOrigin.X(), rayOrigin.Y(), rayOrigin.Z()), // origin
                   BvhVec3(rayDir.X(), rayDir.Y(), rayDir.Z())             // direction
        );
        // bvh::ClosestPrimitiveIntersector<Bvh, BvhTriangle> primitive_intersector(*_bvh, _meshes.data());
        // bvh::SingleRayTraverser<Bvh> traverser(*_bvh);

        // if (auto hit = traverser.traverse(ray, primitive_intersector)) {
        //	auto triangle_index = hit->primitive_index;
        //	auto intersection = hit->intersection;
        //	intersectPt = rayOrigin.Clone() + intersection.t * rayDir;

        //	auto end = std::chrono::steady_clock::now();
        //	auto tt = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        //	std::cout << "Intersect Time = " << tt.count() << "΢��;  " << tt.count() / 1000 << "����" << std::endl;
        //	return true;
        //}
        return false;
    }

    vector <vector<const E3dMath::Mesh *>> MeshBVH::GetLeafMeshes() const {
        vector<vector<const E3dMath::Mesh *>> result;
        if (!_bvh) {
            return result;
        }
        for (size_t i = 0; i < _bvh->node_count; ++i) {
            auto bounds = _bvh->nodes[i].bounds;
            if (_bvh->nodes[i].primitive_count == 0) {
                continue;
            }
            vector<const E3dMath::Mesh *> meshes;
            for (size_t j = 0; j < _bvh->nodes[i].primitive_count; ++j) {
                meshes.push_back(_meshes[_bvh->nodes[i].first_child_or_primitive + j].GetMesh());
            }
            result.push_back(meshes);
        }
        return result;
    }

    vector <vector<const E3dMath::Mesh *>> MeshBVH::GetTreeNodeMeshes() const {
        if (!_bvh || !_bvh->node_count) {
            return vector<vector<const E3dMath::Mesh *>>();
        }

        vector<vector<size_t>> indexByLevel = GetPrimitivesIndexByLevel();
        vector<vector<const E3dMath::Mesh *>> meshResult;
        for (auto &indices: indexByLevel) {
            vector<const E3dMath::Mesh *> meshes;
            for (auto &idx: indices) {
                meshes.push_back(_meshes[idx].GetMesh());
            }
            meshResult.push_back(std::move(meshes));
        }
        return meshResult;
    }

    vector <vector<const E3dMath::Mesh *>> MeshBVH::GetTreeNodeMeshesByLevel(unsigned int level) const {
        if (!_bvh || !_bvh->node_count) {
            return vector<vector<const E3dMath::Mesh *>>();
        }

        vector<vector<const E3dMath::Mesh *>> result;
        std::queue<size_t> queue;
        queue.push(0);
        unsigned int curLevel = 0;
        while (!queue.empty()) {
            size_t currentLevelSize = queue.size();
            if (level == curLevel) {
                while (!queue.empty()) {
                    size_t node = queue.front();
                    queue.pop();
                    vector<const E3dMath::Mesh *> meshes;
                    _PreOrder(&(_bvh->nodes[node]), meshes);
                    result.push_back(std::move(meshes));
                }
                return result;
            }

            for (size_t i = 1; i <= currentLevelSize; ++i) {
                size_t node = queue.front();
                queue.pop();
                if ((_bvh->nodes.get())[node].primitive_count == 0) {
                    queue.push((_bvh->nodes.get())[node].first_child_or_primitive);
                    queue.push(_bvh->sibling((_bvh->nodes.get())[node].first_child_or_primitive));
                }
            }
            ++curLevel;
        }
        return vector<vector<const E3dMath::Mesh *>>();
    }

    std::vector<std::vector<std::vector<const E3dMath::Mesh *>>> MeshBVH::GetTreeNodeMeshesByLevels() const {
        std::vector<std::vector<std::vector<const E3dMath::Mesh *>>> result;
        unsigned int level = this->GetTreeHeight();
        for (unsigned int i = 0; i < level; ++i) {
            result.push_back(GetTreeNodeMeshesByLevel(i));
        }
        return result;
    }

    vector <std::unique_ptr<E3dMath::Box3d>> MeshBVH::GetTreeNodeBoxes() const {
        vector<std::unique_ptr<E3dMath::Box3d>> result;
        if (!_bvh) {
            return result;
        }
        for (size_t i = 0; i < _bvh->node_count; ++i) {
            auto bounds = _bvh->nodes[i].bounds;
            if (_bvh->nodes[i].primitive_count != 0) {
                continue;
            }
            result.push_back(std::make_unique<E3dMath::Box3d>(E3dMath::Vector3d(bounds[0], bounds[2], bounds[4]),
                                                              E3dMath::Vector3d(bounds[1], bounds[3], bounds[5])));
        }
        return result;
    }

    vector <vector<std::unique_ptr<E3dMath::Box3d>>> MeshBVH::GetTreeNodeBoxesByLevel() const {
        if (!_bvh || !_bvh->node_count) {
            return vector<vector<std::unique_ptr<E3dMath::Box3d>>>();
        }

        vector<vector<size_t>> result = GetPrimitivesIndexByLevel();

        vector<vector<std::unique_ptr<E3dMath::Box3d>>> BoxResult;
        for (auto &boxes: result) {
            vector<std::unique_ptr<E3dMath::Box3d>> boxLevel;
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

    size_t MeshBVH::GetMeshCount() const {
        return _meshes.size();
    }

    size_t MeshBVH::GetTriangleCount() const {
        size_t triangleCount = 0;
        for (auto &mesh: _meshes) {
            triangleCount += mesh.GetMesh()->GetPointIndices().size() / 3;
        }
        return triangleCount;
    }

    size_t MeshBVH::GetBoxCount() const {
        size_t count = 0;
        if (!_bvh) {
            return count;
        }
        return _bvh->node_count;
    }

    vector<unsigned int> MeshBVH::GetMeshCountInLeaf() const {
        vector<unsigned int> counts;
        auto nodes = _bvh->nodes.get();
        for (unsigned int i = 0; i < _bvh->node_count; ++i) {
            counts.push_back(nodes[i].primitive_count);
        }
        return counts;
    }

    vector <vector<size_t>> MeshBVH::GetPrimitivesIndexByLevel() const {
        if (!_bvh || !_bvh->node_count) {
            return vector<vector<size_t>>();
        }

        vector<vector<size_t>> result;
        std::queue<size_t> queue;
        queue.push(0);
        while (!queue.empty()) {
            size_t currentLevelSize = queue.size();
            result.push_back(vector<size_t>());
            for (size_t i = 1; i <= currentLevelSize; ++i) {
                size_t node = queue.front();
                queue.pop();
                result.back().push_back(node);
                if ((_bvh->nodes.get())[node].primitive_count == 0) {
                    queue.push((_bvh->nodes.get())[node].first_child_or_primitive);
                    queue.push(_bvh->sibling((_bvh->nodes.get())[node].first_child_or_primitive));
                }
            }
        }
        return result;
    }

    unsigned int MeshBVH::GetTreeHeight() const {
        if (!_bvh || !_bvh->node_count) {
            return 0;
        }

        unsigned int result = 0;
        std::queue<size_t> queue;
        queue.push(0);
        while (!queue.empty()) {
            size_t currentLevelSize = queue.size();
            result++;
            for (size_t i = 1; i <= currentLevelSize; ++i) {
                size_t node = queue.front();
                queue.pop();
                if ((_bvh->nodes.get())[node].primitive_count == 0) {
                    queue.push((_bvh->nodes.get())[node].first_child_or_primitive);
                    queue.push(_bvh->sibling((_bvh->nodes.get())[node].first_child_or_primitive));
                }
            }
        }
        return result + 1;
    }

    void MeshBVH::_PreOrder(BvhNode *root, std::vector<const E3dMath::Mesh *> &meshes) const {
        if (root == nullptr) {
            return;
        }
        if (root->is_leaf()) {
            for (std::size_t i = 0; i < root->primitive_count; ++i) {
                meshes.push_back(_meshes[root->first_child_or_primitive + i].GetMesh());
            }
            return;
        }
        _PreOrder(&(_bvh->nodes[root->first_child_or_primitive]), meshes);
        _PreOrder(&(_bvh->nodes[_bvh->sibling(root->first_child_or_primitive)]), meshes);
    }
} // namespace gmv
