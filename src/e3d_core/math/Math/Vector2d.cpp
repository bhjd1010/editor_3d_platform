#include "Vector2d.h"
#include "MathUtils.h"
#include <math.h>
#include <limits>
#include <cassert>

namespace E3dMath {


    Vector2d Vector2d::Create(double x, double y) {
        return Vector2d(x, y);
    }

    Vector2d Vector2d::MakeZero() {
        return Vector2d();
    }

    Vector2d Vector2d::MakeUintX() {
        return Vector2d(1.0, 0);
    }

    Vector2d Vector2d::MakeUnitY() {
        return Vector2d(0, 1.0);
    }

    const Vector2d &Vector2d::UnitX() {
        static Vector2d _unitX(1.0, 0.0);
        return _unitX;
    }

    const Vector2d &Vector2d::UnitY() {
        static Vector2d _unitY(0.0, 1.0);
        return _unitY;
    }

    const Vector2d &Vector2d::Zero() {
        static Vector2d _zero(0.0, 0.0);
        return _zero;
    }

    Vector2d operator*(const Vector2d &vec, double d) {
        return Vector2d(vec.X() * d, vec.Y() * d);
    }

    Vector2d operator*(double d, const Vector2d &vec) {
        return vec * d;
    }

    Vector2d operator/(const Vector2d &vec, double d) {
        if (MathUtils::IsZero(d)) {
            return Vector2d(vec);
        }
        double inv = 1.0 / d;
        return Vector2d(vec.X() * inv, vec.Y() * inv);
    }

    Vector2d operator+(const Vector2d &v1, const Vector2d &v2) {
        return Vector2d(v1.X() + v2.X(), v1.Y() + v2.Y());
    }

    Vector2d operator-(const Vector2d &v1, const Vector2d &v2) {
        return Vector2d(v1.X() - v2.X(), v1.Y() - v2.Y());
    }

    bool operator==(const Vector2d &v1, const Vector2d &v2) {
        return MathUtils::IsEqual(v1.X(), v2.X())
               && MathUtils::IsEqual(v1.Y(), v2.Y());
    }

    bool operator!=(const Vector2d &v1, const Vector2d &v2) {
        return !(v1 == v2);
    }

    Vector2d::Vector2d() {
        _xy[0] = _xy[1] = 0;
    }

    Vector2d::Vector2d(double vec[2]) {
        _xy[0] = vec[0];
        _xy[1] = vec[1];
    }

    Vector2d::Vector2d(double x, double y) {
        _xy[0] = x;
        _xy[1] = y;
    }

    Vector2d::Vector2d(const Vector2d &src) {
        _xy[0] = src._xy[0];
        _xy[1] = src._xy[1];
    }

    bool Vector2d::Set(double x, double y) {
        _xy[0] = x;
        _xy[1] = y;
        return true;
    }

    void Vector2d::Set(const Vector2d &p) {
        Set(p.X(), p.Y());
    }

    bool Vector2d::SetX(double x) {
        _xy[0] = x;
        return true;
    }

    bool Vector2d::SetY(double y) {
        _xy[1] = y;
        return true;
    }

    double Vector2d::X() const {
        return _xy[0];
    }

    double Vector2d::Y() const {
        return _xy[1];
    }

    double &Vector2d::X() {
        return _xy[0];
    }

    double &Vector2d::Y() {
        return _xy[1];
    }

    bool Vector2d::IsZero(double typeTol) const {
        return SqrLength() <= typeTol * typeTol;
    }

    bool Vector2d::IsNormalized(double typeTol) const {
        return fabs(SqrLength() - 1) <= typeTol * typeTol;
    }

    double Vector2d::Length() const {
        return sqrt(SqrLength());
    }

    Vector2d &Vector2d::Reverse() {
        for (int i = 0; i < 2; ++i) {
            _xy[i] = -_xy[i];
        }
        return *this;
    }

    double Vector2d::SqrLength() const {
        return (_xy[0] * _xy[0]) + (_xy[1] * _xy[1]);
    }

    Vector2d Vector2d::Clone() const {
        return Vector2d(*this);
    }

    Vector2d &Vector2d::Normalize() {
        double magnitude = Length();

        if (!MathUtils::IsZero(magnitude)) {
            (*this) *= 1.0 / magnitude;
        } else {
            magnitude = 0;
            _xy[0] = 0;
            _xy[1] = 0;
        }
        return *this;
    }

