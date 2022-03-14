#ifndef GAMECLASS_H
#define GAMECLASS_H

#include "ghost.h"
#include "pacman.h"
#include <QApplication>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QTimer>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>

class GameLoop : public QGraphicsView {
private:
  std::shared_ptr<QGraphicsScene> scene;
  std::unique_ptr<QGraphicsView> view;
  std::vector<std::vector<std::unique_ptr<QGraphicsPixmapItem>>> map_pix;
  std::shared_ptr<PacMan> pacman;
  std::vector<std::unique_ptr<Ghost>> ghosts;
  std::vector<std::vector<int>> map_int;
  std::unique_ptr<QTimer> timer_pacman;

public:
  GameLoop(char *file_name);
  void ft_write_line_map(std::vector<int> &map, std::string str);
  void ft_roll_game();
  void ft_create_map();
  int ft_check_file_inp(std::string str);
};

#endif // GAMECLASS_H
