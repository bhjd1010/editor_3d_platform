#include "Matrix3d.h"
#include "MathUtils.h"
#include <math.h>
#include <algorithm>
#include <cassert>
#include <cstring>

namespace E3dMath {

    Matrix3d Matrix3d::CreateIdentity() {
        return Matrix3d();
    }

    Matrix3d Matrix3d::MakeTranslate(const Vector2d &t) {
        return MakeTranslate(t[0], t[1]);
    }

    Matrix3d Matrix3d::MakeTranslate(double tx, double ty) {
        Matrix3d m = CreateIdentity();
        m.SetTranslation(tx, ty);
        return m;
    }

    Matrix3d Matrix3d::MakeRotate(const Vector2d &Pos, double Angle) {
        double cosVal = cos(Angle);
        double sinVal = sin(Angle);

        double dx = (1 - cosVal) * Pos.X() + sinVal * Pos.Y();
        double dy = (1 - cosVal) * Pos.Y() - sinVal * Pos.X();

        Matrix3d m;
        m.m_data[0][0] = cosVal;
        m.m_data[0][1] = -sinVal;
        m.m_data[0][2] = dx;
        m.m_data[1][0] = sinVal;
        m.m_data[1][1] = cosVal;
        m.m_data[1][2] = dy;
        m.m_data[2][0] = 0.0;
        m.m_data[2][1] = 0.0;
        m.m_data[2][2] = 1.0;
        return m;
    }

    Matrix3d Matrix3d::MakeScale(double Scale) {
        return MakeScale(Vector2d(Scale, Scale));
    }

    Matrix3d Matrix3d::MakeScale(const Vector2d &Scale) {
        assert(Scale.X() != 0.0 && Scale.Y() != 0.0);
        Matrix3d m;;
        m.m_data[0][0] = Scale.X();
        m.m_data[1][1] = Scale.Y();
        return m;
    }

    Matrix3d::Matrix3d() {
        MakeIdentity();
    }

    Matrix3d::Matrix3d(const double(&array)[9]) {
        m_data[0][0] = array[0];
        m_data[0][1] = array[1];
        m_data[0][2] = array[2];
        m_data[1][0] = array[3];
        m_data[1][1] = array[4];
        m_data[1][2] = array[5];
        m_data[2][0] = array[6];
        m_data[2][1] = array[7];
        m_data[2][2] = array[8];
    }

    Matrix3d::Matrix3d(double a11, double a12, double a13,
                       double a21, double a22, double a23,
                       double a31, double a32, double a33) {
        m_data[0][0] = a11;
        m_data[0][1] = a12;
        m_data[0][2] = a13;
        m_data[1][0] = a21;
        m_data[1][1] = a22;
        m_data[1][2] = a23;
        m_data[2][0] = a31;
        m_data[2][1] = a32;
        m_data[2][2] = a33;
    }

    Matrix3d::Matrix3d(const Vector3d &v1, const Vector3d &v2, const Vector3d &v3) {
        m_data[0][0] = v1[0];
        m_data[1][0] = v1[1];
        m_data[2][0] = v1[2];
        m_data[0][1] = v2[0];
        m_data[1][1] = v2[1];
        m_data[2][1] = v2[2];
        m_data[0][2] = v3[0];
        m_data[1][2] = v3[1];
        m_data[2][2] = v3[2];
    }

    Matrix3d::Matrix3d(const Matrix3d &matrix) {
        *this = matrix;
    }

    bool Matrix3d::MakeIdentity() {
        MakeZero();
        m_data[0][0] = m_data[1][1] = m_data[2][2] = 1.0;
        return true;
    }

    void Matrix3d::MakeZero() {
        memset(m_data, 0, sizeof(double) * 9);
    }

    bool Matrix3d::MakeInverse() {
        Matrix3d inversedMat;
        if (!GetInverse(inversedMat)) {
            return false;
        }
        *this = inversedMat;
        return true;
    }

    void Matrix3d::MakeTranspose() {
        std::swap(m_data[0][1], m_data[1][0]);
        std::swap(m_data[0][2], m_data[2][0]);
        std::swap(m_data[1][2], m_data[2][1]);
    }

