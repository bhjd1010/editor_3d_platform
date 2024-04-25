
#pragma once

#include "math/common/define.h"
#include "math/common/constants.h"
#include "math/common/e3d_object.h"

namespace E3dMath {

// 二维向量定义
    class Vector2d : public E3dObject {
    public:
        static Vector2d Create(double x, double y);

        static Vector2d MakeZero();

        static Vector2d MakeUintX();

        static Vector2d MakeUnitY();

        static const Vector2d &UnitX();

        static const Vector2d &UnitY();

        static const Vector2d &Zero();

        Vector2d();

        explicit Vector2d(double array[2]);

        Vector2d(double x, double y);

        Vector2d(const Vector2d &another);

        double X() const;

        double Y() const;

        double &X();

        double &Y();

        bool Set(double x, double y);

        void Set(const Vector2d &p);;

        bool SetX(double x);

        bool SetY(double y);

        bool IsZero(double tolerance = Constants::DOUBLE_EPS) const;

        bool IsNormalized(double tolerance = Constants::DOUBLE_EPS) const;

        double Length() const;

        Vector2d &Reverse();

        // 长度的平方
        double SqrLength() const;

        Vector2d Clone() const;

        Vector2d &Normalize();

        Vector2d GetNormalized() const;

        double Dot(const Vector2d &another) const;

        double &operator[](int index);

        double operator[](int index) const;

        double Cross(const Vector2d &another) const;

        double DiatanceTo(const Vector2d &another) const;

        double SqDiatanceTo(const Vector2d &another) const;

        bool IsParallel(const Vector2d &another) const;

        bool IsPerpendicularTo(const Vector2d &another) const;

        bool Equals(const Vector2d &another, double tol = Constants::DOUBLE_EPS) const;

        /**
         * 获取两个向量的夹角(锐角/直角)
         * \return   [0, PI/2]
         */
        double AcuteAngleTo(const Vector2d &another) const;

        /**
         *  计算此向量逆时针转到另一向量的转角
         * \return  [0; 2PI]
         */
        double AngleTo(const Vector2d &another) const;

        Vector2d &operator=(const Vector2d &another);

        /**
        * 自乘，会改变本对象
        */
        Vector2d &operator*=(const double d);

        /**
        * 自除，会改变本对象
        */
        Vector2d &operator/=(const double d);

        /**
        * 自加，会改变本对象
        */
        Vector2d &operator+=(const Vector2d &another);

        /**
        * 自减，会改变本对象
        */
        Vector2d &operator-=(const Vector2d &another);

        Vector2d operator-() const;

        virtual MathObjectType GetType() const override { return MathObjectType::Vector2d; }

    private:
        double _xy[2];

        friend class Vector2dUtils;
    };

    Vector2d operator*(const Vector2d &vec, double d);

    Vector2d operator*(double d, const Vector2d &vec);

    Vector2d operator/(const Vector2d &vec, double d);

    Vector2d operator+(const Vector2d &v1, const Vector2d &v2);

    Vector2d operator-(const Vector2d &v1, const Vector2d &v2);

    bool operator==(const Vector2d &v1, const Vector2d &v2);

    bool operator!=(const Vector2d &v1, const Vector2d &v2);


}


