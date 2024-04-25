#pragma once

#include "common/define.h"
#include "LineLineIntersectPrivate.h"
#include "Intervald.h"
#include "ICurve2d.h"
#include "ICurve3d.h"
#include "Vector3d.h"
#include "Line2d.h"
#include "Line3d.h"
#include "Plane.h"

namespace E3dMath {

    namespace {
        template<class T>
        struct PointCurvedDistanceResult {
            T m_foot;
            double m_param;
            double m_distance;
        };
        using PointCurve2dDistanceResult = PointCurvedDistanceResult<Vector2d>;
        using PointCurve3dDistanceResult = PointCurvedDistanceResult<Vector3d>;

        template<class Point = Vector2d, class Curve = ICurve2d>
        PointCurvedDistanceResult<Point> _GetMinDistanceFromEnd(
                const Point &point,
                const Curve &curve
        ) {
            const Point &stPt = curve.GetStartPoint();
            const Point &edPt = curve.GetEndPoint();
            double stDist = stPt.DiatanceTo(point);
            double edDist = edPt.DiatanceTo(point);
            const Intervald &range = curve.GetRange();

            if (stDist < edDist + Constants::DOUBLE_EPS) {
                return PointCurvedDistanceResult<Point>{stPt, range.GetMin(), stDist};
            }
            return PointCurvedDistanceResult<Point>{edPt, range.GetMax(), edDist};
        }

        double _GetMinDistanceFromEnd2d(
                const ICurve2d &curve1,
                const ICurve2d &curve2,
                Vector2d *point1,
                Vector2d *point2
        ) {
            Vector2d tmpPt1[4] = {curve1.GetStartPoint(), curve1.GetEndPoint(), Vector2d(), Vector2d()};
            Vector2d tmpPt2[4] = {Vector2d(), Vector2d(), curve2.GetStartPoint(), curve2.GetEndPoint()};

            double dists[4];
            dists[0] = DistanceCalculator::PointToCurve2d(tmpPt1[0], curve2, &tmpPt2[0]);
            dists[1] = DistanceCalculator::PointToCurve2d(tmpPt1[1], curve2, &tmpPt2[1]);
            dists[2] = DistanceCalculator::PointToCurve2d(tmpPt2[2], curve1, &tmpPt1[2]);
            dists[3] = DistanceCalculator::PointToCurve2d(tmpPt2[3], curve1, &tmpPt1[3]);

            double minDist = dists[0];
            int minI = 0;

            for (int i = 1; i < 4; i++) {
                if (dists[i] < minDist - Constants::DOUBLE_EPS) {
                    minDist = dists[i];
                    minI = i;
                }
            }

            if (point1) {
                point1->Set(tmpPt1[minI]);
            }
            if (point2) {
                point2->Set(tmpPt2[minI]);
            }
            return minDist;
        }

        double _GetMinDistanceFromEnd3d(
                const ICurve3d &curve1,
                const ICurve3d &curve2,
                Vector3d *point1,
                Vector3d *point2
        ) {
            Vector3d tmpPt1[4] = {curve1.GetStartPoint(), curve1.GetEndPoint(), Vector3d(), Vector3d()};
            Vector3d tmpPt2[4] = {Vector3d(), Vector3d(), curve2.GetStartPoint(), curve2.GetEndPoint()};

            double dists[4];
            dists[0] = DistanceCalculator::PointToCurve3d(tmpPt1[0], curve2, &tmpPt2[0]);
            dists[1] = DistanceCalculator::PointToCurve3d(tmpPt1[1], curve2, &tmpPt2[1]);
            dists[2] = DistanceCalculator::PointToCurve3d(tmpPt2[2], curve1, &tmpPt1[2]);
            dists[3] = DistanceCalculator::PointToCurve3d(tmpPt2[3], curve1, &tmpPt1[3]);

            double minDist = dists[0];
            int minI = 0;

            for (int i = 1; i < 4; i++) {
                if (dists[i] < minDist - Constants::DOUBLE_EPS) {
                    minDist = dists[i];
                    minI = i;
                }
            }

            if (point1) {
                point1->Set(tmpPt1[minI]);
            }
            if (point2) {
                point2->Set(tmpPt2[minI]);
            }
            return minDist;
        }
    }


// 距离计算器
    class DistanceCalculatorPrivate {
    public:

        static double PointToLine2d(const Vector2d &point, const Line2d &line, Vector2d *pMinDistancePoint = nullptr) {
            double t = line.GetParamAt(point);
            Vector2d foot = line.GetPointAt(t);

            if (line.GetRange().Contain(t)) {
                if (pMinDistancePoint) {
                    pMinDistancePoint->Set(foot.X(), foot.Y());
                }
                return point.DiatanceTo(foot);
            }
            const PointCurve2dDistanceResult &ret = _GetMinDistanceFromEnd<Vector2d, ICurve2d>(point, line);
            if (pMinDistancePoint) {
                pMinDistancePoint->Set(ret.m_foot);
            }
            return ret.m_distance;
        }

