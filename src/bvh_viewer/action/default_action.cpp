#include "default_action.h"

namespace gmv {
    bool DefaultAction::Init() {
        return true;
    }

    std::string DefaultAction::GetName() const {
        return "DefaultAction";
    }

    void DefaultAction::OnChildActionFinished(const ActionResult &result) {
        ActionBase::OnChildActionFinished(result);

    }

    void DefaultAction::OnActionFinished(const ActionResult &result) {
        throw ("DefaultAction");
    }


    bool DefaultAction::_onLButtonDown(int x, int y, int modifiers) {

        return true;
    }

    bool DefaultAction::_onLButtonUp(int x, int y, int modifiers) {
        return false;
    }

    bool DefaultAction::_onRButtonDown(int x, int y, int modifiers) {
        return false;

    }

    bool DefaultAction::_onRButtonUp(int x, int y, int modifiers) {
        return false;

    }

}