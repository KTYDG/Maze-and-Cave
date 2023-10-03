#include <QApplication>

#include "controller.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model model_instance;
  s21::Controller controller_instance(&model_instance);
  MainWindow w(&controller_instance);
  w.show();
  return a.exec();
}
