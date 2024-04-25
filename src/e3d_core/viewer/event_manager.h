#pragma once

#include <functional>
#include <string>

namespace gmv {
    struct ActionResult;

    class ActionBase;

    enum class EventType {
        KeyBoardEvent = 1,
        MouseEvent = 2,
        ActionFinish = 3,
    };

// Event�����ӿ���
    class IEventArgs {
    public:
        virtual ~IEventArgs() {};
    };


    using EventCallback = std::function<bool(IEventArgs *pArgs)>;

    class EventManager {
    public:
        static EventManager *Get();

        bool AddEventCallback(EventType type, std::string eventName, EventCallback fun);

        bool SendEvent(EventType type, IEventArgs *pArgs);

        bool DeleteEventCallback(EventType type, std::string name);

    private:
        virtual ~EventManager() {};

        EventManager();

    private:
        // EventType To Callbacks; CallbackName To Callback
        std::unordered_map<EventType, std::unordered_map<std::string, EventCallback>> _eventCallbacks;
    };

} // namespace gmv
