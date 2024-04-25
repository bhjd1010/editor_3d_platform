
#include "Line3d.h"
#include "math/MathUtils.h"
#include "math/Box2d.h"
#include <math.h>
#include <cassert>
#include <limits>
#include "common/constants.h"
#include "math/Box3d.h"
#include "math/Vector3dUtils.h"

namespace E3dMath {

//////////////////////////////////////////////////////////////////////////
    Line3d Line3d::Create(const Vector3d &startPoint, const Vector3d &endPoint) {
        return Line3d(startPoint, endPoint);
    }

    Line3d Line3d::Create(const Vector3d &position, const Vector3d &dir, const Intervald &range) {
        return Line3d(position, dir, range);
    }

    Line3d::Line3d(const Vector3d &startPoint, const Vector3d &endPoint) {
        Reset(startPoint, endPoint);
    }

    Line3d::Line3d(const Vector3d &position, const Vector3d &dir, const Intervald &range) {
        _origin = position;
        _dir = dir;
        _dir.Normalize();
        _range = range;
    }

    Line3d::Line3d(const Line3d &another)
            : _origin(another._origin), _dir(another._dir), _range(another._range) {

    }

    bool Line3d::Reset(const Vector3d &start, const Vector3d &end) {
        Vector3d ab = end - start;
        double len = ab.Length();

        if (len < Constants::DOUBLE_EPS) {
            return false;
        } else {
            _dir = ab * (1 / len);
        }
        _origin = start;
        _range = Intervald(0, len);
        return true;
    }

    const Vector3d &Line3d::GetOrigin() const {
        return _origin;
    }

    void Line3d::SetOrigin(const Vector3d &pos) {
        _origin = pos;
    }

    const Vector3d &Line3d::GetDirection() const {
        return _dir;
    }

    void Line3d::SetDirection(const Vector3d &dir) {
        _dir = dir;
    }

    bool Line3d::IsParallelTo(const Line3d &other) const {
        return _dir.IsParallel(other.GetDirection());
    }

    bool Line3d::IsColinearWith(const Line3d &other) const {
        if (!IsParallelTo(other)) {
            return false;
        }
        Vector3d mid = other.GetMiddlePoint();
        return MathUtils::IsZero(this->GetPointAt(this->GetParamAt(mid)).DiatanceTo(mid));
    }

    bool Line3d::IsPerpendicularTo(const Line3d &other) const {
        return _dir.IsPerpendicularTo(other.GetDirection());
    }


//////////////////////////////////////////////////////////////////////////
// ICurve2d接口实现

    const Intervald &Line3d::GetRange() const {
        return _range;
    }

    void Line3d::SetRange(const Intervald &range) {
        _range = range;
    }

    Box3d Line3d::GetBoundingBox() const {
        Box3d box;
        box.MergePoint(GetStartPoint());
        box.MergePoint(GetEndPoint());
        return box;;
    }

    Vector3d Line3d::GetPointAt(double param) const {
        return (_dir * param) + _origin;
    }

    double Line3d::GetParamAt(const Vector3d &pt) const {
        Vector3d refVec = pt - _origin;
        return refVec.Dot(_dir);
    }

    Vector3d Line3d::GetTangent(double param) const {
        return _dir;
    }

    Vector3d Line3d::GetStartPoint() const {
        return GetPointAt(_range.GetMin());
    }

    Vector3d Line3d::GetEndPoint() const {
        return GetPointAt(_range.GetMax());
    }

    Vector3d Line3d::GetMiddlePoint() const {
        return GetPointAt(_range.Middle());
    }

    Vector3d Line3d::GetStartTangent() const {
        return _dir;
    }

    Vector3d Line3d::GetEndTangent() const {
        return _dir;
    }

    bool Line3d::Transform(const Matrix4d &transMatrix) {
        Vector3dUtils::Transform(_origin, transMatrix);
        Vector3dUtils::VecTransform(_dir, transMatrix);
        double scale = _dir.Length();
        _dir *= (1 / scale);
        _range *= scale;
        return true;
    }

    bool Line3d::Translate(const Vector3d &vec) {
        return Vector3dUtils::Translate(_origin, vec);
    }

//////////////////////////////////////////////////////////////////////////
// ICurve接口实现

    double Line3d::GetLength() const {
        return _range.Length();
    }

    double Line3d::GetLength(double startParam, double endParam) const {
        return GetPointAt(startParam).DiatanceTo(GetPointAt(endParam));
    }

    bool Line3d::IsClosed() const {
        return false;
    }

    Line3d *Line3d::Reverse() {
        _dir.Reverse();
        _range.Set(-_range.GetMax(), -_range.GetMin());
        return this;
    }

    bool Line3d::Extend(double howLong, bool bTail /*= true*/) {
        if (bTail) {
            _range.SetMax(_range.GetMax() + howLong);
        } else {
            _range.SetMin(_range.GetMin() - howLong);
        }
        return true;
    }

    bool Line3d::ExtendDouble(double howLong) {
        _range.SetMax(_range.GetMax() + howLong);
        _range.SetMin(_range.GetMin() - howLong);
        return true;
    }

    bool Line3d::IsDegenerated(double dEpsilon) const {
        return MathUtils::IsGreaterThan(_range.Length(), Constants::DOUBLE_EPS);
    }

    std::unique_ptr<ICurve> Line3d::Clone() const {
        return std::make_unique<Line3d>(*this);
    }
//////////////////////////////////////////////////////////////////////////
// IGeometry接口实现

    MathObjectType Line3d::GetType() const {
        return MathObjectType::Line3d;
    }

}