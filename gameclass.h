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
#include <random>
#include <string>
#include <vector>

class GameLoop : public QGraphicsView {
private:
  QGraphicsScene *scene;
  QGraphicsView *view;
  QGraphicsPixmapItem **map_pix;
  PacMan *pacman;
  Blinky *blinky;
  Pinky *pinky;
  Clyde *clyde;
  Inky *inky;
  int **map_int;
  QTimer *timer_pacman;
  QTimer *timer_blinky;
  QTimer *timer_pinky;
  QTimer *timer_clyde;
  QTimer *timer_inky;

public:
  GameLoop(char *file_name);
  ~GameLoop();
  void ft_write_line_map(int *map, std::string str);
  void ft_roll_game();
  void ft_create_map();
  int ft_check_file_inp(std::string str);
};

#endif // GAMECLASS_H
