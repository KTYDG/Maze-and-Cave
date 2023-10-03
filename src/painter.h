#ifndef MAZE_SRC_PAINTER_H
#define MAZE_SRC_PAINTER_H

#include "cave.h"
#include "maze.h"

namespace s21 {

class Painter {
 public:
  Painter();
  void DrawMaze(Maze* maze, std::vector<std::pair<int, int>>& purple_pixels);
  Point FindCell(std::pair<int, int> pixel);
  void DrawSolution(std::list<Point> solution,
                    std::vector<std::pair<int, int>>& green_pixels);
  void DrawCave(Cave* cave, std::vector<std::pair<int, int>>& purple_pixels);

 private:
  void DrawCell(std::vector<std::pair<int, int>>& cave,
                std::pair<int, int> starting_point);
  void DrawSegment(Point start, Point end,
                   std::vector<std::pair<int, int>>& green_pixels);

  double maze_cell_width_;
  double maze_cell_height_;
  double cave_cell_width_;
  double cave_cell_height_;
};
}  // namespace s21
#endif  // MAZE_SRC_PAINTER_H
