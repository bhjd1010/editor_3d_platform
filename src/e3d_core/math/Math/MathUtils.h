#pragma once

#include "math/common/define.h"
#include "math/common/constants.h"

namespace E3dMath {

    class MathUtils {
    public:
        static bool IsZero(double value, double tolerance = Constants::DOUBLE_EPS);

        static bool IsEqual(double value1, double value2, double tolerance = Constants::DOUBLE_EPS);

        // value1 > value2
        static bool IsGreaterThan(double value1, double value2, double tolerance = Constants::DOUBLE_EPS);

        static bool IsGreaterOrEqualThan(double value1, double value2, double tolerance = Constants::DOUBLE_EPS);

        // value1 < value2
        static bool IsLessThan(double value1, double value2, double tolerance = Constants::DOUBLE_EPS);

        static bool IsLessOrEqualThan(double value1, double value2, double tolerance = Constants::DOUBLE_EPS);

        // 数值取整
        static double Round(double value);

        static double RadiansToAngle(double radians);

        static double AngleToRadians(double angle);

        // 限制数值在min和max之间
        static void Clamp(const double &min, const double &max, double &value);
    };

}
