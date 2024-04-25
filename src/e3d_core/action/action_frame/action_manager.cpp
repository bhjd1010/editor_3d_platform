#include "action_manager.h"
#include "viewer/event_manager.h"
#include "action_base.h"
#include "viewer/ui_viewer.h"
#include "utils/debug_warn.h"

namespace {
    bool ProcessMouseEventPrivate(gmv::IEventArgs *pArgs) {
        gmv::MouseEventArgs *p = dynamic_cast<gmv::MouseEventArgs *>(pArgs);
        if (!pArgs) {
            DBG_WARN_RETURN_FALSE(pArgs, "pArgs invalid");
        }
        return gmv::ActionManager::Get()->ProcessMouseEvent(p->x, p->y, p->button, p->modifiers);
    }

    bool ProcessActionFinishEventPrivate(gmv::IEventArgs *pArgs) {
        gmv::ActionFinishEventArgs *p = dynamic_cast<gmv::ActionFinishEventArgs *>(pArgs);
        if (!pArgs) {
            DBG_WARN_RETURN_FALSE(pArgs, "pArgs invalid");
        }
        return gmv::ActionManager::Get()->ProcessActionFinishEvent(p->result, p->pAction);
    }
} // namespace
namespace gmv {

    ActionManager::ActionManager() {
        EventManager::Get()->AddEventCallback(EventType::MouseEvent, "ProcessMouseEvent", ProcessMouseEventPrivate);
        EventManager::Get()->AddEventCallback(EventType::ActionFinish, "ProcessActionFinishEventPrivate",
                                              ProcessActionFinishEventPrivate);
    }

    ActionManager *ActionManager::Get() {
        static ActionManager manager;
        return &manager;
    }

    bool ActionManager::RunAction(std::unique_ptr<ActionBase> action) {
        while (_actions.size() > 1) {
            _actions[_actions.size() - 1]->_markCanceled(ActionResult(false, true));
        }
        if (std::find_if(_actions.begin(), _actions.end(),
                         [&](std::unique_ptr<ActionBase> &item) -> bool { return action.get() == item.get(); }) !=
            _actions.end()) {
            throw ("action�Ѵ���");
            return false;
        }
        ActionBase *pAction = action.get();
        _actions.push_back(std::move(action));
        pAction->Init();

        return true;
    }

    bool ActionManager::RunChildAction(std::unique_ptr<ActionBase> action) {
        if (std::find_if(_actions.begin(), _actions.end(), [&](std::unique_ptr<ActionBase> &item) -> bool {
            return action.get() == item.get();
        }) != _actions.end()) {
            throw ("action�Ѵ���");
            return false;
        }
        ActionBase *pAction = action.get();
        _actions.push_back(std::move(action));
        pAction->Init();

        return true;
    }

    std::vector<const ActionBase *> ActionManager::GetActions() const {
        std::vector<const ActionBase *> results;
        for (auto &p: _actions) {
            results.push_back(p.get());
        }
        return results;
    }

    bool ActionManager::ProcessMouseEvent(int x, int y, int button, int modifiers) {
        ActionBase *currentAction = GetCurrentAction();
        if (!currentAction) {
            return false;
        }
        return currentAction->processMouseEvent(x, y, button, modifiers);
    }

    bool ActionManager::ProcessActionFinishEvent(const ActionResult &result, const ActionBase *pAction) {
        ActionBase *currentAction = GetCurrentAction();
        if (!currentAction || currentAction != pAction) {
            return false;
        }
        currentAction->OnActionFinished(result);
        _actions.pop_back();
        if (_actions.size() > 0) {
            _actions[_actions.size() - 1]->OnChildActionFinished(result);
        }
        return true;
    }

}