#include "Vector4d.h"
#include "MathUtils.h"
#include <math.h>
#include <cassert>

namespace E3dMath {

    const Vector4d &Vector4d::UnitX() {
        static Vector4d UnitX(1.0, 0.0, 0.0, 0.0);
        return UnitX;
    }

    const Vector4d &Vector4d::UnitY() {
        static Vector4d UnitY(0.0, 1.0, 0.0, 0.0);
        return UnitY;
    }

    const Vector4d &Vector4d::UnitZ() {
        static Vector4d UnitZ(0.0, 0.0, 1.0, 0.0);
        return UnitZ;
    }

    const Vector4d &Vector4d::UnitW() {
        static Vector4d UnitW(0.0, 0.0, 0.0, 1.0);
        return UnitW;
    }

    const Vector4d &Vector4d::Zero() {
        static Vector4d Zero(0.0, 0.0, 0.0, 0.0);
        return Zero;
    }

    Vector4d Vector4d::Create(double x, double y, double z, double w) {
        return Vector4d(x, y, z, w);
    }

    Vector4d Vector4d::CreateZero() {
        return Vector4d();
    }

    Vector4d operator*(const Vector4d &vec, const double d) {
        return Vector4d(vec.X() * d,
                        vec.Y() * d,
                        vec.Z() * d,
                        vec.W() * d);
    }

    Vector4d operator*(const double d, const Vector4d &vec) {
        return vec * d;
    }

    double operator*(const Vector4d &v1, const Vector4d &v2) {
        return v1.Dot(v2);
    }

    Vector4d operator/(const Vector4d &vec, const double d) {
        assert(!MathUtils::IsZero(d));
        return Vector4d(vec.X() / d,
                        vec.Y() / d,
                        vec.Z() / d,
                        vec.W() / d);
    }

    Vector4d operator+(const Vector4d &v1, const Vector4d &v2) {
        return Vector4d(v1.X() + v2.X(),
                        v1.Y() + v2.Y(),
                        v1.Z() + v2.Z(),
                        v1.W() + v2.W());
    }

    Vector4d operator-(const Vector4d &v1, const Vector4d &v2) {
        return Vector4d(v1.X() - v2.X(),
                        v1.Y() - v2.Y(),
                        v1.Z() - v2.Z(),
                        v1.W() - v2.W());
    }

    bool operator==(const Vector4d &v1, const Vector4d &v2) {
        return (MathUtils::IsZero(v1.X() - v2.X())
                && MathUtils::IsZero(v1.Y() - v2.Y())
                && MathUtils::IsZero(v1.Z() - v2.Z())
                && MathUtils::IsZero(v1.W() - v2.W()));
    }

    bool operator!=(const Vector4d &v1, const Vector4d &v2) {
        return !(v1 == v2);
    }

    Vector4d::Vector4d() {
        m_xyzw[0] = m_xyzw[1] = m_xyzw[2] = m_xyzw[3] = 0;
    }

    Vector4d::Vector4d(double (&vec)[4]) {
        m_xyzw[0] = vec[0];
        m_xyzw[1] = vec[1];
        m_xyzw[2] = vec[2];
        m_xyzw[3] = vec[3];
    }

    Vector4d::Vector4d(double x, double y, double z, double w) {
        m_xyzw[0] = x;
        m_xyzw[1] = y;
        m_xyzw[2] = z;
        m_xyzw[3] = w;
    }

    Vector4d::Vector4d(const Vector4d &src) {
        m_xyzw[0] = src.m_xyzw[0];
        m_xyzw[1] = src.m_xyzw[1];
        m_xyzw[2] = src.m_xyzw[2];
        m_xyzw[3] = src.m_xyzw[3];
    }

    bool Vector4d::Set(double x, double y, double z, double w) {
        m_xyzw[0] = x;
        m_xyzw[1] = y;
        m_xyzw[2] = z;
        m_xyzw[3] = w;
        return true;
    }

    bool Vector4d::SetX(double x) {
        m_xyzw[0] = x;
        return true;
    }

