#pragma once


//#include "Define.h"
#include "IPolygon.h"

namespace E3dMath {

    class PolygonUtils {
    public:
        /**
         * 计算IPolygon面积，IPolygon为逆时针返回正值，顺时针返回负值
         */
        static double PolygonArea(const IPolygon &polygon);

        /**
         * polygon1与polygon2是否相交
         */
        static bool IsIntersect(const IPolygon &p1, const IPolygon &p2);

        /**
         * polygon1是否包含polygon2
         */
        static bool ContainPolygon(const IPolygon &p1, const IPolygon &p2);

        /**
         * polygon1是否与polygon2完全重合
         */
        static bool CoincidePolygon(const IPolygon &p1, const IPolygon &p2);
    };


}

