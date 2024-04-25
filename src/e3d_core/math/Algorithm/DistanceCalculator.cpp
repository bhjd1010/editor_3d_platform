#include "DistanceCalculator.h"
#include "algorithm/DistanceCalculatorPrivate.h"

namespace E3dMath {

    double DistanceCalculator::PointToCurve2d(const Vector2d &point, const ICurve2d &curve,
                                              Vector2d *pMinDistancePoint /*= nullptr*/) {
        auto type = curve.GetType();
        switch (type) {
            case MathObjectType::Line2d: {
                const Line2d &line = dynamic_cast<const Line2d &>(curve);
                return DistanceCalculatorPrivate::PointToLine2d(point, line, pMinDistancePoint);
            }
            default:
                throw "未支持的类型";
        }
    }

    double DistanceCalculator::PointToCurve3d(const Vector3d &point, const ICurve3d &curve,
                                              Vector3d *pMinDistancePoint /*= nullptr*/) {
        auto type = curve.GetType();
        switch (type) {
            case MathObjectType::Line3d: {
                const Line3d &line = dynamic_cast<const Line3d &>(curve);
                return DistanceCalculatorPrivate::PointToLine3d(point, line);
            }
            default:
                throw "未支持的类型";
        }
    }

    double DistanceCalculator::PointToSurface(const Vector3d &point, const ISurface &surface,
                                              Vector3d *pFootPoint /*= nullptr*/) {
        return abs(PointToSurfaceSigned(point, surface, pFootPoint));
    }

    double DistanceCalculator::PointToSurfaceSigned(const Vector3d &point, const ISurface &surface,
                                                    Vector3d *pFootPoint /*= nullptr*/) {
        auto type = surface.GetType();
        switch (type) {
            case MathObjectType::Plane: {
                const Plane &plane = dynamic_cast<const Plane &>(surface);
                return DistanceCalculatorPrivate::PointToPlaneSigned(point, plane, pFootPoint);
            }
            default:
                throw "未支持的类型";
        }
    }

    double DistanceCalculator::Curve2dToCurve2d(const ICurve2d &curve1, const ICurve2d &curve2,
                                                Vector2d *pMinDistancePoint1 /*= nullptr*/,
                                                Vector2d *pMinDistancePoint2 /*= nullptr*/) {
        auto type1 = curve1.GetType();
        auto type2 = curve2.GetType();
        if (type1 == MathObjectType::Line2d && type2 == MathObjectType::Line2d) {
            const Line2d &line1 = dynamic_cast<const Line2d &>(curve1);
            const Line2d &line2 = dynamic_cast<const Line2d &>(curve2);
            return DistanceCalculatorPrivate::Line2dToLine2d(line1, line2, pMinDistancePoint1, pMinDistancePoint2);
        }

        throw "未支持的曲线类型";
    }

    double DistanceCalculator::Curve3dToCurve3d(const ICurve3d &curve1, const ICurve3d &curve2,
                                                Vector3d *pMinDistancePoint1 /*= nullptr*/,
                                                Vector3d *pMinDistancePoint2 /*= nullptr*/) {
        auto type1 = curve1.GetType();
        auto type2 = curve2.GetType();
        if (type1 == MathObjectType::Line3d && type2 == MathObjectType::Line3d) {
            const Line3d &line1 = dynamic_cast<const Line3d &>(curve1);
            const Line3d &line2 = dynamic_cast<const Line3d &>(curve2);
            return DistanceCalculatorPrivate::Line3dToLine3d(line1, line2, pMinDistancePoint1, pMinDistancePoint2);
        }

        throw "未支持的曲线类型";
    }

}
