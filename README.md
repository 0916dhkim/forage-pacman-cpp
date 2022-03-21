# Vax-Man

## System Requirements

- Tested with QT 5 on Linux.
- Qt Creator is required for development.

## How to Run

1. Open `pacman.pro` project file in Qt Creator.
1. Press F5 to compile & debug.

## Rules

The rules are similar to Pac-Man with several notable exceptions:

- Vax-Man can kill a ghost if he comes into contact with it (vaccinates it).
- Contact with a ghost does not kill Vax-Man.
- Each ghost that has not yet been hit multiplies itself every 30 seconds (the infection grows).
- The goal of the game is to collect all the dots before the number of ghosts grows to 32 times the original number.
