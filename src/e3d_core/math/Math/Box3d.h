#pragma once

#include "math/common/define.h"
#include "math/common/constants.h"
#include "Vector3d.h"

namespace E3dMath {

/**
 * double型三维AABB包围盒
 */
    class Box3d : public E3dObject {
    public:
        // 创建一个空包围盒
        static Box3d CreateEmptyBox3d();

        // 通过最小点， 最大点创建Box3d
        static Box3d Create(const Vector3d &minPoint, const Vector3d &maxPoint);

        // 构造空的包围盒
        explicit Box3d();

        // 根据包围盒的最小点和最大点构造包围盒
        explicit Box3d(const Vector3d &minPoint, const Vector3d &maxPoint);

        // 拷贝构造包围盒
        Box3d(const Box3d &box);

        // 判断包围盒是否为空
        bool IsEmpty() const;

        // 缩放包围盒，以(0,0,0)为中心进行缩放
        bool ScaleBasedOnOriginPoint(double scaleX, double scaleY, double scaleZ);

        // 缩放包围盒，以包围盒中心点为中心按比例缩放
        bool ScaleBasedOnCenterPoint(double scaleX, double scaleY, double scaleZ);

        // 当前包围盒和传入点合并，并设置当前包围盒为合并的结果
        bool MergePoint(const Vector3d &point);

        // 当前包围盒和传入包围盒合并，并设置当前包围盒为合并后的结果
        bool MergeBox(const Box3d &box);

        // 平移当前包围盒
        bool Translate(const Vector3d &translation);

        // 获得当前包围盒和传入包围盒的交集
        Box3d GetIntersectBox(const Box3d &box) const;

        // 判断是否和传入的包围盒相交
        bool IsIntersect(const Box3d &box, double tolerance = Constants::DOUBLE_EPS) const;

        // 获得包围盒的最小点
        const Vector3d &GetMinPoint() const;

        // 获得包围盒的最大点
        const Vector3d &GetMaxPoint() const;

        // 获得包围盒的中心点
        Vector3d GetCenter() const;

        //在给定误差内，判断当前包围盒是否包含传入点（在包围盒内或在包围盒上）
        bool Contain(const Vector3d &point, double tolerance = Constants::DOUBLE_EPS) const;

        // 在给定误差下，判断当前包围盒是否包含传入的包围盒，包括内相切
        bool Contain(const Box3d &box, double tolerance = Constants::DOUBLE_EPS) const;

        // 赋值构造包围盒
        Box3d &operator=(const Box3d &box);

        // 设置包围盒的最小点和最大点
        bool Set(const Vector3d &minPoint, const Vector3d &maxPoint);

        // 获得包围盒的8个角点
        /**
                 *           7                              6
                        /-------------------------------
                       /|                             /|
                      / |                            / |
                     /  |                           /  |
                    /   |                          /   |
                   /    |                         /    |
                  /     |                        /     |
                 /      |                       /      |
             4  /       |                    5 /       |
               ---------|----------------------        |
               |        |                     |        |
               |        |                     |        |
               |        |------------------------------- 2
               |       / 3                    |       /
               |      /                       |      /
               |     /                        |     /
               |    /                         |    /
               |   /                          |   /
               |  /                           |  /
               | /                            | /
               |------------------------------|-
               0                              1
         */
        void GetCorners(Vector3d (&corners)[8]) const;

        // 获得包围盒的长度，宽度和高度
        Vector3d GetSize() const;

        // 初始化包围盒
        void MakeEmpty();

        // 判断点是否在包围盒内部（不在包围盒上）
        bool IsPointInBox(const Vector3d &point, double tolerance = Constants::DOUBLE_EPS) const;

        // 判断点是否在包围盒表面上
        bool IsPointOnBox(const Vector3d &point, double tolerance = Constants::DOUBLE_EPS) const;

        // 判断线段是否和包围盒相交
        bool
        IsIntersect(const Vector3d &rStartPt, const Vector3d &rEndPt, double tolerance = Constants::DOUBLE_EPS) const;

        virtual MathObjectType GetType() const override { return MathObjectType::Box3d; }

    private:
        Vector3d m_min;
        Vector3d m_max;
    };

// Difference
    Box3d operator-(const Box3d &b1, const Box3d &b2);

// Sum
    Box3d operator+(const Box3d &b1, const Box3d &b2);

// 判断两个包围盒的是否相等
    bool operator==(const Box3d &b1, const Box3d &b2);

    bool operator!=(const Box3d &b1, const Box3d &b2);

}
