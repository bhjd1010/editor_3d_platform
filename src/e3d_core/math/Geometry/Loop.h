#pragma once

#include <memory>
#include "ILoop.h"


namespace E3dMath {

/**
 * 环，封闭且无自交的曲线序列
 */
    class Loop : public ILoop {
    public:
        Loop(const std::vector<Vector2d> &points);

        Loop(std::vector<std::unique_ptr<ICurve2d>> &curves);

        std::vector<const ICurve2d *> GetAllCurves() const override;

        // 包含的curve的数量
        unsigned int Size() const override;

        /**
         *  向序列中加一条曲线，直接加入，不作合法性检查
         */
        bool AddCurve(std::unique_ptr<ICurve2d> curve) override;

        /**
         *  环是否合法，封闭且无自交
         */
        bool IsValid(double tol = Constants::DOUBLE_EPS) const override;

        bool IsLineOnly() const override;

        std::vector<Vector2d> ToPath() const override;

        Box2d GetBoundingBox() const override;

        std::unique_ptr<ILoop> Clone() const override;

        ILoop *Reverse() override;

        ///////////////////////////////////////////////////////////////////
        // IAesGeometry接口实现
        virtual MathObjectType GetType() const override;

        virtual void Release() override;


    private:
        std::vector<std::unique_ptr<ICurve2d>> _curves;
    };


}

