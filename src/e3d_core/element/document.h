#pragma once

#include <unordered_map>
#include <memory>
#include "element.h"

namespace gmv {
    class UIViewer;

    const ElementId MAX_TEMP_ID(100000);

    class Document {
    public:
        static Document *Get();

        template<class ElementT>
        const ElementT *GetElementById(ElementId id) const {
            std::unordered_map<ElementId, std::unique_ptr<Element>>::iterator ite = _geomObjects.find(id);
            if (ite != _geomObjects.end()) {
                const Element *ele = ite->second.get();
                return dynamic_cast<const ElementT *>(ele);
            }
            return nullptr;
        }

        template<class ElementT>
        ElementT *GetElementByIdFW(Element id) {
            std::unordered_map<ElementId, std::unique_ptr<Element>>::iterator ite = _geomObjects.find(id);
            if (ite != _geomObjects.end()) {
                const Element *ele = ite->second.get();
                return dynamic_cast<ElementT *>(ele);
            }
            return nullptr;
        }

        template<class ElementT>
        std::vector<const ElementT *> GetElementsByType(ElementType type) const {
            std::vector<const ElementT *> eles;
            for (auto &kv: _geomObjects) {
                if (type != kv.second->GetType()) {
                    continue;
                }
                const Element *pp = kv.second.get();
                const ElementT *pEle = static_cast<const ElementT *>(pp);
                if (pEle) {
                    eles.push_back(pEle);
                }
            }
            return eles;
        }

        template<class ElementT>
        ElementT *CreateElement() {
            _cutId = ElementId(_cutId.AsInt64() + 1);
            ElementT *p = new ElementT(_cutId);
            std::unique_ptr<Element> ele = std::unique_ptr<Element>(p);
            _geomObjects[_cutId] = std::move(ele);
            return p;
        }

        template<class TempElementT>
        TempElementT *CreateTempElement() {
            _cutTempId = ElementId(_cutTempId.AsInt64() + 1);
            TempElementT *p = new TempElementT(_cutTempId);
            std::unique_ptr<Element> ele = std::unique_ptr<Element>(p);
            _tempGeomObjects[_cutTempId] = std::move(ele);
            return p;
        }

        bool DeleteElementById(ElementId id);

        bool DeleteAll();

        gmv::UIViewer *GetViewer();

    private:
        virtual ~Document();

        Document();

    private:
        std::unordered_map<ElementId, std::unique_ptr<Element>, ElementIdHash> _geomObjects;
        std::unordered_map<ElementId, std::unique_ptr<Element>, ElementIdHash> _tempGeomObjects;
        ElementId _cutId = ElementId(MAX_TEMP_ID);
        ElementId _cutTempId;
    };
}
