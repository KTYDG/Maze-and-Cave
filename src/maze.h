#ifndef MAZE_SRC_MAZE_H_
#define MAZE_SRC_MAZE_H_

#include <algorithm>
#include <fstream>
#include <list>
#include <stdexcept>
#include <vector>

#include "matrix.h"

namespace s21 {
class Maze {
 public:
  Maze();
  Maze(const Maze &other);
  Maze(Maze &&other) noexcept;
  Maze &operator=(const Maze &other);
  Maze &operator=(Maze &&other);
  ~Maze();

  void Generate(int rows, int cols);

  std::list<Point> Solve(Point start, Point end);

  int GetRows();
  int GetCols();
  void SetRows(int rows);
  void SetCols(int cols);
  Matrix &GetWalls();
  Matrix &GetFloor();
  void Print(std::list<Point> solution);
  void Print();

 private:
  int rows_, cols_;
  Matrix wall_, floor_;
  void CombineSet(int set, int new_set, std::vector<int> &bar);
  int FloorCheck(int row, int set, std::vector<int> bar);
  std::list<Point> MakePath(std::vector<std::pair<Point, Point>> paths,
                            Point end);
  bool Contains(std::list<Point> &dots, const Point &element);
};
}  // namespace s21

#endif  // MAZE_SRC_MAZE_H_
