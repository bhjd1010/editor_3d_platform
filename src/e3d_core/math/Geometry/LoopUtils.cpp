#include <cmath>
#include "LoopUtils.h"
//#include "clipper/clipper.hpp"
#include "algorithm/ClipperUtils.h"
#include "algorithm/CurveCurveIntersect.h"
#include "Line2d.h"
#include "Loop.h"
#include "MathUtils.h"


namespace E3dMath {

    double LoopUtils::LoopArea(const ILoop &loop) {
        double area = 0.0;
//    if (!loop.Size())
//    {
//        return area;
//    }
//    std::vector<Vector2d> loopPts = loop.ToPath();
//    std::vector<ClipperLib::IntPoint> path;
//    ClipperUtils::ScaleToClipperIntPoints(loopPts, path);
//    area = ClipperLib::Area(path) / Constants::CLIPPER_SCALE / Constants::CLIPPER_SCALE;
        return area;
    }


    bool LoopUtils::IsAnticlockwise(const ILoop &loop) {
        return LoopArea(loop) > 0;
    }

    bool LoopUtils::IsConcave(const ILoop &loop) {
        std::vector<const ICurve2d *> curves = loop.GetAllCurves();
        if (!loop.IsLineOnly() || curves.size() < 3) {
            throw ("仅支持包含Line的ILoop，且Loop至少包含3个line");
            return false;
        }
        std::vector<double> crossValues(curves.size());
        for (std::size_t i = 0; i < curves.size(); ++i) {
            crossValues[i] = curves[i]->GetStartTangent().Cross(curves[(i + 1) % curves.size()]->GetStartTangent());
        }
        bool sign = std::signbit(crossValues[0]);
        auto ite = std::find_if(crossValues.begin(), crossValues.end(), [&](double value) -> bool {
                                    return std::signbit(value) != sign;
                                }
        );
        auto end = crossValues.end();
        if (ite == std::end(crossValues)) {
            return false;
        }
        return true;
    }

    bool LoopUtils::SplitConcaveLoop(const ILoop &loop, std::vector<std::unique_ptr<ILoop>> &results) {
        if (loop.Size() < 4) {
            return false;
        }
        if (!IsConcave(loop)) {
            return false;
        }

        std::vector<std::unique_ptr<ILoop>> concaveLoops;
        concaveLoops.push_back(loop.Clone()); // 凹多边形
        if (!IsAnticlockwise(*concaveLoops[0])) {
            concaveLoops[0]->Reverse();
        }

        while (concaveLoops.size() > 0) {
            std::unique_ptr<ILoop> concaveLoop = std::move(concaveLoops[concaveLoops.size() - 1]);
            concaveLoops.pop_back();
            std::vector<Vector2d> points = concaveLoop->ToPath();
            points.pop_back();
            std::vector<const ICurve2d *> curves = concaveLoop->GetAllCurves();
            for (std::size_t i = 0; i < curves.size(); ++i) {
                double crossVal = curves[i]->GetEndTangent().Cross(curves[(i + 1) % curves.size()]->GetEndTangent());
                if (!MathUtils::IsLessThan(crossVal, 0)) {
                    continue;
                }

                // 延长求交
                std::unique_ptr<Line2d> extendCurve = std::make_unique<Line2d>(curves[i]->GetEndPoint(),
                                                                               curves[(i + 1) %
                                                                                      curves.size()]->GetEndTangent().Clone().Reverse(),
                                                                               Intervald(0, Constants::MAX_SIZE));

                Vector2d intersect;
                std::size_t intersectCurveIdx = -1;
                double minDistance = Constants::MAX_SIZE;
                Vector2d refPoint = curves[i]->GetEndPoint();
                for (std::size_t j = 0; j < curves.size(); ++j) {
                    if (j == i || j == (i + 1) % curves.size()) {
                        continue;
                    }
                    CurveCurveIntersectResult2ds iResults = CurveCurveIntersect::Curve2ds(*(extendCurve.get()),
                                                                                          *curves[j]);
                    if (iResults.size() == 1) {
                        double dis = iResults[0].point.DiatanceTo(refPoint);
                        if (dis < minDistance) {
                            intersect = iResults[0].point;
                            intersectCurveIdx = j;
                            minDistance = dis;
                        }
                    }
                }
                if (intersectCurveIdx == -1) {
                    throw ("未得到交点");
                    return false;
                }

                std::vector<Vector2d> loop1Pts{intersect};
                std::vector<Vector2d> loop2Pts{intersect};
                for (std::size_t idx = intersectCurveIdx;
                     idx != (i + 1) % curves.size(); idx = (idx + 1) % curves.size()) {
                    loop1Pts.push_back(curves[idx]->GetEndPoint());
                }
                for (std::size_t idx = (i + 1) % curves.size();
                     idx != intersectCurveIdx; idx = (idx + 1) % curves.size()) {
                    loop2Pts.push_back(curves[idx]->GetEndPoint());
                }
                //生成两个新Loop
                std::unique_ptr<ILoop> newLoop1 = std::make_unique<Loop>(loop1Pts);
                std::unique_ptr<ILoop> newLoop2 = std::make_unique<Loop>(loop2Pts);
                IsConcave(*newLoop1) ? concaveLoops.push_back(std::move(newLoop1)) : results.push_back(
                        std::move(newLoop1));
                IsConcave(*newLoop2) ? concaveLoops.push_back(std::move(newLoop2)) : results.push_back(
                        std::move(newLoop2));
                break;
            }
        }

        return results.size() > 0;
    }

