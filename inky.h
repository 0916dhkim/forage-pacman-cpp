#ifndef INKY_H
#define INKY_H

#include "blinky.h"
#include "clyde.h"
#include "ghost.h"
#include "pinky.h"

class Blinky;
class Pinky;
class Clyde;

class Inky : public Ghost {
private:
  std::weak_ptr<Blinky> blinky;
  std::weak_ptr<Clyde> clyde;
  std::weak_ptr<Pinky> pinky;
  Q_OBJECT
public:
  void ft_set_default();
  void ft_calculate_point();
  void ft_find_pacman();
  void ft_set_friends(const std::shared_ptr<Blinky> &bl,
                      const std::shared_ptr<Pinky> &pnc,
                      const std::shared_ptr<Clyde> &cld);
  void ft_find_path();
  Inky(const std::shared_ptr<QGraphicsScene> &sc,
       std::vector<std::vector<int>> &map, const std::shared_ptr<PacMan> &pc);
public slots:
  void ft_move_ghost();
};

#endif // INKY_H
