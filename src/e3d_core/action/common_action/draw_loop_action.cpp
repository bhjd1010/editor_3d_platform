#include "pick_point_action.h"
#include "element/document.h"
#include "viewer/ui_viewer.h"
#include "easy3d/gui/picker.h"
#include "easy3d/core/types.h"
#include "math/Vector3d.h"
#include "draw_loop_action.h"
#include "action/action_frame/action_result.h"
#include "geometry/Loop.h"
#include "element/loop_element.h"
#include "Line3d.h"

using namespace easy3d;

namespace gmv {

    DrawLoopAction::DrawLoopAction()
            : ActionBase() {
    }

    bool DrawLoopAction::Init() {
        this->_runChildAction(std::make_unique<PickPointAction>());
        return true;
    }

    std::string DrawLoopAction::GetName() const {
        return "DrawLoopAction";
    }

    void DrawLoopAction::OnActionFinished(const ActionResult &result) {

    }

    void DrawLoopAction::OnChildActionFinished(const ActionResult &result) {
        if (result.isCanceled) {
            if (_step == 0) {
                if (_points.size() > 2) {
                    std::vector<E3dMath::Vector2d> point2ds;
                    for (auto &pt3: _points) {
                        point2ds.push_back(E3dMath::Vector2d(pt3.X(), pt3.Y()));
                    }
                    auto loop = std::make_unique<E3dMath::Loop>(point2ds);
                    if (loop->IsValid()) {
                        this->_markSuccess(DrawLoopActionResult(true, false, std::move(loop)));
                        return;
                    }
                }
                this->_markCanceled(result);
            } else {
                _step = 0;
                this->_runChildAction(std::make_unique<PickPointAction>());
            }
        } else if (result.isSuccess) {
            _step += 1;
            const PickPointActionResult &pickResult = static_cast<const PickPointActionResult &>(result);
            auto point = std::make_unique<E3dMath::Vector3d>(pickResult.point->Clone());
            _points.push_back(point->Clone());
            ElementId id = _DrawTempObject(std::move(point));
            if (_points.size() > 1) {
                _DrawTempObject(
                        std::make_unique<E3dMath::Line3d>(_points[_points.size() - 2], _points[_points.size() - 1]));
            }
            this->_runChildAction(std::make_unique<PickPointAction>());
        }
    }

}