    bool Matrix3d::Set(const double(&array)[9]) {
        m_data[0][0] = array[0];
        m_data[0][1] = array[1];
        m_data[0][2] = array[2];
        m_data[1][0] = array[3];
        m_data[1][1] = array[4];
        m_data[1][2] = array[5];
        m_data[2][0] = array[6];
        m_data[2][1] = array[7];
        m_data[2][2] = array[8];
        return true;
    }

    bool Matrix3d::GetInverse(Matrix3d &inversedMat) const {
        double tmp[3][3] = {0.0};
        // Invert using cofactors.
        tmp[0][0] = m_data[1][1] * m_data[2][2] - m_data[1][2] * m_data[2][1];
        tmp[0][1] = m_data[0][2] * m_data[2][1] - m_data[0][1] * m_data[2][2];
        tmp[0][2] = m_data[0][1] * m_data[1][2] - m_data[0][2] * m_data[1][1];
        tmp[1][0] = m_data[1][2] * m_data[2][0] - m_data[1][0] * m_data[2][2];
        tmp[1][1] = m_data[0][0] * m_data[2][2] - m_data[0][2] * m_data[2][0];
        tmp[1][2] = m_data[0][2] * m_data[1][0] - m_data[0][0] * m_data[1][2];
        tmp[2][0] = m_data[1][0] * m_data[2][1] - m_data[1][1] * m_data[2][0];
        tmp[2][1] = m_data[0][1] * m_data[2][0] - m_data[0][0] * m_data[2][1];
        tmp[2][2] = m_data[0][0] * m_data[1][1] - m_data[0][1] * m_data[1][0];

        double sum = m_data[0][0] * tmp[0][0] + m_data[0][1] * tmp[1][0] + m_data[0][2] * tmp[2][0];
        if (MathUtils::IsEqual(sum, 0.0, Constants::DOUBLE_EPS))
            return false;

        double mInvDet = 1.0 / sum;

        inversedMat[0][0] = tmp[0][0] * mInvDet;
        inversedMat[0][1] = tmp[0][1] * mInvDet;
        inversedMat[0][2] = tmp[0][2] * mInvDet;
        inversedMat[1][0] = tmp[1][0] * mInvDet;
        inversedMat[1][1] = tmp[1][1] * mInvDet;
        inversedMat[1][2] = tmp[1][2] * mInvDet;
        inversedMat[2][0] = tmp[2][0] * mInvDet;
        inversedMat[2][1] = tmp[2][1] * mInvDet;
        inversedMat[2][2] = tmp[2][2] * mInvDet;

        return true;
    }

    Matrix3d Matrix3d::GetTranspose() const {
        return Matrix3d(
                m_data[0][0], m_data[1][0], m_data[2][0],
                m_data[0][1], m_data[1][1], m_data[2][1],
                m_data[0][2], m_data[1][2], m_data[2][2]
        );
    }

    bool Matrix3d::IsIdentity() const {
        double eps = 2.0 * Constants::DOUBLE_EPS;
        if (std::abs(m_data[0][0] - 1.0) > eps) {
            return false;
        }

        if (std::abs(m_data[1][1] - 1.0) > eps) {
            return false;
        }

        if (std::abs(m_data[2][2] - 1.0) > eps) {
            return false;
        }

        double sum =
                m_data[0][1] * m_data[0][1] + m_data[0][2] * m_data[0][2]
                + m_data[1][0] * m_data[1][0] + m_data[1][2] * m_data[1][2]
                + m_data[2][0] * m_data[2][0] + m_data[2][1] * m_data[2][1];

        if (sum > eps * eps) {
            return false;
        }

        return true;
    }

    double Matrix3d::Det() const {
        double a11 = m_data[0][0];
        double a12 = m_data[0][1];
        double a13 = m_data[0][2];
        double a21 = m_data[1][0];
        double a22 = m_data[1][1];
        double a23 = m_data[1][2];
        double a31 = m_data[2][0];
        double a32 = m_data[2][1];
        double a33 = m_data[2][2];

        double M11 = a22 * a33 - a32 * a23;
        double M21 = -(a12 * a33 - a32 * a13);
        double M31 = a12 * a23 - a22 * a13;

        return (a11 * M11 + a21 * M21 + a31 * M31);
    }

