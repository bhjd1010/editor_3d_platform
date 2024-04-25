#pragma once

#include "ILoop.h"


namespace E3dMath {


    class IPolygon : public IGeometry {
    public:
        virtual std::vector<const ILoop *> GetAllLoops() const = 0;

        // 包含的Loop的数量
        virtual unsigned int Size() const = 0;

        /**
         *  环是否合法，封闭且无自交
         */
        virtual bool IsValid(double tol = Constants::DOUBLE_EPS) const = 0;

        virtual bool IsLineOnly() const = 0;

        virtual std::vector<std::vector<Vector2d>> ToPaths() const = 0;

        virtual std::unique_ptr<IPolygon> Clone() const = 0;
    };


}
