/// @file parser.cc

#include "parser.h"

/// @brief constructor
s21::Parser::Parser() {}

/// @brief main function for parsing a maze
/// @param filename name of a file with information on a maze
/// @param maze matrix for storing information on walls
void s21::Parser::ParseMaze(std::string filename, Maze *maze) {
  std::fstream file;
  file.open(filename);
  if (!file.is_open()) throw std::ios_base::failure("Unable to read from file");
  std::string line;
  getline(file, line);
  int rows, cols;
  sscanf(line.c_str(), "%i %i", &rows, &cols);
  maze->SetRows(1);
  maze->SetCols(1);
  maze->GetFloor()(0, 0) = false;
  maze->GetWalls()(0, 0) = false;
  maze->SetRows(rows);
  maze->SetCols(cols);
  ParseMatrix(file, &maze->GetWalls());
  file.ignore();
  ParseMatrix(file, &maze->GetFloor());
}

/// @brief basic function for parsing a matrix
/// @param filename name of a file with information on a maze
/// @param maze matrix for storing information on walls
void s21::Parser::ParseMatrix(std::fstream &file, Matrix *matrix) {
  std::string line;
  for (int i = 0; i < matrix->GetRows(); i++) {
    getline(file, line);
    int j = 0;
    size_t limit = line.size();
    for (size_t k = 0; k < limit; ++k) {
      if (isdigit(line[k])) {
        if (line[k] == '0')
          (*matrix)(i, j) = false;
        else if (line[k] == '1')
          (*matrix)(i, j) = true;
        else
          throw std::logic_error("File has some wrong values");
        j++;
      }
    }
  }
}

/// @brief parser for cave files
/// @param row number of rows
/// @param col number of columns
/// @param life_chance chance for the starting initialization of the cell
/// @param born_limit limit for "birth" of a cell
/// @param death_limit limit for "death" of a cell
void s21::Parser::ParseCave(std::string filename, Cave *cave) {
  std::fstream file;
  file.open(filename, std::ios_base::in);
  if (!file.is_open()) throw std::ios_base::failure("Unable to open file");
  std::string line;
  getline(file, line);
  int rows, cols;

  sscanf(line.c_str(), "%i %i", &rows, &cols);
  cave->SetRows(rows);
  cave->SetCols(cols);
  ParseMatrix(file, &cave->GetCave());
}

/// @brief function for saving a generated perfect maze
/// @param path path to a file chosen by user
void s21::Parser::SaveMaze(std::string path, Maze *maze) {
  std::ofstream file(path);
  if (!file.is_open())
    throw std::ios_base::failure("Unable to write into file");
  int rows = maze->GetRows(), cols = maze->GetCols();
  file << rows << " " << cols << std::endl;
  maze->SetRows(rows);
  maze->SetCols(cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      file << maze->GetWalls()(i, j);
      if (j != cols - 1) file << " ";
    }
    file << "\n";
  }
  file << "\n";
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      file << maze->GetFloor()(i, j);
      if (j != cols - 1) file << " ";
    }
    file << "\n";
  }
  file.close();
}
