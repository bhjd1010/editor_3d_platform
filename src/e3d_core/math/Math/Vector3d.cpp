#include "Vector3d.h"
#include "MathUtils.h"
#include <math.h>
#include <cassert>

namespace E3dMath {

    Vector3d Vector3d::Create(const double x, const double y, const double z) {
        return Vector3d(x, y, z);
    }

    Vector3d Vector3d::MakeZero() {
        return Vector3d();
    }

    Vector3d Vector3d::MakeUintX() {
        return Vector3d(1.0, 0, 0);
    }

    Vector3d Vector3d::MakeUintY() {
        return Vector3d(0, 1.0, 0);
    }

    Vector3d Vector3d::MakeUintZ() {
        return Vector3d(0, 0, 1.0);
    }

    const Vector3d &Vector3d::UnitX() {
        static Vector3d UnitX(1.0, 0.0, 0.0);
        return UnitX;
    }

    const Vector3d &Vector3d::UnitY() {
        static Vector3d UnitY(0.0, 1.0, 0.0);
        return UnitY;
    }

    const Vector3d &Vector3d::UnitZ() {
        static Vector3d UnitZ(0.0, 0.0, 1.0);
        return UnitZ;
    }

    const Vector3d &Vector3d::Zero() {
        static Vector3d Zero(0.0, 0.0, 0.0);
        return Zero;
    }

    Vector3d operator*(const Vector3d &vecSrc, const double d) {
        return Vector3d(vecSrc.X() * d, vecSrc.Y() * d, vecSrc.Z() * d);
    }

    Vector3d operator*(const double &d, const Vector3d &vecSrc) {
        return Vector3d(vecSrc.X() * d, vecSrc.Y() * d, vecSrc.Z() * d);
    }

    Vector3d operator^(const Vector3d &v1, const Vector3d &v2) {
        return v1.Cross(v2);
    }

    Vector3d operator/(const Vector3d &vecSrc, double d) {
        assert(d != 0.0);
        return Vector3d(vecSrc.X() / d, vecSrc.Y() / d, vecSrc.Z() / d);
    }

    bool operator>(const Vector3d &v1, const Vector3d &v2) {
        if (v1.X() > v2.X())
            return true;
        if (v2.X() > v1.X())
            return false;
        if (v1.Y() > v2.Y())
            return true;
        if (v2.Y() > v1.Y())
            return false;
        if (v1.Z() > v2.Z())
            return true;

        return false;
    }

    bool operator<(const Vector3d &v1, const Vector3d &v2) {
        if (v1.X() < v2.X())
            return true;
        if (v2.X() < v1.X())
            return false;
        if (v1.Y() < v2.Y())
            return true;
        if (v2.Y() < v1.Y())
            return false;
        if (v1.Z() < v2.Z())
            return true;

        return false;
    }

    bool operator==(const Vector3d &v1, const Vector3d &v2) {
        return (v1 - v2).SqrLength() < Constants::DOUBLE_EPS * Constants::DOUBLE_EPS;
    }

    bool operator!=(const Vector3d &v1, const Vector3d &v2) {
        return !(v1 == v2);
    }

    Vector3d::Vector3d() {
        _xyz[0] = 0;
        _xyz[1] = 0;
        _xyz[2] = 0;
    }

    Vector3d::Vector3d(const double v[3]) {
        assert(nullptr != v);
        _xyz[0] = v[0];
        _xyz[1] = v[1];
        _xyz[2] = v[2];
    }

    Vector3d::Vector3d(const double x, const double y, const double z) {
        _xyz[0] = x;
        _xyz[1] = y;
        _xyz[2] = z;
    }

    Vector3d::Vector3d(const Vector2d &vecSrc2d, const double z) {
        _xyz[0] = vecSrc2d.X();
        _xyz[1] = vecSrc2d.Y();
        _xyz[2] = z;
    }

    Vector3d::Vector3d(const Vector3d &vecSrc) {
        _xyz[0] = vecSrc._xyz[0];
        _xyz[1] = vecSrc._xyz[1];
        _xyz[2] = vecSrc._xyz[2];
    }

