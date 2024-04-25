#pragma once

#include "common/define.h"
#include "3rd_party/eigen/Eigen/Dense"

namespace E3dMath {

// 非线性方程组求解器
    class EquationsSolver {
    public:
        //***********************************************************
        // Method:    解 n 维非线性方程组 AX = b
        // Parameter: const unsigned int n：方程个数
        // Parameter: const double * A：size为 n * n 的数组，表示 n * n 方阵，数组中逐行排列矩阵数据
        // Parameter: const double * b：size为 n * 1 的数组，表示 n * 1 矩阵
        // Parameter: double * X：输出参数。方程组的解向量，size为 n * 1 的数组，表示 n * 1 矩阵
        // Returns:   bool
        //***********************************************************
        template<const unsigned int n>
        static bool SolveInhomogeneousLinearEquations(const double *A, const double *b, double *X) {
            Eigen::Matrix<double, n, n> _A;
            Eigen::Matrix<double, n, 1> _b;
            for (unsigned int i = 0; i < n; ++i) {
                _b(i, 0) = b[i];
                for (unsigned int j = 0; j < n; ++j) {
                    _A(i, j) = A[n * i + j];
                }
            }

            // https://eigen.tuxfamily.org/dox/group__TutorialLinearAlgebra.html

            if (_A.fullPivLu().rank() < n) {
                return false;
            }

            Eigen::Matrix<double, n, 1> _X;
            _X = _A.partialPivLu().solve(_b);
            for (unsigned int i = 0; i < n; ++i) {
                X[i] = _X(i, 0);
            }
            return true;
        }
    };

}
