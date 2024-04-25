#pragma once

#include "geometry/Loop.h"
#include "common/define.h"

namespace E3dMath {

// 面积计算器
    class AreaCalculator {
    public:
        static double LoopArea(const Loop &loop);

    };


}