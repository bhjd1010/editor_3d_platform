#pragma once

#include "element.h"
#include "geometry/IGeometry.h"


namespace gmv {


    class TempElement : public Element {
    public:
        using Element::Element;

        bool Init(std::unique_ptr<E3dMath::E3dObject> geom);


        virtual std::string GetName() const override;

        virtual std::vector<easy3d::Drawable *> GetRenderNode() const override;

        virtual ElementType GetType() const override;

    private:
        std::unique_ptr<E3dMath::E3dObject> _geom;

    };
}
