#pragma once

#include "element.h"
#include "math/Vector3d.h"
#include "math/Vector2d.h"


namespace gmv {


    class PointElement : public Element {
    public:
        using Element::Element;

        bool Init(std::unique_ptr<E3dMath::Vector3d> pt3d);

        bool Init(std::unique_ptr<E3dMath::Vector2d> pt2d);

        const E3dMath::Vector3d *GetGeometry() const;

        virtual std::string GetName() const override;

        virtual std::vector<easy3d::Drawable *> GetRenderNode() const override;

        virtual ElementType GetType() const override;


    private:
        std::unique_ptr<E3dMath::Vector3d> _point3d;

    };
}
