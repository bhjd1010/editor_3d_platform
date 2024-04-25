#pragma once

#include "ILoop.h"
#include <memory>
#include "IPolygon.h"


namespace E3dMath {

/**
 * 可以有一个外环和多个内环（洞）
 */
    class Polygon : public IPolygon {
    public:
        Polygon(const std::vector<std::vector<Vector2d>> &paths);

        Polygon(std::vector<std::unique_ptr<ILoop>> &loops);

        Polygon(const Polygon &another);


        std::vector<const ILoop *> GetAllLoops() const override;

        // 包含的Loop的数量
        unsigned int Size() const override;

        /**
         *  环是否合法，封闭且无自交
         */
        bool IsValid(double tol = Constants::DOUBLE_EPS) const override;

        bool IsLineOnly() const override;

        std::vector<std::vector<Vector2d>> ToPaths() const override;

        std::unique_ptr<IPolygon> Clone() const override;


        ///////////////////////////////////////////////////////////////////
        // IAesGeometry接口实现
        virtual MathObjectType GetType() const override;

        virtual void Release() override;


    private:
        std::vector<std::unique_ptr<ILoop>> _loops;

        void _AdjustLoops();
    };


}

