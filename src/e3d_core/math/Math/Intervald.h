#pragma once

#include "common/define.h"
#include "common/constants.h"
#include "e3d_object.h"

namespace E3dMath {

/**
 * double型区间定义
 */
    class Intervald : public E3dObject {
    public:
        //缺省为空区间
        explicit Intervald();

        /**
        * 构造方法，最小点和最大点
        * @param min
        * @param max
        * @param autoSwap 若min>max 是否自动交换min与max
        */
        explicit Intervald(double min, double max, bool autoSwap = false);

        Intervald(const Intervald &src);

        static Intervald CreateEmptyIntervald();

        static Intervald Create(double min, double max);

        // 使区间无穷大
        bool MakeInfinite();

        bool MakeEmpty();

        double GetMin() const;

        void SetMin(double min);

        double GetMax() const;

        void SetMax(double max);

        bool Set(double min, double max);

        bool IsEmpty() const;

        double Length() const;

        double Middle() const;

        Intervald Intersection(const Intervald &other) const;

        bool IsIntersect(const Intervald &other, double epsilon = Constants::DOUBLE_EPS) const;

        bool IsEqual(const Intervald &other, double epsilon = Constants::DOUBLE_EPS) const;

        bool Contain(double a, double epsilon = Constants::DOUBLE_EPS) const;

        // 带容差的判断区间是否在区间内
        bool Contain(const Intervald &other, double epsilon = Constants::DOUBLE_EPS) const;

        // 点是否在区间端点处
        bool ContainAtEnds(double a, double epsilon = Constants::DOUBLE_EPS) const;

        // 若数值在区间外, 将其拉回到临近的区间端点
        bool Clamp(double &value) const;

        // 区间集合减法，如果sub1、sub2都不空，说明this区间包含other区间
        bool Substract(const Intervald &other, Intervald &sub1, Intervald &sub2) const;

        // 合并，如果给定值a恰好在原来区间内，区间维持不变
        bool Merge(double a);

        // 合并区间
        bool Merge(const Intervald &other);

        // 区间比例变换，上下限都乘以指定因子
        Intervald operator*(double factor) const;

        // 增加区间的最小和最大值
        Intervald operator+(double value) const;

        // 减小区间的最小和最大值
        Intervald operator-(double value) const;

        // 区间的最小和最大值除以某个值
        Intervald operator/(double value) const;

        // 区间和另一个区间的最小和最大值分别相加
        Intervald operator+(const Intervald &other) const;

        // 区间和另一个区间的最小和最大值分别相减
        Intervald operator-(const Intervald &other) const;

        // 区间比例变换，this区间上下限都乘以指定因子
        Intervald &operator*=(double factor);

        virtual MathObjectType GetType() const override { return MathObjectType::Intervald; }

    private:
        double m_min, m_max;
    };

// 区间比例变换，上下限都乘以指定因子
    Intervald operator*(double factor, const Intervald &i);

// 判断区间是否相等
    bool operator==(const Intervald &v1, const Intervald &v2);

    bool operator!=(const Intervald &v1, const Intervald &v2);


}

