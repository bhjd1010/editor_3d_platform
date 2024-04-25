#include "Intervald.h"
#include "MathUtils.h"
#include <algorithm>
#include <math.h>
#include <cassert>
#include <limits>

namespace E3dMath {

    Intervald Intervald::CreateEmptyIntervald() {
        return Intervald();
    }

    Intervald Intervald::Create(double min, double max) {
        return Intervald(min, max);
    }

    namespace {
        // 交换区间上下限
        void Swap(Intervald &interval) {
            double min = interval.GetMin();
            double max = interval.GetMax();
            interval.Set(max, min);
        }


        // 区间正常化，如果下限大于上限，则交换它们
        void Normalize(Intervald &interval) {
            if (interval.GetMin() > interval.GetMax()) {
                Swap(interval);
            }
        }
    }

    Intervald operator*(double factor, const Intervald &i) {
        Intervald r(factor * i.GetMin(), factor * i.GetMax());
        Normalize(r);
        return r;
    }

    bool operator==(const Intervald &v1, const Intervald &v2) {
        return v1.GetMin() == v2.GetMin() && v1.GetMax() == v2.GetMax();
    }

    bool operator!=(const Intervald &v1, const Intervald &v2) {
        return v1.GetMin() != v2.GetMin() || v1.GetMax() != v2.GetMax();
    }

    Intervald::Intervald() {
        MakeEmpty();
    }

    Intervald::Intervald(double min, double max, bool autoSwap/* = false*/)
            : m_min(min), m_max(max) {
        if (m_min > m_max) {
            Swap(*this);
        }
    }

    Intervald::Intervald(const Intervald &src)
            : m_min(src.m_min), m_max(src.m_max) {}

    double Intervald::GetMin() const {
        return m_min;
    }

    void Intervald::SetMin(double min) {
        this->m_min = min;
    }

    double Intervald::GetMax() const {
        return m_max;
    }

    void Intervald::SetMax(double max) {
        this->m_max = max;
    }

    bool Intervald::Set(double min, double max) {
        m_min = min;
        m_max = max;
        return true;
    }

    double Intervald::Length() const {
        if (IsEmpty()) {
            return 0.0;
        }
        return fabs(m_max - m_min);
    }

    double Intervald::Middle() const {
        return 0.5 * (m_min + m_max);
    }

    bool Intervald::IsEmpty() const {
        return (m_min > m_max + Constants::DOUBLE_EPS);

    }

    bool Intervald::MakeEmpty() {
        if (std::numeric_limits<double>::has_infinity) {
            const double c_infinity = std::numeric_limits<double>::infinity();
            m_min = c_infinity;
            m_max = -c_infinity;
        } else {
            const double c_min = (std::numeric_limits<double>::min)();
            const double c_max = (std::numeric_limits<double>::max)();
            m_min = c_max;
            m_max = c_min;
        }
        return true;
    }

    bool Intervald::MakeInfinite() {
        if (std::numeric_limits<double>::has_infinity) {
            const double c_infinity = std::numeric_limits<double>::infinity();
            m_min = -c_infinity;
            m_max = c_infinity;
        } else {
            const double c_min = (std::numeric_limits<double>::min)();
            const double c_max = (std::numeric_limits<double>::max)();
            m_min = c_min;
            m_max = c_max;
        }
        return true;
    }

    Intervald Intervald::Intersection(const Intervald &other) const {
        if (this->IsEmpty() || other.IsEmpty()) {
            return Intervald();
        }
        return Intervald(m_min < other.m_min ? other.m_min : m_min, //最小值中最大的
                         m_max < other.m_max ? m_max : other.m_max); //最大值中最小的
    }

    bool Intervald::IsIntersect(const Intervald &other, double epsilon) const {
        if (this->IsEmpty() || other.IsEmpty()) {
            return false;
        }
        return m_max >= other.m_min - epsilon && m_min <= other.m_max + epsilon;
    }

    bool Intervald::IsEqual(const Intervald &other, double epsilon) const {
        if (this->IsEmpty() || other.IsEmpty()) {
            return false;
        }
        return fabs(m_min - other.m_min) <= epsilon && fabs(m_max - other.m_max) <= epsilon;
    }

    bool Intervald::Contain(double a, double epsilon) const {
        if (this->IsEmpty()) {
            return false;
        }
        return a >= m_min - epsilon && a <= m_max + epsilon;
    }

    bool Intervald::ContainAtEnds(double a, double epsilon /*= Constants::DOUBLE_EPS*/) const {
        if (this->IsEmpty()) {
            return false;
        }
        return abs(m_min - a) < epsilon || abs(m_max - a) < epsilon;
    }

    bool Intervald::Contain(const Intervald &other, double epsilon) const {
        if (this->IsEmpty() || other.IsEmpty()) {
            return false;
        }
        return Contain(other.m_min, epsilon) && Contain(other.m_max, epsilon);
    }

    bool Intervald::Clamp(double &value) const {
        if (this->IsEmpty()) {
            return false;
        }
        bool clamped = false;
        if (value < m_min) {
            value = m_min;
            clamped = true;
        }
        if (value > m_max) {
            value = m_max;
            clamped = true;
        }
        return clamped;
    }

    bool Intervald::Substract(const Intervald &other, Intervald &sub1, Intervald &sub2) const {
        if (this->IsEmpty() || other.IsEmpty()) {
            return false;
        }
        sub1.Set(m_min, std::min<double>(m_max, other.m_min));
        sub2.Set(std::max<double>(m_min, other.m_max), m_max);
        return true;
    }

    bool Intervald::Merge(double a) {
        if (this->IsEmpty()) {
            return false;
        }
        if (m_min > a) {
            m_min = a;
        }

        if (m_max < a) {
            m_max = a;
        }
        return true;
    }

    bool Intervald::Merge(const Intervald &other) {
        if (this->IsEmpty()) {
            return false;
        }
        Merge(other.m_min);
        Merge(other.m_max);
        return true;
    }

    Intervald Intervald::operator*(double factor) const {
        Intervald r(factor * m_min, factor * m_max);
        Normalize(r);
        return r;
    }

    Intervald Intervald::operator+(double value) const {
        return Intervald(m_min + value, m_max + value);
    }

    Intervald Intervald::operator-(double value) const {
        return Intervald(m_min - value, m_max - value);
    }

    Intervald Intervald::operator/(double value) const {
        double r1 = 1.0 / value;
        return operator*(r1);
    }

    Intervald Intervald::operator+(const Intervald &other) const {
        return Intervald(m_min + other.m_min, m_max + other.m_max);
    }

    Intervald Intervald::operator-(const Intervald &other) const {
        return Intervald(m_min - other.m_max, m_max - other.m_min);
    }

    Intervald &Intervald::operator*=(double factor) {
        m_min *= factor;
        m_max *= factor;
        return *this;
    }


}
