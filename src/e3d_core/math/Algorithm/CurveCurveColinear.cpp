#include "algorithm/CurveCurveColinear.h"

namespace E3dMath {

    bool CurveCurveColinear::Curve2ds(const ICurve2d &curve1, const ICurve2d &curve2) {
        auto type1 = curve1.GetType();
        auto type2 = curve2.GetType();
        if (type1 == MathObjectType::Line2d && type2 == MathObjectType::Line2d) {
            const Line2d &line1 = dynamic_cast<const Line2d &>(curve1);
            const Line2d &line2 = dynamic_cast<const Line2d &>(curve2);
            return CurveCurveColinear::Line2dLine2d(line1, line2);
        }
        throw ("不支持的类型");
    }


    bool CurveCurveColinear::Curve3ds(const ICurve3d &curve1, const ICurve3d &curve2) {
        auto type1 = curve1.GetType();
        auto type2 = curve2.GetType();
        if (type1 == MathObjectType::Line3d && type2 == MathObjectType::Line3d) {
            const Line3d &line1 = dynamic_cast<const Line3d &>(curve1);
            const Line3d &line2 = dynamic_cast<const Line3d &>(curve2);
            return CurveCurveColinear::Line3dLine3d(line1, line2);
        }
        throw ("不支持的类型");

    }

    namespace {
        template<class LineType, class PointType>
        bool IsLineColinear(const LineType &line1, const LineType &line2) {
            auto PtTolineSqDistance = [](const PointType &pt, const LineType &line) -> double {
                return line.GetPointAt(line.GetParamAt(pt)).SqDiatanceTo(pt);
            };
            return (
                    line1.GetDirection().IsParallel(line2.GetDirection()) &&
                    PtTolineSqDistance(line1.GetMiddlePoint(), line2) < Constants::DOUBLE_EPS * Constants::DOUBLE_EPS &&
                    PtTolineSqDistance(line2.GetMiddlePoint(), line1) < Constants::DOUBLE_EPS * Constants::DOUBLE_EPS
            );
        }
    }

    bool CurveCurveColinear::Line2dLine2d(const Line2d &line1, const Line2d &line2) {
        return IsLineColinear<Line2d, Vector2d>(line1, line2);
    }

    bool CurveCurveColinear::Line3dLine3d(const Line3d &line1, const Line3d &line2) {
        return IsLineColinear<Line3d, Vector3d>(line1, line2);
    }
}
