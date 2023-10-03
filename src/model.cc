/// @file model.cc

#include "model.h"

/// @brief constructor
s21::Model::Model() {
  maze_ = new Maze();
  cave_ = new Cave();
  parser_ = new Parser();
  painter_ = new Painter();
}

/// @brief destructor
s21::Model::~Model() {
  delete maze_;
  delete cave_;
  delete parser_;
  delete painter_;
}

/// @brief handles opening of a file that describes a maze, it's parsing and
/// subsequent drawing
/// @param name of a file that user has chosen
/// @param purple_pixels_ vector that contains parameters of pixels that
/// represent walls of a maze
void s21::Model::OpenMaze(std::string filename,
                          std::vector<std::pair<int, int>>& purple_pixels_) {
  if (filename.empty()) throw std::invalid_argument("Empty filename");
  parser_->ParseMaze(filename, maze_);
  painter_->DrawMaze(maze_, purple_pixels_);
}

/// @brief handles functionality of generating a perfect maze and it's
/// subsequent drawing
/// @param rows number of rows that user choose
/// @param cols number of columns that user choose
/// @param purple_pixels_ vector that contains parameters of pixels that
/// represent walls of a maze
void s21::Model::GenerateMaze(
    int rows, int cols, std::vector<std::pair<int, int>>& purple_pixels_) {
  maze_->Generate(rows, cols);
  painter_->DrawMaze(maze_, purple_pixels_);
}

/// @brief handles functionality of finding a path through a maze
/// @param path starting and ending point of intended path
/// @param green_pixels vector that contains parameters of pixels that represent
/// a path
void s21::Model::SolveMaze(std::pair<int, int> start_point,
                           std::pair<int, int> end_point,
                           std::vector<std::pair<int, int>>& green_pixels) {
  std::list<Point> solution = maze_->Solve(painter_->FindCell(start_point),
                                           painter_->FindCell(end_point));
  if (solution.size() == 0) throw std::invalid_argument("NO WAY");
  painter_->DrawSolution(solution, green_pixels);
}

/// @brief handles functionality of saving information on a maze to a file
/// @param path path to the file that will hold information on the maze
void s21::Model::SaveMaze(std::string path) { parser_->SaveMaze(path, maze_); }

/// @brief handles functionality of opening of a file that describes a cave,
/// it's parsing and subsequent drawing
/// @param filename name of a file that user has chosen
/// @param cave vector that contains parameters of pixels that represent caves
/// @param born_limit limit for "birth" of a cell
/// @param death_limit limit for "death" of a cell
/// @param life_chance chance for the starting initialization of the cell
void s21::Model::OpenCave(std::string filename,
                          std::vector<std::pair<int, int>>& purple_pixels_,
                          int born_limit, int death_limit) {
  if (filename.empty()) throw std::invalid_argument("Empty filename");
  parser_->ParseCave(filename, cave_);
  cave_->SetBornLimit(born_limit);
  cave_->SetDeathLimit(death_limit);

  painter_->DrawCave(cave_, purple_pixels_);
}

/// @brief functionality of rendering the next iteration of the algorithm
/// @param purple_pixels vector that contains parameters of pixels that
/// represent
///  cells of a cave
void s21::Model::NextStep(std::vector<std::pair<int, int>>& purple_pixels) {
  cave_->Next();
  painter_->DrawCave(cave_, purple_pixels);
}

/// @brief functionality of changing limit for "birth" of a cell
/// @param new_value birth limit
void s21::Model::ChangeBirthLimit(int new_value) {
  cave_->SetBornLimit(new_value);
}

/// @brief functionality of changing limit for "death" of a cell
/// @param new_value death limit
void s21::Model::ChangeDeathLimit(int new_value) {
  cave_->SetDeathLimit(new_value);
}

/// @brief handles functionality of creating a cave and initialises it's cells
/// according to chance of random initialisation provided by a user
void s21::Model::GenerateRandom(
    int life_chance, std::vector<std::pair<int, int>>& purple_pixels) {
  cave_->GenerateRandom(life_chance);
  painter_->DrawCave(cave_, purple_pixels);
}
