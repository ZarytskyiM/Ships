#ifndef BATTLESHIP_H_INCLUDED
#define BATTLESHIP_H_INCLUDED

#include <vector>

class Battleship
{
public:
    Battleship();
    void startGame();

private:
    void generateField();
    void placeShips();
    void checkPlacement();
    void playGame();

    std::vector<std::vector<int>> field;
};

#endif // BATTLESHIP_H_INCLUDED
