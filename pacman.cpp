#include "pacman.h"
#include <iostream>

void PacMan::ft_update_scene() {
  static int flag;

  if (points == 50) {
    map_int[15][9] = 6;
    if (!flag) {
      map_pix[15][9]->setPixmap(QPixmap(":/pics/cherries.png"));
      scene->addItem(map_pix[15][9].get());
      flag = 1;
    }
  }
  if (map_int[i_pos][j_pos] == 6) {
    score += 200;
    map_int[i_pos][j_pos] = 0;
    scene->removeItem(map_pix[15][9].get());
    flag = 0;
  }
  if (map_int[i_pos][j_pos] == 3) {
    map_int[i_pos][j_pos] = 0;
    score += 10;
    points++;
    scene->removeItem(map_pix[i_pos][j_pos].get());
  }
  if (map_int[i_pos][j_pos] == 4) {
    map_int[i_pos][j_pos] = 0;
    scene->removeItem(map_pix[i_pos][j_pos].get());
  }
}

int PacMan::ft_get_score() { return (score); }

void PacMan::ft_print_score() {
  text->setDefaultTextColor(0x00ffffff);
  text->setFont(QFont("times", 15));
  text->setPlainText("SCORE: " + QString::number(score) +
                     "\t\tLIVES: " + QString::number(lives));
  text->setPos(10, HEIGHT - 30);
}

void PacMan::ft_incr_score() { score += 100; }

void PacMan::ft_set_lives() { lives--; }

PacMan::PacMan(
    std::vector<std::vector<int>> &map_int,
    std::vector<std::vector<std::unique_ptr<QGraphicsPixmapItem>>> &map_pix,
    const std::shared_ptr<QGraphicsScene> &scene)
    : i_pos(15), j_pos(9), direction(0), map_int(map_int), map_pix(map_pix),
      scene(scene), text(new QGraphicsTextItem()),
      message(new QGraphicsTextItem()), lives(3), counter(0), score(0),
      points(0) {
  this->setPixmap(QPixmap(":/pics/pacman_left.png"));
  this->setPos(j_pos * 32, i_pos * 32);
  scene->addItem(this);
  scene->addItem(text.get());
  ft_print_score();
}

int PacMan::ft_get_direction() { return (direction); }

void PacMan::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Left) {
    this->direction = 3;
    this->setPixmap(QPixmap(":/pics/pacman_left.png"));
  }
  if (event->key() == Qt::Key_Right) {
    this->direction = 4;
    this->setPixmap(QPixmap(":/pics/pacman_right.png"));
  }
  if (event->key() == Qt::Key_Down) {
    this->direction = 2;
    this->setPixmap(QPixmap(":/pics/pacman_down.png"));
  }
  if (event->key() == Qt::Key_Up) {
    this->direction = 1;
    this->setPixmap(QPixmap(":/pics/pacman_up.png"));
  }
}

int PacMan::ft_get_point() { return (points); }

void PacMan::ft_move(int ghost_count) {
  static int flag;

  ft_print_score();
  if (has_completed_level() && !flag) {
    message->setDefaultTextColor(0x00ff00ff);
    message->setFont(QFont("times", 40));
    message->setPlainText("YOU WIN");
    message->setPos(60, HEIGHT / 2 - 30);
    scene->addItem(message.get());
    scene->removeItem(this);
    scene->removeItem(text.get());
    flag = 1;
  }
  if (ghost_count >= 64 && !flag) {
    message->setDefaultTextColor(0x00ff00ff);
    message->setFont(QFont("times", 60));
    message->setPlainText("YOU LOST");
    message->setPos(80, HEIGHT / 2);
    scene->addItem(message.get());
    scene->removeItem(this);
    scene->removeItem(text.get());
    flag = 1;
  }
  ft_update_scene();
  if (direction == 1) {
    if (i_pos == 0) {
      if (ft_check_move(size_x - 1, j_pos))
        i_pos = size_x - 1;
    } else if (ft_check_move(i_pos - 1, j_pos))
      i_pos--;
  }
  if (direction == 2) {
    if (i_pos == size_x - 1) {
      if (ft_check_move(0, j_pos))
        i_pos = 0;
    } else if (ft_check_move(i_pos + 1, j_pos))
      i_pos++;
  }
  if (direction == 3) {
    if (j_pos == 0) {
      if (ft_check_move(i_pos, size_y - 1))
        j_pos = size_y - 1;
    } else if (ft_check_move(i_pos, j_pos - 1))
      j_pos--;
  }
  if (direction == 4) {
    if (j_pos == size_y - 1) {
      if (ft_check_move(i_pos, 0))
        j_pos = 0;
    } else if (ft_check_move(i_pos, j_pos + 1))
      j_pos++;
  }
  this->setPos(j_pos * 32, i_pos * 32);
}

int PacMan::ft_get_pacman_i(void) { return (i_pos); }

int PacMan::ft_get_pacman_j(void) { return (j_pos); }

int PacMan::ft_check_move(int i_pos, int j_pos) {
  if (map_int[i_pos][j_pos] == 1)
    return (0);
  return (1);
}

int PacMan::has_completed_level() {
  for (int i = 0; i < size_x; i++) {
    for (int j = 0; j < size_y; j++) {
      int value = map_int[i][j];
      switch (value) {
      case 3:
      case 4:
      case 6:
        return 0;
      default:
        break;
      }
    }
  }
  return 1;
}
