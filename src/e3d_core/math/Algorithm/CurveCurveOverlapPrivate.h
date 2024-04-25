#pragma once

#include "algorithm/AlgorithmResultType.h"
#include "CurveCurveColinear.h"
#include "MathUtils.h"

namespace E3dMath {

// 曲线与曲线重合判断
    class CurveCurveOverlapPrivate {
    public:

        static std::vector<CurveCurveOverlapResult> Line2dLine2d(const Line2d &line1, const Line2d &line2) {
            std::vector<CurveCurveOverlapResult> ret;
            // 是否共线
            if (!CurveCurveColinear::Line2dLine2d(line1, line2)) {
                return ret;
            }

            const Intervald &r1 = line1.GetRange();
            // line2在line1上投影的区间
            double t1 = line1.GetParamAt(line2.GetStartPoint());
            double t2 = line1.GetParamAt(line2.GetEndPoint());
            Intervald r2on1 = Intervald(t1, t2, true);
            Intervald overlap1 = r1.Intersection(r2on1);

            if (MathUtils::IsZero(overlap1.Length())) {
                return ret;
            }

            bool sameDirection = line1.GetDirection().Dot(line2.GetDirection()) > 0;
            double param2st = line2.GetParamAt(line1.GetPointAt(overlap1.GetMin()));
            double param2ed = line2.GetParamAt(line1.GetPointAt(overlap1.GetMax()));

            ret.push_back(CurveCurveOverlapResult(overlap1,
                                                  sameDirection ? Intervald(param2st, param2ed) : Intervald(param2ed,
                                                                                                            param2st)));
            return ret;
        }

        static std::vector<CurveCurveOverlapResult> Line3dLine3d(const Line3d &line1, const Line3d &line2) {
            throw ("未实现");
        }

    };


}
