//#include "ClipperUtils.h"
//
//namespace E3dMath {
//
//}
//
//bool E3dMath::ClipperUtils::BoolOperate(E3dMath::BoolType type, ClipperLib::Paths paths1, ClipperLib::Paths paths2,
//                                        ClipperLib::Paths &solution) {
//    ClipperLib::Clipper clipper;
//    clipper.AddPaths(paths1, ClipperLib::ptSubject, true);
//    clipper.AddPaths(paths2, ClipperLib::ptClip, true);
//
//    ClipperLib::ClipType clipType = ClipperLib::ClipType::ctIntersection;
//    switch (type)
//    {
//        case BoolType::Intersection:
//            clipType = ClipperLib::ClipType::ctIntersection;
//            break;
//        case BoolType::Union:
//            clipType = ClipperLib::ClipType::ctUnion;
//            break;
//        case BoolType::Difference:
//            clipType = ClipperLib::ClipType::ctDifference;
//            break;
//        default:
//            throw("未支持的Bool Operate类型");
//    }
//    return clipper.Execute(clipType, solution, ClipperLib::pftNonZero, ClipperLib::pftNonZero);
//}
//
//void E3dMath::ClipperUtils::PolygonToClipperPaths(const E3dMath::IPolygon &polygon, ClipperLib::Paths &paths) {
//    std::vector<std::vector<Vector2d>> loops = polygon.ToPaths();
//    for (auto &loop : loops) {
//        ClipperLib::Path path;
//        ScaleToClipperIntPoints(loop, path);
//        paths.push_back(path);
//    }
//}
//
//void E3dMath::ClipperUtils::LoopToClipperPaths(const E3dMath::ILoop &loop, ClipperLib::Paths &paths) {
//    std::vector<Vector2d> loopPts = loop.ToPath();
//    ClipperLib::Path path;
//    ScaleToClipperIntPoints(loopPts, path);
//    paths.push_back(path);
//}
//
//void E3dMath::ClipperUtils::ScaleToClipperIntPoint(const E3dMath::Vector2d &point, ClipperLib::IntPoint &intPoint) {
//    ClipperLib::cInt scale = Constants::CLIPPER_SCALE;
//    intPoint.X = static_cast<ClipperLib::cInt>(point.X() * scale);
//    intPoint.Y = static_cast<ClipperLib::cInt>(point.Y() * scale);
//}
//
//void E3dMath::ClipperUtils::ScaleToClipperIntPoints(const std::vector<Vector2d> &points,
//                                                    std::vector<ClipperLib::IntPoint> &path) {
//    ClipperLib::cInt scale = Constants::CLIPPER_SCALE;
//    for (auto& pt : points)
//    {
//        path.push_back(ClipperLib::IntPoint(static_cast<ClipperLib::cInt>(pt.X() * scale),
//                                            static_cast<ClipperLib::cInt>(pt.Y() * scale)));
//    }
//}
