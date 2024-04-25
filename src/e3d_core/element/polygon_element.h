#pragma once

#include "element.h"
#include "geometry/IPolygon.h"


namespace gmv {


    class PolygonElement : public Element {
    public:
        using Element::Element;

        bool Init(std::unique_ptr<E3dMath::IPolygon> loop);

        const E3dMath::IPolygon *GetGeometry() const;

        virtual std::string GetName() const override;

        virtual std::vector<easy3d::Drawable *> GetRenderNode() const override;

        virtual ElementType GetType() const override;

    private:
        std::unique_ptr<E3dMath::IPolygon> _polygon;

    };
}
