#pragma once

#include "action/action_frame/action_base.h"

namespace gmv {

    class IntersectBVhAction : public ActionBase {
    public:

        virtual ~IntersectBVhAction() {};

        IntersectBVhAction() : ActionBase() {};

        virtual bool Init() override;

        virtual std::string GetName() const override;

        virtual void OnChildActionFinished(const ActionResult &result) override;

        virtual bool _onLButtonDown(int x, int y, int modifiers) override;

    };

}
