#include "document.h"
#include "viewer/ui_viewer.h"
#include "geometry/Loop.h"
#include "easy3d/renderer/drawable_lines.h"
#include "viewer/geom_to_drawable.h"
#include "easy3d/renderer/drawable_points.h"
#include "app.h"

namespace gmv {

    Document::~Document() {

    }

    Document::Document() {
    }

    Document *Document::Get() {
        static Document manager;
        return &manager;
    }

    bool Document::DeleteElementById(ElementId id) {
        auto ite = _geomObjects.find(id);
        if (ite != _geomObjects.end()) {
            _geomObjects.erase(ite);
            GetViewer()->DeleteDrawableById(id);
            return true;
        }
        auto iteTemp = _tempGeomObjects.find(id);
        if (iteTemp != _tempGeomObjects.end()) {
            _tempGeomObjects.erase(iteTemp);
            GetViewer()->DeleteDrawableById(id);
            return true;
        }
        return false;
    }

    bool Document::DeleteAll() {
        _geomObjects.clear();
        _tempGeomObjects.clear();
        GetViewer()->clear_scene();
        return true;
    }

    gmv::UIViewer *Document::GetViewer() {
        return App::Get()->GetViewer();
    }

}