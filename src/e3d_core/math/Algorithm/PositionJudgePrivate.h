#pragma once

#include "geometry/ICurve2d.h"
#include "geometry/ICurve3d.h"
#include "algorithm/AlgorithmResultType.h"
#include "CurveCurveIntersectPrivate.h"

namespace E3dMath {

// 位置判断器
    class PositionJudgePrivate {
    public:
        static CurveCuvePositonType Line2dLine2dPosition(const Line2d &line1, const Line2d &line2) {
            // 不相交
            auto intersects = CurveCurveIntersectPrivate::Line2dLine2d(line1, line2);
            if (intersects.size() == 0) {
                return CurveCuvePositonType::NOT_INTERSECT;
            }

            // 重合
            if (std::find_if(intersects.begin(), intersects.end(),
                             [](const CurveCurveIntersectResult<Vector2d> &inte) { return inte.isOverlap; })
                != intersects.end()) {
                if (intersects.size() == 1 && intersects[0].overlap1.IsEqual(line1.GetRange())
                    && intersects[0].overlap2.IsEqual(line2.GetRange())) {
                    return CurveCuvePositonType::OVERLAP_ALL;
                }
                return CurveCuvePositonType::OVERLAP;
            }

            // 相交
            auto NotContainAtEnds = [&](const CurveCurveIntersectResult<Vector2d> &inte) -> bool {
                return !line1.GetRange().ContainAtEnds(inte.param1) || !line2.GetRange().ContainAtEnds(inte.param2);
            };
            if (std::find_if(intersects.begin(), intersects.end(), NotContainAtEnds)
                != intersects.end()) {
                return CurveCuvePositonType::INTERSECT_MID;
            }
            return CurveCuvePositonType::INTERSECT_END;
        }

        static CurveCuvePositonType Line3dLine3dPosition(const Line3d &line1, const Line3d &line2) {
            throw ("未支持的类型");

        }

    };


}