    bool Matrix3d::SetTranslation(const Vector2d &t) {
        m_data[0][2] = t[0];
        m_data[1][2] = t[1];
        return true;
    }

    bool Matrix3d::SetTranslation(double tx, double ty) {
        m_data[0][2] = tx;
        m_data[1][2] = ty;
        return true;
    }

    const Vector2d Matrix3d::GetTranslation() const {
        return Vector2d(m_data[0][2], m_data[1][2]);
    }

    void Matrix3d::GetRotationAxes(Vector2d &xAxis, Vector2d &yAxis) const {
        xAxis = Vector2d(m_data[0][0], m_data[1][0]);
        yAxis = Vector2d(m_data[0][1], m_data[1][1]);
    }

    Vector3d Matrix3d::PreMultiply(const Vector3d &src) const {
        double x = src[0] * m_data[0][0] + src[1] * m_data[1][0] + src[2] * m_data[2][0];
        double y = src[0] * m_data[0][1] + src[1] * m_data[1][1] + src[2] * m_data[2][1];
        double z = src[0] * m_data[0][2] + src[1] * m_data[1][2] + src[2] * m_data[2][2];
        return Vector3d(x, y, z);
    }

    Vector3d Matrix3d::Multiply(const Vector3d &v) {
        double x = m_data[0][0] * v[0] + m_data[0][1] * v[1] + m_data[0][2] * v[2];
        double y = m_data[1][0] * v[0] + m_data[1][1] * v[1] + m_data[1][2] * v[2];
        double z = m_data[2][0] * v[0] + m_data[2][1] * v[1] + m_data[2][2] * v[2];
        return Vector3d(x, y, z);
    }

