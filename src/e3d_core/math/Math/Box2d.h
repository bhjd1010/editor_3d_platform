#pragma once

#include "math/common/define.h"
#include "math/common/constants.h"
#include "Vector2d.h"

namespace E3dMath {

/**
 * double型二维AABB包围盒
 */
    class Box2d : public E3dObject {
    public:
        static Box2d CreateEmptyBox2d();

        static const Box2d Zero;

        //缺省构造函数:构造出一个无效的二维包围盒
        Box2d();

        // 用一个二维点构造大小为零的包围盒: 构造的包围盒两个角点均为输入的向量值
        explicit Box2d(const Vector2d &pt);

        // 用最小点和最大点构造包围盒
        Box2d(const Vector2d &min, const Vector2d &max);

        // 通过包围盒的最小点的坐标和最大点坐标构造包围盒
        Box2d(const double &minX, const double &minY, const double &maxX, const double &maxY);

        //  通过包围盒中心点的坐标和X与Y方向上的范围构造包围盒
        Box2d(const Vector2d &centerPos, const double &extentX, const double &extentY);

        // 拷贝构造包围盒
        Box2d(const Box2d &box);

        // 通过最小点， 最大点创建Box2d
        static Box2d Create(const Vector2d &min, const Vector2d &max);

        // 获得包围盒的最小点
        const Vector2d &GetMinPoint() const;

        // 获得包围盒的最大点
        const Vector2d &GetMaxPoint() const;

        // 平移包围盒
        bool Translate(const Vector2d &moveVector);

        // 设置包围盒的最小点和最大点
        bool Set(const Vector2d &min, const Vector2d &max);

        // 判断包围盒是否为空
        bool IsEmpty() const;

        // 获得包围盒的中心点
        Vector2d GetCenter() const;

        // 当前包围盒扩大使其包含传入点
        bool MergePoint(const Vector2d &point);

        // 当前包围盒和传入包围盒合并，并设置当前包围盒为合并的结果
        bool MergeBox(const Box2d &box);

        // 在给定误差内，判断当前包围盒是否包含传入点（在包围盒内或在包围盒上）
        bool Contain(const Vector2d &point, double tolerance = Constants::DOUBLE_EPS) const;

        //  在给定误差下，判断当前包围盒是否包含传入的包围盒，包括内相切
        bool Contain(const Box2d &box, double tolerance = Constants::DOUBLE_EPS) const;

        // 在给定误差内，判断传入包围盒是否和当前包围盒相交
        bool IsIntersect(const Box2d &box, double tolerance = Constants::DOUBLE_EPS) const;

        // 设置包围盒的最小点坐标和最大点坐标
        bool Set(const double minX, const double minY, const double maxX, const double maxY);

        // 获得包围盒的宽度和高度
        Vector2d GetSize() const;

        // 获得包围盒的4个角点
        void GetCorners(Vector2d corner[4]) const;

        // 初始化包围盒
        bool MakeEmpty();

        // 缩放外包盒，以(0, 0)为中心进行缩放
        bool ScaleBasedOnOriginPoint(double scaleX, double scaleY);

        // 缩放外包盒，以盒的中心为中心进行缩放
        bool ScaleBasedOnCenterPoint(double scaleX, double scaleY);

        /**
         * 获得当前包围盒和传入包围盒的交集
         * \param Box  传入包围盒
         * \param IntersectBox  交集
         * \param tolerance  给定误差
         * \return  true：存在相交包围盒，false: 不相交
         */
        bool GetIntersectBox(const Box2d &Box, Box2d &IntersectBox, double tolerance = Constants::DOUBLE_EPS);

        Box2d &operator=(const Box2d &box);

        // -=操作符，用于包围盒平移
        Box2d &operator-=(const Vector2d &v);

        // += 操作符，用于包围盒平移
        Box2d &operator+=(const Vector2d &v);

        // *= 操作符，用于包围盒缩放
        Box2d &operator*=(double scale);

        virtual MathObjectType GetType() const override { return MathObjectType::Box2d; }

    private:
        Vector2d m_min;
        Vector2d m_max;
    };

// 逻辑等号操作符，判断两个包围盒的是否相等
    bool operator==(const Box2d &b1, const Box2d &b2);


// 逻辑不等号操作符，判断两个包围盒是否不相等
    bool operator!=(const Box2d &b1, const Box2d &b2);

}
