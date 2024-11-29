#include <QApplication>

#include "snakemainwindow.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  app.setApplicationName("Snake");
  app.setOrganizationName("Emil-Iapparov");
  app.setApplicationVersion("1.0");

  // Отключение восстановления состояния
  app.setAttribute(Qt::AA_DisableSessionManager);
  s21::snakeModel model;
  s21::snakeController controller(&model);
  SnakeMainWindow mainWindow(&controller);
  mainWindow.show();
  return app.exec();
}
