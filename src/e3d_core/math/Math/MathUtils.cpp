#include "MathUtils.h"
#include <math.h>

namespace E3dMath {


    bool MathUtils::IsEqual(double value1, double value2, double tolerance) {
        return (value2 - tolerance < value1) && (value1 < value2 + tolerance);
    }

    bool MathUtils::IsZero(double value, double tolerance) {
        return IsEqual(value, 0.0, tolerance);
    }

    bool MathUtils::IsGreaterThan(double value1, double value2, double tolerance) {
        return value1 > value2 + tolerance;
    }

    bool MathUtils::IsGreaterOrEqualThan(double value1, double value2, double tolerance) {
        return value1 >= value2 + tolerance;
    }

    bool MathUtils::IsLessThan(double value1, double value2, double tolerance) {
        return value1 < value2 - tolerance;
    }

    bool MathUtils::IsLessOrEqualThan(double value1, double value2, double tolerance) {
        return value1 <= value2 - tolerance;
    }

    double MathUtils::Round(double value) {
        return value > 0.4 ? floor(value + 0.5) : (value < -0.4 ? -floor(-value + 0.5) : 0.0);
    }

    double MathUtils::RadiansToAngle(double radians) {
        return radians * 180.0 / Constants::Constants::MATH_PI;
    }

    double MathUtils::AngleToRadians(double angle) {
        return angle * Constants::Constants::MATH_PI / 180.0;
    }

    void MathUtils::Clamp(const double &min, const double &max, double &value) {
        if (min >= max) {
            return;
        }
        value = (value < min) ? min : (value > max) ? max : value;
    }
}
