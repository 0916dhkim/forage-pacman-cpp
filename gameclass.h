#ifndef GAMECLASS_H
#define GAMECLASS_H

#include "blinky.h"
#include "clyde.h"
#include "ghost.h"
#include "inky.h"
#include "pacman.h"
#include "pinky.h"
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
  std::shared_ptr<Blinky> blinky;
  std::shared_ptr<Pinky> pinky;
  std::shared_ptr<Clyde> clyde;
  std::shared_ptr<Inky> inky;
  std::vector<std::vector<int>> map_int;
  std::unique_ptr<QTimer> timer_pacman;
  std::unique_ptr<QTimer> timer_blinky;
  std::unique_ptr<QTimer> timer_pinky;
  std::unique_ptr<QTimer> timer_clyde;
  std::unique_ptr<QTimer> timer_inky;

public:
  GameLoop(char *file_name);
  void ft_write_line_map(std::vector<int> &map, std::string str);
  void ft_roll_game();
  void ft_create_map();
  int ft_check_file_inp(std::string str);
};

#endif // GAMECLASS_H
