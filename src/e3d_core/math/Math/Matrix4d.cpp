#include "Matrix4d.h"
#include "MathUtils.h"
#include <math.h>
#include <algorithm>
#include <cassert>
#include <cstring>
#include "Matrix3d.h"

namespace E3dMath {

    Matrix4d Matrix4d::CreateIdentity() {
        return Matrix4d();
    }

    Matrix4d::Matrix4d() {
        MakeIdentity();
    }

    Matrix4d::Matrix4d(double a11, double a12, double a13, double a14,
                       double a21, double a22, double a23, double a24,
                       double a31, double a32, double a33, double a34,
                       double a41, double a42, double a43, double a44) {
        m_data[0][0] = a11;
        m_data[0][1] = a12;
        m_data[0][2] = a13;
        m_data[0][3] = a14;
        m_data[1][0] = a21;
        m_data[1][1] = a22;
        m_data[1][2] = a23;
        m_data[1][3] = a24;
        m_data[2][0] = a31;
        m_data[2][1] = a32;
        m_data[2][2] = a33;
        m_data[2][3] = a34;
        m_data[3][0] = a41;
        m_data[3][1] = a42;
        m_data[3][2] = a43;
        m_data[3][3] = a44;
    }

    Matrix4d::Matrix4d(const Vector3d &c1, const Vector3d &c2, const Vector3d &c3, const Vector3d &c4) {
        m_data[0][0] = c1[0];
        m_data[0][1] = c2[0];
        m_data[0][2] = c3[0];
        m_data[0][3] = c4[0];
        m_data[1][0] = c1[1];
        m_data[1][1] = c2[1];
        m_data[1][2] = c3[1];
        m_data[1][3] = c4[1];
        m_data[2][0] = c1[2];
        m_data[2][1] = c2[2];
        m_data[2][2] = c3[2];
        m_data[2][3] = c4[2];
        m_data[3][0] = 0;
        m_data[3][1] = 0;
        m_data[3][2] = 0;
        m_data[3][3] = 1;
    }

    Matrix4d::Matrix4d(const Vector4d &c1, const Vector4d &c2, const Vector4d &c3,
                       const Vector4d &c4) {
        m_data[0][0] = c1[0];
        m_data[0][1] = c2[0];
        m_data[0][2] = c3[0];
        m_data[0][3] = c4[0];
        m_data[1][0] = c1[1];
        m_data[1][1] = c2[1];
        m_data[1][2] = c3[1];
        m_data[1][3] = c4[1];
        m_data[2][0] = c1[2];
        m_data[2][1] = c2[2];
        m_data[2][2] = c3[2];
        m_data[2][3] = c4[2];
        m_data[3][0] = c1[3];
        m_data[3][1] = c2[3];
        m_data[3][2] = c3[3];
        m_data[3][3] = c4[3];
    }

    Matrix4d::Matrix4d(const Matrix4d &matrix) {
        *this = matrix;
    }

    bool Matrix4d::Set(
            double a11, double a12, double a13, double a14,
            double a21, double a22, double a23, double a24,
            double a31, double a32, double a33, double a34,
            double a41, double a42, double a43, double a44) {
        m_data[0][0] = a11;
        m_data[0][1] = a12;
        m_data[0][2] = a13;
        m_data[0][3] = a14;

        m_data[1][0] = a21;
        m_data[1][1] = a22;
        m_data[1][2] = a23;
        m_data[1][3] = a24;

        m_data[2][0] = a31;
        m_data[2][1] = a32;
        m_data[2][2] = a33;
        m_data[2][3] = a34;

        m_data[3][0] = a41;
        m_data[3][1] = a42;
        m_data[3][2] = a43;
        m_data[3][3] = a44;

        return true;
    }

    bool Matrix4d::Set(double m[4][4]) {
        std::memcpy(m_data, m, sizeof(double) * 16);
        return true;
    }

    double *Matrix4d::operator[](int i) {
        return m_data[i];
    }

    const double *Matrix4d::operator[](int i) const {
        return m_data[i];
    }

    bool Matrix4d::MakeIdentity() {
        memset(m_data, 0, sizeof(double) * 16);
        m_data[0][0] = m_data[1][1] = m_data[2][2] = m_data[3][3] = 1.0;
        return true;
    }