    Matrix3d &Matrix3d::Multiply(const Matrix3d &m) {
        // Trivial cases
        if (m.IsIdentity())
            return *this;
        else if (IsIdentity())
            return (*this = m);

        Matrix3d tmp;

        tmp[0][0] = m_data[0][0] * m.m_data[0][0] + m_data[0][1] * m.m_data[1][0] + m_data[0][2] * m.m_data[2][0];
        tmp[0][1] = m_data[0][0] * m.m_data[0][1] + m_data[0][1] * m.m_data[1][1] + m_data[0][2] * m.m_data[2][1];
        tmp[0][2] = m_data[0][0] * m.m_data[0][2] + m_data[0][1] * m.m_data[1][2] + m_data[0][2] * m.m_data[2][2];

        tmp[1][0] = m_data[1][0] * m.m_data[0][0] + m_data[1][1] * m.m_data[1][0] + m_data[1][2] * m.m_data[2][0];
        tmp[1][1] = m_data[1][0] * m.m_data[0][1] + m_data[1][1] * m.m_data[1][1] + m_data[1][2] * m.m_data[2][1];
        tmp[1][2] = m_data[1][0] * m.m_data[0][2] + m_data[1][1] * m.m_data[1][2] + m_data[1][2] * m.m_data[2][2];

        tmp[2][0] = m_data[2][0] * m.m_data[0][0] + m_data[2][1] * m.m_data[1][0] + m_data[2][2] * m.m_data[2][0];
        tmp[2][1] = m_data[2][0] * m.m_data[0][1] + m_data[2][1] * m.m_data[1][1] + m_data[2][2] * m.m_data[2][1];
        tmp[2][2] = m_data[2][0] * m.m_data[0][2] + m_data[2][1] * m.m_data[1][2] + m_data[2][2] * m.m_data[2][2];


        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                m_data[i][j] = tmp[i][j];
            }
        }
        return *this;
    }

    Matrix3d &Matrix3d::PreMultiply(const Matrix3d &m) {
        // Trivial cases
        if (m.IsIdentity())
            return *this;
        else if (IsIdentity())
            return (*this = m);

        Matrix3d tmp;

        tmp[0][0] = m.m_data[0][0] * m_data[0][0] + m.m_data[0][1] * m_data[1][0] + m.m_data[0][2] * m_data[2][0];
        tmp[0][1] = m.m_data[0][0] * m_data[0][1] + m.m_data[0][1] * m_data[1][1] + m.m_data[0][2] * m_data[2][1];
        tmp[0][2] = m.m_data[0][0] * m_data[0][2] + m.m_data[0][1] * m_data[1][2] + m.m_data[0][2] * m_data[2][2];

        tmp[1][0] = m.m_data[1][0] * m_data[0][0] + m.m_data[1][1] * m_data[1][0] + m.m_data[1][2] * m_data[2][0];
        tmp[1][1] = m.m_data[1][0] * m_data[0][1] + m.m_data[1][1] * m_data[1][1] + m.m_data[1][2] * m_data[2][1];
        tmp[1][2] = m.m_data[1][0] * m_data[0][2] + m.m_data[1][1] * m_data[1][2] + m.m_data[1][2] * m_data[2][2];

        tmp[2][0] = m.m_data[2][0] * m_data[0][0] + m.m_data[2][1] * m_data[1][0] + m.m_data[2][2] * m_data[2][0];
        tmp[2][1] = m.m_data[2][0] * m_data[0][1] + m.m_data[2][1] * m_data[1][1] + m.m_data[2][2] * m_data[2][1];
        tmp[2][2] = m.m_data[2][0] * m_data[0][2] + m.m_data[2][1] * m_data[1][2] + m.m_data[2][2] * m_data[2][2];


        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                m_data[i][j] = tmp[i][j];
            }
        }
        return *this;
    }

    double *Matrix3d::operator[](int i) {
        assert(i >= 0 && i < 3);
        return m_data[i];
    }

    const double *Matrix3d::operator[](int i) const {
        assert(i >= 0 && i < 3);
        return m_data[i];
    }

    Matrix3d &Matrix3d::operator=(const Matrix3d &m) {
        std::memcpy(m_data, m.m_data, sizeof(double) * 9);
        return *this;
    }

    Matrix3d &Matrix3d::operator*=(const Matrix3d &matrix) {
        return Multiply(matrix);
    }

// =========================================================
    Matrix3d operator*(const Matrix3d &m1, const Matrix3d &m2) {
        Matrix3d m = m1;
        m *= m2;
        return m;
    }

    Vector3d operator*(const Matrix3d &m, const Vector3d &v) {
        Vector3d vRet;

        vRet[0] = m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2];
        vRet[1] = m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2];
        vRet[2] = m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2];

        return vRet;
    }

    Vector3d operator*(const Vector3d &v, const Matrix3d &m) {
        Vector3d vRet;

        vRet[0] = v[0] * m[0][0] + v[1] * m[1][0] + v[2] * m[2][0];
        vRet[1] = v[0] * m[0][1] + v[1] * m[1][1] + v[2] * m[2][1];
        vRet[2] = v[0] * m[0][2] + v[1] * m[1][2] + v[2] * m[2][2];

        return vRet;
    }

    bool operator==(const Matrix3d &m1, const Matrix3d &m2) {
        return (
                MathUtils::IsEqual(m1[0][0], m2[0][0]) &&
                MathUtils::IsEqual(m1[0][1], m2[0][1]) &&
                MathUtils::IsEqual(m1[0][2], m2[0][2]) &&

                MathUtils::IsEqual(m1[1][0], m2[1][0]) &&
                MathUtils::IsEqual(m1[1][1], m2[1][1]) &&
                MathUtils::IsEqual(m1[1][2], m2[1][2]) &&

                MathUtils::IsEqual(m1[2][0], m2[2][0]) &&
                MathUtils::IsEqual(m1[2][1], m2[2][1]) &&
                MathUtils::IsEqual(m1[2][2], m2[2][2])
        );
    }

    bool operator!=(const Matrix3d &m1, const Matrix3d &m2) {
        return !(m1 == m2);
    }

}