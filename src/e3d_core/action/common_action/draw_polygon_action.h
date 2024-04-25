#pragma once

#include "math/Vector3d.h"
#include "action/action_frame/action_base.h"


namespace gmv {
    class DrawPolygonAction : public ActionBase {
    public:
        virtual ~DrawPolygonAction() {};

        DrawPolygonAction();

        virtual bool Init() override;

        virtual std::string GetName() const override;

        virtual void OnActionFinished(const ActionResult &result) override;

        virtual void OnChildActionFinished(const ActionResult &result) override;

    protected:
        std::vector<std::unique_ptr<E3dMath::ILoop>> _paths;
    };

} // namespace gmv
