
#pragma once

#include "define.h"

namespace E3dMath {

/// 一些常量值定义
    class Constants {
    public:
        // DOUBLE_EPS =0.000001, 用于对两个没有单位的双精度浮点数进行比较，比如视图缩放比例等。
        inline static const double DOUBLE_EPS = 0.000001;

        // FLOAT_EPS = 0.001f 用于对两个没有单位的单精度浮点数进行比较，比如视图缩放比例等。
        inline static const double FLOAT_EPS = 0.001f;

        // ANGLE_EPS = 1E-4, 用于对两个角度类型的浮点数进行比较，比如判断两条直线之间的夹角等。
        inline static const double ANGLE_EPS = 0.0001;

        // MATH_INFINITY= 1E100, 全局的正无穷大值
        inline static const double MATH_INFINITY = 1E100;
        // MATH_NEGINFINITY = -1E100,全局的负无穷大值
        inline static const double MATH_NEGINFINITY = -1E100;

        // MATH_SIZE= 1E16, 最大尺度
        inline static const double MAX_SIZE = 1E16;

        // MATH_PI_6 = 0.52359877559829887307,  PI/6
        inline static const double MATH_PI_6 = 0.52359877559829887307;
        // MATH_PI_4 = 0.78539816339744830961,  PI/4
        inline static const double MATH_PI_4 = 0.78539816339744830961;
        // MATH_PI_2 = 1.57079632679489661923,  PI/2
        inline static const double MATH_PI_2 = 1.57079632679489661923;
        // MATH_PI = 3.14159265358979323846,  PI
        inline static const double MATH_PI = 3.14159265358979323846;
        // MATH_3PI_2 = 4.71238898038468985769,  3PI/2
        inline static const double MATH_3PI_2 = 4.71238898038468985769;
        // MATH_2PI = 6.28318530717958647692,  2PI
        inline static const double MATH_2PI = 6.28318530717958647692;

        // clipperlib scale(double to int)
        inline static const unsigned long long int CLIPPER_SCALE = (long long int) 1E7;
    };

}
