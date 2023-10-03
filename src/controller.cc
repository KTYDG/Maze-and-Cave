/// @file controller.cc

#include "controller.h"

/// @brief constructor
/// @param model data member of the class controller
s21::Controller::Controller(Model* model) { model_ = model; }

/// @brief handles opening of a file that describes a maze, it's parsing and
/// subsequent drawing
/// @param filename name of a file that user has chosen
/// @param purple_pixels_ vector that contains parameters of pixels that
/// represent walls of a maze
void s21::Controller::OpenMaze(
    QString filename, std::vector<std::pair<int, int>>& purple_pixels_) {
  try {
    model_->OpenMaze(filename.toLocal8Bit().data(), purple_pixels_);
  } catch (std::invalid_argument& error) {
    throw std::invalid_argument("No file chosen");
  } catch (std::logic_error& error) {
    throw std::invalid_argument("Wrong file format");
  } catch (std::ios_base::failure& error) {
    throw std::invalid_argument(error.what());
  }
}

/// @brief handles functionality of generating a perfect maze and it's
/// subsequent drawing
/// @param rows number of rows that user choose
/// @param cols number of columns that user choose
/// @brief handles functionality of opening of a file that describes a cave,
/// it's parsing and subsequent drawing
void s21::Controller::GenerateMaze(
    int rows, int cols, std::vector<std::pair<int, int>>& purple_pixels_) {
  model_->GenerateMaze(rows, cols, purple_pixels_);
}

/// @brief handles functionality of finding a path through a maze
/// @param path starting and ending point of intended path
/// @param green_pixels vector that contains parameters of pixels that represent
/// a path
void s21::Controller::Solve(std::pair<QPoint, QPoint> path,
                            std::vector<std::pair<int, int>>& green_pixels) {
  try {
    model_->SolveMaze(std::make_pair(path.first.x(), path.first.y()),
                      std::make_pair(path.second.x(), path.second.y()),
                      green_pixels);
  } catch (std::invalid_argument& error) {
    throw std::invalid_argument("There is no way");
  } catch (std::logic_error& error) {
    throw std::invalid_argument("Something went wrong");
  }
}

/// @brief handles functionality of saving information on a maze to a file
/// @param path path to the file that will hold information on the maze
void s21::Controller::SaveMaze(QString path) {
  model_->SaveMaze(path.toLocal8Bit().data());
}

/// @brief handles functionality of opening of a file that describes a cave,
/// it's parsing and subsequent drawing
/// @param filename name of a file that user has chosen
/// @param cave vector that contains parameters of pixels that represent caves
/// @param born_limit limit for "birth" of a cell
/// @param death_limit limit for "death" of a cell
/// @param life_chance chance for the starting initialization of the cell
void s21::Controller::OpenCave(QString filename,
                               std::vector<std::pair<int, int>>& cave,
                               int born_limit, int death_limit) {
  try {
    model_->OpenCave(filename.toLocal8Bit().data(), cave, born_limit,
                     death_limit);
  } catch (std::invalid_argument& error) {
    throw std::invalid_argument("No file chosen");
  } catch (std::logic_error& error) {
    throw std::invalid_argument("Wrong file format");
  } catch (std::ios_base::failure& error) {
    throw std::invalid_argument(error.what());
  }
}

/// @brief handles functionality of rendering the next iteration of the
/// algorithm
/// @param cave_  matrix that has  information on status of cells
void s21::Controller::NextGen(std::vector<std::pair<int, int>>& cave_) {
  model_->NextStep(cave_);
}

/// @brief handles functionality of changing limit for "birth" of a cell
/// @param new_value birth limit
void s21::Controller::BirthLimitChanged(int new_value) {
  model_->ChangeBirthLimit(new_value);
}

/// @brief handles functionality of changing limit for "death" of a cell
/// @param new_value death limit
void s21::Controller::DeathLimitChanged(int new_value) {
  model_->ChangeDeathLimit(new_value);
}

/// @brief handles functionality of creating a cave with 625 cells and
/// initialises them according to chance of random initialisation provided by a
/// user
void s21::Controller::GenerateCave(int birth_chance,
                                   std::vector<std::pair<int, int>>& cave) {
  model_->GenerateRandom(birth_chance, cave);
}
