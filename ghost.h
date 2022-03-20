#ifndef GHOST_H
#define GHOST_H

#include "pacman.h"
#include <QTimer>
#include <random>

class Ghost : public QObject, public QGraphicsPixmapItem {
  Q_OBJECT
protected:
  int i_pos;
  int j_pos;
  int i_x;
  int i_y;
  int i_exit;
  int j_exit;
  int direction;
  int map_path[size_x][size_y];
  int x_dir[4] = {1, -1, 0, 0};
  int y_dir[4] = {0, 0, 1, -1};
  std::shared_ptr<PacMan> pacman;
  std::shared_ptr<QGraphicsScene> scene;
  std::mt19937 generator;

public:
  void ft_set_direction();
  void ft_find_pacman();
  int ft_check_intersect();
  int ft_get_i_pos();
  int ft_get_j_pos();
  int ft_check_move(int i_pos, int j_pos);
  void ft_set_default();
  void ft_calculate_point();
  int random_direction();
  Ghost(int i_pos, int j_pos, const std::shared_ptr<QGraphicsScene> &scene,
        std::vector<std::vector<int>> &map,
        const std::shared_ptr<PacMan> &pacman);
  virtual ~Ghost();
public slots:
  void ft_move_ghost();

signals:
  void on_intersect(Ghost *target);
};

#endif // GHOST_H
