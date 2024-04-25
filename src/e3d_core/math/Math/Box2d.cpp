#include "Box2d.h"
#include "Vector2d.h"
#include "MathUtils.h"
#include <math.h>
#include <cassert>
#include <limits>

namespace E3dMath {

    Box2d Box2d::CreateEmptyBox2d() {
        return Box2d();
    }

    Box2d Box2d::Create(const Vector2d &min, const Vector2d &max) {
        return Box2d(min, max);

    }

    bool operator==(const Box2d &b1, const Box2d &b2) {
        return ((b1.GetMinPoint() == b2.GetMinPoint()) && (b1.GetMaxPoint() == b2.GetMaxPoint()));
    }

    bool operator!=(const Box2d &b1, const Box2d &b2) {
        return !(b1 == b2);
    }

    Box2d::Box2d() {
        MakeEmpty();
    }

    Box2d::Box2d(const Vector2d &pt) {
        Set(pt, pt);
    }

    Box2d::Box2d(const Vector2d &min, const Vector2d &max) {
        assert((min.X() <= max.X() + Constants::DOUBLE_EPS) && (min.Y() <= max.Y() + Constants::DOUBLE_EPS));
        Set(min, max);
    }

    Box2d::Box2d(const double &minX, const double &minY, const double &maxX, const double &maxY) {
        assert((minX < maxX + Constants::DOUBLE_EPS) && (minY < maxY + Constants::DOUBLE_EPS));
        Set(minX, minY, maxX, maxY);
    }

    Box2d::Box2d(const Vector2d &centerPos, const double &extentX, const double &extentY) {
        assert((extentX > 0.0) && (extentY > 0.0));
        Set(centerPos.X() - extentX / 2.0, centerPos.Y() - extentY / 2.0, centerPos.X() + extentX / 2.0,
            centerPos.Y() + extentY / 2.0);
    }

    Box2d::Box2d(const Box2d &box) {
        *this = box;
    }

    const Vector2d &Box2d::GetMinPoint() const {
        return m_min;
    }

    const Vector2d &Box2d::GetMaxPoint() const {
        return m_max;
    }

    bool Box2d::Set(const double minX, const double minY, const double maxX, const double maxY) {
        assert((minX < maxX + Constants::DOUBLE_EPS) && (minY < maxY + Constants::DOUBLE_EPS));
        m_min.Set(minX, minY);
        m_max.Set(maxX, maxY);
        return true;
    }

    Vector2d Box2d::GetSize() const {
        if (this->IsEmpty()) {
            return Vector2d::MakeZero();
        }
        return m_max - m_min;
    }

    Vector2d Box2d::GetCenter() const {
        if (this->IsEmpty()) {
            return Vector2d::MakeZero();
        }
        return Vector2d((m_max[0] + m_min[0]) * 0.5, (m_max[1] + m_min[1]) * 0.5);
    }

    bool Box2d::IsEmpty() const {
        return ((m_min.X() > m_max.X() + Constants::DOUBLE_EPS) ||
                (m_min.Y() > m_max.Y() + Constants::DOUBLE_EPS));
    }

    bool Box2d::Set(const Vector2d &min, const Vector2d &max) {
        assert((min.X() < max.X() + Constants::DOUBLE_EPS) && (min.Y() < max.Y() + Constants::DOUBLE_EPS));
        m_min = min;
        m_max = max;
        return true;
    }

    bool Box2d::ScaleBasedOnOriginPoint(double scaleX, double scaleY) {
        if (IsEmpty())
            return false;

        if (scaleX < 0.0 ||
            scaleY < 0.0) {
            return false;
        }

        m_min.X() *= scaleX;
        m_min.Y() *= scaleY;

        m_max.X() *= scaleX;
        m_max.Y() *= scaleY;

        return true;
    }

    bool Box2d::Translate(const Vector2d &moveVector) {
        if (this->IsEmpty()) {
            return false;
        }
        m_min += moveVector;
        m_max += moveVector;
        return true;
    }

    bool Box2d::MergePoint(const Vector2d &point) {
        if (point.X() < m_min.X())
            m_min[0] = point.X();
        if (point.Y() < m_min.Y())
            m_min[1] = point.Y();

        if (point.X() > m_max.X())
            m_max[0] = point.X();
        if (point.Y() > m_max.Y())
            m_max[1] = point.Y();

        return true;
    }

    bool Box2d::MergeBox(const Box2d &box) {
        if (box.m_min.X() < m_min.X())
            m_min[0] = box.m_min.X();
        if (box.m_min.Y() < m_min.Y())
            m_min[1] = box.m_min.Y();

        if (box.m_max.X() > m_max.X())
            m_max[0] = box.m_max.X();
        if (box.m_max.Y() > m_max.Y())
            m_max[1] = box.m_max.Y();

        return true;
    }

