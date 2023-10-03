#ifndef MAZE_SRC_MAINWINDOW_H
#define MAZE_SRC_MAINWINDOW_H

#include <QDebug>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QImage>
#include <QMainWindow>
#include <QMouseEvent>
#include <QSettings>
#include <chrono>
#include <thread>
#include <utility>
#include <vector>

#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(s21::Controller *controller, QWidget *parent = nullptr);
  ~MainWindow();
  QImage maze_image;
  QImage cave_image;
 signals:
  void redraw(std::vector<std::pair<int, int>>);

 private slots:
  //  For maze:
  void on_button_open_maze_clicked();
  void on_button_generate_clicked();
  void on_button_save_clicked();

  // m For cave:

  void on_button_open_cave_clicked();
  void on_button_generate_cave_clicked();
  void on_radioButton_step_by_step_clicked();
  void on_button_step_clicked();
  void on_radioButton_automatic_mode_clicked();
  void new_redraw(std::vector<std::pair<int, int>>);
  void on_spinBox_birth_limit_editingFinished();
  void on_spinBox_death_limit_editingFinished();

 private:
  void GameScene(QObject *parent);
  void mousePressEvent(QMouseEvent *event);
  QGraphicsScene *maze_scene_;
  QGraphicsScene *cave_scene_;
  s21::Controller *controller_;
  Ui::MainWindow *ui;
  std::vector<std::pair<int, int>> purple_pixels_;
  std::vector<std::pair<int, int>> green_pixels_;
  std::vector<std::pair<int, int>> cave_;
  std::pair<QPoint, QPoint> path_;
  void RunCycle();
  void AutoCave(std::vector<std::pair<int, int>> past_cave);
  void Sleep();
  void Draw(std::vector<std::pair<int, int>>, QRgb, bool cave);
};
#endif  // MAZE_SRC_MAINWINDOW_H_
