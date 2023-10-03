#ifndef MAZE_SRC_MODEL_H
#define MAZE_SRC_MODEL_H

#include "cave.h"
#include "maze.h"
#include "painter.h"
#include "parser.h"
namespace s21 {
class Model {
 public:
  Model();
  ~Model();
  void OpenMaze(std::string filename,
                std::vector<std::pair<int, int>> &purple_pixels);
  void SaveMaze(std::string path);
  void GenerateMaze(int rows, int cols,
                    std::vector<std::pair<int, int>> &purple_pixels);
  void SolveMaze(std::pair<int, int> start_point, std::pair<int, int> end_point,
                 std::vector<std::pair<int, int>> &green_pixels);

  void OpenCave(std::string filename,
                std::vector<std::pair<int, int>> &purple_pixels, int born_limit,
                int death_limit);
  void NextStep(std::vector<std::pair<int, int>> &purple_pixels);
  void ChangeBirthLimit(int new_value);
  void ChangeDeathLimit(int new_value);
  void GenerateRandom(int life_chance,
                      std::vector<std::pair<int, int>> &purple_pixels);

 private:
  Maze *maze_;
  Parser *parser_;
  Cave *cave_;
  Painter *painter_;
};
}  // namespace s21
#endif  // MAZE_SRC_MODEL_H
