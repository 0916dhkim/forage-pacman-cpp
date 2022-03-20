#include "ghost.h"
#include <QGraphicsPixmapItem>
#include <QObject>
#include <algorithm>
#include <set>

Ghost::Ghost(int i_pos, int j_pos, const std::shared_ptr<QGraphicsScene> &sc,
             const std::shared_ptr<PacMan> &pc)
    : i_pos(i_pos), j_pos(j_pos), pacman(pc), scene(sc) {

  this->setPixmap(QPixmap(":/pics/blinky.png"));
  this->setPos(j_pos * 32, i_pos * 32);
  scene->addItem(this);

  generator = std::mt19937(std::random_device()());
}

Ghost::~Ghost() { scene->removeItem(this); }

int Ghost::attempt_move(const std::vector<std::vector<int>> &navmap) {
  if (direction == 1) {
    if (ft_check_move(i_pos - 1, j_pos, navmap)) {
      i_pos--;
      return 1;
    }
  }
  if (direction == 2) {
    if (ft_check_move(i_pos + 1, j_pos, navmap)) {
      i_pos++;
      return 1;
    }
  }
  if (direction == 3) {
    if (ft_check_move(i_pos, j_pos - 1, navmap)) {
      j_pos--;
      return 1;
    }
  }
  if (direction == 4) {
    if (ft_check_move(i_pos, j_pos + 1, navmap)) {
      j_pos++;
      return 1;
    }
  }

  return 0;
}

void Ghost::change_direction(const std::vector<std::vector<int>> &navmap) {

  auto pacman_i = pacman->ft_get_pacman_i();
  auto pacman_j = pacman->ft_get_pacman_j();
  std::set<int> options = {1, 2, 3, 4};
  if (pacman_i == i_pos) {
    if (pacman_j > j_pos) {
      options.erase(4);
    } else {
      options.erase(3);
    }
  } else if (pacman_j == j_pos) {
    if (pacman_i > i_pos) {
      options.erase(2);
    } else {
      options.erase(1);
    }
  }
  std::vector<int> v(options.begin(), options.end());
  std::shuffle(v.begin(), v.end(), generator);
  for (auto option : v) {
    direction = option;
    if (attempt_move(navmap)) {
      break;
    }
  }
}

void Ghost::ft_move_ghost(std::vector<std::vector<int>> &navmap) {
  if (ft_check_intersect()) {
    return;
  }
  auto pacman_i = pacman->ft_get_pacman_i();
  auto pacman_j = pacman->ft_get_pacman_j();
  if (pacman_i == i_pos || pacman_j == j_pos || !attempt_move(navmap)) {
    change_direction(navmap);
  }
  this->setPos(j_pos * 32, i_pos * 32);
  ft_check_intersect();
}

int Ghost::ft_get_i_pos() { return (i_pos); }

int Ghost::ft_get_j_pos() { return (j_pos); }

int Ghost::ft_check_move(int i_pos, int j_pos,
                         const std::vector<std::vector<int>> &navmap) {
  if (i_pos < 0 || i_pos >= size_x || j_pos < 0 || j_pos >= size_y) {
    return 0;
  }
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
