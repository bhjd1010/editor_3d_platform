#include "Box3d.h"
#include "Vector2d.h"
#include "MathUtils.h"
#include <math.h>
#include <cassert>
#include <limits>

namespace E3dMath {

    Box3d::Box3d() {
        MakeEmpty();
    }

    Box3d::Box3d(const Vector3d &minPoint, const Vector3d &maxPoint) {
        Set(minPoint, maxPoint);
    }

    Box3d::Box3d(const Box3d &box) {
        if (!box.IsEmpty()) {
            m_min = box.m_min;
            m_max = box.m_max;
        } else {
            MakeEmpty();
        }
    }

    Box3d &Box3d::operator=(const Box3d &box) {
        if (this != &box) {
            if (!box.IsEmpty()) {
                m_min = box.m_min;
                m_max = box.m_max;
            } else {
                MakeEmpty();
            }
        }
        return *this;
    }

    bool Box3d::Set(const Vector3d &minPoint, const Vector3d &maxPoint) {
        m_min = minPoint;
        m_max = maxPoint;

        return true;
    }

    Box3d operator-(const Box3d &b1, const Box3d &b2) {
        Vector3d center1 = b1.GetCenter();
        Vector3d center2 = b2.GetCenter();

        Vector3d center = center1 - center2;
        Vector3d half1 = b1.GetMaxPoint() - center1;
        Vector3d half2 = b2.GetMaxPoint() - center2;

        Vector3d half = half1 + half2;

        return Box3d(center - half, center + half);
    }

    Box3d operator+(const Box3d &b1, const Box3d &b2) {
        Vector3d center1 = b1.GetCenter();
        Vector3d center2 = b2.GetCenter();

        Vector3d center = center1 + center2;
        Vector3d half1 = b1.GetMaxPoint() - center1;
        Vector3d half2 = b2.GetMaxPoint() - center2;

        Vector3d half = half1 + half2;

        return Box3d(center - half, center + half);
    }

    bool operator==(const Box3d &b1, const Box3d &b2) {
        return ((b1.GetMinPoint() == b2.GetMinPoint()) && (b1.GetMaxPoint() == b2.GetMaxPoint()));
    }

    bool operator!=(const Box3d &b1, const Box3d &b2) {
        return !(b1 == b2);
    }

    Box3d Box3d::CreateEmptyBox3d() {
        return Box3d();
    }

    Box3d Box3d::Create(const Vector3d &minPoint, const Vector3d &maxPoint) {
        if (minPoint > maxPoint) {
            return Box3d();
        }
        return Box3d(minPoint, maxPoint);
    }

    bool Box3d::IsEmpty() const {
        return ((m_min.X() > m_max.X() + Constants::DOUBLE_EPS) ||
                (m_min.Y() > m_max.Y() + Constants::DOUBLE_EPS) ||
                (m_min.Z() > m_max.Z() + Constants::DOUBLE_EPS));
    }

    bool Box3d::ScaleBasedOnOriginPoint(double scaleX, double scaleY, double scaleZ) {
        if (IsEmpty())
            return false;

        if (scaleX < 0.0 ||
            scaleY < 0.0 ||
            scaleZ < 0.0) {
            return false;
        }

        m_min.X() *= scaleX;
        m_min.Y() *= scaleY;
        m_min.Z() *= scaleZ;

        m_max.X() *= scaleX;
        m_max.Y() *= scaleY;
        m_max.Z() *= scaleZ;

        return true;
    }

    bool Box3d::ScaleBasedOnCenterPoint(double scaleX, double scaleY, double scaleZ) {
        if (IsEmpty())
            return false;

        if (scaleX < 0.0 ||
            scaleY < 0.0) {
            return false;
        }

        Vector3d boxDir = m_max - m_min;

        Vector3d expandVec;
        expandVec.Set(boxDir.X() * scaleX, boxDir.Y() * scaleY, boxDir.Z() * scaleZ);

        expandVec.Set(expandVec.X() / 2.0, expandVec.Y() / 2.0, expandVec.Z() / 2.0);
        m_max += expandVec;
        m_min -= expandVec;

        return true;
    }

    bool Box3d::MergePoint(const Vector3d &point) {
        if (point.X() < m_min.X()) {
            m_min.SetX(point.X());
        }
        if (point.Y() < m_min.Y()) {
            m_min.SetY(point.Y());
        }
        if (point.Z() < m_min.Z()) {
            m_min.SetZ(point.Z());
        }

        if (point.X() > m_max.X()) {
            m_max.SetX(point.X());
        }
        if (point.Y() > m_max.Y()) {
            m_max.SetY(point.Y());
        }
        if (point.Z() > m_max.Z()) {
            m_max.SetZ(point.Z());
        }

        return true;
    }

