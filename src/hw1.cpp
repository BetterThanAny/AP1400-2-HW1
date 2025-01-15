#include "hw1.h"
namespace algebra
{
  Matrix zeros(std::size_t n, std::size_t m)
  { // 在 algebra 命名空间中不要忘了 size_t是 std 命名空间的
    return Matrix(n, std::vector<double>(m, 0.0));
  }

  Matrix ones(std::size_t n, std::size_t m)
  {
    return Matrix(n, std::vector<double>(m, 1.0));
  }
  Matrix random(std::size_t n, std::size_t m, double min, double max)
  {
    //随机数引擎：基于随机设备生成种子
    std::random_device rd;
    std::mt19937 gen(rd());//使用梅森旋转算法生成伪随机数
    std::uniform_real_distribution<> dis(min, max); //创建均匀分布

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
  void show(const Matrix &matrix)
  {
    // 设置输出格式：每个浮点数显示 3 位小数
    std::cout << std::fixed << std::setprecision(3); 

    // 遍历矩阵并打印
    for (const auto& row : matrix) {
        for (const auto& val : row) {
            std::cout << val << " ";  // 输出矩阵元素，保留3位小数
        }
        std::cout << std::endl; // 每行输出完后换行
    }
  }
}