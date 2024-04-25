#pragma once

#include "math/math/Vector2d.h"
#include "math/math/Vector3d.h"
#include "easy3d/core/types.h"

namespace E3dMath {
    class Mesh;
}

namespace gmv {
    class DataConverter {
    public:
        static easy3d::vec3 AesVector2dToVec3(const E3dMath::Vector2d &vec);

        static easy3d::vec3 AesVector3dToVec3(const E3dMath::Vector3d &vec);

        static E3dMath::Vector3d Vec3ToAesVector3d(const easy3d::vec3 &vec);

        static E3dMath::Vector2d Vec3ToAesVector2d(const easy3d::vec3 &vec);

        static void MeshToPointsIndices(const E3dMath::Mesh *mesh, std::vector<easy3d::vec3> &points,
                                        std::vector<unsigned int> &indices);
    };

} // namespace gmv
