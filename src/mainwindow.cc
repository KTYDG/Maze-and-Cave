/// @file mainwindow.cc

#include "mainwindow.h"

#include "./ui_mainwindow.h"

/// \brief constructor
MainWindow::MainWindow(s21::Controller* controller, QWidget* parent)
    : controller_(controller), QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  maze_image = QImage(500, 500, QImage::Format_RGB32);
  cave_image = QImage(500, 500, QImage::Format_RGB32);
  maze_scene_ = new QGraphicsScene(this);
  cave_scene_ = new QGraphicsScene(this);
  path_ = std::make_pair(QPoint(-1, -1), QPoint(-1, -1));
  green_pixels_.clear();
  purple_pixels_.clear();
  connect(this, SIGNAL(redraw(std::vector<std::pair<int, int>>)), this,
          SLOT(new_redraw(std::vector<std::pair<int, int>>)));
  ui->label_error_cave->setText("");
  ui->label_error_maze->setText("");
}

/// \brief destructor
MainWindow::~MainWindow() {
  delete cave_scene_;
  delete maze_scene_;
  delete ui;
}

/// \brief MainWindow::on_button_open_maze_clicked
/// handles opening of a file with information on a maze
void MainWindow::on_button_open_maze_clicked() {
  QString pathToFile = QFileDialog::getOpenFileName(
      this, tr("Open model"), qApp->applicationDirPath() + "/../../");
  purple_pixels_.clear();
  try {
    controller_->OpenMaze(pathToFile, purple_pixels_);
    ui->label_error_maze->setText("");
    maze_image.fill(qRgb(0, 0, 0));
    Draw(purple_pixels_, qRgb(106, 90, 205), false);
  } catch (std::invalid_argument& error) {
    ui->label_error_maze->setText(error.what());
  }
}

/// \brief MainWindow::on_button_generate_clicked
/// handles functionality of generating a perfect maze
void MainWindow::on_button_generate_clicked() {
  ui->label_error_maze->setText("");
  purple_pixels_.clear();
  controller_->GenerateMaze(ui->spinBox_height->value(),
                            ui->spinBox_width->value(), purple_pixels_);
  maze_image.fill(qRgb(0, 0, 0));
  Draw(purple_pixels_, qRgb(106, 90, 205), false);
}

/// \brief MainWindow::on_button_save_clicked
///  function that ensures file describing a perfect maze is saved
void MainWindow::on_button_save_clicked() {
  try {
    QString fileName = QFileDialog::getSaveFileName(
        this, tr("Save File"), qApp->applicationDirPath() + "../../../../maze",
        tr("Images (*.txt)"));
    controller_->SaveMaze(fileName);
  } catch (std::__1::ios_base::failure& error) {
    ui->label_error_maze->setText(error.what());
  }
}

/// \brief MainWindow::Draw
/// can drow in widget and thus display walls of a maze or a path through it or
/// a cave
void MainWindow::Draw(std::vector<std::pair<int, int>> pixels, QRgb colour,
                      bool cave) {
  unsigned pixels_size = pixels.size();
  QImage m_image = cave == true ? cave_image : maze_image;
  for (unsigned i = 0; i < pixels_size; ++i) {
    m_image.setPixel(pixels[i].first, pixels[i].second, colour);
  }
  if (cave) {
    cave_scene_->clear();
    cave_scene_->addPixmap(QPixmap::fromImage(m_image));
    cave_image = m_image;
    ui->graphicsView_cave->setScene(cave_scene_);
  } else {
    maze_scene_->clear();
    maze_scene_->addPixmap(QPixmap::fromImage(m_image));
    maze_image = m_image;
    ui->graphicsView_maze->setScene(maze_scene_);
  }
}

/// \brief MainWindow::mousePressEvent
/// gets coordinates of clicks that mark starting and ending point of a path
/// through a maze
void MainWindow::mousePressEvent(QMouseEvent* event) {
  QPoint point =
      ui->graphicsView_maze->mapFrom(ui->centralwidget, event->pos());
  ui->label_error_maze->clear();
  if (ui->graphicsView_maze->rect().contains(point) &&
      ui->tabWidget->currentIndex() == 0) {
    if (path_.first == QPoint(-1, -1)) {
      path_.first = point;
    } else {
      path_.second = point;
      Draw(green_pixels_, qRgb(0, 0, 0), false);
      green_pixels_.clear();
      try {
        controller_->Solve(path_, green_pixels_);
      } catch (std::invalid_argument& error) {
        ui->label_error_maze->setText(error.what());
      }
      Draw(purple_pixels_, qRgb(106, 90, 205), false);
      Draw(green_pixels_, qRgb(0, 90, 20), false);
      path_.first = QPoint(-1, -1);
      path_.second = QPoint(-1, -1);
    }
  }
}

