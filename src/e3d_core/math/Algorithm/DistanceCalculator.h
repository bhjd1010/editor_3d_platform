#pragma once

#include "common/define.h"

namespace E3dMath {
    class Vector2d;

    class ICurve2d;

    class Vector3d;

    class ICurve3d;

    class ISurface;

// 距离计算器
    class DistanceCalculator {
    public:
        /**
        * 点到二维曲线距离
        * @param point 点
        * @param curve 二维曲线
        * @param pMinDistancePoint 最小距离曲线上的点
        */
        static double
        PointToCurve2d(const Vector2d &point, const ICurve2d &curve, Vector2d *pMinDistancePoint = nullptr);

        /**
        * 点到二维曲线距离
        * @param point 点
        * @param curve 三维曲线
        * @param pMinDistancePoint 最小距离曲线上的点
        */
        static double
        PointToCurve3d(const Vector3d &point, const ICurve3d &curve, Vector3d *pMinDistancePoint = nullptr);

        /**
         * 点到Surface的距离
         * @param point 三维点
         * @param surface 曲面
         * @param footPoint  [out] 输出参数，若用户想要获取垂足点，则传入该参数
         * @returns 距离值
         */
        static double PointToSurface(const Vector3d &point, const ISurface &surface, Vector3d *pFootPoint = nullptr);

        /**
        * 点到Surface的有向距离，目前支持平面，点在法线同侧为正，在反向为负
        * @param point 三维点
        * @param surface 曲面
        * @param footPoint  [out] 输出参数，若用户想要获取垂足点，则传入该参数
        * @returns 距离值
        */
        static double
        PointToSurfaceSigned(const Vector3d &point, const ISurface &surface, Vector3d *pFootPoint = nullptr);

        /**
         * 二维曲线到二维曲线最近距离
         * @param curve1 二维曲线
         * @param curve2 二维曲线
         * @param pMinDistancePoint1 最小距离曲线1上的点
         * @param pMinDistancePoint2 最小距离曲线2上的点
         */
        static double
        Curve2dToCurve2d(const ICurve2d &curve1, const ICurve2d &curve2, Vector2d *pMinDistancePoint1 = nullptr,
                         Vector2d *pMinDistancePoint2 = nullptr);

        /**
         * 三维曲线到三维曲线最近距离
         * @param curve1 三维曲线
         * @param curve2 三维曲线
         * @param pMinDistancePoint1 最小距离曲线1上的点
         * @param pMinDistancePoint2 最小距离曲线2上的点
         */
        static double
        Curve3dToCurve3d(const ICurve3d &curve1, const ICurve3d &curve2, Vector3d *pMinDistancePoint1 = nullptr,
                         Vector3d *pMinDistancePoint2 = nullptr);

    };

}