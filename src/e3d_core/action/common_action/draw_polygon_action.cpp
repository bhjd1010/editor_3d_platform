#include "pick_point_action.h"
#include "element/document.h"
#include "viewer/ui_viewer.h"
#include "easy3d/gui/picker.h"
#include "easy3d/core/types.h"
#include "math/Vector3d.h"
#include "draw_polygon_action.h"
#include "action/action_frame/action_result.h"
#include "geometry/Loop.h"
#include "element/loop_element.h"
#include "draw_loop_action.h"
#include "element/polygon_element.h"
#include "geometry/Polygon.h"
#include "utils/debug_warn.h"

using namespace easy3d;

namespace gmv {

    DrawPolygonAction::DrawPolygonAction()
            : ActionBase() {
    }

    bool DrawPolygonAction::Init() {
        this->_runChildAction(std::make_unique<DrawLoopAction>());
        return true;
    }

    std::string DrawPolygonAction::GetName() const {
        return "DrawPolygonAction";
    }

    void DrawPolygonAction::OnActionFinished(const ActionResult &result) {

    }

    void DrawPolygonAction::OnChildActionFinished(const ActionResult &result) {
        if (result.isCanceled) {
            if (_paths.size() > 0) {
                std::vector<std::unique_ptr<E3dMath::ILoop>> loops;
                for (auto &path: _paths) {
                    loops.push_back(path->Clone());
                }
                std::unique_ptr<E3dMath::Polygon> polygon = std::make_unique<E3dMath::Polygon>(loops);
                if (!polygon->IsValid()) {
                    LOG_RETURN_VOID(false, "Polygon invalid");
                    this->_markCanceled(result);
                    return;
                }
                this->_markSuccess(DrawPolygonActionResult(true, false, std::move(polygon)));
                return;
            }
            this->_markCanceled(result);
        } else if (result.isSuccess) {
            const DrawLoopActionResult &drawLoopResult = static_cast<const DrawLoopActionResult &>(result);
            _paths.push_back(std::move(drawLoopResult.loop->Clone()));
            ElementId id = _DrawTempObject(std::move(drawLoopResult.loop->Clone()));
            this->_runChildAction(std::make_unique<DrawLoopAction>());
        }
    }

}