    double Vector3d::X() const {
        return _xyz[0];
    }

    double Vector3d::Y() const {
        return _xyz[1];
    }

    double Vector3d::Z() const {
        return _xyz[2];
    }

    double &Vector3d::X() {
        return _xyz[0];
    }

    double &Vector3d::Y() {
        return _xyz[1];
    }

    double &Vector3d::Z() {
        return _xyz[2];
    }

    bool Vector3d::Set(const double x, const double y, const double z) {
        _xyz[0] = x;
        _xyz[1] = y;
        _xyz[2] = z;
        return true;
    }

    bool Vector3d::Set(const Vector2d &vecSrc2d, const double z) {
        _xyz[0] = vecSrc2d.X();
        _xyz[1] = vecSrc2d.Y();
        _xyz[2] = z;
        return true;
    }

    bool Vector3d::Set(const double v[3]) {
        assert(v != nullptr);
        _xyz[0] = v[0];
        _xyz[1] = v[1];
        _xyz[2] = v[2];

        return true;
    }

    bool Vector3d::Set(const Vector3d &v) {
        return Set(v.X(), v.Y(), v.Z());
    }

    Vector3d &Vector3d::Reverse() {
        for (int i = 0; i < 3; ++i) {
            _xyz[i] = -_xyz[i];
        }
        return *this;
    }

    bool Vector3d::SetX(const double x) {
        _xyz[0] = x;
        return true;
    }

    bool Vector3d::SetY(const double y) {
        _xyz[1] = y;
        return true;
    }

    bool Vector3d::SetZ(const double z) {
        _xyz[2] = z;
        return true;
    }

    Vector3d Vector3d::Clone() const {
        return Vector3d(*this);
    }

    double &Vector3d::operator[](int nIndex) {
        assert(nIndex >= 0 && nIndex < 3);
        return _xyz[nIndex];
    }

    const double &Vector3d::operator[](int nIndex) const {
        assert(nIndex >= 0 && nIndex < 3);
        return _xyz[nIndex];
    }

