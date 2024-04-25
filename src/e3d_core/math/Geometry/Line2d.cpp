#include "Line2d.h"
#include "math/MathUtils.h"
#include "math/Box2d.h"
#include "common/constants.h"
#include "math/Vector2dUtils.h"

namespace E3dMath {

//////////////////////////////////////////////////////////////////////////
    Line2d Line2d::Create(const Vector2d &startPoint, const Vector2d &endPoint) {
        return Line2d(startPoint, endPoint);
    }

    Line2d Line2d::Create(const Vector2d &position, const Vector2d &dir, const Intervald &range) {
        return Line2d(position, dir, range);
    }

    Line2d::Line2d(const Vector2d &startPoint, const Vector2d &endPoint) {
        Reset(startPoint, endPoint);
    }

    Line2d::Line2d(const Vector2d &position, const Vector2d &dir, const Intervald &range) {
        _origin = position;
        _dir = dir;
        _dir.Normalize();
        _range = range;
    }

    Line2d::Line2d(const Line2d &another)
            : _origin(another._origin), _dir(another._dir), _range(another._range) {
    }

    bool Line2d::Reset(const Vector2d &start, const Vector2d &end) {
        Vector2d ab = end - start;
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

    const Vector2d &Line2d::GetOrigin() const {
        return _origin;
    }

    void Line2d::SetOrigin(const Vector2d &pos) {
        _origin = pos;
    }

    const Vector2d &Line2d::GetDirection() const {
        return _dir;
    }

    void Line2d::SetDirection(const Vector2d &dir) {
        _dir = dir;
    }

    bool Line2d::IsParallelTo(const Line2d &other) const {
        return _dir.IsParallel(other.GetDirection());
    }

    bool Line2d::IsColinearWith(const Line2d &other) const {
        if (!IsParallelTo(other)) {
            return false;
        }
        Vector2d mid = other.GetMiddlePoint();
        return MathUtils::IsZero(this->GetPointAt(this->GetParamAt(mid)).DiatanceTo(mid));
    }

    bool Line2d::IsPerpendicularTo(const Line2d &other) const {
        return _dir.IsPerpendicularTo(other.GetDirection());
    }

//////////////////////////////////////////////////////////////////////////
// ICurve2d接口实现

    const Intervald &Line2d::GetRange() const {
        return _range;
    }

    void Line2d::SetRange(const Intervald &range) {
        _range = range;
    }

    Box2d Line2d::GetBoundingBox() const {
        Box2d box;
        box.MergePoint(GetStartPoint());
        box.MergePoint(GetEndPoint());
        return box;
    }

    Vector2d Line2d::GetPointAt(double param) const {
        return (_dir * param) + _origin;
    }

    double Line2d::GetParamAt(const Vector2d &pt) const {
        Vector2d refVec = pt - _origin;
        return refVec.Dot(_dir);
    }

    Vector2d Line2d::GetTangent(double param) const {
        return _dir;
    }

    Vector2d Line2d::GetStartPoint() const {
        return GetPointAt(_range.GetMin());
    }

    Vector2d Line2d::GetEndPoint() const {
        return GetPointAt(_range.GetMax());
    }

    Vector2d Line2d::GetMiddlePoint() const {
        return GetPointAt(_range.Middle());
    }

    Vector2d Line2d::GetStartTangent() const {
        return _dir;
    }

    Vector2d Line2d::GetEndTangent() const {
        return _dir;
    }

    bool Line2d::Transform(const Matrix3d &transMatrix) {
        Vector2dUtils::Transform(_origin, transMatrix);
        Vector2dUtils::VecTransform(_dir, transMatrix);
        double scale = _dir.Length();
        _dir *= (1 / scale);
        _range *= scale;
        return true;
    }

    bool Line2d::Translate(const Vector2d &vec) {
        _origin += vec;
        return true;
    }

    std::unique_ptr<ICurve> Line2d::Clone() const {
        return std::make_unique<Line2d>(*this);
    }

//////////////////////////////////////////////////////////////////////////
// ICurve接口实现

    double Line2d::GetLength() const {
        return _range.Length();
    }

    double Line2d::GetLength(double startParam, double endParam) const {
        return GetPointAt(startParam).DiatanceTo(GetPointAt(endParam));
    }

    bool Line2d::IsClosed() const {
        return false;
    }

    Line2d *Line2d::Reverse() {
        _dir.Reverse();
        _range.Set(-_range.GetMax(), -_range.GetMin());
        return this;
    }

    bool Line2d::Extend(double howLong, bool bTail /*= true*/) {
        if (bTail) {
            _range.SetMax(_range.GetMax() + howLong);
        } else {
            _range.SetMin(_range.GetMin() - howLong);
        }
        return true;
    }

    bool Line2d::ExtendDouble(double howLong) {
        _range.SetMax(_range.GetMax() + howLong);
        _range.SetMin(_range.GetMin() - howLong);
        return true;
    }

    bool Line2d::IsDegenerated(double dEpsilon) const {
        return MathUtils::IsGreaterThan(_range.Length(), Constants::DOUBLE_EPS);
    }


//////////////////////////////////////////////////////////////////////////
// IGeometry接口实现

    MathObjectType Line2d::GetType() const {
        return MathObjectType::Line2d;
    }

}