#pragma once

#include "element.h"
#include "geometry/IPolygon.h"
#include "geometry/Mesh.h"


namespace gmv {


    class MeshElement : public Element {
    public:
        using Element::Element;

        bool Init(std::unique_ptr<E3dMath::Mesh> mesh, std::string name = "");

        const E3dMath::Mesh *GetGeometry() const;

        virtual std::string GetName() const override;

        virtual std::vector<easy3d::Drawable *> GetRenderNode() const override;

        virtual ElementType GetType() const override;

    private:
        std::unique_ptr<E3dMath::Mesh> _mesh;
        std::string _name;
    };
}