    bool Box3d::MergeBox(const Box3d &box) {
        if (box.m_min[0] < m_min[0])
            m_min[0] = box.m_min[0];
        if (box.m_min[1] < m_min[1])
            m_min[1] = box.m_min[1];
        if (box.m_min[2] < m_min[2])
            m_min[2] = box.m_min[2];

        if (box.m_max[0] > m_max[0])
            m_max[0] = box.m_max[0];
        if (box.m_max[1] > m_max[1])
            m_max[1] = box.m_max[1];
        if (box.m_max[2] > m_max[2])
            m_max[2] = box.m_max[2];

        return true;
    }

    bool Box3d::Translate(const Vector3d &translation) {
        if (this->IsEmpty()) {
            return false;
        }

        m_min += translation;
        m_max += translation;
        return true;
    }

    Box3d Box3d::GetIntersectBox(const Box3d &box) const {
        if (this->IsEmpty() || box.IsEmpty()) {
            return Box3d();
        }

        Vector3d intersectMinPt(
                box.GetMinPoint().X() > GetMinPoint().X() ? box.GetMinPoint().X() : GetMinPoint().X(),
                box.GetMinPoint().Y() > GetMinPoint().Y() ? box.GetMinPoint().Y() : GetMinPoint().Y(),
                box.GetMinPoint().Z() > GetMinPoint().Z() ? box.GetMinPoint().Z() : GetMinPoint().Z()
        );
        Vector3d intersectMaxPt(
                box.GetMaxPoint().X() < GetMaxPoint().X() ? box.GetMaxPoint().X() : GetMaxPoint().X(),
                box.GetMaxPoint().Y() < GetMaxPoint().Y() ? box.GetMaxPoint().Y() : GetMaxPoint().Y(),
                box.GetMaxPoint().Z() < GetMaxPoint().Z() ? box.GetMaxPoint().Z() : GetMaxPoint().Z()
        );
        return Box3d(intersectMinPt, intersectMaxPt);
    }

    const Vector3d &Box3d::GetMinPoint() const {
        return m_min;
    }

    const Vector3d &Box3d::GetMaxPoint() const {
        return m_max;
    }

    Vector3d Box3d::GetCenter() const {
        if (this->IsEmpty()) {
            return Vector3d();
        }
        return (m_min + m_max) * 0.5;
    }

    bool Box3d::Contain(const Vector3d &point, double tolerance) const {
        if (this->IsEmpty()) {
            return false;
        }
        return (point.X() >= m_min.X() - tolerance) &&
               (point.X() <= m_max.X() + tolerance) &&
               (point.Y() >= m_min.Y() - tolerance) &&
               (point.Y() <= m_max.Y() + tolerance) &&
               (point.Z() >= m_min.Z() - tolerance) &&
               (point.Z() <= m_max.Z() + tolerance);
    }

    bool Box3d::Contain(const Box3d &box, double tolerance) const {
        if (this->IsEmpty() || box.IsEmpty()) {
            return false;
        }

        return (box.GetMinPoint().X() >= m_min.X() + tolerance) &&
               (box.GetMaxPoint().X() <= m_max.X() - tolerance) &&
               (box.GetMinPoint().Y() >= m_min.Y() + tolerance) &&
               (box.GetMaxPoint().Y() <= m_max.Y() - tolerance) &&
               (box.GetMinPoint().Z() >= m_min.Z() + tolerance) &&
               (box.GetMaxPoint().Z() <= m_max.Z() - tolerance);
    }

    void Box3d::GetCorners(Vector3d (&corners)[8]) const {
        if (this->IsEmpty()) {
            return;
        }

        corners[0].Set(m_min.X(), m_min.Y(), m_min.Z());
        corners[1].Set(m_max.X(), m_min.Y(), m_min.Z());
        corners[2].Set(m_max.X(), m_max.Y(), m_min.Z());
        corners[3].Set(m_min.X(), m_max.Y(), m_min.Z());

        corners[4].Set(m_min.X(), m_min.Y(), m_max.Z());
        corners[5].Set(m_max.X(), m_min.Y(), m_max.Z());
        corners[6].Set(m_max.X(), m_max.Y(), m_max.Z());
        corners[7].Set(m_min.X(), m_max.Y(), m_max.Z());
    }

