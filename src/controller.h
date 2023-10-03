#ifndef MAZE_SRC_CONTROLLER_H_
#define MAZE_SRC_CONTROLLER_H_

#include <QMouseEvent>
#include <QString>
#include <string>
#include <utility>
#include <vector>

#include "cave.h"
#include "maze.h"
#include "model.h"

namespace s21 {

class Controller {
 public:
  Controller(Model* model);

  void OpenMaze(QString filename,
                std::vector<std::pair<int, int>>& purple_pixels_);

  void GenerateMaze(int rows, int cols,
                    std::vector<std::pair<int, int>>& purple_pixels_);

  void Solve(std::pair<QPoint, QPoint> path,
             std::vector<std::pair<int, int>>& green_pixels);

  void SaveMaze(QString path);

  void OpenCave(QString filename, std::vector<std::pair<int, int>>& cave,
                int born_limit, int death_limit);

  void NextGen(std::vector<std::pair<int, int>>& cave_);
  void BirthLimitChanged(int new_value);
  void DeathLimitChanged(int new_value);
  void GenerateCave(int birth_chance, std::vector<std::pair<int, int>>& cave);

 private:
  Model* model_;

};  //  class Controller
}  // namespace s21

#endif  //  MAZE_SRC_CONTROLLER_H_