    double Vector3d::AcuteAngleTo(const Vector3d &another) const {
        if (this->IsZero() || another.IsZero()) {
            return 0.0;
        }

        Vector3d normalizedVec1 = *this;
        Vector3d normalizedVec2 = another;
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


    double Vector3d::AngleTo(const Vector3d &vecTo) const {
        if (this->IsZero() || vecTo.IsZero()) {
            return 0.0;
        }

        //确保输入的向量是单位向量
        Vector3d normalizedVecUnitFrom = *this;
        Vector3d normalizedVecUnitTo = vecTo;
        normalizedVecUnitFrom.Normalize();
        normalizedVecUnitTo.Normalize();

        double cosVal = normalizedVecUnitTo.Dot(normalizedVecUnitFrom);
        MathUtils::Clamp(-1.0, 1.0, cosVal);
        double dAngle = acos(cosVal);
        return dAngle;
    }


    double Vector3d::AngleTo(const Vector3d &another, const Vector3d &normal) const {
        if (this->IsZero() || another.IsZero()) {
            return 0.0;
        }

        //确保输入的向量是单位向量
        Vector3d normalizedVecUnitFrom = *this;
        Vector3d normalizedVecUnitTo = another;
        normalizedVecUnitFrom.Normalize();
        normalizedVecUnitTo.Normalize();

        double cosVal = normalizedVecUnitTo.Dot(normalizedVecUnitFrom);
        MathUtils::Clamp(-1.0, 1.0, cosVal);
        double dAngle = acos(cosVal);

        //normal不为空
        Vector3d crossVec = normalizedVecUnitFrom.Cross(normalizedVecUnitTo);
        if (normal.Dot(crossVec) < 0.0) {
            dAngle = Constants::MATH_2PI - dAngle;
        }

        return dAngle;
    }

    bool Vector3d::IsZero(const double epsilon) const {
        return SqrLength() <= epsilon * epsilon;
    }

    bool Vector3d::IsNormalized(const double epsilon) const {
        return fabs(SqrLength() - 1) <= epsilon * epsilon;
    }

    double Vector3d::Dot(const Vector3d &vecSrc) const {
        return _xyz[0] * vecSrc._xyz[0] + _xyz[1] * vecSrc._xyz[1] + _xyz[2] * vecSrc._xyz[2];
    }

    Vector3d Vector3d::Cross(const Vector3d &vecSrc) const {
        return Vector3d(_xyz[1] * vecSrc._xyz[2] - vecSrc._xyz[1] * _xyz[2],
                        _xyz[2] * vecSrc._xyz[0] - vecSrc._xyz[2] * _xyz[0],
                        _xyz[0] * vecSrc._xyz[1] - vecSrc._xyz[0] * _xyz[1]);
    }

    double Vector3d::Length() const {
        return sqrt(_xyz[0] * _xyz[0] + _xyz[1] * _xyz[1] + _xyz[2] * _xyz[2]);
    }

    double Vector3d::SqrLength() const {
        return _xyz[0] * _xyz[0] + _xyz[1] * _xyz[1] + _xyz[2] * _xyz[2];
    }

    Vector3d &Vector3d::Normalize() {
        double length = Length();
        if (length > 0.0) {
            double invLength = (double) (1.0 / length);
            _xyz[0] *= invLength;
            _xyz[1] *= invLength;
            _xyz[2] *= invLength;
        }
        return *this;
    }

    Vector3d Vector3d::GetNormalized() const {
        return Clone().Normalize();
    }

    bool Vector3d::IsPerpendicularTo(const Vector3d &another) const {
        double dis = this->Dot(another);
        return dis * dis <= this->SqrLength() * another.SqrLength() * Constants::DOUBLE_EPS * Constants::DOUBLE_EPS;
    }

    Vector2d Vector3d::ToVector2d() const {
        return Vector2d(_xyz[0], _xyz[1]);
    }

    bool Vector3d::IsParallel(const Vector3d &another) const {
        return this->Cross(another).SqrLength() <=
               this->SqrLength() * another.SqrLength() * Constants::DOUBLE_EPS * Constants::DOUBLE_EPS;
    }

    double Vector3d::DiatanceTo(const Vector3d &another) const {
        return (*this - another).Length();
    }

    double Vector3d::SqDiatanceTo(const Vector3d &another) const {
        return ((*this) - another).SqrLength();
    }

    Vector3d &Vector3d::operator=(const Vector3d &d) {
        _xyz[0] = d._xyz[0];
        _xyz[1] = d._xyz[1];
        _xyz[2] = d._xyz[2];
        return *this;
    }

    Vector3d Vector3d::operator+(const Vector3d &v) const {
        return Vector3d(_xyz[0] + v._xyz[0], _xyz[1] + v._xyz[1], _xyz[2] + v._xyz[2]);
    }

    Vector3d Vector3d::operator-(const Vector3d &v) const {
        return Vector3d(_xyz[0] - v._xyz[0], _xyz[1] - v._xyz[1], _xyz[2] - v._xyz[2]);
    }

    double Vector3d::operator*(const Vector3d &v) const {
        return Dot(v);
    }

    Vector3d &Vector3d::operator*=(const double &d) {
        _xyz[0] *= d;
        _xyz[1] *= d;
        _xyz[2] *= d;
        return *this;
    }

    Vector3d &Vector3d::operator/=(const double &d) {
        assert(d != 0.0);
        _xyz[0] /= d;
        _xyz[1] /= d;
        _xyz[2] /= d;
        return *this;
    }

    Vector3d &Vector3d::operator+=(const Vector3d &vecSrc) {
        _xyz[0] += vecSrc._xyz[0];
        _xyz[1] += vecSrc._xyz[1];
        _xyz[2] += vecSrc._xyz[2];
        return *this;
    }

    Vector3d &Vector3d::operator-=(const Vector3d &vecSrc) {
        _xyz[0] -= vecSrc._xyz[0];
        _xyz[1] -= vecSrc._xyz[1];
        _xyz[2] -= vecSrc._xyz[2];
        return *this;
    }

    Vector3d Vector3d::operator-() const {
        return Vector3d(-_xyz[0], -_xyz[1], -_xyz[2]);
    }

}
