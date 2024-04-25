#include "Coordinate3d.h"
#include "MathUtils.h"
#include <math.h>
#include <cassert>
#include <limits>

namespace E3dMath {


    Coordinate3d::Coordinate3d(const Vector3d &origin, const Vector3d &xDir, const Vector3d &yDir) {
        _origin = origin;
        _xDir = xDir.GetNormalized();
        _yDir = yDir.GetNormalized();
        _update();
    }

    Coordinate3d::Coordinate3d(const Vector3d &origin, const Vector3d &zDir /*= Vector3d(0, 0, 1.0)*/) {
        _origin = origin;
        if (_zDir.IsZero()) {
            return;
        }
        _zDir = zDir;
        _zDir.Normalize();

        _yDir = _zDir.Cross(Vector3d::UnitZ());
        _yDir.Normalize();
        if (_yDir.IsZero()) {
            if (_zDir.Z() > 0.0) {
                _yDir.Set(0, 1, 0);
            } else {
                _yDir.Set(0, -1, 0);
            }
        }
        _xDir = _yDir.Cross(_zDir);
        _xDir.Normalize();
    }

    Coordinate3d::Coordinate3d(const Coordinate3d &other)
            : _origin(other._origin), _xDir(other._xDir), _yDir(other._yDir), _zDir(other._zDir) {

    }

    Coordinate3d::Coordinate3d() {

    }

    Coordinate3d Coordinate3d::MakeXOY(double z /*= 0.0*/) {
        return Coordinate3d(Vector3d(0, 0, z), Vector3d::UnitX(), Vector3d::UnitY());
    }

    Coordinate3d Coordinate3d::MakeZOX(double y /*= 0.0*/) {
        return Coordinate3d(Vector3d(0, y, 0), Vector3d::UnitZ(), Vector3d::UnitX());
    }


    Coordinate3d Coordinate3d::MakeYOZ(double x /*= 0.0*/) {
        return Coordinate3d(Vector3d(x, 0, 0), Vector3d::UnitY(), Vector3d::UnitZ());
    }

////////////////////////////////////////////////////////////////
    const Vector3d &Coordinate3d::Origin() const {
        return _origin;
    }

    const Vector3d &Coordinate3d::Z() const {
        return _zDir;
    }

    const Vector3d &Coordinate3d::Y() const {
        return _yDir;
    }

    const Vector3d &Coordinate3d::X() const {
        return _xDir;
    }

    void Coordinate3d::SetXYDir(const Vector3d &xDir, const Vector3d &yDir) {
        _xDir = xDir;
        _yDir = yDir;
        _update();
    }

    void Coordinate3d::SetOrigin(const Vector3d &origin) {
        _origin = origin;
    }

    Coordinate3d &Coordinate3d::ReverseZDir() {
        _zDir.Reverse();
        _yDir = _zDir.Cross(_xDir);
        return *this;
    }

    Vector3d Coordinate3d::GetWorldVector(const Vector3d &localVec) const {
        return _xDir * localVec.X() + _yDir * localVec.Y() + _zDir * localVec.Z();
    }

    Vector3d Coordinate3d::GetLocalVector(const Vector3d &worldVec) const {
        return Vector3d(worldVec.Dot(_xDir), worldVec.Dot(_yDir), worldVec.Dot(_zDir));
    }

    Vector3d Coordinate3d::GetWorldPoint(const Vector3d &uvw) const {
        return _origin + GetWorldVector(uvw);
    }

    Vector3d Coordinate3d::GetLocalPoint(const Vector3d &worldPt) const {
        Vector3d v = worldPt - _origin;
        return Vector3d(v.Dot(_xDir), v.Dot(_yDir), v.Dot(_zDir));
    }


}
