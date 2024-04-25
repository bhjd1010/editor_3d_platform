#pragma once

#include "define.h"
#include "math/geometry/MathObjectType.h"

namespace E3dMath {

    class E3dObject {
    public:
        virtual ~E3dObject() {};

        virtual MathObjectType GetType() const = 0;

        virtual void Release() { delete this; };
    };

}