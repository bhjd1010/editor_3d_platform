#include "Vector2dUtils.h"
#include "MathUtils.h"
#include <math.h>
#include <limits>
#include <cassert>

namespace E3dMath {

    bool Vector2dUtils::Transform(Vector2d &vec, const Matrix3d &mat) {
        double x = mat[0][0] * vec.X() + mat[0][1] * vec.Y() + mat[0][2];
        double y = mat[1][0] * vec.X() + mat[1][1] * vec.Y() + mat[1][2];

        double w = mat[2][0] * vec.X() + mat[2][1] * vec.Y() + mat[2][2];//考虑投影变换

        vec._xy[0] = x / w;
        vec._xy[1] = y / w;

        return true;
    }

    bool Vector2dUtils::VecTransform(Vector2d &vec, const Matrix3d &mat) {
        double x = mat[0][0] * vec.X() + mat[0][1] * vec.Y();
        double y = mat[1][0] * vec.X() + mat[1][1] * vec.Y();

        double w = mat[2][0] * vec.X() + mat[2][1] * vec.Y() + mat[2][2];//考虑投影变换

        vec._xy[0] = x / w;
        vec._xy[1] = y / w;

        return true;
    }

    bool Vector2dUtils::Translate(Vector2d &vec, const Vector2d &offset) {
        vec += offset;
        return true;
    }

}
