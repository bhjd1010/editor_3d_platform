#pragma once

#include "common/define.h"
#include "IGeometry.h"
#include "MathObjectType.h"

namespace E3dMath {

    class ICurve3d;

    class Vector3d;

    class Vector2d;

    class Intervald;

    class Box3d;

    class Matrix4d;

// 曲面
    class ISurface : public IGeometry {
    public:

        // 得到曲面上u，v参数处的坐标点
        virtual Vector3d GetPointAt(double dU, double dV) const = 0;

        // 得到曲面上u，v参数处的法向
        virtual Vector3d GetNormalAt(double dU, double dV) const = 0;

        // 根据面上坐标点计算对应的参数值
        virtual Vector2d GetParamAt(const Vector3d &pointOnSurface) const = 0;

        //包围盒
        virtual Box3d GetBoundingBox() const = 0;

        virtual bool Transform(const Matrix4d &mat) = 0;

        virtual bool Translate(const Vector3d &vec) = 0;

        virtual bool ContainsCurve(const ICurve3d &Curve, double tol = Constants::DOUBLE_EPS) const = 0;

        virtual bool ContainsPoint(const Vector3d &Curve, double tol = Constants::DOUBLE_EPS) const = 0;

        virtual bool IsCoplanar(const ISurface &other, double tol = Constants::DOUBLE_EPS) const = 0;
    };

}
