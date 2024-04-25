
#include "Polygon.h"
#include <vector>
#include <memory>
#include "Loop.h"
#include "Polygon.h"
#include "LoopUtils.h"


namespace E3dMath {

    Polygon::Polygon(const std::vector<std::vector<Vector2d>> &paths) {
        for (auto &path: paths) {
            _loops.push_back(std::make_unique<Loop>(path));
        }
        _AdjustLoops();
    }

    Polygon::Polygon(std::vector<std::unique_ptr<ILoop>> &loops) {
        for (auto &loop: loops) {
            _loops.push_back(std::move(loop));
        }
        _AdjustLoops();
    }

    Polygon::Polygon(const Polygon &another) {
        for (auto &loop: another._loops) {
            _loops.push_back(loop->Clone());
        }
    }

    std::vector<const ILoop *> Polygon::GetAllLoops() const {
        std::vector<const ILoop *> loops;
        for (auto &loop: _loops) {
            if (!loop) {
                throw ("loop为空");
            }
            loops.push_back(loop.get());
        }
        return loops;
    }

    unsigned int Polygon::Size() const {
        return static_cast<unsigned int>(_loops.size());
    }

    bool Polygon::IsValid(double tol) const {
        for (auto &loop: _loops) {
            if (!loop->IsValid()) {
                return false;
            }
        }
        // loop1需要包含所有其他loop
        for (std::size_t i = 1; i < _loops.size(); ++i) {
            if (!LoopUtils::ContainLoop(*(_loops[0]), *(_loops[i]))) {
                return false;
            }
        }

        // loop[1]~loop[n-1]相互为相离关系
        for (std::size_t i = 1; i < _loops.size(); ++i) {
            for (std::size_t j = i + 1; j < _loops.size(); ++j) {
                if (LoopUtils::IsIntersect(*(_loops[i]), *(_loops[j]))) {
                    return false;
                }
            }
        }
        return true;
    }

    bool Polygon::IsLineOnly() const {
        for (auto &loop: _loops) {
            if (!loop->IsLineOnly()) {
                return false;
            }
        }

        return true;
    }

    std::vector<std::vector<Vector2d>> Polygon::ToPaths() const {
        std::vector<std::vector<Vector2d>> paths;
        for (auto &loop: _loops) {
            std::vector<Vector2d> path = loop->ToPath();
            paths.push_back(path);
        }
        return paths;
    }

    std::unique_ptr<IPolygon> Polygon::Clone() const {
        IPolygon *p = new Polygon(*this);
        return std::unique_ptr<IPolygon>(p);
    }

///////////////////////////////////////////////////////////////////
// IAesGeometry接口实现
    MathObjectType Polygon::GetType() const {
        return MathObjectType::Polygon;
    }

    void Polygon::Release() {
        delete this;
    }

    void Polygon::_AdjustLoops() {
        for (std::size_t i = 0; i < _loops.size(); ++i) {
            if (i == 0 && !LoopUtils::IsAnticlockwise(*(_loops[i]))) {
                _loops[i]->Reverse();
            } else if (i > 0 && LoopUtils::IsAnticlockwise(*(_loops[i]))) {
                _loops[i]->Reverse();
            }
        }
    }


}
