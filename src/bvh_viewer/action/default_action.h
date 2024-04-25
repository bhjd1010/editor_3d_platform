#pragma once

#include "action/action_frame/action_base.h"


namespace gmv {

    class DefaultAction : public ActionBase {
    public:

        virtual ~DefaultAction() {};

        DefaultAction() : ActionBase() {};

        virtual bool Init() override;

        virtual std::string GetName() const override;

        virtual void OnChildActionFinished(const ActionResult &result) override;

        virtual void OnActionFinished(const ActionResult &result) override;

        virtual bool _onLButtonDown(int x, int y, int modifiers) override;

        virtual bool _onLButtonUp(int x, int y, int modifiers) override;

        virtual bool _onRButtonDown(int x, int y, int modifiers) override;

        virtual bool _onRButtonUp(int x, int y, int modifiers) override;


    };

}
