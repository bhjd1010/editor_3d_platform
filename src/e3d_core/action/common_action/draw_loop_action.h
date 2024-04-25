#pragma once

#include "action/action_frame/action_base.h"
#include "math/math/Vector3d.h"


namespace gmv {


    class DrawLoopAction : public ActionBase {
    public:

        virtual ~DrawLoopAction() {};

        DrawLoopAction();

        virtual bool Init() override;

        virtual std::string GetName() const override;

        virtual void OnActionFinished(const ActionResult &result) override;

        virtual void OnChildActionFinished(const ActionResult &result) override;

    protected:
        int _step = 0;
        std::vector<E3dMath::Vector3d> _points;
    };

}
