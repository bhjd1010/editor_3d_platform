
#pragma once

#include "Vector2d.h"

namespace E3dMath {

/**
 * 三维向量的定义
 */
    class Vector3d : public E3dObject {
    public:
        static Vector3d Create(const double x, const double y, const double z);

        static Vector3d MakeZero();

        static Vector3d MakeUintX();

        static Vector3d MakeUintY();

        static Vector3d MakeUintZ();

        static const Vector3d &UnitX();

        static const Vector3d &UnitY();

        static const Vector3d &UnitZ();

        static const Vector3d &Zero();

        Vector3d();

        explicit Vector3d(const double v[3]);

        Vector3d(const double x, const double y, const double z);

        Vector3d(const Vector2d &vec, const double z);

        Vector3d(const Vector3d &vec);

        double X() const;

        double Y() const;

        double Z() const;

        double &X();

        double &Y();

        double &Z();

        bool Set(const double x, const double y, const double z);

        bool Set(const Vector3d &v);

        bool Set(const double v[3]);

        bool Set(const Vector2d &vec, const double z);

        bool SetX(const double x);

        bool SetY(const double y);

        bool SetZ(const double z);

        Vector3d Clone() const;

        bool IsZero(const double epsilon = Constants::DOUBLE_EPS) const;

        bool IsNormalized(const double epsilon = Constants::DOUBLE_EPS) const;

        double Dot(const Vector3d &vec) const;

        Vector3d Cross(const Vector3d &vec) const;

        double Length() const;

        double SqrLength() const;

        // 单位化此向量
        Vector3d &Normalize();

        // 获取此向量的单位矩阵
        Vector3d GetNormalized() const;

        double DiatanceTo(const Vector3d &another) const;

        double SqDiatanceTo(const Vector3d &another) const;

        bool IsParallel(const Vector3d &another) const;

        bool IsPerpendicularTo(const Vector3d &another) const;

        Vector2d ToVector2d() const;

        /**
         * 获取两个向量的夹角(锐角/直角)
         * \return   [0, PI/2]
         */
        double AcuteAngleTo(const Vector3d &another) const;

        /**
        * 计算此向量转到另一向量的转角（返回两种旋转方向中，较小的角度）
        * \param vecTo  终止向量
        * \return  取值范围[0,PI]
        */
        double AngleTo(const Vector3d &vecTo) const;

        /**
        * 计算此向量逆时针转到另一向量的转角
        * \param vecTo  终止向量
        * \param pNormal  此向量和vecTo所在平面的法向或负法向
        * \return  取值范围[0，2PI]
        */
        double AngleTo(const Vector3d &vecTo, const Vector3d &normal) const;

        Vector3d &Reverse();

        Vector3d &operator=(const Vector3d &vec);

        double &operator[](int index);

        const double &operator[](int index) const;

        Vector3d operator+(const Vector3d &v) const;

        Vector3d operator-(const Vector3d &v) const;

        double operator*(const Vector3d &v) const;

        Vector3d &operator*=(const double &d);

        Vector3d &operator/=(const double &d);

        Vector3d &operator+=(const Vector3d &vecSrc);

        Vector3d &operator-=(const Vector3d &vecSrc);

        Vector3d operator-() const;

        virtual MathObjectType GetType() const override { return MathObjectType::Vector3d; }

    private:
        double _xyz[3];

        friend class Vector3dUtils;
    };

    Vector3d operator*(const Vector3d &vec, const double d);

    Vector3d operator*(const double &d, const Vector3d &vec);

    Vector3d operator^(const Vector3d &v1, const Vector3d &v2);

    Vector3d operator/(const Vector3d &vecSrc, double d);

    bool operator>(const Vector3d &v1, const Vector3d &v2);

    bool operator<(const Vector3d &v1, const Vector3d &v2);

    bool operator==(const Vector3d &v1, const Vector3d &v2);

    bool operator!=(const Vector3d &v1, const Vector3d &v2);

}
