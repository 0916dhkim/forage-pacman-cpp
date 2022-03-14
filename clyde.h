#ifndef CLYDE_H
#define CLYDE_H

#include "blinky.h"
#include "ghost.h"
#include "inky.h"
#include "pinky.h"

class Blinky;
class Pinky;
class Inky;

class Clyde : public Ghost {
private:
  std::weak_ptr<Blinky> blinky;
  std::weak_ptr<Pinky> pinky;
  std::weak_ptr<Inky> inky;
  Q_OBJECT
public:
  void ft_set_default();
  void ft_calculate_point();
  void ft_find_pacman();
  void ft_set_friends(const std::shared_ptr<Blinky> &bl,
                      const std::shared_ptr<Pinky> &pnc,
                      const std::shared_ptr<Inky> &ink);
  void ft_find_path();
  Clyde(const std::shared_ptr<QGraphicsScene> &sc,
        std::vector<std::vector<int>> &map, const std::shared_ptr<PacMan> &pc);
public slots:
  void ft_move_ghost();
};
#endif // CLYDE_H
