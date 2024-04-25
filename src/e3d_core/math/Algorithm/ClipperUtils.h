//#pragma once
//#include <vector>
//#include "common/define.h"
//#include "clipper/clipper.hpp"
//#include "Vector2d.h"
//
//namespace E3dMath {
//
//enum class BoolType
//{
//    Intersection = 1, // 布尔交
//    Union = 2, // 布尔并
//    Difference = 3, // 布尔减
//};
//
//class IPolygon;
//class ILoop;
//
//class ClipperUtils
//{
//public:
//    /**
//     * E3dMath point Scale To Clipper IntPoint
//     */
//    static void ScaleToClipperIntPoints(const std::vector<Vector2d>& points, std::vector<ClipperLib::IntPoint>& path);
//
//    static void ScaleToClipperIntPoint(const Vector2d &point, ClipperLib::IntPoint &intPoint);
//
//    /**
//     * E3dMath Loop To Clipper Paths (会乘以clipper缩放系数)
//     */
//    static void LoopToClipperPaths(const ILoop& loop, ClipperLib::Paths& paths);
//
//	static void PolygonToClipperPaths(const IPolygon &polygon, ClipperLib::Paths &paths);
//
//    static bool BoolOperate(BoolType type, ClipperLib::Paths paths1, ClipperLib::Paths paths2, ClipperLib::Paths& solution);
//};
//
//}
