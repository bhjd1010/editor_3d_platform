#include "element.h"
#include "Document.h"
#include "viewer/ui_viewer.h"

namespace gmv {

    Element::Element(const ElementId &id)
            : _id(id) {

    }

    ElementId Element::GetElementId() const {
        return _id;
    }

    bool Element::DrawElement() const {
        return Document::Get()->GetViewer()->DrawGeomObject(this);
    }

    std::string Element::GetName() const {
        return "";
    }

    std::vector<easy3d::Drawable *> Element::GetRenderNode() const {
        return std::vector<easy3d::Drawable *>();
    }

}