#pragma once

#include "math/math/Vector3d.h"
#include <memory>
#include "math/geometry/ILoop.h"
#include "math/geometry/IPolygon.h"

namespace gmv {
    struct ActionResult {
        ActionResult(bool success, bool cancel) : isSuccess(success), isCanceled(cancel) {}

        bool isSuccess = true;
        bool isCanceled = false;
    };

    struct PickPointActionResult : public ActionResult {
        PickPointActionResult(bool success, bool cancel, std::unique_ptr<E3dMath::Vector3d> pt)
                : ActionResult(success, cancel), point(std::move(pt)) {
        }

        std::unique_ptr<E3dMath::Vector3d> point;
    };

    struct DrawLoopActionResult : public ActionResult {
        DrawLoopActionResult(bool success, bool cancel, std::unique_ptr<E3dMath::ILoop> pLoop)
                : ActionResult(success, cancel), loop(std::move(pLoop)) {
        }

        std::unique_ptr<E3dMath::ILoop> loop;
    };

    struct DrawPolygonActionResult : public ActionResult {
        DrawPolygonActionResult(bool success, bool cancel, std::unique_ptr<E3dMath::IPolygon> pPolygon)
                : ActionResult(success, cancel), polygon(std::move(pPolygon)) {
        }

        std::unique_ptr<E3dMath::IPolygon> polygon;
    };
} // namespace gmv
