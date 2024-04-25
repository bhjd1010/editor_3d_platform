#pragma once

#include "action/action_frame/action_base.h"


namespace gmv {

    class PickPointAction : public ActionBase {
    public:

        virtual ~PickPointAction() {};

        PickPointAction() : ActionBase() {};

        virtual std::string GetName() const override;

        virtual void OnActionFinished(const ActionResult &result) override;

        virtual bool _onLButtonDown(int x, int y, int modifiers) override;

        virtual bool _onLButtonUp(int x, int y, int modifiers) override;

        virtual bool _onRButtonDown(int x, int y, int modifiers) override;

        virtual bool _onRButtonUp(int x, int y, int modifiers) override;
    };

}