/// \brief MainWindow::on_button_open_cave_clicked
/// handles opening of a file with information on a cave
void MainWindow::on_button_open_cave_clicked() {
  QString pathToFile = QFileDialog::getOpenFileName(
      this, tr("Open model"), qApp->applicationDirPath() + "/../../");
  purple_pixels_.clear();
  cave_.clear();
  try {
    controller_->OpenCave(pathToFile, cave_, ui->spinBox_birth_limit->value(),
                          ui->spinBox_death_limit->value());
    cave_image.fill(qRgb(0, 0, 0));
    Draw(cave_, qRgb(106, 90, 205), true);
  } catch (std::invalid_argument& error) {
    ui->label_error_cave->setText(error.what());
  }
}

/// \brief MainWindow::on_button_generate_cave_clicked
///  handles functionality of generating a random cave with given parameters
void MainWindow::on_button_generate_cave_clicked() {
  ui->label_error_cave->setText("");
  cave_.clear();
  controller_->GenerateCave(ui->spinBox_chance->value(), cave_);
  cave_image.fill(qRgb(0, 0, 0));
  Draw(cave_, qRgb(106, 90, 205), true);
}

/// \brief MainWindow::on_radioButton_step_by_step_clicked
///  enables mode of generating a mase to step by step
void MainWindow::on_radioButton_step_by_step_clicked() {
  ui->spinBox_birth_limit->clearFocus();
  ui->spinBox_death_limit->clearFocus();
  ui->spinBox_chance->clearFocus();
  ui->button_step->setDisabled(false);
}

/// \brief MainWindow::on_button_step_clicked
/// ensures display of the next generation of a cave
void MainWindow::on_button_step_clicked() {
  ui->spinBox_birth_limit->clearFocus();
  ui->spinBox_death_limit->clearFocus();
  ui->spinBox_chance->clearFocus();
  if (ui->radioButton_step_by_step->isChecked()) {
    controller_->NextGen(cave_);
    cave_image.fill(qRgb(0, 0, 0));
    Draw(cave_, qRgb(106, 90, 205), true);
    cave_.clear();
  }
}

/// \brief MainWindow::on_radioButton_automatic_mode_clicked
///  starts off automatic mode of cave generation
void MainWindow::on_radioButton_automatic_mode_clicked() {
  ui->spinBox_birth_limit->clearFocus();
  ui->spinBox_death_limit->clearFocus();
  ui->spinBox_chance->clearFocus();
  ui->radioButton_automatic_mode->setChecked(true);
  ui->button_step->setDisabled(true);
  RunCycle();
}

/// \brief MainWindow::RunCycle
/// ensures creation of each new generation of a cave and it's display in widget
void MainWindow::RunCycle() {
  std::vector<std::pair<int, int>> past_cave = cave_;
  std::thread draw_cycles(&MainWindow::AutoCave, this, past_cave);
  draw_cycles.detach();
}

/// \brief MainWindow::
///  handles functionality of automatic mode of caves
void MainWindow::AutoCave(std::vector<std::pair<int, int>> past_cave) {
  int i = 0;
  bool changed = true;
  do {
    cave_ = past_cave;
    controller_->NextGen(past_cave);
    emit redraw(past_cave);
    std::this_thread::sleep_for(
        std::chrono::milliseconds(ui->spinBox_frequency->value()));
    if (cave_ == past_cave) changed = false;
    cave_.clear();
    past_cave.clear();
    if (!ui->radioButton_automatic_mode->isChecked()) break;
    i++;
  } while (changed);
}

/// \brief MainWindow::new_redraw
/// ensures display of each new generation of a cave in the automatic mode
void MainWindow::new_redraw(std::vector<std::pair<int, int>> v) {
  cave_image.fill(qRgb(0, 0, 0));
  Draw(v, qRgb(106, 90, 205), true);
}

/// \brief MainWindow::on_spinBox_death_limit_editingFinished
///   function in case user changes birth limit parameter
void MainWindow::on_spinBox_birth_limit_editingFinished() {
  controller_->BirthLimitChanged(ui->spinBox_birth_limit->value());
}

/// \brief MainWindow::on_spinBox_death_limit_editingFinished
///   function in case user changes death limit parameter
void MainWindow::on_spinBox_death_limit_editingFinished() {
  controller_->DeathLimitChanged(ui->spinBox_death_limit->value());
}
