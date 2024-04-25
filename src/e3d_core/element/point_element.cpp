#include "point_element.h"
#include "easy3d/renderer/drawable_points.h"
#include "viewer/geom_to_drawable.h"

namespace gmv {

    bool PointElement::Init(std::unique_ptr<E3dMath::Vector3d> pt3d) {
        _point3d = std::move(pt3d);
        return true;
    }

    bool PointElement::Init(std::unique_ptr<E3dMath::Vector2d> pt2d) {
        _point3d = std::make_unique<E3dMath::Vector3d>(pt2d->X(), pt2d->Y(), 0);
        return true;
    }

    const E3dMath::Vector3d *PointElement::GetGeometry() const {
        return _point3d.get();
    }

    std::string PointElement::GetName() const {
        return "Geo_Point3d";
    }

    std::vector<easy3d::Drawable *> PointElement::GetRenderNode() const {
        if (!_point3d) {
            return std::vector<easy3d::Drawable *>();
        }
        return std::vector<easy3d::Drawable *>{
                GeomToDrawable::Vector3dToPointsDrawable(_point3d.get(), this->GetElementId().ToString())};
    }

    ElementType PointElement::GetType() const {
        return ElementType::POINT_ELE;
    }


}