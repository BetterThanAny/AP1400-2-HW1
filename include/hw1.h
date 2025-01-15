#ifndef AP_HW1_H
#define AP_HW1_H

#include <vector>
#include <random>
#include <iomanip>
#include <iostream> // 只会 include 一次

using Matrix = std::vector<std::vector<double>>;

namespace algebra
{
  Matrix zeros(std::size_t n, std::size_t m); // 元素都为0的 n*m 矩阵
  Matrix ones(std::size_t n, std::size_t m);  // 元素都等于1的 n*m 矩阵
  Matrix random(std::size_t n, std::size_t m, double min, double max);
  // nxm矩阵，元素都是min和max之间的随机数
  void show(const Matrix& matrix);
}

#endif // AP_HW1_H
