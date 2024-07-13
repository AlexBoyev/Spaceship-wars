#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;

void showMenu();
void showInstructions();

int main() {
    bool running = true;

    while (running) {
        showMenu();

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int width, height, numEnemies;
            cout << "Enter board dimensions, recommended size is: 40x10 " << endl;
            cout << "Enter the width of the game board: ";
            cin >> width;
            cout << "Enter the height of the game board: ";
            cin >> height;
            cout << "Enter the number of enemies: ";
            cin >> numEnemies;

            // Initialize random seed
            srand(static_cast<unsigned>(time(0)));

            Game game(width, height, numEnemies);
            game.startGame();
            break;
        }
        case 2:
            showInstructions();
            break;
        case 3:
            cout << "Goodbye!" << endl;
            running = false;
            break;
        default:
            cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
            break;
        }
    }

    return 0;
}

void showMenu() {
    cout << "=== Spaceship wars ===" << endl;
    cout << "1) Start game" << endl;
    cout << "2) How to play?" << endl;
    cout << "3) Exit game" << endl;
}

void showInstructions() {
    cout << "=== How to play ===" << endl;
    cout << "1. Use 'W', 'A', 'S', 'D' keys to move the spaceship up, left, down, and right respectively." << endl;
    cout << "2. Press the 'space' key to shoot bullets." << endl;
    cout << "3. Press the 'G' key to perform a special attack if you have 3 power-ups." << endl;
    cout << "4. The goal is to eliminate all enemies. You win when all enemies are defeated." << endl;
    cout << "5. The game is over if you get hit 5 times by enemy bullets or if you run out of ammo." << endl;
    cout << "6. Enemies shoot randomly and move left or right. Avoid their bullets." << endl;
    cout << "7. Collect power-ups represented by '+'. Each power-up gives you a special attack after collecting three." << endl;
}