    bool Matrix4d::MakeRotate(const Vector3d &pos, const Vector3d &dir, double radian) {
        double a = dir.X();
        double b = dir.Y();
        double c = dir.Z();

        double angleCos = cos(radian);
        double angleSin = sin(radian);

        if (MathUtils::IsZero(b * b + c * c)) {
            if (a < 0) {
                angleCos = cos((double) (Constants::MATH_2PI - radian));
                angleSin = sin((double) (Constants::MATH_2PI - radian));
            }

            double dy = pos.Y() * ((double) 1.0 - angleCos) + pos.Z() * angleSin;
            double dz = pos.Z() * ((double) 1.0 - angleCos) - pos.Y() * angleSin;

            m_data[0][0] = 1.0;
            m_data[0][1] = 0.0;
            m_data[0][2] = 0.0;
            m_data[0][3] = 0.0;
            m_data[1][0] = 0.0;
            m_data[1][1] = angleCos;
            m_data[1][2] = angleSin;
            m_data[1][3] = 0.0;
            m_data[2][0] = 0.0;
            m_data[2][1] = -angleSin;
            m_data[2][2] = angleCos;
            m_data[2][3] = 0.0;
            m_data[3][0] = 0.0;
            m_data[3][1] = dy;
            m_data[3][2] = dz;
            m_data[3][3] = 1.0;
            this->MakeTranspose();
            return true;
        }

        if (MathUtils::IsZero(a * a + c * c))//绕Y轴旋转
        {
            if (b < 0) {
                angleCos = cos(((double) Constants::MATH_2PI) - radian);
                angleSin = sin(((double) Constants::MATH_2PI) - radian);
            }

            double dx = pos.X() * ((double) 1.0 - angleCos) - pos.Z() * angleSin;
            double dz = pos.Z() * ((double) 1.0 - angleCos) + pos.X() * angleSin;

            m_data[0][0] = angleCos;
            m_data[0][1] = 0.0;
            m_data[0][2] = -angleSin;
            m_data[0][3] = 0.0;
            m_data[1][0] = 0.0;
            m_data[1][1] = 1.0;
            m_data[1][2] = 0.0;
            m_data[1][3] = 0.0;
            m_data[2][0] = angleSin;
            m_data[2][1] = 0.0;
            m_data[2][2] = angleCos;
            m_data[2][3] = 0.0;
            m_data[3][0] = dx;
            m_data[3][1] = 0.0;
            m_data[3][2] = dz;
            m_data[3][3] = 1.0;
            this->MakeTranspose();
            return true;
        }

        if (MathUtils::IsZero(a * a + b * b))//绕Z轴旋转
        {
            if (c < 0) {
                angleCos = cos(((double) Constants::MATH_2PI) - radian);
                angleSin = sin(((double) Constants::MATH_2PI) - radian);
            }

            double dx = pos.X() * ((double) 1.0 - angleCos) + pos.Y() * angleSin;
            double dy = pos.Y() * ((double) 1.0 - angleCos) - pos.X() * angleSin;

            m_data[0][0] = angleCos;
            m_data[0][1] = angleSin;
            m_data[0][2] = 0.0;
            m_data[0][3] = 0.0;
            m_data[1][0] = -angleSin;
            m_data[1][1] = angleCos;
            m_data[1][2] = 0.0;
            m_data[1][3] = 0.0;
            m_data[2][0] = 0.0;
            m_data[2][1] = 0.0;
            m_data[2][2] = 1.0;
            m_data[2][3] = 0.0;
            m_data[3][0] = dx;
            m_data[3][1] = dy;
            m_data[3][2] = 0.0;
            m_data[3][3] = 1.0;
            this->MakeTranspose();
            return true;
        }

        double v = sqrt(b * b + c * c);
        double s = sqrt(a * a + b * b + c * c);

        Matrix4d matTa;
        matTa[3][0] = -pos.X();
        matTa[3][1] = -pos.Y();
        matTa[3][2] = -pos.Z();
        matTa[3][3] = (double) 1.0;

        Matrix4d inverseMatTa;
        inverseMatTa[3][0] = pos.X();
        inverseMatTa[3][1] = pos.Y();
        inverseMatTa[3][2] = pos.Z();
        inverseMatTa[3][3] = (double) 1.0;

        double cos1 = c / v;
        double sin1 = b / v;

        Matrix4d matRx;
        matRx[1][1] = cos1;
        matRx[1][2] = sin1;
        matRx[2][1] = -sin1;
        matRx[2][2] = cos1;

        Matrix4d inverseMatRx;

        inverseMatRx[1][1] = cos1;
        inverseMatRx[1][2] = -sin1;
        inverseMatRx[2][1] = sin1;
        inverseMatRx[2][2] = cos1;

        double cos2 = v / s;
        double sin2 = a / s;

        Matrix4d matRy;
        matRy[0][0] = cos2;
        matRy[0][2] = sin2;
        matRy[2][0] = -sin2;
        matRy[2][2] = cos2;

        Matrix4d inverseMatRy;

        inverseMatRy[0][0] = cos2;
        inverseMatRy[0][2] = -sin2;
        inverseMatRy[2][0] = sin2;
        inverseMatRy[2][2] = cos2;

        Matrix4d matRz;
        matRz[0][0] = angleCos;
        matRz[0][1] = angleSin;
        matRz[1][0] = -angleSin;
        matRz[1][1] = angleCos;

        *this = matTa * matRx;
        *this *= matRy;
        *this *= matRz;
        *this *= inverseMatRy;
        *this *= inverseMatRx;
        *this *= inverseMatTa;
        this->MakeTranspose();
        return true;
    }

