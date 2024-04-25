#pragma once

#include <memory>
#include <vector>
#include "action_base.h"


namespace gmv {


    class ActionManager {
    public:
        static ActionManager *Get();

        bool RunAction(std::unique_ptr<ActionBase> action);

        bool RunChildAction(std::unique_ptr<ActionBase> action);

        ActionBase *GetCurrentAction() {
            if (_actions.size() == 0) {
                return nullptr;
            }
            return _actions[_actions.size() - 1].get();
        }

        std::vector<const ActionBase *> GetActions() const;

        bool ProcessMouseEvent(int x, int y, int button, int modifiers);

        bool ProcessActionFinishEvent(const ActionResult &result, const ActionBase *pAction);


    private:
        virtual ~ActionManager() {};

        ActionManager();

    private:
        std::vector<std::unique_ptr<ActionBase>> _actions;
    };

}
