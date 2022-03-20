#include "gameclass.h"

int GameLoop::ft_check_file_inp(std::string str) {
  int i;

  i = 0;
  while (str[i]) {
    if (str[i] < '0' || str[i] > '4')
      return (1);
    i++;
  }
  return (0);
}

void GameLoop::ft_roll_game() {
  timer_pacman = std::unique_ptr<QTimer>(new QTimer());
  timer_ghost.start(400);
  QObject::connect(timer_pacman.get(), SIGNAL(timeout()), pacman.get(),
                   SLOT(ft_move()));
  timer_pacman->start(300);
}

void GameLoop::ft_create_map() {
  for (int i = 0; i < size_x; i++) {
    for (int j = 0; j < size_y; j++) {
      if (map_int[i][j] == 1) {
        map_pix[i][j]->setPixmap(QPixmap(":/pics/greystone.png"));
        map_pix[i][j]->setPos(j * 32, i * 32);
        scene->addItem(map_pix[i][j].get());
      }
      if (map_int[i][j] == 3) {
        map_pix[i][j]->setPixmap(QPixmap(":/pics/ball.png"));
        map_pix[i][j]->setPos(j * 32, i * 32);
        scene->addItem(map_pix[i][j].get());
      }
      if (map_int[i][j] == 4) {
        map_pix[i][j]->setPixmap(QPixmap(":/pics/energizer.png"));
        map_pix[i][j]->setPos(j * 32, i * 32);
        scene->addItem(map_pix[i][j].get());
      }
    }
  }
}

void GameLoop::ft_write_line_map(std::vector<int> &map, std::string str) {
  for (int i = 0; i < size_y; i++)
    map[i] = str[i] - '0';
}
GameLoop::GameLoop(char *file_name) {
  std::ifstream input;
  std::string temp;
  int nb;

  map_int = std::vector<std::vector<int>>(size_x, std::vector<int>(size_y));
  map_pix =
      std::vector<std::vector<std::unique_ptr<QGraphicsPixmapItem>>>(size_x);
  for (auto &each : map_pix) {
    for (int i = 0; i < size_y; i++) {
      each.push_back(
          std::unique_ptr<QGraphicsPixmapItem>(new QGraphicsPixmapItem()));
    }
  }

  input.open(file_name);
  if (input.is_open()) {
    nb = 0;
    while (std::getline(input, temp)) {
      if (temp.length() != size_y) {
        std::cout << "File error.\n";
        exit(0);
      }
      if (ft_check_file_inp(temp)) {
        std::cout << "File error.\n";
        exit(0);
      }
      ft_write_line_map(map_int[nb], temp);
      nb++;
    }
    if (nb != size_x) {
      std::cout << "File error.\n";
      exit(0);
    }
    input.close();
  } else {
    std::cout << "File missing: " << file_name << ".\n";
    exit(0);
  }
  scene = std::unique_ptr<QGraphicsScene>(new QGraphicsScene());
  view = std::unique_ptr<QGraphicsView>(new QGraphicsView());
  this->setScene(scene.get());
  ft_create_map();
  this->setStyleSheet("background-color:black;");
  pacman = std::unique_ptr<PacMan>(new PacMan(map_int, map_pix, scene));
  pacman->setFlag(QGraphicsPixmapItem::ItemIsFocusable);
  pacman->setFocus();

  ghosts.push_back(std::make_unique<Ghost>(8, 9, scene, map_int, pacman));
  ghosts.push_back(std::make_unique<Ghost>(9, 10, scene, map_int, pacman));
  for (auto &ghost : ghosts) {
    QObject::connect(&timer_ghost, &QTimer::timeout, ghost.get(),
                     &Ghost::ft_move_ghost);
    QObject::connect(ghost.get(), &Ghost::on_intersect, this,
                     &GameLoop::handle_intersect);
  }
}

void GameLoop::remove_ghost(Ghost *ghost) {
  //  std::lock_guard l(ghost_mutex);
  for (auto it = ghosts.begin(); it != ghosts.end(); ++it) {
    if (it->get() == ghost) {
      ghosts.erase(it);
      return;
    }
  }
}

void GameLoop::handle_intersect(Ghost *ghost) {
  // Remove ghost in next event loop.
  QTimer::singleShot(0, this, [this, ghost] { this->remove_ghost(ghost); });
}