    bool Matrix4d::MakeTranslate(const Vector3d &t) {
        MakeIdentity();
        m_data[0][3] = t[0];
        m_data[1][3] = t[1];
        m_data[2][3] = t[2];
        return true;
    }

    bool Matrix4d::MakeInverse() {
        double tmp[12] = {0.0};
        double dst[16] = {0.0};

        MakeTranspose();

        tmp[0] = m_data[2][2] * m_data[3][3];
        tmp[1] = m_data[3][2] * m_data[2][3];
        tmp[2] = m_data[1][2] * m_data[3][3];
        tmp[3] = m_data[3][2] * m_data[1][3];
        tmp[4] = m_data[1][2] * m_data[2][3];
        tmp[5] = m_data[2][2] * m_data[1][3];
        tmp[6] = m_data[0][2] * m_data[3][3];
        tmp[7] = m_data[3][2] * m_data[0][3];
        tmp[8] = m_data[0][2] * m_data[2][3];
        tmp[9] = m_data[2][2] * m_data[0][3];
        tmp[10] = m_data[0][2] * m_data[1][3];
        tmp[11] = m_data[1][2] * m_data[0][3];

        dst[0] = tmp[0] * m_data[1][1] + tmp[3] * m_data[2][1] + tmp[4] * m_data[3][1];
        dst[0] -= tmp[1] * m_data[1][1] + tmp[2] * m_data[2][1] + tmp[5] * m_data[3][1];
        dst[1] = tmp[1] * m_data[0][1] + tmp[6] * m_data[2][1] + tmp[9] * m_data[3][1];
        dst[1] -= tmp[0] * m_data[0][1] + tmp[7] * m_data[2][1] + tmp[8] * m_data[3][1];
        dst[2] = tmp[2] * m_data[0][1] + tmp[7] * m_data[1][1] + tmp[10] * m_data[3][1];
        dst[2] -= tmp[3] * m_data[0][1] + tmp[6] * m_data[1][1] + tmp[11] * m_data[3][1];
        dst[3] = tmp[5] * m_data[0][1] + tmp[8] * m_data[1][1] + tmp[11] * m_data[2][1];
        dst[3] -= tmp[4] * m_data[0][1] + tmp[9] * m_data[1][1] + tmp[10] * m_data[2][1];
        dst[4] = tmp[1] * m_data[1][0] + tmp[2] * m_data[2][0] + tmp[5] * m_data[3][0];
        dst[4] -= tmp[0] * m_data[1][0] + tmp[3] * m_data[2][0] + tmp[4] * m_data[3][0];
        dst[5] = tmp[0] * m_data[0][0] + tmp[7] * m_data[2][0] + tmp[8] * m_data[3][0];
        dst[5] -= tmp[1] * m_data[0][0] + tmp[6] * m_data[2][0] + tmp[9] * m_data[3][0];
        dst[6] = tmp[3] * m_data[0][0] + tmp[6] * m_data[1][0] + tmp[11] * m_data[3][0];
        dst[6] -= tmp[2] * m_data[0][0] + tmp[7] * m_data[1][0] + tmp[10] * m_data[3][0];
        dst[7] = tmp[4] * m_data[0][0] + tmp[9] * m_data[1][0] + tmp[10] * m_data[2][0];
        dst[7] -= tmp[5] * m_data[0][0] + tmp[8] * m_data[1][0] + tmp[11] * m_data[2][0];

        tmp[0] = m_data[2][0] * m_data[3][1];
        tmp[1] = m_data[3][0] * m_data[2][1];
        tmp[2] = m_data[1][0] * m_data[3][1];
        tmp[3] = m_data[3][0] * m_data[1][1];
        tmp[4] = m_data[1][0] * m_data[2][1];
        tmp[5] = m_data[2][0] * m_data[1][1];
        tmp[6] = m_data[0][0] * m_data[3][1];
        tmp[7] = m_data[3][0] * m_data[0][1];
        tmp[8] = m_data[0][0] * m_data[2][1];
        tmp[9] = m_data[2][0] * m_data[0][1];
        tmp[10] = m_data[0][0] * m_data[1][1];
        tmp[11] = m_data[1][0] * m_data[0][1];

        dst[8] = tmp[0] * m_data[1][3] + tmp[3] * m_data[2][3] + tmp[4] * m_data[3][3];
        dst[8] -= tmp[1] * m_data[1][3] + tmp[2] * m_data[2][3] + tmp[5] * m_data[3][3];
        dst[9] = tmp[1] * m_data[0][3] + tmp[6] * m_data[2][3] + tmp[9] * m_data[3][3];
        dst[9] -= tmp[0] * m_data[0][3] + tmp[7] * m_data[2][3] + tmp[8] * m_data[3][3];
        dst[10] = tmp[2] * m_data[0][3] + tmp[7] * m_data[1][3] + tmp[10] * m_data[3][3];
        dst[10] -= tmp[3] * m_data[0][3] + tmp[6] * m_data[1][3] + tmp[11] * m_data[3][3];
        dst[11] = tmp[5] * m_data[0][3] + tmp[8] * m_data[1][3] + tmp[11] * m_data[2][3];
        dst[11] -= tmp[4] * m_data[0][3] + tmp[9] * m_data[1][3] + tmp[10] * m_data[2][3];
        dst[12] = tmp[2] * m_data[2][2] + tmp[5] * m_data[3][2] + tmp[1] * m_data[1][2];
        dst[12] -= tmp[4] * m_data[3][2] + tmp[0] * m_data[1][2] + tmp[3] * m_data[2][2];
        dst[13] = tmp[8] * m_data[3][2] + tmp[0] * m_data[0][2] + tmp[7] * m_data[2][2];
        dst[13] -= tmp[6] * m_data[2][2] + tmp[9] * m_data[3][2] + tmp[1] * m_data[0][2];
        dst[14] = tmp[6] * m_data[1][2] + tmp[11] * m_data[3][2] + tmp[3] * m_data[0][2];
        dst[14] -= tmp[10] * m_data[3][2] + tmp[2] * m_data[0][2] + tmp[7] * m_data[1][2];
        dst[15] = tmp[10] * m_data[2][2] + tmp[4] * m_data[0][2] + tmp[9] * m_data[1][2];
        dst[15] -= tmp[8] * m_data[1][2] + tmp[11] * m_data[2][2] + tmp[5] * m_data[0][2];

        double d = m_data[0][0] * dst[0] + m_data[1][0] * dst[1] + m_data[2][0] * dst[2] + m_data[3][0] * dst[3];

        //double类型取值范围内有效即可
        if (MathUtils::IsLessThan(1.0 / d, Constants::MATH_INFINITY)) {
            double det = (double) 1.0 / d;

            m_data[0][0] = dst[0] * det;
            m_data[0][1] = dst[4] * det;
            m_data[0][2] = dst[8] * det;
            m_data[0][3] = dst[12] * det;
            m_data[1][0] = dst[1] * det;
            m_data[1][1] = dst[5] * det;
            m_data[1][2] = dst[9] * det;
            m_data[1][3] = dst[13] * det;
            m_data[2][0] = dst[2] * det;
            m_data[2][1] = dst[6] * det;
            m_data[2][2] = dst[10] * det;
            m_data[2][3] = dst[14] * det;
            m_data[3][0] = dst[3] * det;
            m_data[3][1] = dst[7] * det;
            m_data[3][2] = dst[11] * det;
            m_data[3][3] = dst[15] * det;
            return true;
        }
        return false;
    }

