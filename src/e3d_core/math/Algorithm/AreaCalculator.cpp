#include "geometry/LoopUtils.h"
#include "AreaCalculator.h"

namespace E3dMath {

    double AreaCalculator::LoopArea(const Loop &loop) {
        return LoopUtils::LoopArea(loop);
    }


}
