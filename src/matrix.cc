/// @file matrix.cc
#include "matrix.h"

namespace s21 {

/// @brief assignment operator
bool operator==(const Point& left, const Point& right) {
  return left.col_ == right.col_ && left.row_ == right.row_;
}

/// @brief comparison operator
bool operator<(const Point& left, const Point& right) {
  if (left.row_ < right.row_) return true;
  return left.row_ == right.row_ && left.col_ < right.col_;
}

/// @brief random number generator
/// @param bias chance modifier
/// @return true/false
bool Random(int bias) { return (1 + (rand() % 100)) < bias; }

/// @brief default constructor
Matrix::Matrix() : rows_(1), cols_(1) { matrix_ = new bool[rows_ * cols_](); }

/// @brief parameterized constructor
Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::logic_error("wrong matrix size");
  }
  matrix_ = new bool[rows_ * cols_]();
}

/// @brief parameterized constructor that initialises a matrix with given values
Matrix::Matrix(int rows, int cols, std::initializer_list<bool> values)
    : rows_(rows), cols_(cols) {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::logic_error("wrong matrix size");
  }
  int index = 0;
  matrix_ = new bool[rows_ * cols_]();
  for (bool elem : values) {
    matrix_[index++] = elem;
    if (index >= rows_ * cols_) break;
  }
}

/// @brief copy constructor
Matrix::Matrix(const Matrix& other)
    : rows_(other.rows_),
      cols_(other.cols_),
      matrix_(new bool[rows_ * cols_]()) {
  std::copy(other.matrix_, other.matrix_ + rows_ * cols_, matrix_);
}

/// @brief move constructor
Matrix::Matrix(Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

/// @brief copy assignment operator
Matrix& Matrix::operator=(const Matrix& other) {
  if (this != &other) {
    Matrix copy(other);
    *this = std::move(copy);
  }
  return *this;
}

/// @brief move assignment operator
Matrix& Matrix::operator=(Matrix&& other) {
  if (this != &other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    delete[] matrix_;
    matrix_ = other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}

/// @brief destructor
Matrix::~Matrix() {
  if (matrix_) {
    delete[] matrix_;
  }
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

/// @brief accessor for number of rows of a matrix
/// @return number of rows
int Matrix::GetRows() const { return rows_; }

/// @brief accessor for number of columns of a matrix
/// @return number of columns
int Matrix::GetCols() const { return cols_; }

/// @brief mutator for number of rows
/// @param rows  new value
void Matrix::SetRows(int rows) {
  if (rows <= 0) {
    throw std::logic_error("Wrong row value");
  }
  bool* tmp = new bool[rows * cols_]();
  int amountOfRows = rows > rows_ ? rows_ : rows;
  std::copy(matrix_, matrix_ + (amountOfRows * cols_), tmp);
  delete[] matrix_;
  rows_ = rows;
  matrix_ = tmp;
}

/// @brief mutator for number of columns of a matrix
/// @param cols  new value
void Matrix::SetCols(int cols) {
  if (cols <= 0) {
    throw std::logic_error("wrong col value");
  }
  bool* tmp = new bool[rows_ * cols]();
  for (int i = 0, leveler = 0; i < rows_ * cols; i++) {
    if (cols > cols_ && i % cols >= cols_) {
      leveler--;
      tmp[i] = 0;
    } else {
      tmp[i] = matrix_[i + leveler];
      if (cols < cols_ && i % cols == cols - 1) {
        leveler += cols_ - cols;
      }
    }
  }
  delete[] matrix_;
  cols_ = cols;
  matrix_ = tmp;
}

/// @brief mutator for number of columns of a matrix
/// @param other matrix that the this argument is compared to
bool Matrix::EqMatrix(const Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if ((*this)(i, j) != other(i, j)) {
        return false;
      }
    }
  }
  return true;
}

/// @brief operator overloaded with equality function
bool Matrix::operator==(const Matrix& other) const { return EqMatrix(other); }

/// @brief operator overloaded works as accessor and mutator
bool& Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || col < 0 || row < 0) {
    throw std::logic_error("Wrong index");
  }
  return matrix_[row * cols_ + col];
}

/// @brief operator overloaded for const matrix
bool Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_ || col < 0 || row < 0) {
    throw std::logic_error("Wrong index");
  }
  return matrix_[row * cols_ + col];
}

/// @brief operator overloaded used with Point structure
bool& Matrix::operator()(Point dot) {
  if (dot.row_ >= rows_ || dot.col_ >= cols_ || dot.col_ < 0 || dot.row_ < 0) {
    throw std::logic_error("Wrong point index");
  }
  return matrix_[dot.row_ * cols_ + dot.col_];
}

/// @brief operator overloaded used with const Point structure
bool Matrix::operator()(Point dot) const {
  if (dot.row_ >= rows_ || dot.col_ >= cols_ || dot.col_ < 0 || dot.row_ < 0) {
    throw std::logic_error("Wrong point index");
  }
  return matrix_[dot.row_ * cols_ + dot.col_];
}

/// @brief helper function that prints matrix to a console
void Matrix::PrintMatrix() const {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      std::cout << (*this)(i, j) << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
}  // namespace s21
