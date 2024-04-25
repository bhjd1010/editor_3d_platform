
#pragma once

#include "ICurve3d.h"
#include "math/Intervald.h"
#include "math/Vector3d.h"

namespace E3dMath {

// 三维直线
    class Line3d : public ICurve3d {
    public:
        // 根据起始点，终点创建直线段
        static Line3d Create(const Vector3d &startPoint, const Vector3d &endPoint);

        // 通过基准点、方向、以及直线沿着矢量方向上的起点和终点区间，创建二维直线段
        static Line3d Create(const Vector3d &position, const Vector3d &dir, const Intervald &range);

        Line3d(const Vector3d &startPoint, const Vector3d &endPoint);

        Line3d(const Vector3d &position, const Vector3d &dir, const Intervald &range);

        Line3d(const Line3d &another);

        bool Reset(const Vector3d &start, const Vector3d &end);

        const Vector3d &GetOrigin() const;

        void SetOrigin(const Vector3d &origin);

        // 获取直线方向向量（单位向量）
        const Vector3d &GetDirection() const;

        void SetDirection(const Vector3d &dir);

        bool IsParallelTo(const Line3d &other) const;

        // 是否共线
        bool IsColinearWith(const Line3d &other) const;

        bool IsPerpendicularTo(const Line3d &other) const;


        // ICurve2d 接口实现
        //=============================================================
        const Intervald &GetRange() const;

        void SetRange(const Intervald &range);

        virtual Box3d GetBoundingBox() const override;

        virtual Vector3d GetPointAt(double parameter) const override;

        virtual double GetParamAt(const Vector3d &pt) const override;

        virtual Vector3d GetStartPoint() const override;

        virtual Vector3d GetEndPoint() const override;

        virtual Vector3d GetMiddlePoint() const override;

        virtual Vector3d GetTangent(double parameter) const override;

        virtual Vector3d GetStartTangent() const override;

        virtual Vector3d GetEndTangent() const override;

        virtual bool Transform(const Matrix4d &mat) override;

        virtual bool Translate(const Vector3d &offset) override;
        //=============================================================

        // ICurve 接口实现
        //=============================================================
        virtual double GetLength(double startParameter, double endParameter) const override;

        virtual double GetLength() const override;

        virtual bool IsClosed() const override;

        virtual Line3d *Reverse() override;

        virtual bool Extend(double howLong, bool bTail = true) override;

        virtual bool ExtendDouble(double howLong) override;

        std::unique_ptr<ICurve> Clone() const override;

        virtual bool IsDegenerated(double epsilon) const override;

        //=============================================================
        //
        // IGeometry 接口实现
        //=============================================================
        virtual MathObjectType GetType() const override;
        //=============================================================

        void Release() override {
            delete this;
        }

    private:
        Vector3d _origin = Vector3d();
        Vector3d _dir = Vector3d::MakeUintX();
        Intervald _range = Intervald();
    };


}