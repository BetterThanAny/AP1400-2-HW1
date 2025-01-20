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
    if (matrix.empty()) // 空矩阵
      throw std::logic_error("empty matrix");
    if (!matrix.empty() && matrix[0].empty())
      throw std::logic_error("illegal matrix");

    size_t rols = matrix.size();    // 行数
    size_t cols = matrix[0].size(); // 列数

    Matrix result(matrix.size());
    for (std::size_t i = 0; i < rols; ++i)
    {
      result[i].resize(cols);
      for (std::size_t j = 0; j < cols; ++j)
      {
        result[i][j] = matrix[i][j] * c; // 乘以常数 c
      }
    }
    return result;
  }

  Matrix multiply(const Matrix &matrix1, const Matrix &matrix2)
  {
    // 空 * 空？ 空 * 非空？
    if (matrix1.empty() && matrix2.empty())
    { // 两个矩阵都是空
      return matrix1;
    }
    else if (!matrix1.empty() && matrix1[0].empty())
    {
      throw std::logic_error("illegal matrix1");
    }
    else if (!matrix2.empty() && matrix2[0].empty())
    {
      throw std::logic_error("illegal matrix2");
    }
    else
    {
      size_t rows1 = matrix1.size();    // 矩阵1行数
      size_t cols1 = matrix1[0].size(); // 矩阵1列数
      size_t rows2 = matrix2.size();    // 矩阵2行数
      size_t cols2 = matrix2[0].size(); // 矩阵2列数

      if (cols1 != rows2)
      { // 矩阵1的列数 != 矩阵2的行数
        throw std::logic_error("matrix1 can not multiply matrix2");
      }
      else
      {
        // Strassen算法要求矩阵的行和列是2的幂次方，如果不是2的幂次方，则扩展矩阵
        size_t newSize = std::pow(2, std::ceil(std::log2(std::max(rows1, cols2))));
        Matrix A = zeros(newSize, newSize);
        Matrix B = zeros(newSize, newSize);

        // 填充矩阵A和B
        for (size_t i = 0; i < rows1; ++i)
        {
          for (size_t j = 0; j < cols1; ++j)
          {
            A[i][j] = matrix1[i][j];
          }
        }
        for (size_t i = 0; i < rows2; ++i)
        {
          for (size_t j = 0; j < cols2; ++j)
          {
            B[i][j] = matrix2[i][j];
          }
        }

        // 使用Strassen算法计算矩阵的乘积
        Matrix result = strassen(A, B);

        // 将结果矩阵裁剪成原来矩阵的大小
        Matrix finalResult(rows1, std::vector<double>(cols2));
        for (size_t i = 0; i < rows1; ++i)
        {
          for (size_t j = 0; j < cols2; ++j)
          {
            finalResult[i][j] = result[i][j];
          }
        }

        return finalResult;
      }
    }
  }
  Matrix sum(const Matrix &matrix, double c)
  {
    if (matrix.empty())
    { // 空矩阵
      return matrix;
    }
    else if (!matrix.empty() && matrix[0].empty())
    {
      throw std::logic_error("illegal matrix");
    }

    // 测试程序要求我空矩阵不能 logic_error
    //  throw std::logic_error("empty matrix");

    size_t rows = matrix.size();    // 行数
    size_t vols = matrix[0].size(); // 列数
    Matrix result(rows, std::vector<double>(vols));
    for (std::size_t i = 0; i < rows; ++i)
    {
      for (std::size_t j = 0; j < vols; ++j)
      {
        result[i][j] = matrix[i][j] + c;
      }
    }
    return result;
  }
  Matrix sum(const Matrix &matrix1, const Matrix &matrix2)
  {
    if (matrix1.empty() && matrix2.empty())
    {
      return matrix1;
    }
    else if ((!matrix1.empty() && matrix2.empty()) || (matrix1.empty() && !matrix2.empty()))
    {
      throw std::logic_error("illegal matrix");
    }

    if (!matrix1.empty() && matrix1[0].empty())
    {
      throw std::logic_error("illegal matrix1");
    }

    if (!matrix2.empty() && matrix2[0].empty())
    {
      throw std::logic_error("illegal matrix2");
    }

    size_t rows1 = matrix1.size();    // 矩阵1行数
    size_t vols1 = matrix1[0].size(); // 矩阵1列数
    size_t rows2 = matrix2.size();    // 矩阵2行数
    size_t vols2 = matrix2[0].size(); // 矩阵2列数

    if ((rows1 != rows2) || (vols1 != vols2))
    {
      throw std::logic_error("matrix1 can not add matrix2");
    }

    Matrix result(rows1, std::vector<double>(vols1));
    for (std::size_t i = 0; i < rows1; ++i)
    {
      for (std::size_t j = 0; j < vols1; ++j)
      {
        result[i][j] = matrix1[i][j] + matrix2[i][j];
      }
    }
    return result;
  }
  Matrix transpose(const Matrix &matrix)
  {
    if (matrix.empty())
    { // 空矩阵
      return matrix;
    }
    else if (!matrix.empty() && matrix[0].empty())
    {
      throw std::logic_error("illegal matrix");
    }
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
  Matrix minor(const Matrix &matrix, size_t n, size_t m)
  {
    if (matrix.empty())
    { // 空矩阵不能删除任何行列
      throw std::logic_error("empty matrix");
    }
    else if (!matrix.empty() && matrix[0].empty())
    {
      throw std::logic_error("illegal matrix");
    }
    else
    {
      size_t rows = matrix.size();    // 行数
      size_t cols = matrix[0].size(); // 列数
      if (n >= rows || m >= cols)     // 删除的行列超过范围
        throw std::out_of_range("out of range");

      // 创建一个新的矩阵来存储 minor
      Matrix result;

      // 遍历原矩阵中的每个元素
      for (size_t i = 0; i < rows; ++i)
      {
        // 如果当前行是第 n 行，跳过
        if (i == n)
          continue;

        std::vector<double> row; // 新行

        for (size_t j = 0; j < cols; ++j)
        {
          // 如果当前列是第 m 列，跳过
          if (j == m)
            continue;

          row.push_back(matrix[i][j]); // 将当前元素添加到新行
        }

        result.push_back(row); // 将新行添加到 result 中
      }

      return result;
    }
  }

  double determinant(const Matrix &matrix)
  {
    if (matrix.empty())
    { // 空矩阵行列式为1
      return 1;
    }
    else if (!matrix.empty() && matrix[0].empty())
    {
      // k 行 0 列
      throw std::logic_error("illegal matrix");
    }
    else
    {
      size_t n = matrix.size();    // 行数
      size_t m = matrix[0].size(); // 列数
      if (n != m)
      {
        throw std::logic_error("not a square matrix");
      }
      else if (n == 1)
      {
        return matrix[0][0];
      }
      else
      {
        double det = 0; // 初始化行列式值
        // 代数余子式求法：A[i][k] = (-1)^(i+k) * M[i][k]
        for (size_t j = 0; j < m; ++j)
        {
          // 递归计算行列式
          det += matrix[0][j] * (j % 2 == 0 ? 1 : -1) * determinant(minor(matrix, 0, j));
        }
        return det;
      }
    }
  }

  Matrix inverse(const Matrix &matrix)
  {
    if (matrix.empty())
    { // 测试文件要求返回空矩阵？为什么？
      return matrix;
      // throw std::logic_error("empty matrix has no inverse.");
    }
    else if (!matrix.empty() && matrix[0].empty())
    {
      throw std::logic_error("illegal matrix");
    }
    size_t rows = matrix.size();
    size_t vols = matrix[0].size();
    if (rows != vols)
    {
      throw std::logic_error("A non-square matrix cannot be inverted.");
    }
    double det_matrix = determinant(matrix);
    const double epsilon = 1e-9;
    if (abs(det_matrix) < epsilon) // 与一个误差值进行比较
    {
      throw std::logic_error("A matrix with a determinant of 0 cannot be inverted.");
    }

    Matrix C(rows, std::vector<double>(vols)); // 用来存储代数余子式
    for (std::size_t i = 0; i < rows; ++i)
    {
      for (std::size_t j = 0; j < vols; ++j)
      {
        C[i][j] = determinant(minor(matrix, i, j)) * ((i + j) % 2 == 0 ? 1 : -1);
      }
    }
    Matrix adj_matrix = transpose(C);
    return multiply(adj_matrix, pow(det_matrix, -1));
  }

  Matrix concatenate(const Matrix &matrix1, const Matrix &matrix2, int axis)
  {
    size_t rows1 = matrix1.size();
    size_t rows2 = matrix2.size();
    if (axis == 1)
    {
      if (rows1 != rows2)
      {
        throw std::logic_error("illegal matrix");
      }
      else if (rows1 == 0)
      {
        return Matrix(rows1, std::vector<double>(rows1));
      }
      else
      {
        size_t vols1 = matrix1[0].size();
        size_t vols2 = matrix2[0].size();
        Matrix result(rows1, std::vector<double>(vols1 + vols2));
        for (std::size_t i = 0; i < rows1; ++i)
        {
          for (std::size_t j = 0; j < vols1; ++j)
          {
            result[i][j] = matrix1[i][j];
          }
          for (std::size_t j = 0; j < vols2; ++j)
          {
            result[i][j + vols1] = matrix2[i][j];
          }
        }
        return result;
      }
    }
    else if (axis == 0)
    {
      if (rows1 == 0 && rows2 == 0)
      {
        return Matrix(0, std::vector<double>(0));
      }
      else if (rows1 != 0 && rows2 == 0)
      {
        return matrix1;
      }
      else if (rows1 == 0 && rows2 != 0)
      {
        return matrix2;
      }
      else
      {
        size_t vols1 = matrix1[0].size();
        size_t vols2 = matrix2[0].size();
        if (vols1 != vols2)
        {
          throw std::logic_error("illegal matrix");
        }
        Matrix result(rows1 + rows2, std::vector<double>(vols1));
        for (std::size_t i = 0; i < rows1; ++i)
        {
          for (std::size_t j = 0; j < vols1; ++j)
          {
            result[i][j] = matrix1[i][j];
            result[i + rows1][j] = matrix2[i][j];
          }
        }
        for (std::size_t i = 0; i < rows2; ++i)
        {
          for (std::size_t j = 0; j < vols1; ++j)
          {
            result[i + rows1][j] = matrix2[i][j];
          }
        }
        return result;
      }
    }
    else
    {
      throw std::logic_error("illegal axis");
    }
  }

  Matrix ero_swap(const Matrix &matrix, size_t r1, size_t r2)
  {
    size_t rows = matrix.size(); // 矩阵行数
    if (rows == 0)
    {
      // 空矩阵
      throw std::logic_error("empty can not swap");
    }
    size_t vols = matrix[0].size(); // 矩阵列数
    if (vols == 0)
    {
      throw std::logic_error("illegal matrix");
    }
    if (r1 >= rows || r2 >= rows)
    {
      // 超过行范围了
      throw std::logic_error("out of ranges");
    }
    if (r1 == r2)
    {
      return matrix; // 其实这步不用也行，下面的处理没问题
    }
    Matrix result(rows, std::vector<double>(vols));
    for (size_t i = 0; i < rows; ++i)
      for (size_t j = 0; j < vols; ++j)
      {
        if (i == r1)
        {
          result[i][j] = matrix[r2][j];
        }
        else if (i == r2)
        {
          result[i][j] = matrix[r1][j];
        }
        else
        {
          result[i][j] = matrix[i][j];
        }
      }
    return result;
  }

  Matrix ero_multiply(const Matrix &matrix, size_t r, double c)
  {
    size_t rows = matrix.size(); // 矩阵行数
    if (rows == 0)
    {
      // 空矩阵
      throw std::logic_error("empty can not swap");
    }
    size_t vols = matrix[0].size(); // 矩阵列数
    if (vols == 0)
    {
      throw std::logic_error("illegal matrix");
    }
    if (r >= rows)
    {
      // 超过行范围了
      throw std::logic_error("out of ranges");
    }
    Matrix result(rows, std::vector<double>(vols));
    for (size_t i = 0; i < rows; ++i)
      for (size_t j = 0; j < vols; ++j)
      {
        if (i == r)
        {
          result[i][j] = c * matrix[r][j];
        }
        else
        {
          result[i][j] = matrix[i][j];
        }
      }
    return result;
  }

  Matrix ero_sum(const Matrix &matrix, size_t r1, double c, size_t r2)
  {
    size_t rows = matrix.size(); // 矩阵行数
    if (rows == 0)
    {
      // 空矩阵
      throw std::logic_error("empty can not swap");
    }
    size_t vols = matrix[0].size(); // 矩阵列数
    if (vols == 0)
    {
      throw std::logic_error("illegal matrix");
    }
    if (r1 >= rows || r2 >= rows)
    {
      // 超过行范围了
      throw std::logic_error("out of ranges");
    }
    Matrix result(rows, std::vector<double>(vols));
    for (size_t i = 0; i < rows; ++i)
      for (size_t j = 0; j < vols; ++j)
      {
        if (i == r2)
        {
          result[i][j] = matrix[i][j] + c * matrix[r1][j];
        }
        else
        {
          result[i][j] = matrix[i][j];
        }
      }
    return result;
  }
/*
  Matrix upper_triangular(const Matrix &matrix)
  {
    
  }
*/


  Matrix sub(const Matrix &matrix1, const Matrix &matrix2)
  {
    if (matrix1.empty() && matrix2.empty())
    {
      return matrix1;
    }
    else if ((!matrix1.empty() && matrix2.empty()) || (matrix1.empty() && !matrix2.empty()))
    {
      throw std::logic_error("illegal matrix");
    }
    else if (!matrix1.empty() && matrix1[0].empty())
    {
      throw std::logic_error("illegal matrix1");
    }
    else if (!matrix2.empty() && matrix2[0].empty())
    {
      throw std::logic_error("illegal matrix2");
    }
    else
    {
      size_t rows1 = matrix1.size();    // 矩阵1行数
      size_t vols1 = matrix1[0].size(); // 矩阵1列数
      size_t rows2 = matrix2.size();    // 矩阵2行数
      size_t vols2 = matrix2[0].size(); // 矩阵2列数

      if ((rows1 != rows2) || (vols1 != vols2))
      {
        throw std::logic_error("matrix1 can not sub matrix2");
      }

      Matrix result(rows1, std::vector<double>(vols1));
      for (std::size_t i = 0; i < rows1; ++i)
      {
        for (std::size_t j = 0; j < vols1; ++j)
        {
          result[i][j] = matrix1[i][j] - matrix2[i][j];
        }
      }
      return result;
    }
  }

  Matrix strassen(const Matrix &matrix1, const Matrix &matrix2)
  {
    if (matrix1.empty() || matrix2.empty())
    {
      throw std::logic_error("Matrix is empty");
    }
    else if (matrix1[0].empty() || matrix2[0].empty())
    {
      throw std::logic_error("Matrix is empty");
    }
    size_t rows1 = matrix1.size();
    size_t cols1 = matrix1[0].size();
    if (rows1 != cols1 || rows1 != matrix2.size() || matrix2[0].size() != cols1)
    {
      throw std::logic_error("Matrix dimensions do not match for multiplication.");
    }

    // 基本情况：当矩阵大小为1时，直接相乘
    if (rows1 == 1)
    {
      Matrix result(1, std::vector<double>(1, matrix1[0][0] * matrix2[0][0]));
      return result;
    }

    // 分割矩阵为子矩阵
    size_t mid = rows1 / 2;
    Matrix A11(mid, std::vector<double>(mid));
    Matrix A12(mid, std::vector<double>(mid));
    Matrix A21(mid, std::vector<double>(mid));
    Matrix A22(mid, std::vector<double>(mid));

    Matrix B11(mid, std::vector<double>(mid));
    Matrix B12(mid, std::vector<double>(mid));
    Matrix B21(mid, std::vector<double>(mid));
    Matrix B22(mid, std::vector<double>(mid));

    for (size_t i = 0; i < mid; ++i)
    {
      for (size_t j = 0; j < mid; ++j)
      {
        A11[i][j] = matrix1[i][j];
        A12[i][j] = matrix1[i][j + mid];
        A21[i][j] = matrix1[i + mid][j];
        A22[i][j] = matrix1[i + mid][j + mid];

        B11[i][j] = matrix2[i][j];
        B12[i][j] = matrix2[i][j + mid];
        B21[i][j] = matrix2[i + mid][j];
        B22[i][j] = matrix2[i + mid][j + mid];
      }
    }

    // 计算7个M矩阵
    Matrix M1 = strassen(sum(A11, A22), sum(B11, B22));
    Matrix M2 = strassen(sum(A21, A22), B11);
    Matrix M3 = strassen(A11, sub(B12, B22));
    Matrix M4 = strassen(A22, sub(B21, B11));
    Matrix M5 = strassen(sum(A11, A12), B22);
    Matrix M6 = strassen(sub(A21, A11), sum(B11, B12));
    Matrix M7 = strassen(sub(A12, A22), sum(B21, B22));

    // 计算最终的四个子矩阵
    Matrix C11 = sum(sub(sum(M1, M4), M5), M7);
    Matrix C12 = sum(M3, M5);
    Matrix C21 = sum(M2, M4);
    Matrix C22 = sum(sub(sum(M1, M3), M2), M6);

    // 合并子矩阵C11, C12, C21, C22
    Matrix C(rows1, std::vector<double>(rows1));
    for (size_t i = 0; i < mid; ++i)
    {
      for (size_t j = 0; j < mid; ++j)
      {
        C[i][j] = C11[i][j];
        C[i][j + mid] = C12[i][j];
        C[i + mid][j] = C21[i][j];
        C[i + mid][j + mid] = C22[i][j];
      }
    }
    return C;
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