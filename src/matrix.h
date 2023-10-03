#ifndef MAZE_SRC_MATRIX_H_
#define MAZE_SRC_MATRIX_H_

#include <exception>
#include <initializer_list>
#include <iostream>

namespace s21 {

struct Point {
  int row_;
  int col_;
};

bool operator==(const Point &left, const Point &right);
bool operator<(const Point &left, const Point &right);

bool Random(int bias = 50);

class Matrix final {
 public:
  // methods
  Matrix();
  Matrix(int rows, int cols);
  Matrix(int rows, int cols, std::initializer_list<bool> values);
  Matrix(const Matrix &other);
  Matrix(Matrix &&other) noexcept;
  Matrix &operator=(const Matrix &other);
  Matrix &operator=(Matrix &&other);
  ~Matrix();

  // operations
  int GetRows() const;
  int GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);

  bool EqMatrix(const Matrix &other) const;

  // other
  void PrintMatrix() const;

  // operators
  bool operator==(const Matrix &other) const;
  bool &operator()(int row, int col);
  bool operator()(int row, int col) const;
  bool &operator()(Point dot);
  bool operator()(Point dot) const;

 private:
  int rows_, cols_;
  bool *matrix_;
};
}  // namespace s21

#endif  // MAZE_SRC_MATRIX_H_
