#pragma once

#include <functional>
#include "action_result.h"
#include "element/element_id.h"
#include "viewer/event_manager.h"

namespace gmv {
    using ActionFinishedCallback = std::function<void(const ActionResult &result)>;

    class UIViewer;

    struct ActionFinishEventArgs : public IEventArgs {
        ActionFinishEventArgs(const ActionResult &inRes, ActionBase *p) : result(inRes), pAction(p) {}

        const ActionResult &result;
        ActionBase *pAction;
    };

    class ActionBase {
    public:

        virtual ~ActionBase() {};

        ActionBase() {};

        virtual bool Init() { return true; };

        bool IsFinished() const { return _isFinished; };

        bool IsCanceled() const { return _isCanceled; };

        UIViewer *GetUIViewer() const;

        virtual std::string GetName() const = 0;

        bool processKeyboardEvent() {
            return false;
        }

        bool processMouseEvent(int x, int y, int button, int modifiers) {
            if (button == 0) {
                return _onLButtonDown(x, y, modifiers);
            } else if (button == 1) {
                return _onRButtonDown(x, y, modifiers);

            }
            return false;
        }

        virtual void OnChildActionFinished(const ActionResult &result) {};

        virtual void OnActionFinished(const ActionResult &result) {};
    protected:
        bool _runChildAction(std::unique_ptr<ActionBase> childAction);

        ElementId _DrawTempObject(std::unique_ptr<E3dMath::E3dObject> tempObject);

        bool _ClearTempObjects();

        void _markSuccess(const ActionResult &result) {
            _MarkFinished(result);
        }

        void _markCanceled(const ActionResult &result) {
            _MarkFinished(result);
        }

        virtual bool _onLButtonDown(int x, int y, int modifiers) {
            return false;
        }

        virtual bool _onLButtonUp(int x, int y, int modifiers) {
            return false;
        }

        virtual bool _onRButtonDown(int x, int y, int modifiers) {
            this->_markCanceled(ActionResult(false, true));
            return true;
        }

        virtual bool _onRButtonUp(int x, int y, int modifiers) {
            return false;
        }

    private:
        void _MarkFinished(const ActionResult &result);

    private:
        bool _isFinished = false;
        bool _isCanceled = false;

        std::vector<ElementId> _tempObjectIds;

        ActionFinishedCallback _actionFinishedCallback;

        friend class ActionManager;
    };

}
