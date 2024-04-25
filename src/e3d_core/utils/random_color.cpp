
#include "random_color.h"
#include <random>

using namespace easy3d;

namespace gmv {
    void RandomColor::Genete(easy3d::vec4 &color) {
        std::random_device rd;  // Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dis(0.0, 1.0);
        color[0] = dis(gen);
        color[1] = dis(gen);
        color[2] = dis(gen);
        color[3] = dis(gen);
    }
}