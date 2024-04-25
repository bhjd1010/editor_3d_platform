#pragma once

#include "ICurve.h"

namespace E3dMath {
    class Box3d;

    class Vector3d;

    class Matrix4d;

    class Intervald;

// 三维曲线
    class ICurve3d : public ICurve {
    public:
        virtual const Intervald &GetRange() const = 0;

        virtual void SetRange(const Intervald &range) = 0;

        virtual Box3d GetBoundingBox() const = 0;

        // 根据参数求曲线上的点
        virtual Vector3d GetPointAt(double parameter) const = 0;

        // 根据坐标点计算对应的参数值
        virtual double GetParamAt(const Vector3d &pt) const = 0;

        virtual Vector3d GetStartPoint() const = 0;

        virtual Vector3d GetEndPoint() const = 0;

        virtual Vector3d GetMiddlePoint() const = 0;

        // 根据参数求二维曲线上的对应位置的切向
        virtual Vector3d GetTangent(double parameter) const = 0;

        // 计算二维曲线起点的切向
        virtual Vector3d GetStartTangent() const = 0;

        // 计算二维曲线终点的切向
        virtual Vector3d GetEndTangent() const = 0;

        virtual bool Transform(const Matrix4d &transformMatrix) = 0;

        virtual bool Translate(const Vector3d &offset) = 0;

        virtual ICurve3d *Reverse() = 0;

    };
}