    Vector2d Vector2d::GetNormalized() const {
        return Clone().Normalize();
    }

    double Vector2d::Dot(const Vector2d &vec) const {
        return (_xy[0] * vec._xy[0] + _xy[1] * vec._xy[1]);
    }

    double &Vector2d::operator[](int nIndex) {
        assert(nIndex >= 0 && nIndex <= 1);
        return _xy[nIndex];
    }

    double Vector2d::operator[](int nIndex) const {
        assert(nIndex >= 0 && nIndex <= 1);
        return _xy[nIndex];
    }

    double Vector2d::Cross(const Vector2d &vec) const {
        return (_xy[0] * vec._xy[1] - _xy[1] * vec._xy[0]);
    }

    double Vector2d::DiatanceTo(const Vector2d &another) const {
        return ((*this) - another).Length();
    }

    double Vector2d::SqDiatanceTo(const Vector2d &another) const {
        return ((*this) - another).SqrLength();
    }

    bool Vector2d::IsParallel(const Vector2d &another) const {
        double dis = this->Cross(another);
        return dis * dis <= this->SqrLength() * another.SqrLength() * Constants::DOUBLE_EPS * Constants::DOUBLE_EPS;
    }

    bool Vector2d::IsPerpendicularTo(const Vector2d &another) const {
        double dis = this->Dot(another);
        return dis * dis <= this->SqrLength() * another.SqrLength() * Constants::DOUBLE_EPS * Constants::DOUBLE_EPS;
    }

    bool Vector2d::Equals(const Vector2d &another, double tol /*= Constants::DOUBLE_EPS*/) const {
        return MathUtils::IsEqual(this->_xy[0], another.X(), tol) && MathUtils::IsEqual(this->_xy[1], another.Y(), tol);
    }

    double Vector2d::AcuteAngleTo(const Vector2d &another) const {
        if (this->IsZero() || another.IsZero()) {
            return 0.0;
        }

        Vector2d normalizedVec1 = *this;
        Vector2d normalizedVec2 = another;
        normalizedVec1.Normalize();
        normalizedVec2.Normalize();

        double cosVal =
                normalizedVec1.Dot(normalizedVec2) / sqrt((normalizedVec1.SqrLength() * normalizedVec2.SqrLength()));
        MathUtils::Clamp(-1.0, 1.0, cosVal);
        double dAngle = acos(cosVal);

        if (dAngle > Constants::MATH_PI / 2) {
            return Constants::MATH_PI - dAngle;
        }

        return dAngle;
    }

    double Vector2d::AngleTo(const Vector2d &another) const {
        if (this->IsZero() || another.IsZero()) {
            return 0.0;
        }

        //确保输入的向量是单位向量
        Vector2d normalizedVecUnitFrom = *this;
        Vector2d normalizedVecUnitTo = another;
        normalizedVecUnitFrom.Normalize();
        normalizedVecUnitTo.Normalize();

        double dCos = normalizedVecUnitTo.Dot(normalizedVecUnitFrom);
        MathUtils::Clamp(-1.0, 1.0, dCos);
        double dAngle = acos(dCos);
        if ((normalizedVecUnitFrom.Cross(normalizedVecUnitTo)) < -std::numeric_limits<double>::epsilon()) {
            dAngle = Constants::MATH_2PI - dAngle;
        }

        return double(dAngle);
    }

    Vector2d &Vector2d::operator=(const Vector2d &vec) {
        _xy[0] = vec._xy[0];
        _xy[1] = vec._xy[1];
        return (*this);
    }

    Vector2d &Vector2d::operator*=(const double d) {
        _xy[0] *= d;
        _xy[1] *= d;
        return (*this);
    }

    Vector2d &Vector2d::operator/=(const double d) {
        assert(!MathUtils::IsZero(d));
        double inv = double(1.0 / d);
        _xy[0] *= inv;
        _xy[1] *= inv;
        return (*this);
    }

    Vector2d &Vector2d::operator+=(const Vector2d &vec) {
        _xy[0] += vec._xy[0];
        _xy[1] += vec._xy[1];
        return (*this);
    }

    Vector2d &Vector2d::operator-=(const Vector2d &vec) {
        _xy[0] -= vec._xy[0];
        _xy[1] -= vec._xy[1];
        return (*this);
    }

    Vector2d Vector2d::operator-() const {
        return Vector2d(-_xy[0], -_xy[1]);
    }

}
