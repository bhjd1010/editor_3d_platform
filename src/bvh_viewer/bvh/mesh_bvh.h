#pragma once

#include <iostream>
#include <type_traits>
#include <vector>

#include <bvh/primitive_intersectors.hpp>
#include <bvh/single_ray_traverser.hpp>
#include <bvh/sweep_sah_builder.hpp>

#include "math/Math//Vector3d.h"
#include "bvh_types.h"
#include "math/geometry/Mesh.h"
#include "math/math/Box3d.h"

namespace gmv {
    struct BvhMesh {
        struct Intersection {
            double t;

            // Required member: returns the distance along the ray
            double distance() const { return t; }
        };

        // Required type: the intersection data type returned by the intersect() method
        using IntersectionType = Intersection;

        BvhMesh(const E3dMath::Mesh *mesh) : _mesh(mesh) {}

        const E3dMath::Mesh *GetMesh() const { return _mesh; }

        // Required member: returns the center of the primitive
        BvhVec3 center() const { return bounding_box().center(); }

        // Required member: returns a bounding box for the primitive (tighter is better)
        BvhBoundingBox bounding_box() const {
            auto &points = _mesh->GetPoints();
            E3dMath::Box3d box;
            for (auto &p: points) {
                box.MergePoint(p);
            }
            auto &min = box.GetMinPoint();
            auto &max = box.GetMaxPoint();
            return BvhBoundingBox(BvhVec3(min.X(), min.Y(), min.Z()), BvhVec3(max.X(), max.Y(), max.Z()));
        }

        // Required member: computes the intersection between a ray and the primitive
        std::optional<Intersection> intersect(const BvhRay &ray) const {
            return std::make_optional<Intersection>(Intersection{(ray.tmin + ray.tmax) * double(0.5)});
        }

    private:
        const E3dMath::Mesh *_mesh;
    };

    class MeshBVH final {
    public:
        MeshBVH(const std::vector<const E3dMath::Mesh *> &&meshes);

        void Build(unsigned int maxDepth = 16, unsigned int maxLeafSize = 16);

        void Build1(unsigned int maxDepth = 16, unsigned int maxLeafSize = 16);


        bool
        Intersect(const E3dMath::Vector3d &rayOrigin, const E3dMath::Vector3d &rayDir, E3dMath::Vector3d &intersectPt,
                  std::size_t &hitTriIndex);

        std::vector<std::vector<const E3dMath::Mesh *>> GetLeafMeshes() const;

        std::vector<std::vector<const E3dMath::Mesh *>> GetTreeNodeMeshes() const;

        std::vector<std::vector<const E3dMath::Mesh *>> GetTreeNodeMeshesByLevel(unsigned int level) const;

        std::vector<std::vector<std::vector<const E3dMath::Mesh *>>> GetTreeNodeMeshesByLevels() const;


        std::vector<std::unique_ptr<E3dMath::Box3d>> GetTreeNodeBoxes() const;

        std::vector<std::vector<std::unique_ptr<E3dMath::Box3d>>> GetTreeNodeBoxesByLevel() const;

        std::size_t GetMeshCount() const;

        std::size_t GetTriangleCount() const;

        std::size_t GetBoxCount() const;

        std::vector<unsigned int> GetMeshCountInLeaf() const;

        std::vector<std::vector<std::size_t>> GetPrimitivesIndexByLevel() const;

        unsigned int GetTreeHeight() const;

    private:
        void _PreOrder(BvhNode *root, std::vector<const E3dMath::Mesh *> &meshes) const;

        std::vector<BvhMesh> _meshes;
        std::unique_ptr<Bvh> _bvh;
    };

} // namespace gmv
