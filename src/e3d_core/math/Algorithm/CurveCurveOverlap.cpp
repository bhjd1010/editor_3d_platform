#include "CurveCurveOverlap.h"
#include "CurveCurveColinear.h"
#include "Line2d.h"
#include "CurveCurveOverlapPrivate.h"

namespace E3dMath {

    std::vector<CurveCurveOverlapResult> CurveCurveOverlap::Curve2ds(const ICurve2d &curve1, const ICurve2d &curve2) {
        auto type1 = curve1.GetType();
        auto type2 = curve2.GetType();
        if (type1 == MathObjectType::Line2d && type2 == MathObjectType::Line2d) {
            const Line2d &line1 = dynamic_cast<const Line2d &>(curve1);
            const Line2d &line2 = dynamic_cast<const Line2d &>(curve2);
            return CurveCurveOverlapPrivate::Line2dLine2d(line1, line2);
        }

        throw ("未支持的类型");
    }


    std::vector<CurveCurveOverlapResult> CurveCurveOverlap::Curve3ds(const ICurve3d &curve1, const ICurve3d &curve2) {
        auto type1 = curve1.GetType();
        auto type2 = curve2.GetType();
        if (type1 == MathObjectType::Line3d && type2 == MathObjectType::Line3d) {
            const Line3d &line1 = dynamic_cast<const Line3d &>(curve1);
            const Line3d &line2 = dynamic_cast<const Line3d &>(curve2);
            return CurveCurveOverlapPrivate::Line3dLine3d(line1, line2);
        }

        throw ("未支持的类型");
    }

}
