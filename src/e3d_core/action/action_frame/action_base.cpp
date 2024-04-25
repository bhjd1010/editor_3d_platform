#include "action_base.h"
#include "action_manager.h"
#include "viewer/event_manager.h"
#include "element/document.h"
#include "viewer/ui_viewer.h"
#include "element/temp_element.h"
#include "app.h"

namespace gmv {

    gmv::UIViewer *ActionBase::GetUIViewer() const {
        return App::Get()->GetViewer();
    }

    bool ActionBase::_runChildAction(std::unique_ptr<ActionBase> childAction) {
        return ActionManager::Get()->RunChildAction(std::move(childAction));

    }

    ElementId ActionBase::_DrawTempObject(std::unique_ptr<E3dMath::E3dObject> tempObject) {
        TempElement *ele = Document::Get()->CreateTempElement<TempElement>();
        if (!ele) {
            throw ("eleΪ��");
        }
        ele->Init(std::move(tempObject));
        ele->DrawElement();
        _tempObjectIds.push_back(ele->GetElementId());
        return ele->GetElementId();
    }

    bool ActionBase::_ClearTempObjects() {
        for (auto &id: _tempObjectIds) {
            Document::Get()->DeleteElementById(id);
        }
        _tempObjectIds.clear();

        return true;
    }

    void ActionBase::_MarkFinished(const ActionResult &result) {
        if (_isFinished) {
            return;
        }
        _isFinished = true;
        _ClearTempObjects();

        std::shared_ptr<ActionFinishEventArgs> pArgs = NEW_AS_SHARED_PTR(ActionFinishEventArgs, result, this);
        EventManager::Get()->SendEvent(EventType::ActionFinish, pArgs.get());
    }
}