    bool Vector4d::SetY(double y) {
        m_xyzw[1] = y;
        return true;
    }

    bool Vector4d::SetZ(double z) {
        m_xyzw[2] = z;
        return true;
    }

    bool Vector4d::SetW(double w) {
        m_xyzw[3] = w;
        return true;
    }

    double Vector4d::X() const {
        return m_xyzw[0];
    }

    double Vector4d::Y() const {
        return m_xyzw[1];
    }

    double Vector4d::Z() const {
        return m_xyzw[2];
    }

    double Vector4d::W() const {
        return m_xyzw[3];
    }

    double &Vector4d::X() {
        return m_xyzw[0];
    }

    double &Vector4d::Y() {
        return m_xyzw[1];
    }

    double &Vector4d::Z() {
        return m_xyzw[2];
    }

    double &Vector4d::W() {
        return m_xyzw[3];
    }

    double &Vector4d::operator[](int nIndex) {
        assert(nIndex >= 0 && nIndex < 4);
        return m_xyzw[nIndex];
    }

    double Vector4d::operator[](int nIndex) const {
        assert(nIndex >= 0 && nIndex < 4);
        return m_xyzw[nIndex];
    }

    bool Vector4d::IsZero(double typeTol) const {
        return SqrLength() <= typeTol * typeTol;
    }

    bool Vector4d::IsUnit(double typeTol) const {
        return fabs(SqrLength() - 1) <= typeTol * typeTol;
    }

    double Vector4d::Length() const {
        return sqrt(SqrLength());
    }

    double Vector4d::SqrLength() const {
        return (m_xyzw[0] * m_xyzw[0]) + (m_xyzw[1] * m_xyzw[1])
               + (m_xyzw[2] * m_xyzw[2]) + (m_xyzw[3] * m_xyzw[3]);
    }

    Vector4d Vector4d::Clone() const {
        return Vector4d(*this);
    }

    Vector4d &Vector4d::Normalize() {
        double magnitude = Length();

        if (!MathUtils::IsZero(magnitude)) {
            (*this) *= 1.0 / magnitude;
        } else {
            magnitude = 0;
            m_xyzw[0] = 0;
            m_xyzw[1] = 0;
            m_xyzw[2] = 0;
            m_xyzw[3] = 0;
        }
        return *this;
    }

    Vector4d Vector4d::GetNormalized() {
        return Clone().Normalize();
    }

    double Vector4d::Dot(const Vector4d &vec) const {
        return (m_xyzw[0] * vec.m_xyzw[0] + m_xyzw[1] * vec.m_xyzw[1] +
                m_xyzw[2] * vec.m_xyzw[2] + m_xyzw[3] * vec.m_xyzw[3]);
    }

    Vector4d &Vector4d::operator*=(const double d) {
        m_xyzw[0] *= d;
        m_xyzw[1] *= d;
        m_xyzw[2] *= d;
        m_xyzw[3] *= d;

        return (*this);
    }

    Vector4d &Vector4d::operator/=(const double d) {
        assert(MathUtils::IsZero(d));

        double inv = 1.0f / d;
        m_xyzw[0] *= inv;
        m_xyzw[1] *= inv;
        m_xyzw[2] *= inv;
        m_xyzw[3] *= inv;

        return (*this);
    }

    Vector4d &Vector4d::operator+=(const Vector4d &vec) {
        m_xyzw[0] += vec.X();
        m_xyzw[1] += vec.Y();
        m_xyzw[2] += vec.Z();
        m_xyzw[3] += vec.W();

        return (*this);
    }

    Vector4d &Vector4d::operator-=(const Vector4d &vec) {
        m_xyzw[0] -= vec.m_xyzw[0];
        m_xyzw[1] -= vec.m_xyzw[1];
        m_xyzw[2] -= vec.m_xyzw[2];
        m_xyzw[3] -= vec.m_xyzw[3];

        return (*this);
    }

    Vector4d Vector4d::operator-() const {
        return Vector4d(-m_xyzw[0], -m_xyzw[1], -m_xyzw[2], -m_xyzw[3]);
    }

}