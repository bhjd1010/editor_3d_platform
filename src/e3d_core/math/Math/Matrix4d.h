#pragma once

#include "common/constants.h"
#include "Vector3d.h"
#include "Vector4d.h"
#include "Matrix3d.h"

namespace E3dMath {

/**
 * double型4x4矩阵，左乘矩阵
 */
    class Matrix4d : public E3dObject {
    public:
        // 构造单位矩阵
        static Matrix4d CreateIdentity();

        // 默认构造函数，单位矩阵
        Matrix4d();

        Matrix4d(double a11, double a12, double a13, double a14,
                 double a21, double a22, double a23, double a24,
                 double a31, double a32, double a33, double a34,
                 double a41, double a42, double a43, double a44);

        //  构造函数，四个三维列向量构造矩阵
        Matrix4d(const Vector3d &c1, const Vector3d &c2, const Vector3d &c3, const Vector3d &c4);

        Matrix4d(const Vector4d &c1, const Vector4d &c2, const Vector4d &c3, const Vector4d &c4);

        Matrix4d(const Matrix4d &matrix);

        bool MakeIdentity();

        /**
         * 设置自身矩阵为绕空间任意轴的旋转矩阵
         * \param pos  基点
         * \param dir  轴方向
         * \param radian  旋转角度
         */
        bool MakeRotate(const Vector3d &pos, const Vector3d &dir, double radian);

        //  设置自身矩阵为平移矩阵
        bool MakeTranslate(const Vector3d &t);

        // 把矩阵本身变为逆矩阵
        bool MakeInverse();

        // 自身矩阵不变，返回自身矩阵的逆矩阵
        bool GetInverse(Matrix4d &inversedMat) const;

        // 获得其转置矩阵
        Matrix4d GetTranspose() const;

        // 返回矩阵中的代表平移的分量
        Vector3d GetTranslation() const;

        // 返回三维旋转矩阵
        Matrix3d GetRotation() const;

        //  判断矩阵是否为单位阵
        bool IsIdentity() const;

        // 计算矩阵行列式的值
        double Det() const;

        bool Set(
                double a11, double a12, double a13, double a14,
                double a21, double a22, double a23, double a24,
                double a31, double a32, double a33, double a34,
                double a41, double a42, double a43, double a44);

        bool Set(double m[4][4]);

        /**
         * 三维点vec左乘矩阵，vec * this
         */
        Vector4d PreMultiply(const Vector4d &vec) const;

        /**
         * 三维点vec右乘矩阵，this * vec
         */
        Vector4d Multiply(const Vector4d &vec);

        /**
         * 左乘以另外一个矩阵，m * this，改变this
         */
        Matrix4d &PreMultiply(const Matrix4d &m);

        /**
         * 右乘以另外一个矩阵，this * m，改变this
         */
        Matrix4d &Multiply(const Matrix4d &m);

        void MakeZero();

        //  返回矩阵中的旋转部分对应的坐标轴分量
        bool GetRotationAxes(Vector3d &xAxis, Vector3d &yAxis, Vector3d &zAxis) const;

        // 设置矩阵的旋转矩阵和平移向量
        bool SetRotationAndTranslation(const Matrix3d &r, const Vector3d &t);

        // 设置自身矩阵为转置矩阵
        void MakeTranspose();

        //  根据平移向量的三个分量设置自身矩阵为平移矩阵
        void MakeTranslate(double tx, double ty, double tz);

        // 返回矩阵中的代表缩放的分量
        Vector3d GetScale() const;

        //  设置自身矩阵等比缩放矩阵
        void MakeScale(const Vector3d &pos, double scale);

        //  设置自身矩阵非等比缩放矩阵
        void MakeScale(const Vector3d &pos, const Vector3d &scales);

        // 自身矩阵乘以传入矩阵，结果设置为自身
        // this = this * m
        Matrix4d &operator*=(const Matrix4d &m);

        //矩阵赋值操作
        Matrix4d &operator=(const Matrix4d &m);

        //返回二维数组中某行的指针
        double *operator[](int i);

        //返回二维数组中某行的指针
        const double *operator[](int i) const;

        virtual MathObjectType GetType() const override { return MathObjectType::Matrix4d; }

    private:
        //  计算给定行和列的三阶行列式的值
        double Det(int r1, int r2, int r3, int c1, int c2, int c3) const;

        double m_data[4][4];
    };


//两个矩阵相加
    Matrix4d operator+(const Matrix4d &m1, const Matrix4d &m2);

//两个矩阵相减
    Matrix4d operator-(const Matrix4d &m1, const Matrix4d &m2);

//两个矩阵相乘
    Matrix4d operator*(const Matrix4d &m1, const Matrix4d &m2);

//矩阵乘以列向量，返回列向量
    Vector4d operator*(const Matrix4d &m, const Vector4d &v);

//行向量乘以矩阵，返回行向量
    Vector4d operator*(const Vector4d &v, const Matrix4d &m);

//判断两矩阵是否相等
    bool operator==(const Matrix4d &m1, const Matrix4d &m2);

//判断两矩阵是否不相等
    bool operator!=(const Matrix4d &m1, const Matrix4d &m2);

}


