#pragma once

#include "element.h"
#include "geometry/ILoop.h"


namespace gmv {


    class LoopElement : public Element {
    public:
        using Element::Element;

        bool Init(std::unique_ptr<E3dMath::ILoop> loop);

        const E3dMath::ILoop *GetGeometry() const;

        virtual std::string GetName() const override;

        virtual std::vector<easy3d::Drawable *> GetRenderNode() const override;

        virtual ElementType GetType() const override;

    private:
        std::unique_ptr<E3dMath::ILoop> _loop;

    };
}
