#ifndef MAZE_SRC_CAVE_H_
#define MAZE_SRC_CAVE_H_

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>

#include "matrix.h"

namespace s21 {
class Cave {
 public:
  Cave();
  ~Cave();

  void Next();
  void GenerateRandom(int life_chance);

  void Print();
  int GetRows();
  int GetCols();
  void SetRows(int rows);
  void SetCols(int cols);
  void SetBornLimit(int born_limit);
  void SetDeathLimit(int death_limit);
  Matrix &GetCave();
  Matrix GetPastCave();

 private:
  bool operator()(int row, int col) const;
  int AliveAmount(int row, int col);
  int rows_, cols_;
  int born_limit_, death_limit_;
  Matrix cave_, past_cave_;
};
}  // namespace s21

#endif  // MAZE_SRC_CAVE_H_
