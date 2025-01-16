#include "hw1.h"
namespace algebra
{
  Matrix zeros(std::size_t n, std::size_t m)
  {
    if (n == 0 || m == 0)
      throw std::logic_error("empty matrix");
    // 在 algebra 命名空间中不要忘了 size_t是 std 命名空间的
    return Matrix(n, std::vector<double>(m, 0.0));
  }

  Matrix ones(std::size_t n, std::size_t m)
  {
    if (n == 0 || m == 0)
      throw std::logic_error("empty matrix");
    return Matrix(n, std::vector<double>(m, 1.0));
  }
  Matrix random(std::size_t n, std::size_t m, double min, double max)
  {
    if (n == 0 || m == 0)
      throw std::logic_error("empty matrix");
    // std::logic_error 的头文件和用法
    if (min >= max)
      throw std::logic_error("min should less than max!");
    // 随机数引擎：基于随机设备生成种子
    std::random_device rd;
    std::mt19937 gen(rd());                         // 使用梅森旋转算法生成伪随机数
    std::uniform_real_distribution<> dis(min, max); // 创建均匀分布

    // 创建矩阵并填充随机数
    Matrix mat(n, std::vector<double>(m));
    for (std::size_t i = 0; i < n; ++i)
    {
      for (std::size_t j = 0; j < m; ++j)
      {
        mat[i][j] = dis(gen); // 为每个元素生成随机数
      }
    }
    return mat;
  }
  Matrix multiply(const Matrix &matrix, double c)
  {
    if (matrix.empty() || matrix[0].empty())
      throw std::logic_error("empty matrix");

    size_t n = matrix.size();    // 行数
    size_t m = matrix[0].size(); // 列数

    Matrix result(matrix.size());
    for (std::size_t i = 0; i < n; ++i)
    {
      result[i].resize(m);
      for (std::size_t j = 0; j < m; ++j)
      {
        result[i][j] = matrix[i][j] * c; // 乘以常数 c
      }
    }
    return result;
  }
  /*
  Matrix multiply(const Matrix &matrix1, const Matrix &matrix2)
  {
    // 空 * 空？ 空 * 非空？
    if (matrix1.empty() || matrix1[0].empty())
      return matrix1;
    size_t n1 = matrix1.size();    // 矩阵1行数
    size_t m1 = matrix1[0].size(); // 矩阵1列数
    size_t n2 = matrix2.size();    // 矩阵2行数
    size_t m2 = matrix2[0].size(); // 矩阵2列数
    if (n1 == 0 || m1 == 0 || n2 == 0 || m2 == 0)
      throw std::logic_error("empty matrix");
    if (m1 != n2)
      throw std::logic_error("matrix1 can not multiply matrix2");

    return matrix1;
  }
  */
  Matrix sum(const Matrix &matrix, double c)
  {
    if (matrix.empty() || matrix[0].empty())
      return matrix;
    // 测试程序要求我空矩阵不能 logic_error
    //  throw std::logic_error("empty matrix");

    size_t n = matrix.size();    // 行数
    size_t m = matrix[0].size(); // 列数

    Matrix result(n);
    for (std::size_t i = 0; i < n; ++i)
    {
      result[i].resize(m);
      for (std::size_t j = 0; j < m; ++j)
      {
        result[i][j] = matrix[i][j] + c;
      }
    }
    return result;
  }
  Matrix sum(const Matrix &matrix1, const Matrix &matrix2)
  {
    if ((matrix1.empty() || matrix1[0].empty()) && (matrix2.empty() || matrix2[0].empty()))
      return matrix1;
    if (matrix1.empty() || matrix1[0].empty())
      throw std::logic_error("empty matrix1");
    if (matrix2.empty() || matrix2[0].empty())
      throw std::logic_error("empty matrix1");

    size_t n1 = matrix1.size();    // 矩阵1行数
    size_t m1 = matrix1[0].size(); // 矩阵1列数
    size_t n2 = matrix2.size();    // 矩阵2行数
    size_t m2 = matrix2[0].size(); // 矩阵2列数

    if ((n1 != n2) || (m1 != m2))
      throw std::logic_error("matrix1 can not add matrix2");

    Matrix result(n1);
    for (std::size_t i = 0; i < n1; ++i)
    {
      result[i].resize(m1);
      for (std::size_t j = 0; j < m1; ++j)
      {
        result[i][j] = matrix1[i][j] + matrix2[i][j];
      }
    }
    return result;
  }
  Matrix transpose(const Matrix &matrix)
  {
    if (matrix.empty() || matrix[0].empty())
      return matrix;
    // throw std::logic_error("empty matrix");
    size_t n = matrix.size();    // 行数
    size_t m = matrix[0].size(); // 列数

    // 创建一个新的矩阵，大小是 m x n
    Matrix transposed(m, std::vector<double>(n));

    // 将元素转置到新的矩阵中
    for (size_t i = 0; i < n; ++i)
    {
      for (size_t j = 0; j < m; ++j)
      {
        transposed[j][i] = matrix[i][j];
      }
    }

    return transposed;
  }
  void show(const Matrix &matrix)
  {
    // 设置输出格式：每个浮点数显示 3 位小数
    std::cout << std::fixed << std::setprecision(3);

    // 遍历矩阵并打印
    for (const auto &row : matrix)
    {
      for (const auto &val : row)
      {
        std::cout << val << " "; // 输出矩阵元素，保留3位小数
      }
      std::cout << std::endl; // 每行输出完后换行
    }
  }
}