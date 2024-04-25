#include "app.h"
#include "viewer/ui_viewer.h"

namespace gmv {

    App::~App() {

    }

    App::App() {
        _viewer = std::unique_ptr<gmv::UIViewer>(new gmv::UIViewer("BVH Viewer"));
    }

    App *App::Get() {
        static App manager;
        return &manager;
    }

    gmv::UIViewer *App::GetViewer() {
        return _viewer.get();
    }

}