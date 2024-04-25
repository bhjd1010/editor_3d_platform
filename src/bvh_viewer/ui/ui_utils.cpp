#include "ui_utils.h"
#include "element/document.h"
#include "easy3d/util/dialog.h"
#include "viewer/ui_viewer.h"
#include <string>
#include <vector>
#include <easy3d/util/resource.h>


using namespace gmv;

//std::vector<std::pair<std::string, fastObjMesh *>> UIUtils::LoadMesh() {
//    const std::string title("Please choose a file");
//    const std::string &default_path = easy3d::resource::directory() + "/data/";
//    const std::vector<std::string> &filters = {"Surface Mesh (*.obj *.ply *.off *.stl *.sm *.geojson *.trilist)",
//                                               "*.obj *.ply *.off *.stl *.sm *.geojson *.trilist",
//                                               "Point Cloud (*.bin *.ply *.xyz *.bxyz *.las *.laz *.vg *.bvg *.ptx)",
//                                               "*.bin *.ply *.xyz *.bxyz *.las *.laz *.vg *.bvg *.ptx",
//                                               "Polytope Mesh (*.plm *.pm *.mesh)",
//                                               "*.plm *.pm *.mesh",
//                                               "All Files (*.*)",
//                                               "*"};
//    const std::vector<std::string> &file_names = easy3d::dialog::open(title, default_path, filters, true);
//    std::vector<std::pair<std::string, fastObjMesh *>> results;
//    for (const auto &file_name: file_names) {
//        fastObjMesh *mesh = fast_obj_read(file_name.c_str());
//        results.push_back(std::make_pair(file_name, mesh));
//    }
//    return results;
//}

std::string UIUtils::OpenFolder() {
    std::string path = easy3d::dialog::open_folder();
    return path;
}

std::string UIUtils::filerPath;
