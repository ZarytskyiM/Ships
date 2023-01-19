

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;

const int FIELD_SIZE = 10;

const vector<int> SHIPS = {2, 3, 3, 4, 5};

const char EMPTY_CELL = '.';
const char SHIP_CELL = '#';

enum Direction {
    HORIZONTAL,
    VERTICAL
};

struct Ship {
    int size;
    int x;
    int y;
    Direction direction;
};

struct Field {
    char cells[FIELD_SIZE][FIELD_SIZE];
};

Field generateField() {
    Field field;
    
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            field.cells[i][j] = EMPTY_CELL;
        }
    }

    vector<Ship> ships;
    for (int size : SHIPS) {
        Ship ship;
        ship.size = size;

        ship.x = rand() % FIELD_SIZE;
        ship.y = rand() % FIELD_SIZE;
        ship.direction = (Direction)(rand() % 2);

        bool fits = true;
        if (ship.direction == HORIZONTAL) {
            if (ship.x + ship.size > FIELD_SIZE) {
                fits = false;
            }
        } else {
            if (ship.y + ship.size > FIELD_SIZE) {
                fits = false;
            }
        }
        
        if (fits) {
            ships.push_back(ship);
            for (int i = 0; i < ship.size; i++) {
                if (ship.direction == HORIZONTAL) {
                    field.cells[ship.y][ship.x + i] = SHIP_CELL;
                } else {
                    field.cells[ship.y + i][ship.x] = SHIP_CELL;
                }
            }
        }
    }

    return field;
}


void printField(Field field) {
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            cout << field.cells[i][j] << " ";
        }
        cout << endl;
    }
}


bool checkField(Field field) {
    // Check if all ships are present
    vector<int> shipCount(SHIPS.size(), 0);
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            if (field.cells[i][j] == SHIP_CELL) {
                int size = 0;
                while (j + size < FIELD_SIZE && field.cells[i][j + size] == SHIP_CELL) {
                    size++;
                }
                if (find(SHIPS.begin(), SHIPS.end(), size) == SHIPS.end()) {
                    return false;
                }
                shipCount[size - 2]++;
            }
        }
    }
    for (int i = 0; i < SHIPS.size(); i++) {
        if (shipCount[i] != SHIPS[i]) {
            return false;
        }
    }
    
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            if (field.cells[i][j] == SHIP_CELL) {
                if (i > 0 && field.cells[i - 1][j] == SHIP_CELL) {
                    return false;
                }
                if (j > 0 && field.cells[i][j - 1] == SHIP_CELL) {
                    return false;
                }
            }
        }
    }

    return true;
}


void playGame(Field field) {
  
}

int main() {
    Field field = generateField();
    
    printField(field);
   
    if (checkField(field)) {
        cout << "Playing field is valid!" << endl;

        playGame(field);
    } else {
        cout << "Playing field is invalid!" << endl;
    }

    return 0;
}
