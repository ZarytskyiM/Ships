

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;

// Define the size of the playing field
const int FIELD_SIZE = 10;

// Define the available ships
const vector<int> SHIPS = {2, 3, 3, 4, 5};

// Define the symbols used to represent the playing field
const char EMPTY_CELL = '.';
const char SHIP_CELL = '#';

// Define the directions in which ships can be placed
enum Direction {
    HORIZONTAL,
    VERTICAL
};

// Define a structure to represent a ship
struct Ship {
    int size;
    int x;
    int y;
    Direction direction;
};

// Define a structure to represent the playing field
struct Field {
    char cells[FIELD_SIZE][FIELD_SIZE];
};

// Function to generate a random playing field
Field generateField() {
    Field field;

    // Initialize the playing field with empty cells
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            field.cells[i][j] = EMPTY_CELL;
        }
    }

    // Generate a random arrangement of ships
    vector<Ship> ships;
    for (int size : SHIPS) {
        Ship ship;
        ship.size = size;

        // Generate random coordinates and direction

        ship.x = rand() % FIELD_SIZE;
        ship.y = rand() % FIELD_SIZE;
        ship.direction = (Direction)(rand() % 2);

        // Check if the ship fits on the playing field
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

        // If the ship fits, add it to the playing field
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

// Function to print the playing field
void printField(Field field) {
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            cout << field.cells[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if the playing field is valid
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

    // Check if ships are not overlapping
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

// Function to play the game
void playGame(Field field) {
    // TODO: Implement the game logic
}

int main() {
    // Generate a random playing field
    Field field = generateField();

    // Print the playing field
    printField(field);

    // Check if the playing field is valid
    if (checkField(field)) {
        cout << "Playing field is valid!" << endl;

        // Play the game
        playGame(field);
    } else {
        cout << "Playing field is invalid!" << endl;
    }

    return 0;
}
