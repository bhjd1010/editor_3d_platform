#include "event_manager.h"
#include <utils/debug_warn.h>

namespace gmv {
    EventManager::EventManager() {}

    EventManager *EventManager::Get() {
        static EventManager manager;
        return &manager;
    }

    bool EventManager::AddEventCallback(EventType type, std::string eventName, EventCallback fun) {
        if (_eventCallbacks.find(type) != _eventCallbacks.end()) {
            auto &callbacks = _eventCallbacks[type];
            if (callbacks.find(eventName) != callbacks.end()) {
                DBG_WARN_RETURN_FALSE(false, "eventName invalid");
                return false;
            }
            callbacks[eventName] = fun;
            return true;
        }
        std::unordered_map<std::string, EventCallback> callbacks;
        callbacks[eventName] = fun;
        _eventCallbacks[type] = callbacks;
        return true;
    }

    bool EventManager::SendEvent(EventType type, IEventArgs *pArgs) {
        if (_eventCallbacks.find(type) == _eventCallbacks.end()) {
            return false;
        }
        auto &callbacks = _eventCallbacks[type];
        for (auto &kv: callbacks) {
            kv.second(pArgs);
        }
        return true;
    }

    bool EventManager::DeleteEventCallback(EventType type, std::string name) {
        if (_eventCallbacks.find(type) == _eventCallbacks.end()) {
            return false;
        }
        auto &callbacks = _eventCallbacks[type];
        return callbacks.erase(name) > 0;
    }

} // namespace gmv