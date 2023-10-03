#ifndef MAZE_SRC_PARSER_H
#define MAZE_SRC_PARSER_H

#include <string>

#include "cave.h"
#include "maze.h"

namespace s21 {

class Parser {
 public:
  Parser();

  void ParseMaze(std::string filename, Maze *maze);
  void ParseCave(std::string filename, Cave *cave);
  void ParseMatrix(std::fstream &file, Matrix *matrix);

  void SaveMaze(std::string path, Maze *maze);
};
}  // namespace s21

#endif  // MAZEPARSER_H
