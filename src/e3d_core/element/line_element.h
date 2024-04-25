#pragma once

#include "element.h"
#include "geometry/Line3d.h"
#include <memory>
#include "geometry/Line2d.h"


namespace gmv {


    class LineElement : public Element {
    public:
        using Element::Element;

        bool Init(std::unique_ptr<E3dMath::Line3d> line3d);

        bool Init(std::unique_ptr<E3dMath::Line2d> line2d);

        const E3dMath::Line3d *GetGeometry() const;

        virtual std::string GetName() const override;

        virtual std::vector<easy3d::Drawable *> GetRenderNode() const override;

        virtual ElementType GetType() const override;

    private:
        std::unique_ptr<E3dMath::Line3d> _line3d;

    };
}
