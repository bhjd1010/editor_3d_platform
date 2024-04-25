#include "Vector3dUtils.h"
#include "MathUtils.h"
#include <math.h>
#include <cassert>
#include "Matrix4d.h"

namespace E3dMath {

    bool Vector3dUtils::VecTransform(Vector3d &vec, const Matrix4d &mat) {
        double x = mat[0][0] * vec.X() + mat[0][1] * vec.Y() + mat[0][2] * vec.Z();
        double y = mat[1][0] * vec.X() + mat[1][1] * vec.Y() + mat[1][2] * vec.Z();
        double z = mat[2][0] * vec.X() + mat[2][1] * vec.Y() + mat[2][2] * vec.Z();

        double w = mat[3][0] * vec.X() + mat[3][1] * vec.Y() + mat[3][2] * vec.Z() + mat[3][3];//考虑投影变换

        vec._xyz[0] = x / w;
        vec._xyz[1] = y / w;
        vec._xyz[2] = z / w;

        return true;
    }

    bool Vector3dUtils::Transform(Vector3d &vec, const Matrix4d &mat) {
        double x = mat[0][0] * vec.X() + mat[0][1] * vec.Y() + mat[0][2] * vec.Z() + mat[0][3];
        double y = mat[1][0] * vec.X() + mat[1][1] * vec.Y() + mat[1][2] * vec.Z() + mat[1][3];
        double z = mat[2][0] * vec.X() + mat[2][1] * vec.Y() + mat[2][2] * vec.Z() + mat[2][3];

        double w = mat[3][0] * vec.X() + mat[3][1] * vec.Y() + mat[3][2] * vec.Z() + mat[3][3];//考虑投影变换

        vec._xyz[0] = x / w;
        vec._xyz[1] = y / w;
        vec._xyz[2] = z / w;

        return true;
    }

    bool Vector3dUtils::Translate(Vector3d &vec, const Vector3d &offset) {
        vec += offset;
        return true;
    }

}
