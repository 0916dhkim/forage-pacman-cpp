#ifndef BLINKY_H
#define BLINKY_H

#include "clyde.h"
#include "ghost.h"
#include "inky.h"
#include "pinky.h"

class Pinky;
class Clyde;
class Inky;

class Blinky : public Ghost {
private:
  std::weak_ptr<Pinky> pinky;
  std::weak_ptr<Clyde> clyde;
  std::weak_ptr<Inky> inky;

public:
  Blinky(const std::shared_ptr<QGraphicsScene> &sc,
         std::vector<std::vector<int>> &map, const std::shared_ptr<PacMan> &pc);
  void ft_set_default();
  void ft_calculate_point();
  void ft_find_pacman();
  void ft_set_friends(const std::shared_ptr<Pinky> &pin,
                      const std::shared_ptr<Clyde> &cl,
                      std::shared_ptr<Inky> &ink);
  void ft_find_path();
public slots:
  void ft_move_ghost();
};

#endif // BLINKY_H
