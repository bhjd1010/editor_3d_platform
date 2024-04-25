
#pragma once

#include "Vector3d.h"
#include "Matrix4d.h"

namespace E3dMath {

    class Vector3dUtils {
    public:

        /**
         * 点的变换，包括平移、旋转、缩放，会改变Vector3d
         */
        static bool Transform(Vector3d &vec, const Matrix4d &mat);

        /**
         * 向量的变换，包括旋转、缩放，忽略平移，会改变Vector3d
         */
        static bool VecTransform(Vector3d &vec, const Matrix4d &mat);

        /**
         * 点的平移，会改变Vector3d
         */
        static bool Translate(Vector3d &vec, const Vector3d &offset);
    };

}
