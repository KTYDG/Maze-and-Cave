/// @file cave.cc
#include "cave.h"

namespace s21 {

/// @brief Default constructor
Cave::Cave() : rows_(0), cols_(0), born_limit_(3), death_limit_(3) {}

/// @brief Destructor
Cave::~Cave() {}

/// @brief creates the next iteration of the algorithm
void Cave::Next() {
  for (int row = 0; row < rows_; row++) {
    for (int col = 0; col < cols_; col++) {
      if (cave_(row, col) && AliveAmount(row, col) < death_limit_)
        past_cave_(row, col) = false;
      else if (!cave_(row, col) && AliveAmount(row, col) > born_limit_)
        past_cave_(row, col) = true;
      else
        past_cave_(row, col) = cave_(row, col);
    }
  }
  cave_ = past_cave_;
}

/// @brief creates a cave with 625 cells and initialises them according to
/// chance of random initialisation provided by a user
/// @param life_chance the said chance
void Cave::GenerateRandom(int life_chance) {
  cave_.SetCols(25);
  cave_.SetRows(25);
  past_cave_.SetCols(25);
  past_cave_.SetRows(25);
  cols_ = 25;
  rows_ = 25;
  for (int i = 0; i < 625; ++i) {
    cave_(i / 25, i % 25) = (rand() % 100 > life_chance - 1);
    //      cave_(i / 25, i % 25) = (1 + (rand() % 100)) < life_chance;
  }
}

/// @brief Prints cave to a console
void Cave::Print() {
  for (int row = -1; row <= rows_; row++) {
    for (int col = -1; col <= cols_; col++) {
      if (row == -1 && col == -1)
        std::cout << "╔";
      else if (row == -1 && col == cols_)
        std::cout << "╗";
      else if (row == rows_ && col == -1)
        std::cout << "╚";
      else if (row == rows_ && col == cols_)
        std::cout << "╝";
      else if (row == -1 || row == rows_)
        std::cout << "══";
      else if (col == -1 || col == cols_)
        std::cout << "║";
      else if (cave_(row, col))
        std::cout << "  ";
      else
        std::cout << "██";
    }
    std::cout << std::endl;
  }
}

/// @brief Accessor for a cave
/// @param row row of a matrix that describes a cave
/// @param col column of a matrix that describes a cave
/// @return true if an element is out of the field
bool Cave::operator()(int row, int col) const {
  try {
    return cave_(row, col);
  } catch (std::logic_error &e) {
    return true;
  }
}

/// @brief Counts number of neighbours
/// @param row of a matrix where the cell is
/// @param col of a matrix  where the cell is
/// @return number of neighbours
int Cave::AliveAmount(int row, int col) {
  int count = 0;
  for (int item : {(*this)(row, col - 1), (*this)(row, col + 1),
                   (*this)(row - 1, col), (*this)(row + 1, col),
                   (*this)(row - 1, col - 1), (*this)(row - 1, col + 1),
                   (*this)(row + 1, col - 1), (*this)(row + 1, col + 1)})
    if (item) count++;
  return count;
}

/// @brief mutator for number of rows of a matrix that describes a cave
/// @param rows  new value
void Cave::SetRows(int rows) {
  if (rows < 0) throw std::out_of_range("Negative dimension");
  cave_.SetRows(rows);
  past_cave_.SetRows(rows);
  rows_ = rows;
}

/// @brief mutator for number of columns of a matrix that describes a cave
/// @param cols  new value
void Cave::SetCols(int cols) {
  if (cols < 0) throw std::out_of_range("Negative dimension");
  cave_.SetCols(cols);
  past_cave_.SetCols(cols);
  cols_ = cols;
}

/// @brief mutator for "birth limit"
/// @param born_limit  new value
void Cave::SetBornLimit(int born_limit) {
  if (born_limit < 0 || born_limit > 8)
    throw std::out_of_range("Wrong limit value");
  born_limit_ = born_limit;
}

/// @brief mutator for "death limit"
/// @param death_limit  new value
void Cave::SetDeathLimit(int death_limit) {
  if (death_limit < 0 || death_limit > 8)
    throw std::out_of_range("Wrong limit value");
  death_limit_ = death_limit;
}

/// @brief accessor for number of rows of a matrix that describes a cave
/// @return number of rows
int Cave::GetRows() { return rows_; }

/// @brief accessor for number of columns of a matrix that describes a cave
/// @return number of columns
int Cave::GetCols() { return cols_; }

/// @brief accessor for a matrix that describes a cave
/// @return the matrix
Matrix &Cave::GetCave() { return cave_; }

/// @brief accessor for a matrix that describes a previous state of a cave
/// @return the matrix
Matrix Cave::GetPastCave() { return past_cave_; }

}  // namespace s21
