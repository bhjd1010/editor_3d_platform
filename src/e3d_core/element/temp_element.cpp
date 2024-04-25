#include "temp_element.h"
#include "viewer/geom_to_drawable.h"
#include "math/Vector3d.h"
#include "geometry/Line3d.h"
#include "geometry/Loop.h"
#include "easy3d/renderer/drawable_lines.h"
#include "easy3d/renderer/drawable_points.h"

namespace gmv {

    bool TempElement::Init(std::unique_ptr<E3dMath::E3dObject> geom) {
        _geom = std::move(geom);
        return true;
    }

    std::string TempElement::GetName() const {
        return "Temp_Element";
    }

    std::vector<easy3d::Drawable *> TempElement::GetRenderNode() const {
        E3dMath::MathObjectType type = _geom->GetType();
        switch (type) {
            case E3dMath::MathObjectType::Vector3d:
                return std::vector<easy3d::Drawable *>{GeomToDrawable::Vector3dToPointsDrawable(
                        dynamic_cast<E3dMath::Vector3d *>(_geom.get()), this->GetElementId().ToString())};
            case E3dMath::MathObjectType::Line3d:
                return std::vector<easy3d::Drawable *>{GeomToDrawable::Line3dToLinesDrawable(
                        dynamic_cast<E3dMath::Line3d *>(_geom.get()), this->GetElementId().ToString())};
            case E3dMath::MathObjectType::Loop:
                return std::vector<easy3d::Drawable *>{GeomToDrawable::LoopToLinesDrawable(
                        dynamic_cast<E3dMath::Loop *>(_geom.get()), this->GetElementId().ToString())};
            default:
                throw ("δ֧�ֵ�����");
        }
        return std::vector<easy3d::Drawable *>();
    }

    ElementType TempElement::GetType() const {
        return ElementType::TEMP_ELE;
    }


}