#include "intersect_bvh_action.h"
#include "element/document.h"
#include "viewer/ui_viewer.h"
#include "easy3d/gui/picker.h"
#include "element/line_element.h"
#include "utils/data_converter.h"
#include "element/point_element.h"
#include "ui/ui_creater.h"
#include "bvh/triangle_bvh.h"
#include "ui/ui_triangle_bvh.h"

namespace gmv {
    bool IntersectBVhAction::Init() {
        return true;
    }

    std::string IntersectBVhAction::GetName() const {
        return "IntersectBVhAction";
    }

    void IntersectBVhAction::OnChildActionFinished(const ActionResult &result) {
        ActionBase::OnChildActionFinished(result);
    }


    bool IntersectBVhAction::_onLButtonDown(int x, int y, int modifiers) {
        UIViewer *viewer = GetUIViewer();
        easy3d::vec3 pos, dir;
        viewer->camera()->convertClickToLine(x, y, pos, dir);
        if (UITriangleBVhMenu::GetBVH()) {
            E3dMath::Vector3d intersect;
            std::size_t idx;
            UITriangleBVhMenu::GetBVH()->Intersect(DataConverter::Vec3ToAesVector3d(pos),
                                                   DataConverter::Vec3ToAesVector3d(dir), intersect, idx);

            PointElement *pointEle = Document::Get()->CreateElement<PointElement>();
            pointEle->Init(std::make_unique<E3dMath::Vector3d>(intersect));
            pointEle->DrawElement();
        }
        return true;
    }
}