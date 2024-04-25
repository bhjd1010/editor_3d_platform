#pragma once

#include <string>
#include <vector>

struct fastObjMesh;

namespace gmv {

    class UIUtils {
    public:
//        static std::vector<std::pair<std::string, fastObjMesh*>> LoadMesh();

        static std::string OpenFolder();

        static std::string filerPath;
    protected:
    private:
    };
}

