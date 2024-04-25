#pragma once

#include <unordered_map>
#include <memory>

namespace gmv {
    class UIViewer;

    class App {
    public:
        static App *Get();

        gmv::UIViewer *GetViewer();

    private:
        virtual ~App();

        App();

    private:
        std::unique_ptr<UIViewer> _viewer;
    };
}
