#pragma once

#include "Line2d.h"
#include "common/constants.h"
#include <vector>
#include "ICurve.h"
#include "Line3d.h"

namespace E3dMath {

/**
 * 几何对象工具方法
 */
    class GeomUtils {
    public:
        static const Line2d *ToLine2d(const ICurve *curve);

        static const Line3d *ToLine3d(const ICurve *curve);

        static bool CurvesConnected2d(const std::vector<const ICurve2d *> &curves, double tol = Constants::DOUBLE_EPS);

        static bool CurvesConnected3d(const std::vector<const ICurve3d *> &curves, double tol = Constants::DOUBLE_EPS);

    };

}