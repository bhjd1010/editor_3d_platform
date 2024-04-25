#include "line_element.h"
#include "math/Vector2d.h"
#include "math/Vector3d.h"
#include "viewer/geom_to_drawable.h"
#include "easy3d/renderer/drawable_lines.h"

namespace gmv {

    bool LineElement::Init(std::unique_ptr<E3dMath::Line3d> line3d) {
        _line3d = std::move(line3d);
        return true;
    }

    bool LineElement::Init(std::unique_ptr<E3dMath::Line2d> line2d) {
        E3dMath::Vector2d start = line2d->GetStartPoint();
        E3dMath::Vector2d end = line2d->GetEndPoint();
        E3dMath::Vector3d start3d(start.X(), start.Y(), 0);
        E3dMath::Vector3d end3d(end.X(), end.Y(), 0);
        _line3d = std::make_unique<E3dMath::Line3d>(start3d, end3d);
        return true;
    }

    const E3dMath::Line3d *LineElement::GetGeometry() const {
        return _line3d.get();
    }

    std::string LineElement::GetName() const {
        return "Geo_Line3d";
    }

    std::vector<easy3d::Drawable *> LineElement::GetRenderNode() const {
        return std::vector<easy3d::Drawable *>{
                GeomToDrawable::Line3dToLinesDrawable(_line3d.get(), this->GetElementId().ToString())};
    }

    ElementType LineElement::GetType() const {
        return ElementType::LINE_ELE;
    }


}