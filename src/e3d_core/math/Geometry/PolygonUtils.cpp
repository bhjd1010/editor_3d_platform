#include "PolygonUtils.h"
#include "algorithm/ClipperUtils.h"
//#include "LoopUtils.h"


namespace E3dMath {

    double PolygonUtils::PolygonArea(const IPolygon &polygon) {
//	double area = 0.0;
//	for (auto& loop : polygon.GetAllLoops())
//	{
//		area += LoopUtils::LoopArea(*loop);
//	}
        return 0.0;
    }

    bool PolygonUtils::IsIntersect(const IPolygon &p1, const IPolygon &p2) {
        return false;
//	ClipperLib::Paths paths1;
//	ClipperLib::Paths paths2;
//	ClipperUtils::PolygonToClipperPaths(p1, paths1);
//	ClipperUtils::PolygonToClipperPaths(p2, paths2);
//
//	ClipperLib::Paths solution;
//	ClipperUtils::BoolOperate(BoolType::Intersection, paths1, paths2, solution);
//	return solution.size() != 0;
    }

    bool PolygonUtils::ContainPolygon(const IPolygon &p1, const IPolygon &p2) {
        return false;
//	ClipperLib::Paths paths1;
//	ClipperLib::Paths paths2;
//	ClipperUtils::PolygonToClipperPaths(p1, paths1);
//	ClipperUtils::PolygonToClipperPaths(p2, paths2);
//
//	ClipperLib::Paths solution1;
//	ClipperUtils::BoolOperate(BoolType::Difference, paths1, paths2, solution1);
//
//	ClipperLib::Paths solution2;
//	ClipperUtils::BoolOperate(BoolType::Difference, paths2, paths1, solution2);
//	return solution1.size() && !solution2.size();
    }

    bool PolygonUtils::CoincidePolygon(const IPolygon &p1, const IPolygon &p2) {
        return false;
//	ClipperLib::Paths paths1;
//	ClipperLib::Paths paths2;
//	ClipperUtils::PolygonToClipperPaths(p1, paths1);
//	ClipperUtils::PolygonToClipperPaths(p2, paths2);
//
//	ClipperLib::Paths solution1;
//	ClipperUtils::BoolOperate(BoolType::Difference, paths1, paths2, solution1);
//
//	ClipperLib::Paths solution2;
//	ClipperUtils::BoolOperate(BoolType::Difference, paths2, paths1, solution2);
//	return !solution1.size() && !solution2.size();
    }

}