    bool Matrix4d::GetInverse(Matrix4d &inversedMat) const {
        inversedMat = *this;
        return inversedMat.MakeInverse();
    }

    Matrix4d Matrix4d::GetTranspose() const {
        return Matrix4d(
                m_data[0][0], m_data[1][0], m_data[2][0], m_data[3][0],
                m_data[0][1], m_data[1][1], m_data[2][1], m_data[3][1],
                m_data[0][2], m_data[1][2], m_data[2][2], m_data[3][2],
                m_data[0][3], m_data[1][3], m_data[2][3], m_data[3][3]
        );
    }

    Vector3d Matrix4d::GetTranslation() const {
        return Vector3d(m_data[0][3], m_data[1][3], m_data[2][3]);
    }

    Matrix3d Matrix4d::GetRotation() const {
        Matrix3d mat3;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                mat3[i][j] = m_data[i][j];
            }
        }
        return mat3;
    }

    bool Matrix4d::IsIdentity() const {
        auto eps = Constants::DOUBLE_EPS;
        if (std::abs(m_data[0][0] - 1.0) > eps) {
            return false;
        }

        if (std::abs(m_data[1][1] - 1.0) > eps) {
            return false;
        }

        if (std::abs(m_data[2][2] - 1.0) > eps) {
            return false;
        }

        if (std::abs(m_data[3][3] - 1.0) > eps) {
            return false;
        }

        auto sum =
                m_data[0][1] * m_data[0][1] + m_data[0][2] * m_data[0][2] + m_data[0][3] * m_data[0][3]
                + m_data[1][0] * m_data[1][0] + m_data[1][2] * m_data[1][2] + m_data[1][3] * m_data[1][3]
                + m_data[2][0] * m_data[2][0] + m_data[2][1] * m_data[2][1] + m_data[2][3] * m_data[2][3]
                + m_data[3][0] * m_data[3][0] + m_data[3][1] * m_data[3][1] + m_data[3][2] * m_data[3][2];

        if (sum > eps * eps) {
            return false;
        }

        return true;
    }

    double Matrix4d::Det(int r1, int r2, int r3, int c1, int c2, int c3) const {
        double a11 = m_data[r1][c1];
        double a12 = m_data[r1][c2];
        double a13 = m_data[r1][c3];
        double a21 = m_data[r2][c1];
        double a22 = m_data[r2][c2];
        double a23 = m_data[r2][c3];
        double a31 = m_data[r3][c1];
        double a32 = m_data[r3][c2];
        double a33 = m_data[r3][c3];

        double M11 = a22 * a33 - a32 * a23;
        double M21 = -(a12 * a33 - a32 * a13);
        double M31 = a12 * a23 - a22 * a13;
        return (a11 * M11 + a21 * M21 + a31 * M31);
    }

    double Matrix4d::Det() const {
        double det = double(0.0);
        det += m_data[0][0] * Det(1, 2, 3, 1, 2, 3);
        det -= m_data[1][0] * Det(0, 2, 3, 1, 2, 3);
        det += m_data[2][0] * Det(0, 1, 3, 1, 2, 3);
        det -= m_data[3][0] * Det(0, 1, 2, 1, 2, 3);
        return det;
    }

    void Matrix4d::MakeZero() {
        memset(m_data, 0, sizeof(double) * 16);
    }

    bool Matrix4d::GetRotationAxes(Vector3d &xAxis, Vector3d &yAxis, Vector3d &zAxis) const {
        xAxis = Vector3d(m_data[0][0], m_data[1][0], m_data[2][0]);
        yAxis = Vector3d(m_data[0][1], m_data[1][1], m_data[2][1]);
        zAxis = Vector3d(m_data[0][2], m_data[1][2], m_data[2][2]);
        return true;
    }

    bool Matrix4d::SetRotationAndTranslation(const Matrix3d &r, const Vector3d &t) {
        m_data[0][0] = r[0][0];
        m_data[0][1] = r[0][1];
        m_data[0][2] = r[0][2];
        m_data[1][0] = r[1][0];
        m_data[1][1] = r[1][1];
        m_data[1][2] = r[1][2];
        m_data[2][0] = r[2][0];
        m_data[2][1] = r[2][1];
        m_data[2][2] = r[2][2];

        m_data[0][3] = t.X();
        m_data[1][3] = t.Y();
        m_data[2][3] = t.Z();
        return true;
    }

    void Matrix4d::MakeTranspose() {
        std::swap(m_data[0][1], m_data[1][0]);
        std::swap(m_data[0][2], m_data[2][0]);
        std::swap(m_data[0][3], m_data[3][0]);
        std::swap(m_data[1][2], m_data[2][1]);
        std::swap(m_data[1][3], m_data[3][1]);
        std::swap(m_data[2][3], m_data[3][2]);
    }

    void Matrix4d::MakeTranslate(double tx, double ty, double tz) {
        MakeIdentity();
        m_data[0][3] = tx;
        m_data[1][3] = ty;
        m_data[2][3] = tz;
    }

    Vector3d Matrix4d::GetScale() const {
        Vector3d vCols[3] = {
                Vector3d(m_data[0][0], m_data[0][1], m_data[0][2]),
                Vector3d(m_data[1][0], m_data[1][1], m_data[1][2]),
                Vector3d(m_data[2][0], m_data[2][1], m_data[2][2])
        };

        return Vector3d(vCols[0].Length(), vCols[1].Length(), vCols[2].Length());
    }

    void Matrix4d::MakeScale(const Vector3d &pos, double scale) {
        assert(scale > 0.0);

        MakeIdentity();

        m_data[0][0] = scale;
        m_data[1][1] = scale;
        m_data[2][2] = scale;
        m_data[0][3] = pos.X() * (1.0 - scale);
        m_data[1][3] = pos.Y() * (1.0 - scale);
        m_data[2][3] = pos.Z() * (1.0 - scale);
    }

    void Matrix4d::MakeScale(const Vector3d &pos, const Vector3d &scales) {
        assert(scales.X() != 0.0 && scales.Y() != 0.0 && scales.Z() != 0);

        MakeIdentity();

        m_data[0][0] = scales.X();
        m_data[1][1] = scales.Y();
        m_data[2][2] = scales.Z();
        m_data[0][3] = pos.X() * (1.0 - scales.X());
        m_data[1][3] = pos.Y() * (1.0 - scales.Y());
        m_data[2][3] = pos.Z() * (1.0 - scales.Z());
    }

    Matrix4d &Matrix4d::operator*=(const Matrix4d &m) {
        // Trivial cases
        if (m.IsIdentity()) {
            return *this;
        } else if (IsIdentity()) {
            return (*this = m);
        }

        double tmp[4][4] = {0.0};

        tmp[0][0] = m_data[0][0] * m.m_data[0][0] + m_data[0][1] * m.m_data[1][0] + m_data[0][2] * m.m_data[2][0] +
                    m_data[0][3] * m.m_data[3][0];
        tmp[0][1] = m_data[0][0] * m.m_data[0][1] + m_data[0][1] * m.m_data[1][1] + m_data[0][2] * m.m_data[2][1] +
                    m_data[0][3] * m.m_data[3][1];
        tmp[0][2] = m_data[0][0] * m.m_data[0][2] + m_data[0][1] * m.m_data[1][2] + m_data[0][2] * m.m_data[2][2] +
                    m_data[0][3] * m.m_data[3][2];
        tmp[0][3] = m_data[0][0] * m.m_data[0][3] + m_data[0][1] * m.m_data[1][3] + m_data[0][2] * m.m_data[2][3] +
                    m_data[0][3] * m.m_data[3][3];
        tmp[1][0] = m_data[1][0] * m.m_data[0][0] + m_data[1][1] * m.m_data[1][0] + m_data[1][2] * m.m_data[2][0] +
                    m_data[1][3] * m.m_data[3][0];
        tmp[1][1] = m_data[1][0] * m.m_data[0][1] + m_data[1][1] * m.m_data[1][1] + m_data[1][2] * m.m_data[2][1] +
                    m_data[1][3] * m.m_data[3][1];
        tmp[1][2] = m_data[1][0] * m.m_data[0][2] + m_data[1][1] * m.m_data[1][2] + m_data[1][2] * m.m_data[2][2] +
                    m_data[1][3] * m.m_data[3][2];
        tmp[1][3] = m_data[1][0] * m.m_data[0][3] + m_data[1][1] * m.m_data[1][3] + m_data[1][2] * m.m_data[2][3] +
                    m_data[1][3] * m.m_data[3][3];
        tmp[2][0] = m_data[2][0] * m.m_data[0][0] + m_data[2][1] * m.m_data[1][0] + m_data[2][2] * m.m_data[2][0] +
                    m_data[2][3] * m.m_data[3][0];
        tmp[2][1] = m_data[2][0] * m.m_data[0][1] + m_data[2][1] * m.m_data[1][1] + m_data[2][2] * m.m_data[2][1] +
                    m_data[2][3] * m.m_data[3][1];
        tmp[2][2] = m_data[2][0] * m.m_data[0][2] + m_data[2][1] * m.m_data[1][2] + m_data[2][2] * m.m_data[2][2] +
                    m_data[2][3] * m.m_data[3][2];
        tmp[2][3] = m_data[2][0] * m.m_data[0][3] + m_data[2][1] * m.m_data[1][3] + m_data[2][2] * m.m_data[2][3] +
                    m_data[2][3] * m.m_data[3][3];
        tmp[3][0] = m_data[3][0] * m.m_data[0][0] + m_data[3][1] * m.m_data[1][0] + m_data[3][2] * m.m_data[2][0] +
                    m_data[3][3] * m.m_data[3][0];
        tmp[3][1] = m_data[3][0] * m.m_data[0][1] + m_data[3][1] * m.m_data[1][1] + m_data[3][2] * m.m_data[2][1] +
                    m_data[3][3] * m.m_data[3][1];
        tmp[3][2] = m_data[3][0] * m.m_data[0][2] + m_data[3][1] * m.m_data[1][2] + m_data[3][2] * m.m_data[2][2] +
                    m_data[3][3] * m.m_data[3][2];
        tmp[3][3] = m_data[3][0] * m.m_data[0][3] + m_data[3][1] * m.m_data[1][3] + m_data[3][2] * m.m_data[2][3] +
                    m_data[3][3] * m.m_data[3][3];

        Set(tmp);

        return *this;
    }

    Matrix4d &Matrix4d::operator=(const Matrix4d &m) {
        std::memcpy(m_data, m.m_data, sizeof(double) * 16);
        return *this;
    }

    Matrix4d &Matrix4d::PreMultiply(const Matrix4d &m) {
        // Trivial cases
        if (m.IsIdentity()) {
            return *this;
        } else if (IsIdentity()) {
            return (*this = m);
        }

        double tmp[4][4] = {0.0};

        tmp[0][0] = m.m_data[0][0] * m_data[0][0] + m.m_data[0][1] * m_data[1][0] + m.m_data[0][2] * m_data[2][0] +
                    m.m_data[0][3] * m_data[3][0];
        tmp[0][1] = m.m_data[0][0] * m_data[0][1] + m.m_data[0][1] * m_data[1][1] + m.m_data[0][2] * m_data[2][1] +
                    m.m_data[0][3] * m_data[3][1];
        tmp[0][2] = m.m_data[0][0] * m_data[0][2] + m.m_data[0][1] * m_data[1][2] + m.m_data[0][2] * m_data[2][2] +
                    m.m_data[0][3] * m_data[3][2];
        tmp[0][3] = m.m_data[0][0] * m_data[0][3] + m.m_data[0][1] * m_data[1][3] + m.m_data[0][2] * m_data[2][3] +
                    m.m_data[0][3] * m_data[3][3];
        tmp[1][0] = m.m_data[1][0] * m_data[0][0] + m.m_data[1][1] * m_data[1][0] + m.m_data[1][2] * m_data[2][0] +
                    m.m_data[1][3] * m_data[3][0];
        tmp[1][1] = m.m_data[1][0] * m_data[0][1] + m.m_data[1][1] * m_data[1][1] + m.m_data[1][2] * m_data[2][1] +
                    m.m_data[1][3] * m_data[3][1];
        tmp[1][2] = m.m_data[1][0] * m_data[0][2] + m.m_data[1][1] * m_data[1][2] + m.m_data[1][2] * m_data[2][2] +
                    m.m_data[1][3] * m_data[3][2];
        tmp[1][3] = m.m_data[1][0] * m_data[0][3] + m.m_data[1][1] * m_data[1][3] + m.m_data[1][2] * m_data[2][3] +
                    m.m_data[1][3] * m_data[3][3];
        tmp[2][0] = m.m_data[2][0] * m_data[0][0] + m.m_data[2][1] * m_data[1][0] + m.m_data[2][2] * m_data[2][0] +
                    m.m_data[2][3] * m_data[3][0];
        tmp[2][1] = m.m_data[2][0] * m_data[0][1] + m.m_data[2][1] * m_data[1][1] + m.m_data[2][2] * m_data[2][1] +
                    m.m_data[2][3] * m_data[3][1];
        tmp[2][2] = m.m_data[2][0] * m_data[0][2] + m.m_data[2][1] * m_data[1][2] + m.m_data[2][2] * m_data[2][2] +
                    m.m_data[2][3] * m_data[3][2];
        tmp[2][3] = m.m_data[2][0] * m_data[0][3] + m.m_data[2][1] * m_data[1][3] + m.m_data[2][2] * m_data[2][3] +
                    m.m_data[2][3] * m_data[3][3];
        tmp[3][0] = m.m_data[3][0] * m_data[0][0] + m.m_data[3][1] * m_data[1][0] + m.m_data[3][2] * m_data[2][0] +
                    m.m_data[3][3] * m_data[3][0];
        tmp[3][1] = m.m_data[3][0] * m_data[0][1] + m.m_data[3][1] * m_data[1][1] + m.m_data[3][2] * m_data[2][1] +
                    m.m_data[3][3] * m_data[3][1];
        tmp[3][2] = m.m_data[3][0] * m_data[0][2] + m.m_data[3][1] * m_data[1][2] + m.m_data[3][2] * m_data[2][2] +
                    m.m_data[3][3] * m_data[3][2];
        tmp[3][3] = m.m_data[3][0] * m_data[0][3] + m.m_data[3][1] * m_data[1][3] + m.m_data[3][2] * m_data[2][3] +
                    m.m_data[3][3] * m_data[3][3];

        Set(tmp);

        return *this;
    }

    Matrix4d &Matrix4d::Multiply(const Matrix4d &m) {
        return (*this) *= m;
    }

    Vector4d Matrix4d::PreMultiply(const Vector4d &vec) const {
        return (*this) * vec;
    }

    Vector4d Matrix4d::Multiply(const Vector4d &vec) {
        return vec * (*this);
    }
