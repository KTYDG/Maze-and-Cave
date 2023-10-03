/// @file model.cc

#include "painter.h"

/// @brief constructor
s21::Painter::Painter() {
  maze_cell_width_ = 498.0;
  maze_cell_height_ = 498.0;
  cave_cell_width_ = 500.0;
  cave_cell_height_ = 500.0;
}

///@brief Fills in vector that contains parameters of pixels that
/// represent walls of a maze
/// @param purple_pixels_ vector in question
void s21::Painter::DrawMaze(Maze* maze,
                            std::vector<std::pair<int, int>>& purple_pixels) {
  for (int i = 0; i < 500; i++) {
    purple_pixels.push_back(std::make_pair(1, i));
    purple_pixels.push_back(std::make_pair(0, i));
    purple_pixels.push_back(std::make_pair(i, 0));
    purple_pixels.push_back(std::make_pair(i, 1));
  }
  int cols = maze->GetCols();
  int rows = maze->GetRows();
  maze_cell_width_ = 498.0 / cols;
  maze_cell_height_ = 498.0 / rows;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (maze->GetWalls()(i, j) == 1) {
        for (int k = round(maze_cell_height_ * i);
             k < round(maze_cell_height_ * (i + 1)) + 2; ++k) {
          purple_pixels.push_back(
              std::make_pair(round(maze_cell_width_ * (j + 1)), k));
          purple_pixels.push_back(
              std::make_pair(round(maze_cell_width_ * (j + 1)) + 1, k));
        }
      }
      if (maze->GetFloor()(i, j) == 1) {
        for (int k = round(maze_cell_width_ * j);
             k < round(maze_cell_width_ * (j + 1)); ++k) {
          purple_pixels.push_back(
              std::make_pair(k, round(maze_cell_height_ * (i + 1))));
          purple_pixels.push_back(
              std::make_pair(k, round(maze_cell_height_ * (i + 1)) + 1));
        }
      }
    }
  }
}

/// @brief places a point chosen as a start or end of a path in a matrix
/// @param pixel coordinates of a point
s21::Point s21::Painter::FindCell(std::pair<int, int> pixel) {
  Point point;
  point.col_ = floor(pixel.first / (500 / (498 / maze_cell_width_)));
  point.row_ = floor(pixel.second / (500 / (498 / maze_cell_height_)));
  return point;
}

/// @brief changes solution as a list of cells of a matrix into coordinates of
/// pixels
/// @param solution list of cells that constitute a path trough
/// @param green_pixels vector that contains parameters of pixels that represent
/// a path
void s21::Painter::DrawSolution(
    std::list<Point> solution, std::vector<std::pair<int, int>>& green_pixels) {
  auto end = solution.end();
  green_pixels.push_back(std::make_pair(
      round(maze_cell_width_ * (solution.begin()->col_ + 0.5)),
      round(maze_cell_height_ * (solution.begin()->row_ + 0.5))));
  auto previous_dot = solution.begin();
  for (auto i = ++(solution.begin()); i != end; ++i) {
    DrawSegment(*previous_dot, *i, green_pixels);
    previous_dot++;
  }
}

/// @brief helper function for DrawSolution
/// @param start coordinates of the starting point
/// @param end coordinates of the ending point
/// @param green_pixels vector that contains parameters of pixels that represent
/// a path
void s21::Painter::DrawSegment(Point start, Point end,
                               std::vector<std::pair<int, int>>& green_pixels) {
  if (start.col_ > end.col_) std::swap(start, end);
  if (start.row_ > end.row_) std::swap(start, end);
  std::pair<int, int> start_coords =
      std::make_pair(round((start.col_ + 0.5) * maze_cell_width_),
                     round((start.row_ + 0.5) * maze_cell_height_));
  std::pair<int, int> end_coords =
      std::make_pair(round((end.col_ + 0.5) * maze_cell_width_) - 1,
                     round((end.row_ + 0.5) * maze_cell_height_) + 1);
  // horizontal lines
  while (start_coords.first <= end_coords.first) {
    green_pixels.push_back(
        std::make_pair(start_coords.first, start_coords.second));
    green_pixels.push_back(
        std::make_pair(start_coords.first, start_coords.second + 1));
    start_coords.first += 1;
  }
  // vertical lines
  while (start_coords.second <= end_coords.second) {
    green_pixels.push_back(
        std::make_pair(start_coords.first, start_coords.second));
    green_pixels.push_back(
        std::make_pair(start_coords.first + 1, start_coords.second));
    start_coords.second += 1;
  }
}

/// @brief handles functionality of drawing a cave
/// @param vector that contains parameters of pixels that
/// represent cells of cave
void s21::Painter::DrawCave(Cave* cave,
                            std::vector<std::pair<int, int>>& purple_pixels) {
  purple_pixels.clear();
  cave_cell_width_ = 500.0 / cave->GetCols();
  cave_cell_height_ = 500.0 / cave->GetRows();
  int rows = cave->GetRows();
  int cols = cave->GetCols();
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (cave->GetCave()(i, j) == false) {
        DrawCell(purple_pixels, std::make_pair(round(i * cave_cell_height_),
                                               round(j * cave_cell_width_)));
      }
    }
  }
}

/// @brief helper function for DrawCave
void s21::Painter::DrawCell(std::vector<std::pair<int, int>>& cave,
                            std::pair<int, int> starting_point) {
  for (int i = starting_point.first;
       (i < starting_point.first + cave_cell_height_) && (i < 500); i++) {
    for (int j = starting_point.second;
         j < round(starting_point.second + cave_cell_width_); j++) {
      cave.push_back(std::make_pair(j, i));
    }
  }
}
