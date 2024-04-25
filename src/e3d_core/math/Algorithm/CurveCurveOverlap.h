#pragma once

#include "geometry/ICurve2d.h"
#include "geometry/ICurve3d.h"
#include "math/Intervald.h"
#include "AlgorithmResultType.h"

namespace E3dMath {

// 曲线与曲线重合判断
    class CurveCurveOverlap {
    public:

        static std::vector<CurveCurveOverlapResult> Curve2ds(const ICurve2d &curve1, const ICurve2d &curve2);

        static std::vector<CurveCurveOverlapResult> Curve3ds(const ICurve3d &curve1, const ICurve3d &curve2);

    };


}
