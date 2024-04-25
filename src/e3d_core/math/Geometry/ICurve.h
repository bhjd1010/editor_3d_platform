#pragma once

#include "math/common/define.h"
#include "IGeometry.h"
#include "MathObjectType.h"

namespace E3dMath {

// 曲线
    class ICurve : public IGeometry {
    public:
        /**
         * \brief  计算指定参数区间的曲线长度
         * \param startParameter  参数区间起始值
         * \param endParameter    参数区间终止值
         */
        virtual double GetLength(double startParameter, double endParameter) const = 0;

        // 判断曲线是否封闭
        virtual bool IsClosed() const = 0;

        // 是否退化为点
        virtual bool IsDegenerated(double epsilon) const = 0;

        // 计算曲线长度
        virtual double GetLength() const = 0;

        /**
         * 延伸曲线，会改变this，若曲线参数域为[0,1]，从尾部增加1，参数域变为[0,2]，从头部增加1，参数域变为[-1,1]
         * bTail，是否从尾部增加
         */
        virtual bool Extend(double howLong, bool bTail = true) = 0;

        /**
         * 从参数域的两端分别延伸曲线，会改变this
         */
        virtual bool ExtendDouble(double howLong) = 0;

        virtual std::unique_ptr<ICurve> Clone() const = 0;

        /**
         * 翻转curve方向
         */
        virtual ICurve *Reverse() = 0;
    };

}
