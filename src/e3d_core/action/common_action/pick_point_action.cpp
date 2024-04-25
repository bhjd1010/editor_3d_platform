#include "pick_point_action.h"
#include "math/Vector3d.h"
#include "easy3d/core/types.h"
#include "easy3d/gui/picker.h"
#include "element/document.h"
#include "viewer/ui_viewer.h"

using namespace easy3d;
namespace gmv {
    std::string PickPointAction::GetName() const {
        return "PickPointAction";
    }

    void PickPointAction::OnActionFinished(const ActionResult &result) {
        if (result.isCanceled) {
        }
    }


    bool PickPointAction::_onLButtonDown(int x, int y, int modifiers) {
        UIViewer *viewer = GetUIViewer();
        Picker pick(viewer->camera());
        Line3 line = pick.picking_line(x, y);
        Plane3 xoy(vec3(0, 0, 0), vec3(1, 0, 0), vec3(0, 1, 0));
        vec3 ptInXoy;
        xoy.intersect(line, ptInXoy);
        this->_markSuccess(
                PickPointActionResult(true, false,
                                      std::make_unique<E3dMath::Vector3d>(ptInXoy[0], ptInXoy[1], ptInXoy[2])));
        return true;
    }

    bool PickPointAction::_onLButtonUp(int x, int y, int modifiers) {
        return false;
    }

    bool PickPointAction::_onRButtonDown(int x, int y, int modifiers) {
        this->_markCanceled(ActionResult(false, true));
        return true;
    }

    bool PickPointAction::_onRButtonUp(int x, int y, int modifiers) {
        return false;
    }

} // namespace gmv