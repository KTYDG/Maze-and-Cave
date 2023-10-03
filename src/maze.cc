#include "maze.h"

namespace s21 {

/// @brief constructor that creates a maze of a singular cell
Maze::Maze() : rows_(1), cols_(1), wall_(Matrix()), floor_(Matrix()) {}

/// @brief copy constructor
/// @param other a constructor to copy
Maze::Maze(const Maze& other)
    : rows_(other.rows_),
      cols_(other.cols_),
      wall_(other.wall_),
      floor_(other.floor_) {}

/// @brief move constructor
/// @param other maze to move
Maze::Maze(Maze&& other) noexcept
    : rows_(other.rows_),
      cols_(other.cols_),
      wall_(std::move(other.wall_)),
      floor_(std::move(other.floor_)) {
  other.rows_ = 0;
  other.cols_ = 0;
}

/// @brief copy assignment operator
/// @param other maze to copy
/// @return copied maze
Maze& Maze::operator=(const Maze& other) {
  if (this != &other) {
    Maze copy(other);
    *this = std::move(copy);
  }
  return *this;
}

/// @brief move assignment operator
/// @param other maze to move
/// @return moved maze
Maze& Maze::operator=(Maze&& other) {
  if (this != &other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    wall_ = std::move(other.wall_);
    floor_ = std::move(other.floor_);
    other.rows_ = 0;
    other.cols_ = 0;
  }
  return *this;
}

/// @brief destructor
Maze::~Maze() {}

/// @brief Function that generates a perfect maze
/// @param rows  number of rows that user choose
/// @param cols number of columns that user choose
void Maze::Generate(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  wall_ = Matrix(rows, cols);
  floor_ = Matrix(rows, cols);
  std::vector<int> bar(cols_);
  int plenty = 1;
  for (int row = 0; row < rows_; row++) {
    // base
    for (int col = 0; col < cols_; col++) {
      if (!bar[col] || floor_(row - 1, col)) bar[col] = plenty++;
    }
    for (int col = 0; col < cols_; col++) {
      // side walls
      if ((col == cols_ - 1 || Random() || bar[col] == bar[col + 1]) &&
          !(row == rows_ - 1 && col != cols_ - 1 && bar[col] != bar[col + 1])) {
        wall_(row, col) = true;
      } else {
        CombineSet(bar[col + 1], bar[col], bar);
      }
      // bottom walls
      if (row == rows_ - 1 ||
          (Random() && FloorCheck(row, bar[col], bar) > 1)) {
        floor_(row, col) = true;
      }
    }
  }
}

/// @brief function that solves a maze by breadth-first search
/// @param start starting point
/// @param end ending point
/// @return shortest way through
std::list<Point> Maze::Solve(Point start, Point end) {
  std::list<Point> open = {start};
  std::list<Point> closed;
  Point dot = open.front();
  std::vector<std::pair<Point, Point>> paths;
  while (!open.empty()) {
    dot = open.front();
    open.pop_front();
    if (dot == end) {
      return MakePath(paths, end);
    }
    closed.push_back(dot);
    int i = dot.row_;
    int j = dot.col_;
    if (j != cols_ - 1 && !wall_(i, j) &&
        !(Contains(open, {i, j + 1}) || Contains(closed, {i, j + 1}))) {
      open.push_back({i, j + 1});
      paths.push_back(std::make_pair(dot, Point{i, j + 1}));
    }
    if (i != rows_ - 1 && !floor_(i, j) &&
        !(Contains(open, {i + 1, j}) || Contains(closed, {i + 1, j}))) {
      open.push_back({i + 1, j});
      paths.push_back(std::make_pair(dot, Point{i + 1, j}));
    }
    if (j != 0 && !wall_(i, j - 1) &&
        !(Contains(open, {i, j - 1}) || Contains(closed, {i, j - 1}))) {
      open.push_back({i, j - 1});
      paths.push_back(std::make_pair(dot, Point{i, j - 1}));
    }
    if (i != 0 && !floor_(i - 1, j) &&
        !(Contains(open, {i - 1, j}) || Contains(closed, {i - 1, j}))) {
      open.push_back({i - 1, j});
      paths.push_back(std::make_pair(dot, Point{i - 1, j}));
    }
  }
  return {};
}

/// @brief Accessor for number of rows of a maze
/// @return number of rows
int Maze::GetRows() { return rows_; }

/// @brief Accessor for number of columns of a matrix that describes a maze
/// @return number of columns
int Maze::GetCols() { return cols_; }

/// @brief setter function for rows
void Maze::SetRows(int rows) {
  if (rows < 0) throw std::out_of_range("Negative dimension");
  floor_.SetRows(rows);
  wall_.SetRows(rows);
  rows_ = rows;
}

/// @brief setter function for columns
void Maze::SetCols(int cols) {
  if (cols < 0) throw std::out_of_range("Negative dimension");
  floor_.SetCols(cols);
  wall_.SetCols(cols);
  cols_ = cols;
}

/// @brief Accessor for a matrix that has information on side walls
/// @return the matrix
Matrix& Maze::GetWalls() { return wall_; }

/// @brief Accessor for a matrix that has information on bottom walls
/// @return the matrix
Matrix& Maze::GetFloor() { return floor_; }

/// @brief function for printing a solved maze to the console
void Maze::Print(std::list<Point> solution) {
  solution.sort();
  for (int row = -1; row < rows_; row++) {
    for (int col = -1; col < cols_; col++) {
      if (row == -1) {
        std::cout << " __";
        continue;
      }
      if (col == -1) {
        std::cout << "|";
        continue;
      }
      if (floor_(row, col))
        if (!solution.empty() && solution.front() == Point{row, col}) {
          std::cout << "߸߸";
          if (!solution.empty()) solution.pop_front();
        } else
          std::cout << "__";
      else if (!solution.empty() && solution.front() == Point{row, col}) {
        std::cout << "··";
        if (!solution.empty()) solution.pop_front();
      } else
        std::cout << "  ";
      if (wall_(row, col))
        std::cout << "|";
      else
        std::cout << " ";
    }
    std::cout << std::endl;
  }
}

/// @brief function for printing a maze to the console
void Maze::Print() {
  for (int row = -1; row < rows_; row++) {
    for (int col = -1; col < cols_; col++) {
      if (row == -1) {
        std::cout << " __";
        continue;
      }
      if (col == -1) {
        std::cout << "|";
        continue;
      }
      if (floor_(row, col))
        std::cout << "__";
      else
        std::cout << "  ";
      if (wall_(row, col))
        std::cout << "|";
      else
        std::cout << " ";
    }
    std::cout << std::endl;
  }
}

/// @brief function that combines two sets
/// @param set initial set
/// @param new_set new set
/// @param bar vector of integers
void Maze::CombineSet(int set, int new_set, std::vector<int>& bar) {
  for (int col = 0; col < cols_; col++) {
    if (bar[col] == set) bar[col] = new_set;
  }
}

/// @brief helper function for generating a perfect maze
/// @param row a row that we check
/// @param set identifier
/// @param bar  vector of integers
/// @return number of holes
int Maze::FloorCheck(int row, int set, std::vector<int> bar) {
  int amount_of_holes = 0;
  for (int col = 0; col < cols_; col++) {
    if (!floor_(row, col) && bar[col] == set) amount_of_holes++;
  }
  return amount_of_holes;
}

/// @brief turns list of pairs into a path trough a maze
/// @param paths list of pairs
/// @param end ending point of a path
/// @return path through
std::list<Point> Maze::MakePath(std::vector<std::pair<Point, Point>> paths,
                                Point end) {
  std::list<Point> path = {end};
  for (auto it = paths.rbegin(); it != paths.rend(); ++it) {
    if (path.front() == it->second) {
      path.push_front(it->first);
    }
  }
  return path;
}

/// @brief checks if there is a particular element in a list of Points
/// @param dots a list of Points
/// @param element a Point
/// @return true/false
bool Maze::Contains(std::list<Point>& dots, const Point& element) {
  auto it = std::find_if(dots.begin(), dots.end(),
                         [&](const Point& dot) { return dot == element; });
  return it != dots.end();
}

}  // namespace s21