//=======================================================================

    Matrix4d operator+(const Matrix4d &m1, const Matrix4d &m2) {
        Matrix4d m;

        m[0][0] = m1[0][0] + m2[0][0];
        m[1][0] = m1[1][0] + m2[1][0];
        m[2][0] = m1[2][0] + m2[2][0];
        m[3][0] = m1[3][0] + m2[3][0];

        m[0][1] = m1[0][1] + m2[0][1];
        m[1][1] = m1[1][1] + m2[1][1];
        m[2][1] = m1[2][1] + m2[2][1];
        m[3][1] = m1[3][1] + m2[3][1];

        m[0][2] = m1[0][2] + m2[0][2];
        m[1][2] = m1[1][2] + m2[1][2];
        m[2][2] = m1[2][2] + m2[2][2];
        m[3][2] = m1[3][2] + m2[3][2];

        m[0][3] = m1[0][3] + m2[0][3];
        m[1][3] = m1[1][3] + m2[1][3];
        m[2][3] = m1[2][3] + m2[2][3];
        m[3][3] = m1[3][3] + m2[3][3];

        return m;
    }

    Matrix4d operator-(const Matrix4d &m1, const Matrix4d &m2) {
        Matrix4d m;

        m[0][0] = m1[0][0] - m2[0][0];
        m[1][0] = m1[1][0] - m2[1][0];
        m[2][0] = m1[2][0] - m2[2][0];
        m[3][0] = m1[3][0] - m2[3][0];

        m[0][1] = m1[0][1] - m2[0][1];
        m[1][1] = m1[1][1] - m2[1][1];
        m[2][1] = m1[2][1] - m2[2][1];
        m[3][1] = m1[3][1] - m2[3][1];

        m[0][2] = m1[0][2] - m2[0][2];
        m[1][2] = m1[1][2] - m2[1][2];
        m[2][2] = m1[2][2] - m2[2][2];
        m[3][2] = m1[3][2] - m2[3][2];

        m[0][3] = m1[0][3] - m2[0][3];
        m[1][3] = m1[1][3] - m2[1][3];
        m[2][3] = m1[2][3] - m2[2][3];
        m[3][3] = m1[3][3] - m2[3][3];

        return m;
    }

    Matrix4d operator*(const Matrix4d &m1, const Matrix4d &m2) {
        Matrix4d m = m1;
        m *= m2;
        return m;
    }

    Vector4d operator*(const Matrix4d &m, const Vector4d &v) {
        Vector4d vRet;

        vRet[0] = m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2] + m[0][3] * v[3];
        vRet[1] = m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2] + m[1][3] * v[3];
        vRet[2] = m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2] + m[2][3] * v[3];
        vRet[3] = m[3][0] * v[0] + m[3][1] * v[1] + m[3][2] * v[2] + m[3][3] * v[3];

        return vRet;
    }

    Vector4d operator*(const Vector4d &v, const Matrix4d &m) {
        Vector4d vRet;

        vRet[0] = v[0] * m[0][0] + v[1] * m[1][0] + v[2] * m[2][0] + v[3] * m[3][0];
        vRet[1] = v[0] * m[0][1] + v[1] * m[1][1] + v[2] * m[2][1] + v[3] * m[3][1];
        vRet[2] = v[0] * m[0][2] + v[1] * m[1][2] + v[2] * m[2][2] + v[3] * m[3][2];
        vRet[3] = v[0] * m[0][3] + v[1] * m[1][3] + v[2] * m[2][3] + v[3] * m[3][3];

        return vRet;
    }

    bool operator==(const Matrix4d &m1, const Matrix4d &m2) {
        return (
                MathUtils::IsEqual(m1[0][0], m2[0][0]) &&
                MathUtils::IsEqual(m1[0][1], m2[0][1]) &&
                MathUtils::IsEqual(m1[0][2], m2[0][2]) &&
                MathUtils::IsEqual(m1[0][3], m2[0][3]) &&

                MathUtils::IsEqual(m1[1][0], m2[1][0]) &&
                MathUtils::IsEqual(m1[1][1], m2[1][1]) &&
                MathUtils::IsEqual(m1[1][2], m2[1][2]) &&
                MathUtils::IsEqual(m1[1][3], m2[1][3]) &&

                MathUtils::IsEqual(m1[2][0], m2[2][0]) &&
                MathUtils::IsEqual(m1[2][1], m2[2][1]) &&
                MathUtils::IsEqual(m1[2][2], m2[2][2]) &&
                MathUtils::IsEqual(m1[2][3], m2[2][3]) &&

                MathUtils::IsEqual(m1[3][0], m2[3][0]) &&
                MathUtils::IsEqual(m1[3][1], m2[3][1]) &&
                MathUtils::IsEqual(m1[3][2], m2[3][2]) &&
                MathUtils::IsEqual(m1[3][3], m2[3][3])
        );
    }

    bool operator!=(const Matrix4d &m1, const Matrix4d &m2) {
        return !(m1 == m2);
    }

}
