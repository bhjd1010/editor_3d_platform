#pragma once

#include "common/define.h"
#include "common/constants.h"
#include "Vector3d.h"

namespace E3dMath {


// 三维坐标系定义（右手系）
    class Coordinate3d : public E3dObject {
    public:
        /**
        * 构造XOY坐标系
        * @param z 原点的Z坐标，默认为零
        */
        static Coordinate3d MakeXOY(double z = 0.0);

        static Coordinate3d MakeYOZ(double x = 0.0);

        static Coordinate3d MakeZOX(double y = 0.0);

        Coordinate3d();

        Coordinate3d(const Coordinate3d &other);

        Coordinate3d(const Vector3d &origin, const Vector3d &zDir = Vector3d(0, 0, 1.0));

        Coordinate3d(const Vector3d &origin, const Vector3d &xDir, const Vector3d &yDir);

        const Vector3d &X() const;

        const Vector3d &Y() const;

        const Vector3d &Z() const;

        const Vector3d &Origin() const;

        void SetOrigin(const Vector3d &origin);

        void SetXYDir(const Vector3d &xDir, const Vector3d &yDir);

        /**
         * z轴反向 (Y轴也会反向)
         */
        Coordinate3d &ReverseZDir();

        /**
         * 根据世界坐标系的点获取当前局部坐标系的点
         */
        Vector3d GetLocalPoint(const Vector3d &worldPt) const;

        /**
         * 根据当前局部坐标系的点获取世界坐标系的点
         */
        Vector3d GetWorldPoint(const Vector3d &uvw) const;

        /**
         * 根据世界坐标系的向量获取当前局部坐标系的向量
         */
        Vector3d GetLocalVector(const Vector3d &worldVec) const;

        /**
         * 由局部向量得到世界向量
         */
        Vector3d GetWorldVector(const Vector3d &localVec) const;

        virtual MathObjectType GetType() const override { return MathObjectType::Coordinate3d; }

    private:
        inline void _update() { _zDir = _xDir.Cross(_yDir); }

        //坐标系的原点
        Vector3d _origin = Vector3d::MakeZero();
        //坐标系的X轴
        Vector3d _xDir = Vector3d::MakeUintX();
        //坐标系的Y轴
        Vector3d _yDir = Vector3d::MakeUintY();
        //坐标系的Z轴，计算得到
        Vector3d _zDir = Vector3d::MakeUintZ();

        friend class Coordinate3dUtils;
    };

}


