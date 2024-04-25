#pragma once

#include "geometry/ICurve2d.h"
#include "geometry/ICurve3d.h"
#include "AlgorithmResultType.h"
#include "geometry/ILoop.h"
#include "geometry/IPolygon.h"

namespace E3dMath {

// 位置判断器
    class PositionJudge {
    public:
        static CurveCuvePositonType CurveCuvePosition2d(const ICurve2d &curve1, const ICurve2d &curve2);

        static CurveCuvePositonType CurveCuvePosition3d(const ICurve3d &curve1, const ICurve3d &curve2);

        /**
         * 点和Loop位置关系判断，需保证loop合法
         */
        static PointLoopPositonType PointLoopPosition(const Vector2d &point, const ILoop &loop);

        static PointPolygonPositonType PointPolygonPosition(const Vector2d &point, const IPolygon &polygon);


        /**
         * Loop和Loop位置关系判断，需保证loop合法
         */
        //static LoopLoopPositonType LoopLoopPosition(const Loop& loop1, const Loop& loop2);

    };


}