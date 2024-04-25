#include "loop_element.h"
#include "viewer/geom_to_drawable.h"
#include "easy3d/renderer/drawable_lines.h"

namespace gmv {

    bool LoopElement::Init(std::unique_ptr<E3dMath::ILoop> loop) {
        _loop = std::move(loop);
        return true;
    }

    const E3dMath::ILoop *LoopElement::GetGeometry() const {
        return _loop.get();
    }

    std::string LoopElement::GetName() const {
        return "Geo_Loop";
    }

    std::vector<easy3d::Drawable *> LoopElement::GetRenderNode() const {
        return std::vector<easy3d::Drawable *>{
                GeomToDrawable::LoopToLinesDrawable(_loop.get(), this->GetElementId().ToString())};
    }

    ElementType LoopElement::GetType() const {
        return ElementType::LOOP_ELE;
    }


}