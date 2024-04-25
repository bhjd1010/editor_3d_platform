#include "GeometryUtils.h"
#include "ICurve2d.h"
#include "Line2d.h"
#include "MathObjectType.h"
#include "Line3d.h"
#include <vector>


namespace E3dMath {

    namespace {
        template<class Curve = ICurve2d>
        bool _CurvesConnected(const std::vector<const Curve *> &curves) {
            for (std::size_t i = 0; i < curves.size() - 1; i++) {
                auto curve = curves[i];
                auto nxtCurve = curves[i + 1];
                auto endPt = curve->GetEndPoint();
                auto startPt = nxtCurve->GetStartPoint();
                if (startPt != endPt) {
                    return false;
                }
            }
            return true;
        }
    }

    const Line2d *GeomUtils::ToLine2d(const ICurve *curve) {
        if (!curve) {
            return nullptr;
        }
        auto type = curve->GetType();
        if (type == MathObjectType::Line2d) {
            return dynamic_cast<const Line2d *>(curve);
        }
        return nullptr;
    }

    const E3dMath::Line3d *E3dMath::GeomUtils::ToLine3d(const ICurve *curve) {
        if (!curve) {
            return nullptr;
        }
        auto type = curve->GetType();
        if (type == MathObjectType::Line3d) {
            return dynamic_cast<const Line3d *>(curve);
        }
        return nullptr;
    }

    bool
    GeomUtils::CurvesConnected2d(const std::vector<const ICurve2d *> &curves, double tol /*= Constants::DOUBLE_EPS*/) {
        return _CurvesConnected<ICurve2d>(curves);
    }

    bool
    GeomUtils::CurvesConnected3d(const std::vector<const ICurve3d *> &curves, double tol /*= Constants::DOUBLE_EPS*/) {
        return _CurvesConnected<ICurve3d>(curves);
    }

}
