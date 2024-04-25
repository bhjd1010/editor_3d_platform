#include "Plane.h"
#include "math/MathUtils.h"
#include <cmath>
#include <cassert>
#include <limits>
#include "common/constants.h"
#include "math/Box3d.h"
#include "geometry/ICurve3d.h"
#include "math/Coordinate3dUtils.h"


namespace E3dMath {
//////////////////////////////////////////////////////////////////////////

    Plane::Plane(const Vector3d &origin, const Vector3d &normal)
            : _coord(origin, normal) {
    }

    Plane::Plane(const Vector3d &origin, const Vector3d &dirU, const Vector3d &dirV)
            : _coord(origin, dirU, dirV) {
    }

    Plane::Plane(const Plane &other)
            : _coord(other._coord) {
    }

    Plane::Plane(const Coordinate3d &coord) {
        _coord = Coordinate3d(coord);
    }

    Plane Plane::XOY(double z /*= 0.0*/) {
        return Plane(Vector3d(0, 0, z), Vector3d::UnitX(), Vector3d::UnitY());
    }

    Plane Plane::YOZ(double x /*= 0.0*/) {
        return Plane(Vector3d(x, 0, 0), Vector3d::UnitY(), Vector3d::UnitZ());
    }

    Plane Plane::ZOX(double y /*= 0.0*/) {
        return Plane(Vector3d(0, y, 0), Vector3d::UnitZ(), Vector3d::UnitX());
    }

    Plane Plane::MakePlaneByTreePoints(const Vector3d &pt1, const Vector3d &pt2, const Vector3d &pt3) {
        Vector3d dx = (pt2 - pt1).Normalize();
        Vector3d v = pt3 - pt1;
        double dotValue = v.Dot(dx);
        Vector3d dxNew = dx * dotValue;
        Vector3d dy = (v - dxNew).Normalize();
        if (dx.IsZero() || dy.IsZero()) {
            assert(false);
            return Plane::XOY();
        }
        return Plane(pt1, dx, dy);
    }

    Plane
    Plane::MakePlaneByPointNormal(const Vector3d &pt1, const Vector3d &normal, const Vector3d *pXDir /*= nullptr*/) {
        if (pXDir && !pXDir->IsParallel(normal)) {
            Vector3d y = normal.Cross(*pXDir).Normalize();
            return Plane(pt1, pXDir->GetNormalized(), y);
        }
        return Plane(pt1, normal);
    }

    const Vector3d &Plane::GetVDir() const {
        return _coord.Y();
    }

    const Vector3d &Plane::GetUDir() const {
        return _coord.X();
    }

    const Vector3d &Plane::GetNormal() const {
        return _coord.Z();

    }

    const Vector3d &Plane::GetOrigin() const {
        return _coord.Origin();

    }

    Vector2d Plane::GetParamAt(const Vector3d &pointOnSurface) const {
        Vector3d localPt = _coord.GetLocalPoint(pointOnSurface);
        return Vector2d(localPt.X(), localPt.Y());
    }

    Vector3d Plane::GetNormalAt(double dU, double dV) const {
        return _coord.Z();
    }

    Vector3d Plane::GetPointAt(double dU, double dV) const {
        return _coord.GetWorldPoint(Vector3d(dU, dV, 0));
    }

    MathObjectType Plane::GetType() const {
        return MathObjectType::Plane;
    }

    bool Plane::IsCoplanar(const ISurface &other, double tol /*= Constants::DOUBLE_EPS*/) const {
        if (other.GetType() != MathObjectType::Plane) {
            return false;
        }

        const Plane &plane = dynamic_cast<const Plane &>(other);
        return (
                _coord.Z().IsParallel(plane.GetNormal()) &&
                ContainsPoint(plane.GetOrigin())
        );
    }

    bool Plane::ContainsPoint(const Vector3d &point, double tol /*= Constants::DOUBLE_EPS*/) const {
        //点到面距离
        return false;

    }

    bool Plane::ContainsCurve(const ICurve3d &curve, double tol /*= Constants::DOUBLE_EPS*/) const {
        if (curve.GetType() == MathObjectType::Line3d) {
            return (
                    ContainsPoint(curve.GetStartPoint(), tol) &&
                    ContainsPoint(curve.GetEndPoint(), tol)
            );
        }
        return false;
    }

    bool Plane::Translate(const Vector3d &vec) {
        return Coordinate3dUtils::Translate(_coord, vec);
    }

    bool Plane::Transform(const Matrix4d &mat) {
        Coordinate3dUtils::Transform(_coord, mat);

        // 处理镜像变换时，保留V向和法向
        bool isMirror = mat.Det() < 0.0;
        if (isMirror) {
            _coord.SetXYDir(_coord.X().Clone().Reverse(), _coord.Y());
        }
        return true;
    }

    Box3d Plane::GetBoundingBox() const {
        assert(false);
        return Box3d();
    }


}
