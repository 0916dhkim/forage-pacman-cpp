#include "ghost.h"
#include <QGraphicsPixmapItem>
#include <QObject>

Ghost::Ghost(int i_pos, int j_pos, const std::shared_ptr<QGraphicsScene> &sc,
             const std::shared_ptr<PacMan> &pc)
    : i_pos(i_pos), j_pos(j_pos), pacman(pc), scene(sc) {

  this->setPixmap(QPixmap(":/pics/blinky.png"));
  this->setPos(j_pos * 32, i_pos * 32);
  scene->addItem(this);

  generator = std::mt19937(std::random_device()());
}

Ghost::~Ghost() { scene->removeItem(this); }

void Ghost::ft_set_default() {
  i_exit = i_pos;
  j_exit = j_pos;
  i_pos = 9;
  j_pos = 9;
  direction = 0;
  this->setPos(j_pos * 32, i_pos * 32);
}

void Ghost::ft_calculate_point() {
  if (!pacman->ft_scared_state()) {
    i_exit = pacman->ft_get_pacman_i();
    j_exit = pacman->ft_get_pacman_j();
    this->setPixmap(QPixmap(":/pics/blinky.png"));
  } else {
    if (i_pos == 1 && j_pos == 1)
      pacman->ft_set_scared();
    else {
      this->setPixmap(QPixmap(":/pics/frightened.png"));
      i_exit = 1;
      j_exit = 1;
    }
  }
}

void Ghost::ft_set_direction() { direction = random_direction(); }

void Ghost::ft_find_pacman() {
  if (ft_check_intersect()) {
    return;
  }
  ft_set_direction();
}

void Ghost::ft_move_ghost(const std::vector<std::vector<int>> &navmap) {
  ft_calculate_point();
  ft_find_pacman();
  if (direction == 1) {
    if (ft_check_move(i_pos - 1, j_pos, navmap))
      i_pos--;
  }
  if (direction == 2) {
    if (ft_check_move(i_pos + 1, j_pos, navmap))
      i_pos++;
  }
  if (direction == 3) {
    if (ft_check_move(i_pos, j_pos - 1, navmap))
      j_pos--;
  }
  if (direction == 4) {
    if (ft_check_move(i_pos, j_pos + 1, navmap))
      j_pos++;
  }
  this->setPos(j_pos * 32, i_pos * 32);
  if (ft_check_intersect()) {
    return;
  }
}

int Ghost::ft_get_i_pos() { return (i_pos); }

int Ghost::ft_get_j_pos() { return (j_pos); }

int Ghost::ft_check_move(int i_pos, int j_pos,
                         const std::vector<std::vector<int>> &navmap) {
  if (navmap[i_pos][j_pos] == 0)
    return (0);
  return (1);
}

int Ghost::ft_check_intersect() {
  if (i_pos == pacman->ft_get_pacman_i() &&
      j_pos == pacman->ft_get_pacman_j()) {
    emit on_intersect(this);
    return (1);
  }
  return (0);
}

int Ghost::random_direction() {
  std::uniform_int_distribution distribute(1, 4);
  return distribute(generator);
}
