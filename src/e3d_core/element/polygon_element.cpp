#include "polygon_element.h"
#include "viewer/geom_to_drawable.h"
#include "easy3d/renderer/drawable_lines.h"

namespace gmv {

    bool PolygonElement::Init(std::unique_ptr<E3dMath::IPolygon> p) {
        _polygon = std::move(p);
        return true;
    }

    const E3dMath::IPolygon *PolygonElement::GetGeometry() const {
        return _polygon.get();
    }

    std::string PolygonElement::GetName() const {
        return "Geo_Polygon";
    }

    std::vector<easy3d::Drawable *> PolygonElement::GetRenderNode() const {
        std::vector<easy3d::Drawable *> results;
        int idx = 0;
        for (auto &p: _polygon->GetAllLoops()) {
            results.push_back(
                    GeomToDrawable::LoopToLinesDrawable(p,
                                                        this->GetElementId().ToString() + "_" + std::to_string(idx)));
            ++idx;
        }
        for (std::size_t i = 1; i < results.size(); ++i) {
            results[i]->set_uniform_coloring(results[0]->color());
        }
        return results;
    }

    ElementType PolygonElement::GetType() const {
        return ElementType::POLYGON_ELE;
    }


}