#ifndef PINKY_H
#define PINKY_H

#include "blinky.h"
#include "clyde.h"
#include "ghost.h"
#include "inky.h"

class Blinky;
class Clyde;
class Inky;

class Pinky : public Ghost {
private:
  std::weak_ptr<Blinky> blinky;
  std::weak_ptr<Clyde> clyde;
  std::weak_ptr<Inky> inky;
  Q_OBJECT
public:
  void ft_set_default();
  void ft_calculate_point();
  void ft_find_pacman();
  void ft_set_friends(const std::shared_ptr<Blinky> &bl,
                      const std::shared_ptr<Clyde> &cl,
                      const std::shared_ptr<Inky> &ink);
  void ft_find_path();
  Pinky(const std::shared_ptr<QGraphicsScene> &sc,
        std::vector<std::vector<int>> &map, const std::shared_ptr<PacMan> &pc);
public slots:
  void ft_move_ghost();
};

#endif // PINKY_H
