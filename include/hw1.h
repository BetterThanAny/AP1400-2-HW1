#ifndef AP_HW1_H
#define AP_HW1_H

#include <vector>
#include <random>
#include <iomanip>
#include <iostream> // 只会 include 一次
#include <stdexcept>
#include <cmath>

using Matrix = std::vector<std::vector<double>>;

namespace algebra
{
  Matrix zeros(std::size_t n, std::size_t m); // 元素都为0的 n*m 矩阵
  Matrix ones(std::size_t n, std::size_t m);  // 元素都等于1的 n*m 矩阵
  // nxm矩阵，元素都是min和max之间的随机数
  Matrix random(std::size_t n, std::size_t m, double min, double max);
  // 矩阵乘标量
  Matrix multiply(const Matrix &matrix, double c);
  // strassen 算法实现矩阵乘法
  Matrix multiply(const Matrix &matrix1, const Matrix &matrix2);
  // 矩阵加常数
  Matrix sum(const Matrix &matrix, double c);
  // 矩阵加法
  Matrix sum(const Matrix &matrix1, const Matrix &matrix2);
  // 矩阵转置
  Matrix transpose(const Matrix &matrix);
  // 余子式
  Matrix minor(const Matrix &matrix, size_t n, size_t m);
  // 行列式 代数余子式求法：A[i][k] = (-1)^(i+k) * M[i][k]
  double determinant(const Matrix &matrix);
  // 矩阵的逆
  Matrix inverse(const Matrix &matrix);
  // 矩阵的连接
  Matrix concatenate(const Matrix &matrix1, const Matrix &matrix2, int axis = 0);
  /***********************************/
  // 矩阵减法
  Matrix sub(const Matrix &matrix1, const Matrix &matrix2);
  // strassen 算法
  Matrix strassen(const Matrix &A, const Matrix &B);
  void show(const Matrix &matrix);
}

#endif // AP_HW1_H