    bool Box2d::Contain(const Vector2d &point, double tolerance) const {
        return (point.X() >= GetMinPoint().X() - tolerance
                && point.X() <= GetMaxPoint().X() + tolerance
                && point.Y() >= GetMinPoint().Y() - tolerance
                && point.Y() <= GetMaxPoint().Y() + tolerance);
    }

    bool Box2d::Contain(const Box2d &box, double tolerance) const {
        if (this->IsEmpty() || box.IsEmpty()) {
            return false;
        }

        return GetMinPoint().X() <= box.GetMinPoint().X() - tolerance
               && GetMaxPoint().X() >= box.GetMaxPoint().X() + tolerance
               && GetMinPoint().Y() <= box.GetMinPoint().Y() - tolerance
               && GetMaxPoint().Y() >= box.GetMaxPoint().Y() + tolerance;
    }

    bool Box2d::IsIntersect(const Box2d &box, double tolerance) const {
        if (IsEmpty() || box.IsEmpty()) {
            return false;
        }

        return (m_max.X() >= box.GetMinPoint().X() - tolerance
                && m_min.X() <= box.GetMaxPoint().X() + tolerance
                && m_max.Y() >= box.GetMinPoint().Y() - tolerance
                && m_min.Y() <= box.GetMaxPoint().Y() + tolerance);
    }

    void Box2d::GetCorners(Vector2d corner[4]) const {
        bool bSortByMinMax = true;

        if (bSortByMinMax) {
            corner[0].Set(m_min.X(), m_min.Y());
            corner[1].Set(m_max.X(), m_min.Y());
            corner[2].Set(m_min.X(), m_max.Y());
            corner[3].Set(m_max.X(), m_max.Y());
        } else {
            corner[0].Set(m_max.X(), m_max.Y());
            corner[1].Set(m_min.X(), m_max.Y());
            corner[2].Set(m_min.X(), m_min.Y());
            corner[3].Set(m_max.X(), m_min.Y());
        }
    }

    bool Box2d::MakeEmpty() {
        if (std::numeric_limits<double>::has_infinity) {
            const double &c_infinity = std::numeric_limits<double>::infinity();
            m_min.Set(c_infinity, c_infinity);
            m_max.Set(-c_infinity, -c_infinity);
        } else {
            const double &c_min = (std::numeric_limits<double>::min)();
            const double &c_max = (std::numeric_limits<double>::max)();
            m_min.Set(c_max, c_max);
            m_max.Set(c_min, c_min);
        }
        return true;
    }

    bool Box2d::ScaleBasedOnCenterPoint(double scaleX, double scaleY) {
        if (IsEmpty())
            return false;

        if (scaleX < 0.0 ||
            scaleY < 0.0) {
            return false;
        }

        Vector2d boxDir = m_max - m_min;

        Vector2d expandVec;
        expandVec.Set(boxDir.X() * scaleX, boxDir.Y() * scaleY);

        expandVec.Set(expandVec.X() / 2.0, expandVec.Y() / 2.0);
        m_max += expandVec;
        m_min -= expandVec;

        return true;
    }

    bool Box2d::GetIntersectBox(const Box2d &Box, Box2d &IntersectBox, double tolerance) {
        Vector2d intersectMinPt(Box.GetMinPoint().X() > GetMinPoint().X() ? Box.GetMinPoint().X() : GetMinPoint().X(),
                                Box.GetMinPoint().Y() > GetMinPoint().Y() ? Box.GetMinPoint().Y() : GetMinPoint().Y());
        Vector2d intersectMaxPt(Box.GetMaxPoint().X() < GetMaxPoint().X() ? Box.GetMaxPoint().X() : GetMaxPoint().X(),
                                Box.GetMaxPoint().Y() < GetMaxPoint().Y() ? Box.GetMaxPoint().Y() : GetMaxPoint().Y());
        IntersectBox.Set(intersectMinPt, intersectMaxPt);
        if (IntersectBox.GetMaxPoint().X() < IntersectBox.GetMinPoint().X() - tolerance ||
            IntersectBox.GetMaxPoint().Y() < IntersectBox.GetMinPoint().Y() - tolerance) {
            return false;
        }

        return true;
    }

    Box2d &Box2d::operator=(const Box2d &box) {
        if (this == &box)
            return *this;

        m_min = box.m_min;
        m_max = box.m_max;

        return *this;
    }

    Box2d &Box2d::operator-=(const Vector2d &v) {
        m_min -= v;
        m_max -= v;
        return *this;
    }

    Box2d &Box2d::operator+=(const Vector2d &v) {
        m_min += v;
        m_max += v;
        return *this;
    }

    Box2d &Box2d::operator*=(double scale) {
        ScaleBasedOnOriginPoint(scale, scale);
        return *this;
    }
}