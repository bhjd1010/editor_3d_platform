#pragma once

#include "ICurve.h"
#include "math/math/Box2d.h"

namespace E3dMath {
    class Box2d;

    class Vector2d;

    class Matrix3d;

    class Intervald;

// 二维曲线
    class ICurve2d : public ICurve {
    public:
        virtual Box2d GetBoundingBox() const = 0;

        virtual const Intervald &GetRange() const = 0;

        virtual void SetRange(const Intervald &range) = 0;

        // 根据参数求二维曲线上的点
        virtual Vector2d GetPointAt(double parameter) const = 0;

        // 根据坐标点计算对应的参数值
        virtual double GetParamAt(const Vector2d &pt) const = 0;

        virtual Vector2d GetStartPoint() const = 0;

        virtual Vector2d GetEndPoint() const = 0;

        virtual Vector2d GetMiddlePoint() const = 0;

        // 根据参数求二维曲线上的对应位置的切向
        virtual Vector2d GetTangent(double parameter) const = 0;

        // 计算二维曲线起点的切向
        virtual Vector2d GetStartTangent() const = 0;

        // 计算二维曲线终点的切向
        virtual Vector2d GetEndTangent() const = 0;

        virtual bool Transform(const Matrix3d &transformMatrix) = 0;

        virtual bool Translate(const Vector2d &offset) = 0;

        /**
         * 翻转curve方向
         */
        virtual ICurve2d *Reverse() = 0;

    };
}
