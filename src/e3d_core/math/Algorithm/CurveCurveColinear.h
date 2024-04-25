#pragma once

#include "geometry/ICurve2d.h"
#include "geometry/ICurve3d.h"
#include "math/Intervald.h"
#include "Line2d.h"
#include "Line3d.h"

namespace E3dMath {


// 判断曲线是否共线（忽略Range后是否具有相同的数学表达）
    class CurveCurveColinear {
    public:

        static bool Curve2ds(const ICurve2d &curve1, const ICurve2d &curve2);

        static bool Curve3ds(const ICurve3d &curve1, const ICurve3d &curve2);

        static bool Line2dLine2d(const Line2d &line1, const Line2d &line2);

        static bool Line3dLine3d(const Line3d &line1, const Line3d &line2);
    };


}