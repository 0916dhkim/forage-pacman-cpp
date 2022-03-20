#ifndef PACMAN_H
#define PACMAN_H

#define WIDTH 608
#define HEIGHT 702
#define size_x 21
#define size_y 19

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QObject>
#include <unistd.h>

class PacMan : public QObject, public QGraphicsPixmapItem {
  Q_OBJECT
private:
  int i_pos;
  int j_pos;
  int direction;
  std::vector<std::vector<int>> &map_int;
  std::vector<std::vector<std::unique_ptr<QGraphicsPixmapItem>>> &map_pix;
  std::shared_ptr<QGraphicsScene> scene;
  std::unique_ptr<QGraphicsTextItem> text;
  std::unique_ptr<QGraphicsTextItem> message;
  int lives;
  void ft_update_scene();
  int ft_check_move(int i_pos, int j_pos);
  int has_completed_level();
  int scared;
  int counter;
  int score;
  int points;

public:
  PacMan(
      std::vector<std::vector<int>> &map_int,
      std::vector<std::vector<std::unique_ptr<QGraphicsPixmapItem>>> &map_pix,
      const std::shared_ptr<QGraphicsScene> &scene);
  void keyPressEvent(QKeyEvent *event);
  int ft_get_pacman_i(void);
  void ft_set_defaut();
  int ft_get_score();
  int ft_scared_state();
  void ft_set_scared();
  int ft_get_direction();
  int ft_get_pacman_j(void);
  void ft_incr_score();
  void ft_print_score();
  void ft_set_lives();
  int ft_get_point();
  void ft_move(int ghost_count);
};

#endif // PACMAN_H