    Vector3d Box3d::GetSize() const {
        if (this->IsEmpty()) {
            return Vector3d();
        }
        return m_max - m_min;
    }

    void Box3d::MakeEmpty() {
        if (std::numeric_limits<double>::has_infinity) {
            const double c_infinity = std::numeric_limits<double>::infinity();
            m_min.Set(c_infinity, c_infinity, c_infinity);
            m_max.Set(-c_infinity, -c_infinity, -c_infinity);
        } else {
            const double c_min = (std::numeric_limits<double>::min)();
            const double c_max = (std::numeric_limits<double>::max)();
            m_min.Set(c_max, c_max, c_max);
            m_max.Set(c_min, c_min, c_min);
        }
    }

    bool Box3d::IsPointInBox(const Vector3d &point, double tolerance) const {
        if (this->IsEmpty()) {
            return false;
        }

        return (point.X() > m_min.X() + tolerance) &&
               (point.X() < m_max.X() - tolerance) &&
               (point.Y() > m_min.Y() + tolerance) &&
               (point.Y() < m_max.Y() - tolerance) &&
               (point.Z() > m_min.Z() + tolerance) &&
               (point.Z() < m_max.Z() - tolerance);
    }

    bool Box3d::IsPointOnBox(const Vector3d &point, double tolerance) const {
        if (this->IsEmpty()) {
            return false;
        }

        //构造6个退化的三维包围盒，其实是二维包围盒
        Vector3d corners[8];
        GetCorners(corners);
        Box3d box0(corners[0], corners[3]);
        Box3d box1(corners[4], corners[7]);
        Box3d box2(corners[0], corners[5]);
        Box3d box3(corners[1], corners[7]);
        Box3d box4(corners[2], corners[7]);
        Box3d box5(corners[0], corners[6]);

        if (box0.Contain(point) || box1.Contain(point) || box2.Contain(point) ||
            box3.Contain(point) || box4.Contain(point) || box5.Contain(point)) {
            return true;
        }

        return false;
    }

    bool Box3d::IsIntersect(const Box3d &box, double tolerance) const {
        if (this->IsEmpty() || box.IsEmpty()) {
            return false;
        }
        return (m_max.X() >= box.GetMinPoint().X() - tolerance) &&
               (m_min.X() <= box.GetMaxPoint().X() + tolerance) &&
               (m_max.Y() >= box.GetMinPoint().Y() - tolerance) &&
               (m_min.Y() <= box.GetMaxPoint().Y() + tolerance) &&
               (m_max.Z() >= box.GetMinPoint().Z() - tolerance) &&
               (m_min.Z() <= box.GetMaxPoint().Z() + tolerance);
    }

    bool Box3d::IsIntersect(const Vector3d &rStartPt, const Vector3d &rEndPt, double tolerance) const {
        if (this->IsEmpty()) {
            return false;
        }

        Vector3d c = 0.5 * (m_min + m_max);     //包围盒中心
        Vector3d e = m_max - c;                       //包围盒半长向量
        Vector3d m = 0.5 * (rStartPt + rEndPt); //线段中点
        Vector3d d = rEndPt - m;                      //线段半长向量
        m = m - c;                                       //变换 box 和线段到原点

        //尝试世界坐标轴作为分离轴
        double adx = std::abs(d.X());
        e.SetX(e.X() + tolerance);
        if (std::abs(m.X()) > e.X() + adx) {
            return false;
        }

        double ady = std::abs(d.Y());
        e.SetY(e.Y() + tolerance);
        if (std::abs(m.Y()) > e.Y() + ady) {
            return false;
        }

        double adz = std::abs(d.Z());
        e.SetZ(e.Z() + tolerance);
        if (std::abs(m.Z()) > e.Z() + adz) {
            return false;
        }

        //增加容差项。当线段几乎平行于坐标轴的时候误差会增大
        if (std::abs(m.Y() * d.Z() - m.Z() * d.Y()) > e.Y() * adz + e.Z() * ady) {
            return false;
        }

        if (std::abs(m.Z() * d.X() - m.X() * d.Z()) > e.Z() * adx + e.X() * adz) {
            return false;
        }

        if (std::abs(m.X() * d.Y() - m.Y() * d.X()) > e.X() * ady + e.Y() * adx) {
            return false;
        }

        return true;
    }

}