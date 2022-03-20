#ifndef GHOST_H
#define GHOST_H

#include "pacman.h"
#include <QTimer>
#include <random>
#include <vector>

class Ghost : public QObject, public QGraphicsPixmapItem {
  Q_OBJECT
private:
  int attempt_move(const std::vector<std::vector<int>> &navmap);
  void change_direction(const std::vector<std::vector<int>> &navmap);

protected:
  int i_pos;
  int j_pos;
  int i_exit;
  int j_exit;
  int direction;
  std::shared_ptr<PacMan> pacman;
  std::shared_ptr<QGraphicsScene> scene;
  std::mt19937 generator;

public:
  int ft_check_intersect();
  int ft_get_i_pos();
  int ft_get_j_pos();
  int ft_check_move(int i_pos, int j_pos,
                    const std::vector<std::vector<int>> &navmap);
  Ghost(int i_pos, int j_pos, const std::shared_ptr<QGraphicsScene> &scene,
        const std::shared_ptr<PacMan> &pacman);
  virtual ~Ghost();
  void ft_move_ghost(std::vector<std::vector<int>> &navmap);

signals:
  void on_intersect(Ghost *target);
};

#endif // GHOST_H