    bool LoopUtils::SplitConcaveLoopFaster(const ILoop &loop, std::vector<std::unique_ptr<ILoop>> &results) {
        if (loop.Size() < 4) {
            return false;
        }
        if (!IsConcave(loop)) {
            return false;
        }
        std::unique_ptr<ILoop> loopClone = loop.Clone();
        if (!IsAnticlockwise(loop)) {
            loopClone->Reverse();
        }

        while (true) {
            std::vector<Vector2d> points = loopClone->ToPath();
            points.pop_back();
            std::vector<const ICurve2d *> curves = loopClone->GetAllCurves();
            bool isConcave = false;
            for (std::size_t i = 0; i < curves.size(); ++i) {
                double crossVal = curves[i]->GetEndTangent().Cross(curves[(i + 1) % curves.size()]->GetEndTangent());
                if (MathUtils::IsLessThan(crossVal, 0)) {
                    isConcave = true;
                    if (i == 0) {
                        std::vector<Vector2d> newLoopPts{curves[curves.size() - 1]->GetStartPoint(),
                                                         curves[curves.size() - 1]->GetEndPoint(),
                                                         curves[i]->GetEndPoint()};
                        results.push_back(std::make_unique<Loop>(newLoopPts));
                    } else {
                        std::vector<Vector2d> newLoopPts{curves[i - 1]->GetStartPoint(), curves[i - 1]->GetEndPoint(),
                                                         curves[i]->GetEndPoint()};
                        results.push_back(std::make_unique<Loop>(newLoopPts));
                    }

                    points.erase(points.begin() + i);
                    loopClone = std::make_unique<Loop>(points);
                    break;
                }
            }
            if (!isConcave) {
                results.push_back(std::move(loopClone));
                break;
            }
        }
        return results.size() > 0;
    }

    bool LoopUtils::IsIntersect(const ILoop &loop1, const ILoop &loop2) {
        return false;
//    ClipperLib::Paths paths1;
//    ClipperLib::Paths paths2;
//    ClipperUtils::LoopToClipperPaths(loop1, paths1);
//    ClipperUtils::LoopToClipperPaths(loop2, paths2);
//
//    ClipperLib::Paths solution;
//    ClipperUtils::BoolOperate(BoolType::Intersection, paths1, paths2, solution);
//    return solution.size() != 0;
    }

    bool LoopUtils::ContainLoop(const ILoop &loop1, const ILoop &loop2) {
//    ClipperLib::Paths paths1;
//    ClipperLib::Paths paths2;
//    ClipperUtils::LoopToClipperPaths(loop1, paths1);
//    ClipperUtils::LoopToClipperPaths(loop2, paths2);
//
//    ClipperLib::Paths solution1;
//    ClipperUtils::BoolOperate(BoolType::Difference, paths1, paths2, solution1);
//
//    ClipperLib::Paths solution2;
//    ClipperUtils::BoolOperate(BoolType::Difference, paths2, paths1, solution2);
//    return solution1.size() && !solution2.size();
        return false;
    }

    bool LoopUtils::CoincideLoop(const ILoop &loop1, const ILoop &loop2) {
        return false;
//    ClipperLib::Paths paths1;
//    ClipperLib::Paths paths2;
//    ClipperUtils::LoopToClipperPaths(loop1, paths1);
//    ClipperUtils::LoopToClipperPaths(loop2, paths2);
//
//    ClipperLib::Paths solution1;
//    ClipperUtils::BoolOperate(BoolType::Difference, paths1, paths2, solution1);
//
//    ClipperLib::Paths solution2;
//    ClipperUtils::BoolOperate(BoolType::Difference, paths2, paths1, solution2);
//    return !solution1.size() && !solution2.size();
    }


}
