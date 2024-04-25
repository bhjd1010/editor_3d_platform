#include "Coordinate3dUtils.h"
#include "MathUtils.h"
#include <math.h>
#include <cassert>
#include <limits>
#include "Vector3dUtils.h"

namespace E3dMath {

    Matrix4d Coordinate3dUtils::GetLocalToWorldMatrix(const Coordinate3d &coord) {
        auto &_xDir = coord.X();
        auto &_yDir = coord.Y();
        auto &_zDir = coord.Z();
        auto &_origin = coord.Origin();

        return Matrix4d(_xDir.X(), _yDir.X(), _zDir.X(), _origin.X(),
                        _xDir.Y(), _yDir.Y(), _zDir.Y(), _origin.Y(),
                        _xDir.Z(), _yDir.Z(), _zDir.Z(), _origin.Z(),
                        0, 0, 0, 1);
    }

    Matrix4d Coordinate3dUtils::GetWorldToLocalMatrix(const Coordinate3d &coord) {
        Matrix4d mat = GetLocalToWorldMatrix(coord);
        bool ret = mat.MakeInverse();
        if (!ret) {
            return Matrix4d();
        }
        return mat;
    }

    bool Coordinate3dUtils::Translate(Coordinate3d &coord, const Vector3d &offset) {
        coord._origin += offset;
        return true;
    }

    bool Coordinate3dUtils::Transform(Coordinate3d &coord, const Matrix4d &m) {
        Vector3dUtils::Transform(coord._origin, m);
        Vector3dUtils::VecTransform(coord._xDir, m);
        coord._xDir.Normalize();
        Vector3dUtils::VecTransform(coord._yDir, m);
        coord._yDir = coord._xDir.Cross(coord._yDir).Cross(coord._xDir).Normalize();
        coord._update();
        return true;
    }


}
