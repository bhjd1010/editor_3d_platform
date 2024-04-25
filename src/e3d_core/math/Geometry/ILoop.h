#pragma once

#include <vector>
#include "ICurve2d.h"
#include "IGeometry.h"
#include "math/math/Vector2d.h"


namespace E3dMath {

/**
 * 环，封闭且无自交的曲线序列
 */
    class ILoop : public IGeometry {
    public:

        virtual std::vector<const ICurve2d *> GetAllCurves() const = 0;

        // 包含的curve的数量
        virtual unsigned int Size() const = 0;

        /**
         *  向序列中加一条曲线，直接加入，不作合法性检查
         */
        virtual bool AddCurve(std::unique_ptr<ICurve2d> curve) = 0;

        /**
         *  环是否合法，封闭且无自交
         */
        virtual bool IsValid(double tol = Constants::DOUBLE_EPS) const = 0;

        /**
         * Loop中是否只包含Line
         */
        virtual bool IsLineOnly() const = 0;

        virtual std::vector<Vector2d> ToPath() const = 0;

        virtual Box2d GetBoundingBox() const = 0;

        virtual std::unique_ptr<ILoop> Clone() const = 0;

        /**
         * 翻转Loop方向，逆时针→顺时针，顺时针→逆时针
         */
        virtual ILoop *Reverse() = 0;
    };


}

