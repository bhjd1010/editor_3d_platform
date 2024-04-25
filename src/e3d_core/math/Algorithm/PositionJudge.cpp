//#include "clipper/clipper.hpp"
#include "algorithm/ClipperUtils.h"
#include "algorithm/PositionJudgePrivate.h"
#include "PositionJudge.h"

namespace E3dMath {


    CurveCuvePositonType PositionJudge::CurveCuvePosition2d(const ICurve2d &curve1, const ICurve2d &curve2) {
        auto type1 = curve1.GetType();
        auto type2 = curve2.GetType();
        if (type1 == MathObjectType::Line2d && type2 == MathObjectType::Line2d) {
            const Line2d &line1 = dynamic_cast<const Line2d &>(curve1);
            const Line2d &line2 = dynamic_cast<const Line2d &>(curve2);
            return PositionJudgePrivate::Line2dLine2dPosition(line1, line2);

        }
        throw ("未支持的类型");

    }

    CurveCuvePositonType PositionJudge::CurveCuvePosition3d(const ICurve3d &curve1, const ICurve3d &curve2) {
        return CurveCuvePositonType();
    }

    PointLoopPositonType PositionJudge::PointLoopPosition(const Vector2d &point, const ILoop &loop) {
        return PointLoopPositonType::OUT_LOOP;
//    ClipperLib::IntPoint intPoint;
//	ClipperUtils::ScaleToClipperIntPoint(point, intPoint);
//    auto loopPts = loop.ToPath();
//    std::vector<ClipperLib::IntPoint> path;
//    ClipperUtils::ScaleToClipperIntPoints(loopPts, path);
//    int ret = ClipperLib::PointInPolygon(intPoint, path);
//    switch (ret)
//    {
//    case 0:
//        return PointLoopPositonType::OUT_LOOP;
//    case -1:
//        return PointLoopPositonType::ON_LOOP;
//    case 1:
//        return PointLoopPositonType::IN_LOOP;
//    default:
//        throw("不符合预期的返回值");
//    }
    }

    PointPolygonPositonType PositionJudge::PointPolygonPosition(const Vector2d &point, const IPolygon &polygon) {
        auto allLoops = polygon.GetAllLoops();
        for (std::size_t i = 0; i < allLoops.size(); ++i) {
            PointLoopPositonType type = PointLoopPosition(point, *(allLoops[i]));
            if (type == PointLoopPositonType::ON_LOOP) {
                return PointLoopPositonType::ON_LOOP;
            } else if (i == 0 && type == PointLoopPositonType::OUT_LOOP) {
                return PointLoopPositonType::OUT_LOOP;
            } else if (i > 0 && type == PointLoopPositonType::IN_LOOP) {
                return PointLoopPositonType::OUT_LOOP;
            }
        }
        return PointLoopPositonType::IN_LOOP;
    }

//LoopLoopPositonType PositionJudge::LoopLoopPosition(const Loop& loop1, const Loop& loop2)
//{
//
//    throw("不符合预期的返回值");
//
//}

}
