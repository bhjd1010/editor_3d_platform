#pragma once

#include "Vector2d.h"

namespace E3dMath {

/**
 * 三维向量的定义
 */
    class Vector4d : public E3dObject {
    public:
        static Vector4d Create(double x, double y, double z, double w);

        static Vector4d CreateZero();

        static const Vector4d &UnitX();

        static const Vector4d &UnitY();

        static const Vector4d &UnitZ();

        static const Vector4d &UnitW();

        static const Vector4d &Zero();

        Vector4d();

        explicit Vector4d(double (&vec)[4]);

        Vector4d(double x, double y, double z, double w);

        Vector4d(const Vector4d &vec);

        double X() const;

        double Y() const;

        double Z() const;

        double W() const;

        double &X();

        double &Y();

        double &Z();

        double &W();

        bool Set(double x, double y, double z, double w);

        bool SetX(double x);

        bool SetY(double y);

        bool SetZ(double z);

        bool SetW(double w);

        bool IsZero(double tol = Constants::DOUBLE_EPS) const;

        bool IsUnit(double tol = Constants::DOUBLE_EPS) const;

        double Length() const;

        double SqrLength() const;

        Vector4d Clone() const;

        Vector4d &Normalize();

        Vector4d GetNormalized();

        double Dot(const Vector4d &vec) const;

        double &operator[](int nIndex);

        double operator[](int nIndex) const;

        Vector4d &operator*=(const double d);

        Vector4d &operator/=(const double d);

        Vector4d &operator+=(const Vector4d &vec);

        Vector4d &operator-=(const Vector4d &vec);

        Vector4d operator-() const;

        virtual MathObjectType GetType() const override { return MathObjectType::Vector4d; }

    private:
        double m_xyzw[4];
    };

/// \brief    向量乘给定数值
    Vector4d operator*(const Vector4d &vec, const double d);

/// \brief    数值乘给定向量
    Vector4d operator*(const double d, const Vector4d &vec);

/// \brief    两个向量的点乘
    double operator*(const Vector4d &v1, const Vector4d &v2);

/// \brief    向量除以一个数
    Vector4d operator/(const Vector4d &vec, const double d);

/// \brief    两个向量的加法，即向量的每个分量相加
    Vector4d operator+(const Vector4d &v1, const Vector4d &v2);

/// \brief    两个向量的减法，即向量1的每个分量减去向量2的每个分量
    Vector4d operator-(const Vector4d &v1, const Vector4d &v2);

/// \brief    判断向量是否相同
    bool operator==(const Vector4d &v1, const Vector4d &v2);

/// \brief    判断向量是否不同
    bool operator!=(const Vector4d &v1, const Vector4d &v2);

}
