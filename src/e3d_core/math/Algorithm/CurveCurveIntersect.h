#pragma once

#include "geometry/ICurve2d.h"
#include "geometry/ICurve3d.h"
#include "AlgorithmResultType.h"

namespace E3dMath {

/**
 * 曲线与曲线的交点，目前支持：直线+直线
 * 若两曲线重合，则交点为重合段内的某个交点
 * 此接口是求两有限长曲线段的交点，若求无限长的曲线的交点，可将曲线extend至无限长
 */
    class CurveCurveIntersect {
    public:
        static CurveCurveIntersectResult2ds Curve2ds(const ICurve2d &curve1, const ICurve2d &curve2);

        static CurveCurveIntersectResult3ds Curve3ds(const ICurve3d &curve1, const ICurve3d &curve2);
    };


}