        static double PointToLine3d(const Vector3d &point, const Line3d &line, Vector3d *pMinDistancePoint = nullptr) {
            double t = line.GetParamAt(point);
            Vector3d foot = line.GetPointAt(t);

            if (line.GetRange().Contain(t)) {
                if (pMinDistancePoint) {
                    pMinDistancePoint->Set(foot.X(), foot.Y(), foot.Z());
                }
                return point.DiatanceTo(foot);
            }
            const PointCurve3dDistanceResult &ret = _GetMinDistanceFromEnd<Vector3d, ICurve3d>(point, line);
            if (pMinDistancePoint) {
                pMinDistancePoint->Set(ret.m_foot.X(), ret.m_foot.Y(), ret.m_foot.Z());
            }
            return ret.m_distance;
        }

        static double PointToPlane(const Vector3d &point, const Plane &plane, Vector3d *pFootPoint = nullptr) {
            return abs(PointToPlaneSigned(point, plane, pFootPoint));
        }

        /**
        * 点到Plane的有向距离，目前支持平面，点在法线同侧为正，在反向为负
        */
        static double PointToPlaneSigned(const Vector3d &point, const Plane &plane, Vector3d *pFootPoint = nullptr) {
            Vector3d originToPoint = plane.GetOrigin() - point;
            Vector3d norm = plane.GetNormal();
            double d = originToPoint.Dot(norm);
            if (pFootPoint) {
                Vector3d foot = point - (plane.GetNormal() * d);
                pFootPoint->Set(foot);
            }
            return d;
        }

        static double Line2dToLine2d(const Line2d &line1, const Line2d &line2,
                                     Vector2d *pMinDistancePoint1 = nullptr, Vector2d *pMinDistancePoint2 = nullptr) {
            if (!line1.IsParallelTo(line2)) {
                const Vector2d &dir1 = line1.GetDirection();
                const Vector2d &dir2 = line2.GetDirection();

                const Vector2d &t = LineLineIntersectUtils::GetLineLineIntersectParams2d(line1.GetOrigin(),
                                                                                         line2.GetOrigin(),
                                                                                         line1.GetDirection(),
                                                                                         line2.GetDirection());
                // 相交
                if (line1.GetRange().Contain(t[0]) && line2.GetRange().Contain(t[1])) {
                    if (pMinDistancePoint1) {
                        pMinDistancePoint1->Set(line1.GetPointAt(t[0]));
                    }

                    if (pMinDistancePoint2) {
                        pMinDistancePoint2->Set(line2.GetPointAt(t[1]));
                    }

                    return 0.0;
                }
            }
            return _GetMinDistanceFromEnd2d(line1, line2, pMinDistancePoint1, pMinDistancePoint2);
        }

        static double Line3dToLine3d(const Line3d &line1, const Line3d &line2,
                                     Vector3d *pMinDistancePoint1 = nullptr, Vector3d *pMinDistancePoint2 = nullptr) {
            // 1.相交和异面直线的垂足都在参数域内的情况
            if (!line1.IsParallelTo(line2)) {
                // 求两异面直线的最近距离点参数
                Vector3d dp = line2.GetOrigin() - line1.GetOrigin();
                const Vector3d &dir1 = line1.GetDirection();
                const Vector3d &dir2 = line2.GetDirection();

                double A[4] = {dir1.Dot(dir1), -dir1.Dot(dir2), dir2.Dot(dir1), -dir2.Dot(dir2)};
                double b[2] = {dir1.Dot(dp), dir2.Dot(dp)};
                double t[2];
                EquationsSolver::SolveInhomogeneousLinearEquations<2>(A, b, t);

                if (line1.GetRange().Contain(t[0]) && line2.GetRange().Contain(t[1])) {
                    Vector3d resPt1 = line1.GetPointAt(t[0]);
                    Vector3d resPt2 = line2.GetPointAt(t[1]);
                    if (pMinDistancePoint1) {
                        pMinDistancePoint1->Set(resPt1);
                    }
                    if (pMinDistancePoint2) {
                        pMinDistancePoint2->Set(resPt2);
                    }
                    return resPt1.DiatanceTo(resPt2);
                }
            }

            // 2.否则，最小距离一定在直线端点处取得
            return _GetMinDistanceFromEnd3d(line1, line2, pMinDistancePoint1, pMinDistancePoint2);
        }

    };

}