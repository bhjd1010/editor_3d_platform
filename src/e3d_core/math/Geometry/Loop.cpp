
#include "Loop.h"
#include <vector>
#include <memory>
#include "ICurve2d.h"
#include "geometry/GeometryUtils.h"
#include "algorithm/AlgorithmResultType.h"
#include "algorithm/PositionJudge.h"


namespace E3dMath {

    Loop::Loop(const std::vector<Vector2d> &points) {
        for (std::size_t i = 0; i < points.size(); ++i) {
            if (points[i] != points[(i + 1) % points.size()]) {
                _curves.push_back(NEW_AS_UNIQUE_PTR(Line2d, points[i], points[(i + 1) % points.size()]));
            }
        }
    }


    Loop::Loop(std::vector<std::unique_ptr<ICurve2d>> &curves) {
        for (auto &curve: curves) {
            _curves.push_back(std::move(curve));
        }
    }

    bool Loop::AddCurve(std::unique_ptr<ICurve2d> curve) {
        _curves.push_back(std::move(curve));
        return true;
    }

    std::vector<const ICurve2d *> Loop::GetAllCurves() const {
        std::vector<const ICurve2d *> curves;
        for (auto &c: _curves) {
            curves.push_back(c.get());
        }
        return curves;
    }

    unsigned int Loop::Size() const {
        return static_cast<unsigned int>(_curves.size());
    }

    bool Loop::IsValid(double tol /*= Constants::DOUBLE_EPS*/) const {
        std::vector<const ICurve2d *> curves;
        for (auto &p: _curves) {
            curves.push_back(p.get());
        }
        // 依次连接
        if (!GeomUtils::CurvesConnected2d(curves)) {
            return false;
        }
        // 首尾封闭
        if (_curves[0]->GetStartPoint() != _curves[_curves.size() - 1]->GetEndPoint()) {
            return false;
        }

        // 无自交
        for (std::size_t i = 0; i < _curves.size(); i++) {
            auto &cur1 = _curves[i];
            for (std::size_t j = i + 1; j < _curves.size(); j++) {
                auto &cur2 = _curves[j];
                CurveCuvePositonType posRes = PositionJudge::CurveCuvePosition2d(*(cur1.get()), *(cur2.get()));
                if (posRes != CurveCuvePositonType::INTERSECT_END && posRes != CurveCuvePositonType::NOT_INTERSECT) {
                    return false;
                }
            }
        }

        return true;
    }

    bool Loop::IsLineOnly() const {
        std::vector<const ICurve2d *> curves = GetAllCurves();
        for (auto &cv: curves) {
            if (cv->GetType() != MathObjectType::Line2d) {
                return false;
            }
        }
        return true;
    }

    std::vector<Vector2d> Loop::ToPath() const {
        std::vector<Vector2d> points;
        for (auto &p: _curves) {
            points.push_back(p->GetStartPoint());
        }
        points.push_back(_curves[_curves.size() - 1]->GetEndPoint());
        return points;
    }

    Box2d Loop::GetBoundingBox() const {
        Box2d box;
        for (auto &c: _curves) {
            box.MergeBox(c->GetBoundingBox());
        }
        return box;
    }

    std::unique_ptr<E3dMath::ILoop> Loop::Clone() const {
        std::vector<Vector2d> points = this->ToPath();
        points.pop_back();
        return std::make_unique<E3dMath::Loop>(points);
    }

    ILoop *Loop::Reverse() {
        std::reverse(_curves.begin(), _curves.end());
        for (std::unique_ptr<ICurve2d> &cv: _curves) {
            cv->Reverse();
        }
        return this;
    }

///////////////////////////////////////////////////////////////////
// IAesGeometry接口实现
    MathObjectType Loop::GetType() const {
        return MathObjectType::Loop;
    }

    void Loop::Release() {
        delete this;
    }

}
