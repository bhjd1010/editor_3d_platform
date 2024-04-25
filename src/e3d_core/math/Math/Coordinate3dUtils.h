#pragma once

#include "Vector3d.h"
#include "Coordinate3d.h"
#include "Matrix4d.h"

namespace E3dMath {

    class Coordinate3dUtils {
    public:
        /**
         * 构造一个矩阵，将当前局部坐标系的位置变换到世界坐标系
         */
        static Matrix4d GetLocalToWorldMatrix(const Coordinate3d &coord);

        /**
         * 构造一个矩阵，将世界坐标系位置变换到当前局部坐标系
         */
        static Matrix4d GetWorldToLocalMatrix(const Coordinate3d &coord);

        /**
         * 平移，会改变coord
         */
        static bool Translate(Coordinate3d &coord, const Vector3d &offset);

        static bool Transform(Coordinate3d &coord, const Matrix4d &mat);
    };

}


