

#pragma once

#include "ICurve2d.h"
#include "math/Intervald.h"

namespace E3dMath {

// 二维直线
    class Line2d : public ICurve2d {
    public:
        // 根据起始点，终点创建二维直线段
        static Line2d Create(const Vector2d &startPoint, const Vector2d &endPoint);

        // 通过基准点、方向、以及直线沿着矢量方向上的起点和终点区间，创建二维直线段
        static Line2d Create(const Vector2d &position, const Vector2d &dir, const Intervald &range);

        Line2d(const Vector2d &startPoint, const Vector2d &endPoint);

        Line2d(const Vector2d &position, const Vector2d &dir, const Intervald &range);

        Line2d(const Line2d &another);

        bool Reset(const Vector2d &start, const Vector2d &end);

        const Vector2d &GetOrigin() const;

        void SetOrigin(const Vector2d &origin);

        // 获取直线方向向量（单位向量）
        const Vector2d &GetDirection() const;

        void SetDirection(const Vector2d &dir);

        bool IsParallelTo(const Line2d &other) const;

        // 是否共线
        bool IsColinearWith(const Line2d &other) const;

        bool IsPerpendicularTo(const Line2d &other) const;

        // ICurve2d 接口实现
        //=============================================================
        virtual const Intervald &GetRange() const override;

        virtual void SetRange(const Intervald &range) override;

        virtual Box2d GetBoundingBox() const override;

        virtual Vector2d GetPointAt(double parameter) const override;

        virtual double GetParamAt(const Vector2d &pt) const override;

        virtual Vector2d GetStartPoint() const override;

        virtual Vector2d GetEndPoint() const override;

        virtual Vector2d GetMiddlePoint() const override;

        virtual Vector2d GetTangent(double parameter) const override;

        virtual Vector2d GetStartTangent() const override;

        virtual Vector2d GetEndTangent() const override;

        virtual bool Transform(const Matrix3d &transformMatrix) override;

        virtual bool Translate(const Vector2d &offset) override;

        virtual Line2d *Reverse() override;

        //=============================================================

        // ICurve 接口实现
        //=============================================================
        virtual double GetLength(double startParameter, double endParameter) const override;

        virtual double GetLength() const override;

        virtual bool IsClosed() const override;

        virtual bool IsDegenerated(double epsilon) const override;

        virtual bool Extend(double howLong, bool bTail = true) override;

        virtual bool ExtendDouble(double howLong) override;

        virtual std::unique_ptr<ICurve> Clone() const override;

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
        Vector2d _origin = Vector2d();
        Vector2d _dir = Vector2d::MakeUintX();
        Intervald _range = Intervald();
    };
}
