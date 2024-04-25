#pragma once

#include "math/Intervald.h"
#include <vector>

namespace E3dMath {

    /**
     * Curve Curve重合计算结果
     */
    struct CurveCurveOverlapResult {
        /** 重合段在第一条曲线上的参数 */
        Intervald range1;
        /** 重合段在第二条曲线上的参数 */
        Intervald range2;

        CurveCurveOverlapResult(const Intervald &r1, const Intervald &r2)
                : range1(r1), range2(r2) {
        }
    };

    /**
     * 曲线间位置关系类型
     */
    enum class CurveCuvePositonType {
        INTERSECT_END, // 相交于曲线端点
        INTERSECT_MID, // 相交于曲线内部
        NOT_INTERSECT, // 不相交
        OVERLAP, // 部分重叠
        OVERLAP_ALL, // 完全重叠
    };

    /**
     * 点与loop的关系类型:
     * OUT 点在loop外部
     * ON  点在loop边界上
     * IN 点在loop内部
     */
    enum class PointLoopPositonType {
        OUT_LOOP = 0,
        ON_LOOP = -1,
        IN_LOOP = 1,
    };
    using PointPolygonPositonType = PointLoopPositonType;

    /**
     * loop与loop的关系
     */
    enum class LoopLoopPositonType {
        // A在B的内部
        IN_LOOP = 0,

        // 重合
        EQUAL_LOOP = 1,

        // 相交
        INTERSECT_LOOP = 2,
        // A在B外部，相离
        OUT_LOOP = 3,

        // A包含B，B在A的内部
        CONTAIN_LOOP = 4,
    };

    template<class PointType>
    struct CurveCurveIntersectResult {
        /** 交点 */
        PointType point;
        /** 交点在第一条曲线上的参数 */
        double param1 = 0.0;
        /** 交点在第二条曲线上的参数 */
        double param2 = 0.0;
        /** 是否重合 */
        bool isOverlap = false;
        /** 若是重合，重合段在第一条曲线上的参数 */
        Intervald overlap1 = Intervald::CreateEmptyIntervald();
        /** 若是重合，重合段在第二条曲线上的参数 */
        Intervald overlap2 = Intervald::CreateEmptyIntervald();
    };
    using CurveCurveIntersectResult2d = CurveCurveIntersectResult<Vector2d>;
    using CurveCurveIntersectResult3d = CurveCurveIntersectResult<Vector3d>;
    using CurveCurveIntersectResult2ds = std::vector<CurveCurveIntersectResult<Vector2d>>;
    using CurveCurveIntersectResult3ds = std::vector<CurveCurveIntersectResult<Vector3d>>;

}