#pragma once

#include "LineLineIntersectPrivate.h"
#include "CurveCurveOverlapPrivate.h"

namespace E3dMath {

    namespace {
        template<class CurveType = ICurve2d, class PointType = Vector2d>
        CurveCurveIntersectResult<PointType> GetIntersectResultFromOverlap(const CurveCurveOverlapResult &overlap,
                                                                           const CurveType &curve1,
                                                                           const CurveType &curve2) {
            CurveCurveIntersectResult<PointType> result;
            double param1 = overlap.range1.Middle();
            auto point = curve1.GetPointAt(param1);
            double param2 = curve2.GetParamAt(point);
            bool isOverlap = overlap.range1.Length() > Constants::DOUBLE_EPS;
            result.point = point;
            result.param1 = param1;
            result.param2 = param2;
            result.isOverlap = isOverlap;
            if (isOverlap) {
                result.overlap1 = overlap.range1;
                result.overlap2 = overlap.range2;
            }
            return result;
        }
    }

/**
 * 曲线与曲线的交点，目前支持：直线+直线
 * 若两曲线重合，则交点为重合段内的某个交点
 * 此接口是求两有限长曲线段的交点，若求无限长的曲线的交点，可将曲线extend至无限长
 */
    class CurveCurveIntersectPrivate {
    public:
        static CurveCurveIntersectResult2ds Line2dLine2d(const Line2d &line1, const Line2d &line2) {
            CurveCurveIntersectResult2ds results;

            // 处理重合
            const std::vector<CurveCurveOverlapResult> &overlaps = CurveCurveOverlapPrivate::Line2dLine2d(line1, line2);
            if (overlaps.size() > 0) {
                for (auto &overlap: overlaps) {
                    results.push_back(GetIntersectResultFromOverlap<ICurve2d, Vector2d>(overlap, line1, line2));
                }
                return results;
            }

            // 求交
            const Vector2d &t = LineLineIntersectUtils::GetLineLineIntersectParams2d(line1.GetOrigin(),
                                                                                     line2.GetOrigin(),
                                                                                     line1.GetDirection(),
                                                                                     line2.GetDirection());
            if (!line1.GetRange().Contain(t[0]) || !line2.GetRange().Contain(t[1])) {
                return results;
            }

            Vector2d p1 = line1.GetPointAt(t[0]);
            CurveCurveIntersectResult2d result;
            result.point = p1;
            result.param1 = t[0];
            result.param2 = t[1];
            results.push_back(result);
            return results;
        }

        static CurveCurveIntersectResult3ds Line3dLine3d(const Line3d &line1, const Line3d &line2) {
            throw ("未实现");
        }
    };


}
