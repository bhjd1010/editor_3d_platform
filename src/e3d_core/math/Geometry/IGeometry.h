#pragma once

#include "math/common/define.h"
#include "math/common/constants.h"
#include "math/common/e3d_object.h"

namespace E3dMath {

// 几何对象基类
    class IGeometry : public E3dObject {
    public:
        virtual ~IGeometry() {};
    };

}
