//#include "easy3d/viewer/viewer.h"
//#include "easy3d/util/initializer.h"
//
//int main(int argc, char** argv) {
//    easy3d::initialize();
//    easy3d::Viewer viewer("Test");
//    return viewer.run();
//}

#include <iostream>
#include <algorithm>

#include <easy3d/util/logging.h>

#include "viewer/ui_viewer.h"
#include "easy3d/core/poly_mesh.h"
#include "easy3d/renderer/drawable_lines.h"
#include "easy3d/renderer/drawable_points.h"
#include "element/document.h"
#include "viewer/app.h"
#include "ui/ui_creater.h"

using namespace easy3d;

int main(int argc, char **argv) {

    // start App

    gmv::App::Get();
    auto document = gmv::Document::Get();
    document->GetViewer()->registerUiPainer([]() {
        gmv::UICreater::CreateMenu();
    });
    document->GetViewer()->run();
}
