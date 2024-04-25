#pragma once

#include "ILoop.h"

namespace E3dMath {

    class LoopUtils {
    public:
        /**
         * 计算ILoop面积，ILoop为逆时针返回正值，顺时针返回负值
         */
        static double LoopArea(const ILoop &loop);

        /**
         *  是否是逆时针的环
         */
        static bool IsAnticlockwise(const ILoop &loop);

        /**
         * 是否为凹多边形，仅支持直线段ILoop
         */
        static bool IsConcave(const ILoop &loop);

        /**
         * 分割凹多边形为多个凸多边形
         * @results 输出参数，得到的多个凸多边形
         */
        static bool SplitConcaveLoop(const ILoop &loop, std::vector<std::unique_ptr<ILoop>> &results);

        /**
         * 分割凹多边形为多个凸多边形（一种性能更好的方法，但是分割出的多边形数量会较多）
         * @results 输出参数，得到的多个凸多边形
         */
        static bool SplitConcaveLoopFaster(const ILoop &loop, std::vector<std::unique_ptr<ILoop>> &results);

        /**
         * loop1与loop2是否相交
         */
        static bool IsIntersect(const ILoop &loop1, const ILoop &loop2);

        /**
         * loop1是否包含loop2
         */
        static bool ContainLoop(const ILoop &loop1, const ILoop &loop2);

        /**
         * loop1是否与loop2完全重合
         */
        static bool CoincideLoop(const ILoop &loop1, const ILoop &loop2);
    };


}
