#pragma once

#include "common/define.h"
#include "common/constants.h"
#include "Vector2d.h"
#include "Vector3d.h"

namespace E3dMath {

/**
 * double型3x3矩阵，左乘矩阵
 */
    class Matrix3d : public E3dObject {
    public:
        static Matrix3d CreateIdentity();

        // 根据平移量构造平移矩阵
        static Matrix3d MakeTranslate(const Vector2d &t);

        // 根据平移量构造平移矩阵
        static Matrix3d MakeTranslate(double tx, double ty);

        /**
         * \brief 构造旋转矩阵
         * \param Pos  中心点
         * \param Angle  旋转角度弧度值，正值表示逆时针方向
         */
        static Matrix3d MakeRotate(const Vector2d &Pos, double Angle);

        /**
         * \brief 构造缩放矩阵（等比缩放）
         * \param Scale  缩放比例
         */
        static Matrix3d MakeScale(double Scale);

        /**
         * \brief 构造缩放矩阵（非等比缩放）
         * \param Scale  缩放比例
         */
        static Matrix3d MakeScale(const Vector2d &Scale);

        // 缺省为单位矩阵
        Matrix3d();

        // 按行传入
        Matrix3d(const double(&array)[9]);

        Matrix3d(double a11, double a12, double a13,
                 double a21, double a22, double a23,
                 double a31, double a32, double a33);

        // 用三个列向量，构造矩阵
        Matrix3d(const Vector3d &v1, const Vector3d &v2, const Vector3d &v3);

        Matrix3d(const Matrix3d &matrix);

        /**
         * 使当前矩阵变为单位矩阵
         */
        bool MakeIdentity();

        // 使矩阵的每个值为0
        void MakeZero();

        /**
         * 使当前矩阵变为其逆矩阵
         */
        bool MakeInverse();

        /**
         * 使当前矩阵变为其转置矩阵
         */
        void MakeTranspose();

        // 按行设置
        bool Set(const double(&array)[9]);

        // 获取当前矩阵的逆矩阵
        bool GetInverse(Matrix3d &inversedMat) const;

        // 获取当前矩阵的转置矩阵
        Matrix3d GetTranspose() const;

        bool IsIdentity() const;

        // 行列式的值
        double Det() const;

        // 设置矩阵位移分量
        bool SetTranslation(const Vector2d &t);

        bool SetTranslation(double tx, double ty);

        // 获取矩阵位移分量
        const Vector2d GetTranslation() const;

        // 返回矩阵中的旋转部分对应的坐标轴分量
        void GetRotationAxes(Vector2d &xAxis, Vector2d &yAxis) const;

        /**
         * 三维点vec左乘矩阵，vec * this
         */
        Vector3d PreMultiply(const Vector3d &vec) const;

        /**
         * 三维点vec右乘矩阵，this * vec
         */
        Vector3d Multiply(const Vector3d &vec);

        /**
         * 左乘以另外一个矩阵，m * this，改变this
         */
        Matrix3d &PreMultiply(const Matrix3d &m);

        /**
         * 右乘以另外一个矩阵，this * m，改变this
         */
        Matrix3d &Multiply(const Matrix3d &m);

        // 返回长度为3的double数组
        double *operator[](int i);

        const double *operator[](int i) const;

        Matrix3d &operator=(const Matrix3d &m);

        // 自身矩阵乘以传入矩阵，结果设置为自身
        // this = this * m
        Matrix3d &operator*=(const Matrix3d &m);

        virtual MathObjectType GetType() const override { return MathObjectType::Matrix3d; }

    private:
        double m_data[3][3];
    };


// 两矩阵相乘，返回一个新的结果矩阵，m = m1 * m2
    Matrix3d operator*(const Matrix3d &m1, const Matrix3d &m2);

// 矩阵乘以列向量，返回列向量，v_new = m * v
    Vector3d operator*(const Matrix3d &m, const Vector3d &v);

// 行向量乘以矩阵，返回行向量，v_new = v * m
    Vector3d operator*(const Vector3d &v, const Matrix3d &m);

// 判断两矩阵是否相等
    bool operator==(const Matrix3d &m1, const Matrix3d &m2);

    bool operator!=(const Matrix3d &m1, const Matrix3d &m2);

}
