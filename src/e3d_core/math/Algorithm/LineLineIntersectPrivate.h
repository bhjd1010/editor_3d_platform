#pragma once

#include "common/define.h"
#include "EquationsSolver.h"
#include "Vector2d.h"

namespace E3dMath {

    class LineLineIntersectUtils {
    public:
        /**
         * 求两无限长直线交点的参数，需要保证两直线不平行
         */
        static Vector2d GetLineLineIntersectParams2d(const Vector2d &origin1, const Vector2d &origin2,
                                                     const Vector2d &dir1, const Vector2d &dir2) {
            double A[4] = {dir1.X(), -dir2.X(), dir1.Y(), -dir2.Y()};
            double b[2] = {origin2.X() - origin1.X(), origin2.Y() - origin1.Y()};
            double t[2];
            EquationsSolver::SolveInhomogeneousLinearEquations<2>(A, b, t);
            Vector2d ret(t);
            return ret;
        }
    };

}
