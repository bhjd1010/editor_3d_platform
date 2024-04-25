#pragma once

#include "ISurface.h"
#include "math/Intervald.h"
#include "math/Vector3d.h"
#include "math/Coordinate3d.h"

namespace E3dMath {
    class Coordinate3d;

// 平面
    class Plane : public ISurface {
    public:
        static Plane XOY(double z = 0.0);

        static Plane YOZ(double x = 0.0);

        static Plane ZOX(double y = 0.0);

        /**
         * 通过三个点创建平面，三点不能共线
         */
        static Plane MakePlaneByTreePoints(const Vector3d &pt1, const Vector3d &pt2, const Vector3d &pt3);

        static Plane
        MakePlaneByPointNormal(const Vector3d &pt1, const Vector3d &normal, const Vector3d *pXDir = nullptr);

        Plane(const Vector3d &origin, const Vector3d &dirU, const Vector3d &dirV);

        Plane(const Vector3d &origin, const Vector3d &normal);

        Plane(const Coordinate3d &coord);

        Plane(const Plane &other);

        const Vector3d &GetOrigin() const;

        const Vector3d &GetNormal() const;

        const Vector3d &GetUDir() const;

        const Vector3d &GetVDir() const;

        // ISurface接口实现
        //========================================================================
        // 得到曲面上u，v参数处的坐标点
        virtual Vector3d GetPointAt(double dU, double dV) const override;

        // 得到曲面上u，v参数处的法向
        virtual Vector3d GetNormalAt(double dU, double dV) const override;

        // 根据面上坐标点计算对应的参数值
        virtual Vector2d GetParamAt(const Vector3d &pointOnSurface) const override;

        //包围盒
        virtual Box3d GetBoundingBox() const override;

        virtual bool Transform(const Matrix4d &mat) override;

        virtual bool Translate(const Vector3d &vec) override;

        virtual bool ContainsCurve(const ICurve3d &curve, double tol = Constants::DOUBLE_EPS) const override;

        virtual bool ContainsPoint(const Vector3d &point, double tol = Constants::DOUBLE_EPS) const override;

        virtual bool IsCoplanar(const ISurface &other, double tol = Constants::DOUBLE_EPS) const override;
        //========================================================================

        virtual MathObjectType GetType() const override;

        virtual void Release() override { delete this; };

    private:
        Coordinate3d _coord = Coordinate3d();
    };

}
