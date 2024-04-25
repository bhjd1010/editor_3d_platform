
#pragma once

#include "Matrix3d.h"
#include "Vector2d.h"

namespace E3dMath {

// 二维向量定义
    class Vector2dUtils {
    public:

        /**
         * 点的变换，包括平移、旋转、缩放，会改变Vector2d
         */
        static bool Transform(Vector2d &vec, const Matrix3d &mat);

        /**
         * 向量的变换，包括旋转、缩放，忽略平移，会改变Vector2d
         */
        static bool VecTransform(Vector2d &vec, const Matrix3d &mat);

        /**
         * 点的平移，会改变Vector2d
         */
        static bool Translate(Vector2d &vec, const Vector2d &offset);

    };

}


